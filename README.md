# ServerGuard

An environmental monitoring shield for the Arduino Uno. It watches temperature and humidity and gives a visual and audible warning when conditions drift out of range. It's built for spaces like server rooms, where heat and moisture damage equipment.

I designed the schematic and the 2-layer PCB in KiCad 9.

## Features

- **Two sensors:** a DHT11 reads temperature and humidity, and an LM35 analog sensor gives a second temperature reading.
- **Status LEDs:** a green LED for normal conditions, plus separate yellow (warning) and red (alert) LEDs for temperature and for humidity.
- **Buzzer:** sounds an audible alarm.
- **Shield form factor:** the board stacks directly on an Arduino Uno R3, using the Uno's mounting holes. It takes power from the Uno's 5V rail.

## Hardware

| Ref | Part | Purpose |
|-----|------|---------|
| A1 | Arduino Uno R3 | Microcontroller (the shield mounts on it) |
| U1 | DHT11 | Temperature and humidity sensor |
| U3 | LM35 (SOIC-8) | Analog temperature sensor |
| D1 | Green LED | System normal |
| D2 / D3 | Yellow / red LED | Temperature warning / alert |
| D4 / D5 | Yellow / red LED | Humidity warning / alert |
| BZ1 | Buzzer (12 mm) | Audible alarm |
| R2–R7 | 220 Ω resistors | Current limiting for the LEDs and buzzer |

### Pin map

| Arduino pin | Connected to |
|-------------|--------------|
| A1 | DHT11 data |
| A2 | LM35 output |
| D8 | Yellow LED (humidity) |
| D9 | Red LED (humidity) |
| D10 | Yellow LED (temperature) |
| D11 | Red LED (temperature) |
| D12 | Green LED (normal) |
| D13 | Buzzer |
| 5V / GND | Sensor power |

## PCB

- 2 layers, about 82 × 88 mm
- +5V copper pour on the top layer and a GND pour on the bottom layer
- Through-hole LEDs, resistors and buzzer for easy hand assembly. The LM35 is surface-mount (SOIC-8).

## Repository contents

| File | Contents |
|------|----------|
| `ECCSEgroup7.kicad_pro` | KiCad project file |
| `ECCSEgroup7.kicad_sch` | Schematic |
| `ECCSEgroup7.kicad_pcb` | PCB layout |

To view the design, open `ECCSEgroup7.kicad_pro` in KiCad 9 or later.

## My role

This was a four-person team project for a college engineering course. I led the team, designed the schematic and PCB layout, wrote the Arduino firmware, and authored most of the presentation and the final report. My teammates came up with the initial concept and helped with brainstorming, Tinkercad prototyping and the presentation.
