# OPIN Smart Lamp

![Smart Lamp](https://github.com/OPIN-Smart-Home/SmartLamp/blob/main/asset/SmartLamp.png)

## Table of Contents
For User
- [Introduction](#introduction)
- [Features](#features)
- [Components and Interface](#components-and-interface)
- [User Guide](#user-guide)

For Developer
- [Installation](#installation)
- [MQTT Topics](#mqtt-topics)
- [Limitations](#limitations)
- [Future Development](#future-development)

Additional Information
- [OPIN Smart Home Devices](#opin-smart-home-devices)
- [Further Information](#further-information)

 ---
 ---

# For User
## Introduction  
The OPIN Smart Lamp empowers users to manage their home lighting effortlessly through the [OPIN Gateway](<https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public>), offering both automation and manual control via the OPIN mobile application. It provides a flexible lighting solution that can be integrated into various smart home routines, making it an essential element for enhancing comfort, security, and energy efficiency.

With the Smart Lamp integrated into the OPIN system, users can remotely switch lights on or off, and configure intelligent automation based on [human detection](<https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public?tab=readme-ov-file#auto-off-system-human-detection>), optimizing light usage according to activity within the home. This functionality reduces unnecessary energy consumption, contributing to a more efficient and eco-friendly household.

For developers, the Smart Lamp leverages MQTT topics for communication, allowing seamless integration into the OPIN Gateway. By utilizing MQTT messaging, developers can easily control the Smart Lamp, implement custom automation rules, and expand its functionality within the OPIN network. The simplicity of MQTT makes it ideal for quick deployment and further customization, enabling the Smart Lamp to be an adaptable part of any smart home system.

## Features
1. **Remote Control**  
   Manage your home lighting from anywhere using the OPIN mobile app, providing the flexibility to control lights whether you're at home or away.
2. **Automation**  
   Set up automation triggers based on human detection, enabling lights to turn on or off automatically when people are detected in the room, enhancing convenience.
3. **Energy Efficiency**  
   Reduce electricity consumption by automating lights to turn off when no one is detected in a room, contributing to a more sustainable and eco-friendly home.
4. **Manual Override**  
   Lights can be manually controlled through a conventional light switch, allowing users to turn the Smart Lamp on or off without needing the app.
5. **Seamless Integration**  
   The Smart Lamp communicates with the OPIN Gateway via MQTT, simplifying the integration process into your existing smart home ecosystem.
6. **Status Monitoring**  
   Keep track of the lamp’s status (on/off) in real-time within the OPIN app, ensuring full visibility and control over your lighting setup.
7. **Easy Installation**  
   Connects seamlessly to the OPIN Gateway for quick and hassle-free setup, making it accessible even for beginners.

## Components and Interface
The following components are used in the OPIN Smart Lamp. The numbers correspond to the labels in the [cover image](#opin-smart-lamp).
1. [**ESP32 Devkit V1**](<https://olddocs.zerynth.com/r2.3.3/official/board.zerynth.doit_esp32/docs/index.html>)  
   The microcontroller responsible for managing the device's operations and communication via MQTT.
2. **LED**  
   The device features an LED that indicates the WiFi connection status, helping users verify whether the device is connected to the network.
3. **Button**  
   A button is provided for initiating the WiFi configuration process, allowing users to connect the device to their network. This button can also be used to reset the WiFi connection.
4. [**HLK-PM01 AC-DC Converter**](<https://www.hlktech.net/index.php?id=105>)  
   Converts the AC power input to a lower DC voltage suitable for the ESP32 and other internal components.
5. **Relay Module 5V with Optocoupler**  
   Controls the electrical switching of the lights, allowing automation and remote control.
6. **Switch**  
   The device includes two cables that connect to an external switch. This switch allows users to manually turn the Smart Lamp on or off.
7. **AC Power Input (L/N)**  
   Two cables are provided for AC power input, connecting the device to the line (L) and neutral (N) lines of the electrical source.
8. **Load Connection (L)**  
   A single cable connects to the load (i.e., the light), providing the necessary power to the lamp.

## User Guide
This section provides step-by-step instructions on how to set up and use the OPIN Smart Lamp effectively.
### 1. Setting Up the OPIN Smart Lamp
1. **Connect the Hardware**  
   - Connect the external switch to the provided cables.
   - Connect the load cable to your lights.
   - Connect the AC power input cables to your electrical source.
   - Ensure that all connections are secure and insulated for safety.  
   >⚠️ **Caution**: The installation process involves working with electrical wiring. It is strongly recommended to have the installation performed by a qualified electrician or someone experienced with electrical appliances to avoid potential hazards. Improper handling of electrical components can result in serious injury or damage to the device.

   For detailed wiring instructions, please refer to [cover image](#opin-smart-lamp) or the following schematics:  
   ![Schematic](https://github.com/OPIN-Smart-Home/SmartLamp/blob/main/asset/schematic.png)
   
   These diagrams illustrate the correct way to connect the device to the power source, load, and switch for safe and efficient operation.

2. **Power On the Device**  
   - Turn on the power supply to the Smart Lamp. The LED indicator should light up (blinking or solid blue), indicating that the device is powered.

### 2. LED Indicator
1. **Solid**: The device is connected to the network.
2. **Blinking continuously**: The device is not connected to a network or in the process of connecting.
3. **Off**: The device is either not powered or in WiFi configuration mode.

### 3. WiFi Configuration
#### Add WiFi Configuration
1. **Initiate WiFi Configuration**  
   - Press the button once to enter WiFi configuration mode. The LED will blink twice, indicating that the device is ready to connect to a network.  
   ![Button1](https://github.com/OPIN-Smart-Home/SmartLamp/blob/main/asset/button1.gif)

2. **Connect to the Network**  
   - Open the WiFi settings on your mobile, laptop, or PC.
   - Connect to the Smart Lamp SSID `OPIN-SmartLamp-[device_id]`. Your device should automatically redirect you to the WiFi configuration interface (captive portal).
      > **Tips**: If you're not redirected to the captive portal automatically, try the following:  
      (1) Look for a notification asking you to `log in to the network`,  
      (2) Go to [WiFi settings](<https://media.techietech.tech/2020/06/Forget-Network.jpg.webp>) and select something like `Manage network settings`,  
      (3) Manually access the captive portal by opening `192.168.4.1` in your browser.
   - Once inside the configuration interface, select `Configure WiFi`. Choose your home WiFi SSID from the list, enter the password, and click `Save`. (Refer to the provided images for detailed guidance.)  
   ![Configure WiFi](https://github.com/OPIN-Smart-Home/SmartLamp/blob/main/asset/configure_wifi.png)

3. **Confirm Connection**  
   - After the connection is established, the LED will turn solid, indicating that the Smart Lamp is successfully connected to your WiFi network.

#### Reset WiFi Configuration
1. **Initiate Reset**  
   - Press and hold the button for at least two seconds. The LED will blink three times (indicating reset) followed by two blinks (entering WiFi configuration mode), signaling that the WiFi settings have been reset. This action will erase all previously saved WiFi configurations.  
   ![Button2](https://github.com/OPIN-Smart-Home/SmartLamp/blob/main/asset/button2.gif)

2. **Reconnect to the Network**  
   - After resetting the WiFi, follow step [2 "Connect to the Network"](#add-WiFi-configuration) from the **Add WiFi Configuration** section to reconnect the Smart Lamp to your WiFi.

#### Check IP Address of the Smart Lamp
1. **Initiate WiFi Configuration**  
   - Press the button once to enter WiFi configuration mode. The LED will blink twice, indicating that the device is ready for network configuration.  
   ![Button1](https://github.com/OPIN-Smart-Home/SmartLamp/blob/main/asset/button1.gif)

2. **Connect to the Network**  
   - Open the WiFi settings on your mobile, laptop, or PC.
   - Connect to the Smart Lamp SSID `OPIN-SmartLamp-[device_id]`, and your device will be redirected to the WiFi configuration interface (captive portal).  
      > **Tip**: If you're not redirected to the captive portal automatically, try the following:  
      (1) Look for a notification asking you to `log in to the network`,  
      (2) Go to [WiFi settings](<https://media.techietech.tech/2020/06/Forget-Network.jpg.webp>) and select `Manage network settings`,  
      (3) Manually access the captive portal by opening `192.168.4.1` in your browser.
   - The IP address of the Smart Lamp will be shown in the connected WiFi details box. (Refer to the provided image for reference.)  
   ![Check IP](https://github.com/OPIN-Smart-Home/SmartLamp/blob/main/asset/check_ip.jpeg)

3. **Exit Configuration Mode**  
   - After checking the IP address, select `Exit` to complete the configuration process. The LED will turn solid, indicating that the Smart Lamp is successfully connected to your WiFi network.

### 4. Connect OPIN Smart Lamp to OPIN Mobile App
1. **Add New Device**  
   - Open the OPIN mobile app and click the `Add New Device` option.  
   - Select `Smart Lamp` from the list of devices.  
   - Enter the `Device ID` and `IP Address` of the Smart Lamp.  
   - Click `Submit`.  
   > **Note**: Ensure that the device ID and IP address are correct; otherwise, the process will fail.

2. **Control the Smart Lamp**  
   - Navigate to the dashboard in the OPIN mobile app.  
   - Select `Smart Lamp`.  
   - You can remotely turn the Smart Lamp on or off and monitor its current state. Additionally, the app offers the `Auto Off` feature, which automatically turns off the Smart Lamp when no person is detected in the room. For more details, refer to the [Auto Off feature documentation](<https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public#auto-off-feature>).


### 5. Manual Control
- Use the connected switch to manually turn the Smart Lamp on or off. This feature allows users to control the device without the need for the mobile app.  
- When the Smart Lamp is controlled via the switch, the state will automatically sync and update in the OPIN mobile app, ensuring the app always displays the correct status of the Smart Lamp.

### 6. Troubleshooting
- **Device Not Responding**:  
   - Check if the [gateway (Jetson Nano)](<https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public?tab=readme-ov-file#nvidia-jetson-nano-as-the-gateway-for-opin-smart-home-system>) is online and connected to the same local network.
   - Check the power connections and ensure the device is properly powered on.
   - Verify that all wiring is secure and correctly installed.
   - Unplug and reconnect the power source to restart the device if necessary.
- **WiFi Connection Issues**: 
   - Ensure that the WiFi credentials entered during configuration are correct.
   - Verify that the WiFi network is operational and within range of the Smart Lamp.
   - Inspect the wiring, especially for any loose or faulty connections.

By following these steps, users can effectively set up and utilize the OPIN Smart Lamp for enhanced home automation and lighting control.

---
---

# For Developer
This section provides guidelines for developers looking to contribute to the OPIN Smart Home system. It's recommended to pay attention on [For User](#for-user) section.
## Installation
### Prerequisites
Before you begin, ensure you have the following installed on your development environment:
- **Arduino IDE** for uploading the firmware to the ESP32.
- **ESP32 Board Package** for Arduino IDE. For Arduino IDE, you can install it by going to **File > Preferences > Additional Board Manager URLs** and adding `https://dl.espressif.com/dl/package_esp32_index.json`. Then, navigate to **Tools > Board > Board Manager** and search for "ESP32".
- **Required Libraries**:
  - **WiFi**: For WiFi connectivity.
  - [**PicoMQTT** by Michał Leśniewski](<https://github.com/mlesniew/PicoMQTT>) version `0.3.8` : To enable the ESP32 to function as an MQTT broker/server.
  - [**WiFiManager** by tzapu](<https://github.com/tzapu/WiFiManager>) version `2.0.17`: For handling WiFi connections and configurations.

### Clone the Repository
To get started with the project, clone the repository to your local machine:
```bash
git clone https://github.com/OPIN-Smart-Home/SmartLamp.git
```

## MQTT Topics
The following MQTT topics are utilized for communication between the OPIN Smart Lamp and the OPIN gateway:
- **Device to User (d2u)**:  
  `opin/SmartLamp_[device_id]/d2u`  
  This topic is used to send messages from the Smart Lamp to the mobile app (device to user). It reports the current state of the lamp, including updates triggered by the manual switch.
- **User to Device (u2d)**:  
  `opin/SmartLamp_[device_id]/u2d`  
  This topic is used for sending commands from the mobile app to the Smart Lamp (user to device). Commands include turning the lamp on or off.
- **Device SSID**:  
  `OPIN-SmartLamp-[device_id]`  
  This SSID is employed for connecting the Smart Lamp to WiFi during the initial configuration process.
> **Note**: The gateway will not accept the same `device_id` for multiple Smart Lamps. Developers must ensure that each Smart Lamp has a unique `device_id` to avoid communication conflicts within the system.

## Limitations
While the OPIN Smart Lamp is designed to provide a reliable smart lighting solution, there are some limitations to be aware of:  
1. **Network Dependency**: The Smart Lamp requires a stable WiFi connection for full functionality. Any interruptions or disconnections from the network can result in loss of control or status updates.
2. **Device ID Uniqueness**: Each Smart Lamp must have a unique `device_id`. Duplicate `device_id`s are not permitted, as they can lead to communication conflicts with the gateway.
3. **Range Limitations**: The effective range of the WiFi signal can affect the Smart Lamp's performance. Ensure that the Smart Lamp is within the coverage area of the WiFi network for optimal operation.
4. **Power Dependency**: The Smart Lamp must be powered on to function. If the power supply is interrupted or turned off, the Smart Lamp will be non-operational until power is restored.
5. **Basic Functionality**: The Smart Lamp is designed primarily for basic on/off control of the lights. It does not support advanced features such as brightness adjustment or RGB color customization.
6. **Dependency on the Gateway**: The Smart Lamp relies on the OPIN gateway for communication with the mobile app. Any issues with the gateway may affect the Smart Lamp's functionality.

## Future Development
To enhance the functionality and usability of the OPIN Smart Lamp, the following areas are identified for future development:
1. **Improved Connectivity Options**: Investigate the implementation of alternative connectivity protocols (e.g., Zigbee, Z-Wave) to provide a more robust and reliable connection, minimizing dependency on WiFi.
2. **Expanded Functionality**: Develop features that allow users to adjust brightness levels and RGB colors. This will provide users with greater control over their lighting environment and enhance the overall smart home experience.
3. **Enhanced Range and Signal Strength**: Explore solutions to extend the effective range of the WiFi signal, such as the integration of mesh networking or the use of WiFi range extenders, ensuring that the Smart Lamp can operate effectively in larger spaces.

---
---

# Additional Information
## OPIN Smart Home Devices
Other devices:
- [OPIN Smart Gateway](<https://github.com/OPIN-Smart-Home/OPIN-JetsonNano-public>)
- [OPIN Smart kWh Meter](<https://github.com/OPIN-Smart-Home/kWhMeter>)
- [OPIN Smart Door Lock](<https://github.com/OPIN-Smart-Home/DoorLock>)
- [OPIN Smart AC Control](<https://github.com/OPIN-Smart-Home/ACControl>)

## Further Information
For further information, please feel free to contact me at:
- **Email**: [anisahfarah28@gmail.com](mailto:anisahfarah28@gmail.com)
- **LinkedIn**: [Anisah Farah Fadhilah](https://www.linkedin.com/in/anisahfarahfadhilah)
