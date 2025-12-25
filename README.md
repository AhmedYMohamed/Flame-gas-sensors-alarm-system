# Flame and Gas Sensor Alarm System

## 📖 Description
This project is an automated safety system designed to detect hazardous gas leaks and open flames. When a threat is detected, the system triggers an audible alarm and visual indicators to warn occupants, potentially preventing fires and gas poisoning incidents.

## ✨ Features
* **Real-time Detection:** Continuously monitors for smoke, gas (LPG, Methane, etc.), and fire.
* **Visual Warning:** LEDs indicate system status (Safe, Gas Detected, Fire Detected).
* **Automated Safety Future improvement:** Can automatically shut off gas valves or turn on exhaust fans.

## 🛠️ Hardware Required
* Microcontroller Atmega32
* Flame Sensor (e.g., KY-026 or IR Flame Sensor)
* Gas Sensor (e.g., MQ-2, MQ-5, or MQ-6)
* LEDs (Red for alert, Green for power)
* Jumper Wires & Breadboard
* Resistors (220Ω for LEDs)

## 💻 Software & Libraries
* **IDE:** Arduino IDE (or specify if using Python/MicroPython)
* **Libraries:** * (List any specific libraries you used, e.g., `MQ2.h`)

## 🔌 Circuit Diagram
*(Upload a picture of your wiring to your repo and link it here, or describe the pin connections briefly)*
* **Flame Sensor:** Digital Pin D2
* **Gas Sensor:** Analog Pin A0
* **Buzzer:** Digital Pin D8
* **Red LED:** Digital Pin D9

## 🚀 Installation & Usage
1.  **Clone the repository:**
    ```bash
    git clone [https://github.com/AhmedYMohamed/Flame-gas-sensors-alarm-system.git](https://github.com/AhmedYMohamed/Flame-gas-sensors-alarm-system.git)
    ```
2.  Open the project code in your IDE.
3.  Connect your Arduino/Board to the computer.
4.  Select the correct Board and Port.
5.  **Upload** the code.
6.  Test the system using a gas lighter (for gas) or a flame source (cautiously) to verify the alarm triggers.

## 🤝 Contributing
1.  Fork the Project
2.  Create your Feature Branch (`git checkout -b feature/NewFeature`)
3.  Commit your Changes (`git commit -m 'Add some NewFeature'`)
4.  Push to the Branch (`git push origin feature/NewFeature`)
5.  Open a Pull Request

## 📜 License
This project is open-source and available under the [MIT License](LICENSE).
