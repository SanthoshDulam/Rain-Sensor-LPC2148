# 🌧 Rain Sensor Interfacing with LPC2148 Microcontroller

## 📘 Overview

This project demonstrates **interfacing a rain sensor with the LPC2148 ARM7 microcontroller** to detect rainfall and display the alert message on an **LCD screen**.
The system uses an **LM393 comparator** to detect moisture levels and triggers an alert when rain is sensed.

---

## ⚙️ Components Required

| Component                  | Description                 |
| -------------------------- | --------------------------- |
| LPC2148                    | ARM7TDMI Microcontroller    |
| LM393                      | Comparator IC               |
| Rain Sensor Module         | Detects raindrops           |
| 16x2 LCD Display           | Shows rain detection status |
| Jumper Wires, Power Supply | Connections and power       |

---

## 🧩 Block Diagram

```
Rain Sensor → LM393 Comparator → LPC2148 Microcontroller → LCD Display
```

---

## 🧠 Connections

| Component        | LPC2148 Pin |
| ---------------- | ----------- |
| Rain Sensor (D0) | P1.24       |
| LCD RS           | P0.8        |
| LCD RW           | P0.9        |
| LCD EN           | P0.10       |
| LCD Data Lines   | P0.0 – P0.7 |

---

## 💻 Code: `rain_sensor.c`

Create a new file named **`rain_sensor.c`** and paste this:

```c
#include <lpc214x.h>
#define bit(x) (1 << x)
#define delay for(i = 0; i < 70000; i++);
#define RAIN (IO1PIN & (1 << 24))

unsigned int i;

void lcd_init();
void dat(unsigned char);
void cmd(unsigned char);
void string(unsigned char *);

void main() {
    IO0DIR = 0xFFF;  // P0.0 - P0.11 as output
    IO1DIR = 0x0;    // P1 as input (rain sensor)
    lcd_init();
    cmd(0x80);
    string("Alert");
    delay; delay;
    
    while(1) {
        if(RAIN == 0) {  // Active low when rain detected
            string("!Rain Detected!");
            delay; delay;
            cmd(0x01);  // Clear display
        }
    }
}

void lcd_init() {
    cmd(0x38);
    cmd(0x0C);
    cmd(0x06);
    cmd(0x01);
    cmd(0x80);
}

void cmd(unsigned char a) {
    IO0PIN &= 0x00;
    IO0PIN |= (a << 0);
    IO0CLR |= bit(8);
    IO0CLR |= bit(9);
    IO0SET |= bit(10);
    delay;
    IO0CLR |= bit(10);
}

void dat(unsigned char b) {
    IO0PIN &= 0x00;
    IO0PIN |= (b << 0);
    IO0SET |= bit(8);
    IO0CLR |= bit(9);
    IO0SET |= bit(10);
    delay;
    IO0CLR |= bit(10);
}

void string(unsigned char *p) {
    while(*p != '\0') {
        dat(*p++);
    }
}
```

---

## 📊 Working Principle

* The **rain sensor module** consists of a nickel-coated plate and an LM393 comparator.
* When raindrops fall, the resistance decreases → comparator output goes **LOW**.
* This digital signal is read by **P1.24** of the LPC2148.
* The microcontroller displays the message **“Rain Detected!”** on the LCD.

---

## ⚡ Output

When rain is detected:

```
!Rain Detected!
```

Otherwise:

```
Alert
```

---

## 🧪 Applications

* Automatic window or roof-closing systems
* Smart irrigation control
* Weather monitoring stations
* Vehicle wiper automation

---

## 👨‍💻 Author

**Santhosh Dulam**
📍 Coimbatore, India
🎓 B.Tech – Electronics & Communication Engineering
📧 [santhosh.dulam45@gmail.com](mailto:santhosh.dulam45@gmail.com)
🔗 [LinkedIn](https://linkedin.com/in/santhosh-dulam-94b8b9242)

---

## 🪪 License

This project is open-source under the **MIT License**.

---
