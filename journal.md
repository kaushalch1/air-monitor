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
