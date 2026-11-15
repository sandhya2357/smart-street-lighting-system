# Smart Street Lighting System

An IoT-enabled smart street lighting system built using ESP32. The system automatically controls street lights based on ambient light and motion detection, which saves energy. LEDs fade smoothly using PWM.

## Features
- Automatic day and night detection using LDR sensor
- Motion detection using PIR sensor
- 3 LEDs controlled with PWM for smooth fading
- Three brightness levels: OFF, 50% and 100%
- Live status display on the Serial Monitor

## Components Used
- ESP32
- PIR Sensor
- LDR Sensor Module (Digital Output)
- 3 x LED
- Resistors
- Breadboard
- Jumper wires

## Software Used
- Arduino IDE

## How It Works
| Condition | LED Brightness |
| Daytime | OFF (0%) |
| Night, no motion | DIM (50%) |
| Night, motion detected | BRIGHT (100%) |

1. The LDR sensor checks whether it is day or night.
2. During the day, all LEDs stay OFF to save energy.
3. At night, the LEDs glow at 50% brightness.
4. When the PIR sensor detects motion (confirmed by 3 readings in a row), the LEDs glow at 100%.
5. When the motion stops, the LEDs fade back to 50%.

## Pin Connections
| Component | ESP32 Pin |
|---|---|
| LDR (Digital Out) | GPIO 4 |
| PIR Sensor (OUT) | GPIO 27 |
| LED 1 | GPIO 2 |
| LED 2 | GPIO 18 |
| LED 3 | GPIO 19 |

## Project Images
### Block Diagram
![Block Diagram](images/Block_Diagram.png)

### Circuit Diagram
![Circuit Diagram](images/Circuit_Diagram.png)

### Flowchart
![Flowchart](images/Flowchart.png)

### Hardware Setup
![Hardware Setup](images/hardware_setup.jpeg)

### Prototype
![Prototype](images/prototype.jpeg)

## Folder Structure
- `code` - Arduino code
- `images` - block diagram, circuit diagram, flowchart and photos
- `report` - project paper (PDF)

## How to Run
1. Connect the components as shown in the Pin Connections table.
2. Open `code/smart_street_lighting/smart_street_lighting.ino` in Arduino IDE.
3. Select the **ESP32** board and the correct COM port.
4. Click **Upload**.
5. Open the Serial Monitor and set the baud rate to **115200**.
6. Wait 40 seconds for the PIR sensor to warm up.

## Serial Monitor Output
The system prints the LDR state, PIR output, motion status and LED brightness every 400 ms.

## License
This project is licensed under the MIT License.
