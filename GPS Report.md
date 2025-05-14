![Advanced Search](Aspose.Words.818f480c-ae9a-42c3-83ef-137d61d6c7f9.001.png)

**CSE211s Spring 2025**

` `**Introduction to Embedded Systems** 

**GPS Project**

|Name|ID|Department|
| :-: | :-: | :-: |
|Nour  Ayman Mahmoud |**2200105**|**ECE**|
|Eyad Osama Ali|**2200115**|**ECE**|
|Ahmed Mahmoud ElMorsy|**2200725**|**CSE**|
|Ganna Khaled Abd ElNasser  |**2200089**|**CSE**|
|Mostafa Ahmed Abd ELSattar|**2201092**|**CSE**|

Project Description      

The goal of this project is to develop an embedded system using C programming that gathers real-time positional coordinates while a microcontroller is in motion, and display location information on an attached computer or an LCD. The positioning system should use the TM4C123G LaunchPad. A map of the place with coordinates of various landmarks should be stored on the device. When approaching a landmark, its name should be displayed.

Hardware Components

1. TM4C123G LaunchPad à Microcontroller

![Getting Started with TIVA C Series TM4C123G LaunchPad from ...](Aspose.Words.818f480c-ae9a-42c3-83ef-137d61d6c7f9.002.jpeg)

1. Ublox NEO-6M à GPS module to acquire real-time location data

   ![Ublox NEO-6MV2 GPS Module](Aspose.Words.818f480c-ae9a-42c3-83ef-137d61d6c7f9.003.jpeg)

1. 16x2 LCD Display 

![16x2 LCD Display Module Pinout, Features, Description & Datasheet](Aspose.Words.818f480c-ae9a-42c3-83ef-137d61d6c7f9.004.png)

The system was powered via USB or battery setup.

For visual feedback, we implemented data output to a PC via UART, and an LCD display for standalone operation.

Connections 

![C:\Users\lenovo\AppData\Local\Packages\5319275A.WhatsAppDesktop_cv1g1gvanyjgm\TempState\11198926C4E3F0F5828457E3C3CED88D\WhatsApp Image 2025-05-08 at 14.11.08_08fb35b2.jpg](Aspose.Words.818f480c-ae9a-42c3-83ef-137d61d6c7f9.005.jpeg)

|||
| :- | :- |

|**LCD Pin**|**TivaC Pin**|**Breadboard**|**Function**|
| :-: | :-: | :-: | :-: |
|**VSS**|GND|GND|Ground|
|**VDD**|+5V||Power|
|**V0**||Middle of pot||

||
| :-: |

||||Contrast control|
| :-: | :-: | :-: | :-: |
|**RS**|PD0||Register Select|
|**RW**|PD1||Write mode|
|**EN**|PD2||Enable|
|**D0**|PA7|||
|**D1**|PA6|||
|**D2**|PA5|||
|**D3**|PB4||Data bits|
|**D4**|PE5|||
|**D5**|PE4|||
|**D6**|PE1|||
|**D7**|PD3|||
|**A (LED+)**||+5V (via resistor)|LCD backlight|
|**K (LED−)**||GND|Backlight GND|

|<p>LCD Connection :</p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p>**Potentiometer:**<br>Connect side pins to **GND and +5V**, center pin to **V0** of LCD.</p><p></p><p>LCD works in 8 bit mode</p>|<p>GPS Connection :</p><p></p>|
| :- | :- |

|**GPS Pin**|**TivaC**|
| :- | :- |
|**VCC**|+3.3V|
|**GND**|GND|
|**RX**|PB1|
|**TX**|PB0|

||<p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p><p></p>|
| :- | :- |

Software Tools

All firmware was developed using the Keil uVision IDE in Embedded C, ensuring precise control over the hardware. GitHub was used for version control, allowing team collaboration and continuous code integration. The software stack included UART communication, data parsing, and logic for matching GPS coordinates with stored landmark data.

***GitHub Link :*** 

<https://github.com/motta97/GPSProject>

System Design

The system is composed of a modular design featuring GPS input, UART data handling, coordinate parsing, and landmark detection. UART was configured to match the GPS module’s baud rate (typically 9600 bps). The logic compares incoming coordinates with stored data using a distance formula (Harvensine) to determine proximity to known locations.

Implementation Details

We initialized necessary GPIO ports to support UART and potential LCD use. UART was configured to receive ASCII-formatted NMEA sentences from the GPS module. Parsing functions were written to extract latitude and longitude from the $GPRMC or $GPGGA sentences. Landmark coordinates were stored in arrays, and a comparison algorithm determined the closest match for display via serial monitor or LCD.

Testing and Results

The system was tested by walking between five known hall locations within the faculty. GPS data was successfully parsed and compared against stored landmarks. The correct location name was displayed upon proximity. We recorded test outputs using a smartphone (recorded video) and documented successful transitions between locations. Challenges included initial UART configuration and GPS signal stability.

Demo and Deliverables

Our GitHub repository contains all project files and code, accessible via a shared link. A demo video was recorded, showcasing the system in motion while displaying real-time landmark updates. Photos of the setup and hardware wiring were included to help visualize the implementation of the project.

|![C:\Users\lenovo\AppData\Local\Packages\5319275A.WhatsAppDesktop_cv1g1gvanyjgm\TempState\63F9D29FECCCF60145E2AD4EA65507BA\WhatsApp Image 2025-05-14 at 00.50.55_f23aba2f.jpg](Aspose.Words.818f480c-ae9a-42c3-83ef-137d61d6c7f9.006.jpeg)|![C:\Users\lenovo\AppData\Local\Packages\5319275A.WhatsAppDesktop_cv1g1gvanyjgm\TempState\28F96513E88A2CB49AAEC43599CF3F17\WhatsApp Image 2025-05-14 at 00.51.05_64c66368.jpg](Aspose.Words.818f480c-ae9a-42c3-83ef-137d61d6c7f9.007.jpeg)|
| :- | :- |

***Video link:***   <https://youtu.be/PkJ-l7r4MOc?si=knBLwEKxsFeGWuRz>

Copy and paste to browser if not directly working by clicking it

Team Contributions

|**Name**|**Contribution**|
| :-: | :-: |
|<p>**Nour Ayman Mahmoud** </p><p>**2200105**</p>|Hardware implementation , LCD driver , Documentation|
|<p>Eyad Osama Ali** </p><p>**2200115**</p>|Landmark Mapping , Distance Calculation , GPS|
|Ganna Khaled Abd ElNasser  **2200089**|UART , SysTick|
|Ahmed Mahmoud ElMorsy **2200725**|UART , GPS|
|Mostafa Ahmed Abd ELSattar **2201092**|Battery , Documentation|

Bonus Work We did

-Packaging

-autonomous working (connected to battery not PC)

-LCD driver

-LCD display

-controlling LCD contrast using Potentiometer

Conclusion and Future Work

The project successfully demonstrated a basic embedded GPS tracking system. Key achievements included accurate coordinate parsing and real-time location identification. Future improvements could include integrating a full GUI, expanding landmark storage, improving signal reliability with better antennas, or adding GSM communication for remote updates.

Appendices

TivaC Driver : <https://www.ti.com/tool/STELLARIS_ICDI_DRIVERS>

Tm4c123gh6pm.h : [tm4c123gh6pm.h - Google Drive](https://drive.google.com/file/d/1Gyt1VkYgfyEYHeF1VL6ivI9W2FQkB-GQ/view)

