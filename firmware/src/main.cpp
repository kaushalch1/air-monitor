#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <Adafruit_SHT31.h>
#include <Adafruit_BMP280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <RTClib.h>
#include <NimBLEDevice.h>

#define PIN_SDA 8
#define PIN_SCL 9
#define SCK_SD 12
#define MISO_SD 13
#define MOSI_SD 11
#define CS_SD 10
#define SW_SEL 4
#define SW_BACK 5
#define BAT_PIN 1
#define RX_PM 17
#define TX_PM 18

#define TICK_MS 2000
#define UI_MS 500
#define WRITE_MS 10000
#define VOLT_GAIN 2.0
#define VREF 3.3

Adafruit_SHT31 thSensor = Adafruit_SHT31();
Adafruit_BMP280 prSensor;
Adafruit_SSD1306 screen(128, 64, &Wire, -1);
RTC_DS3231 clock;

HardwareSerial pmUart(1);
SPIClass sdBus(FSPI);

struct Snapshot {
  uint16_t fine = 0;
  uint16_t mid = 0;
  uint16_t coarse = 0;
  float deg = NAN;
  float rh = NAN;
  float hpa = NAN;
  float volts = NAN;
  bool gotPm = false;
  bool gotTh = false;
  bool gotPr = false;
  bool gotTime = false;
  bool gotCard = false;
};

Snapshot snap;
uint32_t tickStamp = 0;
uint32_t uiStamp = 0;
uint32_t writeStamp = 0;
uint32_t btnStamp = 0;
bool sdLogging = true;
bool altScreen = false;
String csvName;
NimBLECharacteristic* bleChar = nullptr;

String timeText() {
  if (!snap.gotTime) return String("NO_CLOCK");
  DateTime t = clock.now();
  char stamp[24];
  snprintf(stamp, sizeof(stamp), "%04d-%02d-%02d %02d:%02d:%02d",
           t.year(), t.month(), t.day(), t.hour(), t.minute(), t.second());
  return String(stamp);
}

String fileTag() {
  if (!snap.gotTime) return String("run");
  DateTime t = clock.now();
  char stamp[20];
  snprintf(stamp, sizeof(stamp), "%04d%02d%02d_%02d%02d%02d",
           t.year(), t.month(), t.day(), t.hour(), t.minute(), t.second());
  return String(stamp);
}

bool grabDust(uint16_t& a, uint16_t& b, uint16_t& c) {
  const uint8_t ask[] = {0xFE, 0xA5, 0x00, 0x01, 0xA6};
  while (pmUart.available()) pmUart.read();
  pmUart.write(ask, sizeof(ask));
  pmUart.flush();

  uint8_t buf[11];
  size_t have = 0;
  uint32_t began = millis();
  while (have < sizeof(buf) && millis() - began < 400) {
    if (pmUart.available()) {
      uint8_t byteIn = pmUart.read();
      if (have == 0 && byteIn != 0xFE) continue;
      if (have == 1 && byteIn != 0xA5) {
        have = 0;
        if (byteIn == 0xFE) buf[have++] = byteIn;
        continue;
      }
      buf[have++] = byteIn;
    }
    delay(1);
  }
  if (have != sizeof(buf)) return false;
  if (buf[0] != 0xFE || buf[1] != 0xA5) return false;

  uint8_t sum = 0;
  for (int i = 1; i <= 9; ++i) sum += buf[i];
  if (sum != buf[10]) return false;

  a = (uint16_t(buf[4]) << 8) | buf[5];
  b = (uint16_t(buf[6]) << 8) | buf[7];
  c = (uint16_t(buf[8]) << 8) | buf[9];
  return true;
}

