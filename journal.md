# date:19/10
# time spent:1.25hr
## description:
i started put in some researching the architecture for this project.i carefully mapped out how to handle a portable and battery powered diving deep into component datasheetss to choose the bq24074 for smart power path management and defining proper usbc sink behavior, that thorough upfront research made translating the ir monitor and started drawing the schematic.i studied about many air monitor projects and figured out making one

## images:
<img width="532" height="455" alt="image" src="https://github.com/user-attachments/assets/0c26122c-7850-4208-96a8-1fe4cb8d9eb3" />
<img width="1380" height="890" alt="image" src="https://github.com/user-attachments/assets/7a332af8-7dbd-44ee-a754-2141c24cc20b" />


-------

# date:19/10
# time spent:2hr
## description:
i started the entire project from block 1 by placing the esp32-s3 controller and setting up its essential decoupling and reset passives. from there i got the usbc power input properly hooked up with its sink resistors and esd protection and dialed in the bq24074 battery charger circuit, and carefully walked through the dual voltage regulator stage getting both the 3.3v main rail and the mt3608 5v boost converter complete with its inductor and diode and feedback network totally squared away.

## images:
<img width="1227" height="800" alt="image" src="https://github.com/user-attachments/assets/e53af004-bc1d-448f-b69f-6579ccdaa9fe" />
<img width="552" height="651" alt="image" src="https://github.com/user-attachments/assets/9b7cdca9-8f87-450e-aff9-b468007b8dae" />
<img width="1132" height="828" alt="image" src="https://github.com/user-attachments/assets/10d93cdc-b63d-4d5e-bb0c-89e70e6e9d7e" />


-------
# date:20/10
# time spent:1.25hr
## description:
In the block 2,i integrated the SHT31 and bmp280 environmental sensors onto a shared i2c bus connected to the esp32-s3 gpioO8 and gpioO9 pins, grounding the sht31 address pin for 0x44, and locking the bmp280 into i2c mode with address 0x76. and then going to block 3,i searched for a particulate sensor i had found many modules but none of these had an symbol in kicad , i tried importing it through a plugin but it didn't work so i successfully set up an 8 pin connector for the pms5003 particulate matter sensor, powering it via the regulated 5V rail and grounding it properly, and cross connecting its uart lines to the microcontroller serial pins.

## images:
<img width="1382" height="540" alt="image" src="https://github.com/user-attachments/assets/8d8a2d4b-122f-49d5-832b-22872de00438" />
<img width="715" height="677" alt="image" src="https://github.com/user-attachments/assets/1b487646-d050-42b2-b97a-f0202eaa6a88" />
<img width="1215" height="747" alt="image" src="https://github.com/user-attachments/assets/bda8ceb0-3037-4e2d-8bc7-0e83ae3dae7c" />
<img width="1382" height="787" alt="image" src="https://github.com/user-attachments/assets/81413a26-d400-4af6-b9be-cdf2f9b68a1c" />

-------
# date:20/10
# time spent:1.25hr
## description:
after the particulate sensor integration,i moved straight into block 4 ,i placed and wired the connectors for the ssd1306 oled display, a spi based microsd card module for saving csv data, and a ds3231 real time clock complete with a cr2032 coin cell backup battery for persistent timestamps,i also integrated the user interface navigation buttons and designed a safe battery voltage monitoring circuitand by  using a a voltage divider and a stabilization capacitor connected to the esp32-s3 adc pin.now the schematic is done,i should check for erc and assign footprints.

## images:
<img width="958" height="447" alt="image" src="https://github.com/user-attachments/assets/41156f40-06f9-4c2e-b793-5a9006c92401" />
<img width="952" height="510" alt="image" src="https://github.com/user-attachments/assets/22665c97-ab55-421d-8f1b-ec68f9421349" />
<img width="1431" height="783" alt="image" src="https://github.com/user-attachments/assets/41c57862-493f-4a1e-a124-0d8971737fef" />


-------
# date:20/10
# time spent:0.5hr
## description:
I started fixing all the drc errors there were 50+ errors and i had go through each one and then i fixed all the errors by placing pwr_flag and then i should assign footprints.

## images:
<img width="1617" height="845" alt="image" src="https://github.com/user-attachments/assets/3e99a5e2-3a05-4319-bbd3-f77990d01411" />
<img width="1442" height="712" alt="image" src="https://github.com/user-attachments/assets/cb1fe550-cfd5-49f9-bedd-40e8f63c824e" />
<img width="1807" height="836" alt="image" src="https://github.com/user-attachments/assets/482a9972-f711-4ee1-ac2c-3a0efe4f055f" />


-------
# date:20/10
# time spent:0.5hr
## description:
i had searcched the internet and gathered footprints for all the parts and assigned them for each part and then added them in the pcb.

