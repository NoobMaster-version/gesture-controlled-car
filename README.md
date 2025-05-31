# Gesture-Controlled RC Car

## Project Overview
This project demonstrates a gesture-controlled RC car using an ESP32 microcontroller, an MPU6050 accelerometer/gyroscope sensor, and the ESP-NOW protocol for wireless communication. By tilting a sender device equipped with the MPU6050, users can control the direction and movement of an RC car in real-time. The project consists of two ESP32 modules: one as the sender (transmitting gesture data) and the other as the receiver (controlling the car's motors).

## Media
- **RC Car Model**:
  ![RC Car](assets/RC_Car.png)
- **Demo Video**: [Demo.mp4](assets/Demo.mp4)
- **Project Report**: [Project_Report.pdf](Kartikey_Pathak_POSTER_Winter_Internship_SRW.pdf)

## Features
- **Gesture Control**: Tilt-based control using the MPU6050 sensor to detect X and Y axis movements.
- **Wireless Communication**: Utilizes ESP-NOW protocol for low-latency, peer-to-peer data transmission between ESP32 modules.
- **Motor Control**: Controls four DC motors for forward, backward, left, and right movements of the RC car.
- **Simple Setup**: Minimal hardware requirements with easy-to-follow code structure.

## Hardware Requirements
- 2x ESP32 Development Boards (e.g., ESP32-WROOM-32)
- 1x MPU6050 Accelerometer/Gyroscope Module
- 4x DC Motors with Motor Driver (e.g., L298N)
- RC Car Chassis
- Jumper Wires
- Power Supply (e.g., batteries for the car and sender module)
- USB Cable for programming

## Software Requirements
- Arduino IDE (or compatible IDE)
- ESP32 Board Support Package for Arduino
- Libraries:
  - `ESP32` (built-in with ESP32 board package)
  - `Wire` (built-in with Arduino)
  - `MPU6050` (available via Arduino Library Manager)

## Pin Configuration
### Receiver ESP32
- Right Motors (two motors connected to one channel of the L298N motor driver):
  - Motor Pin 1: GPIO 12
  - Motor Pin 2: GPIO 14
  - Enable Pin: GPIO 33
- Left Motors (two motors connected to one channel of the L298N motor driver):
  - Motor Pin 1: GPIO 27
  - Motor Pin 2: GPIO 26
  - Enable Pin: GPIO 32

### Sender ESP32
- MPU6050:
  - SCL: GPIO 22 (default I2C)
  - SDA: GPIO 21 (default I2C)

## Installation and Setup
1. **Install Arduino IDE**:
   - Download and install the Arduino IDE from [arduino.cc](https://www.arduino.cc/en/software).
   - Add ESP32 board support by following the [ESP32 Arduino setup guide](https://docs.espressif.com/projects/arduino-esp32/en/latest/installing.html).

2. **Install Libraries**:
   - Install the `MPU6050` library via the Arduino Library Manager (`Sketch > Include Library > Manage Libraries`).

3. **Upload Code**:
   - Clone or download this repository.
   - Open `SenderESPCode_2.ino` and `RecieverESPCode_2.ino` in the Arduino IDE.
   - Update the `broadcastAddress` in `SenderESPCode_2.ino` with the MAC address of the receiver ESP32. Use `MACaddressCode.ino` to find the MAC address by uploading it to the receiver ESP32 and checking the Serial Monitor.

4. **Hardware Connections**:
   - Connect the MPU6050 to the sender ESP32 (SCL to GPIO 22, SDA to GPIO 21, VCC to 3.3V, GND to GND).
   - Connect the motor driver to the receiver ESP32 as per the pin configuration above.
   - Assemble the RC car chassis with the motors and power supply.

5. **Upload and Test**:
   - Upload `SenderESPCode_2.ino` to the sender ESP32 and `RecieverESPCode_2.ino` to the receiver ESP32.
   - Power on both modules.
   - Tilt the sender ESP32 to control the RC car's movements (forward, backward, left, right).

## How It Works
- The sender ESP32 reads tilt angles from the MPU6050 sensor and converts them into directional commands (`x_direction` and `y_direction`).
- These commands are transmitted to the receiver ESP32 via ESP-NOW.
- The receiver ESP32 interprets the commands to control the motors, enabling the car to move forward, backward, left, or right based on the tilt direction.

## Code Structure
- `SenderESPCode_2.ino`: Reads MPU6050 data, calculates tilt angles, and sends directional commands via ESP-NOW.
- `RecieverESPCode_2.ino`: Receives commands via ESP-NOW and controls the DC motors for car movement.
- `MACaddressCode.ino`: Utility code to retrieve the MAC address of an ESP32 for ESP-NOW configuration.

## Usage
- Tilt the sender ESP32 along the X-axis (>40° for right, <-40° for left) to turn the car.
- Tilt along the Y-axis (>40° for backward, <-40° for forward) to move the car forward or backward.
- No tilt (within ±40°) stops the car or maintains straight movement.

## Troubleshooting
- **No movement**: Ensure the MAC address in `SenderESPCode_2.ino` matches the receiver's MAC address.
- **MPU6050 not responding**: Check I2C connections (SCL/SDA) and ensure the sensor is powered correctly.
- **Erratic motor behavior**: Verify motor driver connections and power supply voltage.
- **ESP-NOW errors**: Confirm both ESP32s are on the same Wi-Fi channel (default is 0).

## Future Improvements
- Add speed control using PWM signals.
- Implement a calibration routine for the MPU6050.
- Add a mobile app interface for additional control options.
- Enhance the car with obstacle avoidance using ultrasonic sensors.


## Acknowledgments
- Thanks to the Arduino and ESP32 communities for their extensive documentation and libraries.
- Inspired by DIY robotics and gesture control projects.