void pollAll() {
  uint16_t x, y, z;
  snap.gotPm = grabDust(x, y, z);
  if (snap.gotPm) {
    snap.fine = x;
    snap.mid = y;
    snap.coarse = z;
  }

  float temp = thSensor.readTemperature();
  float humid = thSensor.readHumidity();
  snap.gotTh = !isnan(temp) && !isnan(humid);
  if (snap.gotTh) {
    snap.deg = temp;
    snap.rh = humid;
  }

  float baro = prSensor.readPressure() / 100.0;
  snap.gotPr = isfinite(baro) && baro > 100.0 && baro < 1200.0;
  if (snap.gotPr) snap.hpa = baro;

  uint32_t rawAdc = analogRead(BAT_PIN);
  float pinVolts = (float(rawAdc) / 4095.0) * VREF;
  snap.volts = pinVolts * VOLT_GAIN;
}

void makeFile() {
  if (!snap.gotCard || csvName.length()) return;
  csvName = "/DUST_" + fileTag() + ".csv";
  File h = SD.open(csvName.c_str(), FILE_WRITE);
  if (!h) {
    snap.gotCard = false;
    return;
  }
  h.println("time,pm1,pm25,pm10,tempC,humPct,hPa,volts");
  h.close();
}

void writeRow() {
  if (!sdLogging || !snap.gotCard) return;
  makeFile();
  if (!csvName.length()) return;

  File h = SD.open(csvName.c_str(), FILE_APPEND);
  if (!h) {
    snap.gotCard = false;
    return;
  }
  h.print(timeText()); h.print(',');
  if (snap.gotPm) { h.print(snap.fine); h.print(','); h.print(snap.mid); h.print(','); h.print(snap.coarse); }
  else h.print(",,");
  h.print(',');
  if (snap.gotTh) { h.print(snap.deg, 2); h.print(','); h.print(snap.rh, 2); }
  else h.print(',');
  h.print(',');
  if (snap.gotPr) h.print(snap.hpa, 2);
  h.print(',');
  if (isfinite(snap.volts)) h.print(snap.volts, 2);
  h.println();
  h.close();
}

void drawScreen() {
  screen.clearDisplay();
  screen.setTextColor(SSD1306_WHITE);
  screen.setTextSize(1);
  screen.setCursor(0, 0);
  screen.println("AirTrace");
  screen.drawLine(0, 10, 127, 10, SSD1306_WHITE);

  if (!altScreen) {
    screen.setCursor(0, 14);
    screen.print("PM1.0: "); snap.gotPm ? screen.print(snap.fine) : screen.print("--");
    screen.println(" ug/m3");
    screen.print("PM2.5: "); snap.gotPm ? screen.print(snap.mid) : screen.print("--");
    screen.println(" ug/m3");
    screen.print("PM10 : "); snap.gotPm ? screen.print(snap.coarse) : screen.print("--");
    screen.println(" ug/m3");
    screen.print("T:");
    snap.gotTh ? screen.print(snap.deg, 1) : screen.print("--");
    screen.print("C H:");
    snap.gotTh ? screen.print(snap.rh, 0) : screen.print("--");
    screen.println("%");
  } else {
    screen.setCursor(0, 14);
    screen.print("Press: ");
    snap.gotPr ? screen.print(snap.hpa, 1) : screen.print("--");
    screen.println(" hPa");
    screen.print("Vbat: ");
    isfinite(snap.volts) ? screen.print(snap.volts, 2) : screen.print("--");
    screen.println(" V");
    screen.print("SD: "); screen.println(snap.gotCard ? "OK" : "ERR");
    screen.print("Log: "); screen.println(sdLogging ? "ON" : "PAUSE");
    screen.print("RTC: "); screen.println(snap.gotTime ? "OK" : "CHECK");
  }
  screen.setCursor(0, 56);
  screen.print("SEL:view BACK:log");
  screen.display();
}

