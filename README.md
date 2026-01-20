# LPG Gas Leakage Detection and Automatic Valve Shut-Off System using ESP32

## 📌 Problem Statement
LPG gas leakage poses serious safety risks in homes and small industrial setups. Manual detection and response can be delayed, increasing the chances of accidents. 
This project aims to not only detect LPG leakage in real time but also automatically shut off the gas supply to minimize risk.

---

## 🧠 Project Overview
This system uses an MQ-series gas sensor interfaced with an ESP32 microcontroller to continuously monitor LPG concentration.
When the gas level exceeds a predefined safe threshold, the ESP32 triggers a local alarm, sends a mobile notification, 
and actuates a servo motor to close the gas valve automatically.

The project demonstrates sensing, decision-making, actuation, and IoT-based alerting in a single embedded system.

---

## ⚙️ System Block Diagram (Description)
1. Gas sensor continuously monitors LPG concentration  
2. ESP32 reads sensor data via analog input  
3. Sensor value is compared with a safety threshold  
4. If leakage is detected:
   - Servo motor rotates to close the gas valve
   - Alert notification is sent to the user’s mobile phone via Wi-Fi  

---

## 🔌 Hardware Components Used

| Component | Description |
|---------|-------------|
| ESP32 | Main controller with Wi-Fi |
| MQ-6 Gas Sensor | LPG gas detection |
| Servo Motor | 
| Jumper Wires |
| Power Supply | USB / External 5V |

---

## 💻 Software & Tools
- Arduino IDE  
- ESP32 Board Package  
- Servo motor control library  
- Wi-Fi and notification libraries  
- Blynk iot
---

## 🔁 Working Algorithm
1. Initialize ESP32, Wi-Fi, and servo motor  
2. Set servo to normal (valve open) position  
3. Continuously read gas sensor values  
4. Compare sensor readings with threshold  
5. If threshold is exceeded:
   - Rotate servo motor to close gas valve
   - Send mobile alert notification  
6. Continue monitoring system status  

---

## 📊 Results & Testing
- LPG leakage detected within **3–5 seconds**
- Servo motor successfully closed the valve within **1 second**
- Mobile alert received within **2–3 seconds**
- System operated reliably during repeated test cycles


---

## 🚀 Future Improvements
- Closed-loop control using valve position feedback  
- PID-based servo control for smoother actuation  
- Integration with industrial-grade solenoid valves  
- Battery backup and fail-safe mechanism  
- Mobile app dashboard for system status  

---

## 🎓 Learning Outcomes
- Sensor and actuator interfacing using ESP32  
- Servo motor control and basic actuation logic  
- Embedded decision-making for safety systems  
- Introduction to automation and control concepts  

---

## 👤 Author
**Mohd Raza**  
B.Tech Electronics Engineering (3rd Year)  
JSS Academy of Technical Education, Noida  

---