## images:
<img width="1662" height="886" alt="image" src="https://github.com/user-attachments/assets/a405edfb-4715-4529-bb34-cccf9a3281e6" />
<img width="707" height="665" alt="image" src="https://github.com/user-attachments/assets/6633c007-820a-4129-a81f-8958d5d2e5a4" />

-------
# date:21/10
# time spent:0.5hr
## description:
I had started doing the layout by arranging the antenas,usb,microsd card at the edges and now i should route each of them/

## images:
<img width="1917" height="810" alt="image" src="https://github.com/user-attachments/assets/1438861b-ea01-4d6c-9806-3a6aafed4483" />

-------
# date:21/10
# time spent:1.5hr
## description:
after arranging the layout i had started doing the routing , i had started routing the micro controllers and then connected the sd card in the nenxt i should connect all of them bby using the ground plate and fill it 
## images:
<img width="792" height="777" alt="image" src="https://github.com/user-attachments/assets/e1361c5b-bfed-43f4-bbd4-8bd0e2b4a476" />
<img width="1027" height="788" alt="image" src="https://github.com/user-attachments/assets/8e1d9831-84fc-4ef0-ae0a-b14f6fdbea64" />
<img width="1192" height="792" alt="image" src="https://github.com/user-attachments/assets/118083ae-9c2d-4052-a0ab-1c2ab4e1f711" />


-------
# date:21/10
# time spent:1.5hr
## description:
after arranging the layout i had started doing the routing , i had started routing the micro controllers and then connected the sd card in the nenxt i should connect all of them bby using the ground plate and fill it 
## images:
<img width="792" height="777" alt="image" src="https://github.com/user-attachments/assets/e1361c5b-bfed-43f4-bbd4-8bd0e2b4a476" />
<img width="1027" height="788" alt="image" src="https://github.com/user-attachments/assets/8e1d9831-84fc-4ef0-ae0a-b14f6fdbea64" />
<img width="1192" height="792" alt="image" src="https://github.com/user-attachments/assets/118083ae-9c2d-4052-a0ab-1c2ab4e1f711" />


-------
# date:21/10
# time spent:1.5hr
## description:
i had completed the routing part of the pcb and also fixed all the erc errors mainly the errors were regarding the unconnected items or the sd card footprint was wrong so i had updated it.
## images:
<img width="848" height="788" alt="image" src="https://github.com/user-attachments/assets/cd404779-bab1-4a77-8634-ab90af783ef3" />
<img width="1052" height="791" alt="image" src="https://github.com/user-attachments/assets/fb582f8a-6257-49b2-b90d-0c2871bc8019" />
<img width="1171" height="782" alt="image" src="https://github.com/user-attachments/assets/69621df0-0521-433f-860f-77ff373362c0" />

-------

# date:21/10
# time spent:0.75hr
## description:
i had started making the firmware of the project in the wowki simulator i gathered all the libraries and started making the digram.json file for the project and and adding all sensors to it
## images:
<img width="927" height="811" alt="image" src="https://github.com/user-attachments/assets/ee4a9200-91f0-4455-913e-6533a31e1a59" />
<img width="955" height="850" alt="image" src="https://github.com/user-attachments/assets/35f67f3f-bcfc-43f3-bf93-947ae3d58ec4" />

-------
# date:21/10
# time spent:1.75hr
## description:
i studied about how to use cpp in arduino projects and then with the help of ai ,i started learning the coding part of the project and then i had completed the coding part of the project
## images:
<img width="1911" height="886" alt="image" src="https://github.com/user-attachments/assets/58b4ee1d-0bb8-42fc-b142-ad024f4cf196" />
<img width="916" height="867" alt="image" src="https://github.com/user-attachments/assets/1bf0d0ac-a5d7-4f02-8020-4bc25b9b8ad5" />

-------
# date:21/10
# time spent:0.5hr
## description:
i had added the bom files in the repo by checking in the lscs number and also i i had rendered the gerber files and the dril files and published them in the repo.
## images:
<img width="1902" height="640" alt="image" src="https://github.com/user-attachments/assets/0ae4fe20-7c22-4d13-987c-9e09a60804db" />


-------
# date:24/10
# time spent:1hr
## description:
as reviewer asked me to make cad case ,i had made  the case for the model and then created an assembly model for the pcb and pusshed the files to the repo
## images:
<img width="1917" height="782" alt="image" src="https://github.com/user-attachments/assets/bae7919f-d188-454c-8835-f9d5cdf17f04" />
<img width="1297" height="700" alt="image" src="https://github.com/user-attachments/assets/ecdc4740-5a21-4fa6-9d1f-6b4c4bade911" />


-------