void pushBle() {
  if (!bleChar) return;
  String payload = "{";
  payload += "\"pm1\":" + (snap.gotPm ? String(snap.fine) : String("null")) + ",";
  payload += "\"pm25\":" + (snap.gotPm ? String(snap.mid) : String("null")) + ",";
  payload += "\"pm10\":" + (snap.gotPm ? String(snap.coarse) : String("null")) + ",";
  payload += "\"temp\":" + (snap.gotTh ? String(snap.deg, 2) : String("null")) + ",";
  payload += "\"rh\":" + (snap.gotTh ? String(snap.rh, 2) : String("null")) + ",";
  payload += "\"press\":" + (snap.gotPr ? String(snap.hpa, 2) : String("null")) + ",";
  payload += "\"volt\":" + (isfinite(snap.volts) ? String(snap.volts, 2) : String("null")) + ",";
  payload += "\"ts\":\"" + timeText() + "\"}";
  bleChar->setValue(payload.c_str());
  bleChar->notify();
}

void startBle() {
  NimBLEDevice::init("AirTrace");
  NimBLEServer* srv = NimBLEDevice::createServer();
  NimBLEService* svc = srv->createService("7f510001-1b15-4f0d-8e9b-1c2d3e4f5000");
  bleChar = svc->createCharacteristic(
    "7f510002-1b15-4f0d-8e9b-1c2d3e4f5000",
    NIMBLE_PROPERTY::READ | NIMBLE_PROPERTY::NOTIFY
  );
  bleChar->setValue("{\"status\":\"boot\"}");
  svc->start();
  NimBLEAdvertising* adv = NimBLEDevice::getAdvertising();
  adv->addServiceUUID(svc->getUUID());
  adv->start();
}

void scanKeys() {
  if (millis() - btnStamp < 35) return;
  btnStamp = millis();

  static bool selWas = HIGH;
  static bool backWas = HIGH;
  bool selIs = digitalRead(SW_SEL);
  bool backIs = digitalRead(SW_BACK);

  if (selWas == HIGH && selIs == LOW) {
    altScreen = !altScreen;
    drawScreen();
  }
  if (backWas == HIGH && backIs == LOW) {
    sdLogging = !sdLogging;
    drawScreen();
  }
  selWas = selIs;
  backWas = backIs;
}

void setup() {
  Serial.begin(115200);
  delay(300);

  pinMode(SW_SEL, INPUT_PULLUP);
  pinMode(SW_BACK, INPUT_PULLUP);
  analogReadResolution(12);
  analogSetPinAttenuation(BAT_PIN, ADC_11db);

  Wire.begin(PIN_SDA, PIN_SCL);
  bool oledUp = screen.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  if (!oledUp) Serial.println("WARN OLED 0x3C");

  snap.gotTh = thSensor.begin(0x44);
  if (!snap.gotTh) Serial.println("WARN SHT31 0x44");

  snap.gotPr = prSensor.begin(0x76);
  if (!snap.gotPr) snap.gotPr = prSensor.begin(0x77);
  if (!snap.gotPr) Serial.println("WARN BMP280 0x76/77");

  snap.gotTime = clock.begin();
  if (!snap.gotTime) {
    Serial.println("WARN RTC");
  } else if (clock.lostPower()) {
    Serial.println("WARN RTC lost power");
    snap.gotTime = false;
  }

  sdBus.begin(SCK_SD, MISO_SD, MOSI_SD, CS_SD);
  snap.gotCard = SD.begin(CS_SD, sdBus);
  if (!snap.gotCard) Serial.println("WARN SD");

  pmUart.begin(9600, SERIAL_8N1, RX_PM, TX_PM);
  startBle();

  Serial.println("AirTrace online");
  pollAll();
  drawScreen();
}

void loop() {
  uint32_t now = millis();

  scanKeys();

  if (now - tickStamp >= TICK_MS) {
    tickStamp = now;
    pollAll();
    pushBle();
    Serial.printf("ok=%d p1=%u p25=%u p10=%u T=%.2f H=%.2f P=%.2f V=%.2f\n",
      snap.gotPm, snap.fine, snap.mid, snap.coarse,
      snap.deg, snap.rh, snap.hpa, snap.volts);
  }

  if (now - uiStamp >= UI_MS) {
    uiStamp = now;
    drawScreen();
  }

  if (now - writeStamp >= WRITE_MS) {
    writeStamp = now;
    writeRow();
  }

  delay(2);
}
