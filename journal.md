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
