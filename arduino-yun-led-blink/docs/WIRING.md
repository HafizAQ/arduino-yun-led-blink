# Wiring the Arduino Yún to one external LED

Disconnect the USB cable while wiring.

## Parts
- Arduino Yún (original Arduino Yún, not Yún Shield)
- Small breadboard
- One red LED
- One 220 Ω or 330 Ω resistor (330 Ω recommended)
- Two male-to-male jumper wires
- Micro-USB *data* cable

## Circuit

```text
Arduino Yún D13 ---- [330 Ω resistor] ---- LED long leg (anode, +)
Arduino Yún GND -------------------------- LED short leg (cathode, -)
```

The resistor and LED are in **series**. Do not wire the LED directly between 5V and GND.

## Exact example breadboard holes

These holes are an example for a standard breadboard, where **a–e holes of each numbered row are connected** and row 10 is isolated from row 11 and row 15. Confirm the markings on your own breadboard.

1. Put LED long leg into **e10**.
2. Put LED short leg into **e11**.
3. Put one leg of the resistor into **a10** and its other leg into **a15**.
4. Run a jumper from **Yún D13** to **b15**.
5. Run a jumper from **Yún GND** to **a11**.
6. Check that the LED legs are in separate numbered rows, the resistor bridges rows 10 and 15, and the two jumper wires are in the intended rows.
7. Reconnect USB to power and program the Yún.

If your breadboard has a different pattern, follow the circuit diagram instead of the row numbers. For a common breadboard, a–e in a numbered row connect to each other, f–j in the same numbered row connect to each other, but the center groove separates the two groups.

## Expected result
The external LED switches ON for 1 second and OFF for 1 second. The onboard D13 LED may blink too.

## Troubleshooting
- LED always dark: reverse LED orientation (with power disconnected), confirm GND and D13 labels, verify series resistor path, and re-upload.
- LED always on: check that code was uploaded rather than merely compiled.
- Resistor: use 220 Ω or 330 Ω, not 0 Ω; color bands vary by resistor tolerance.
- Port not found: try a known data-capable cable, reconnect USB, and run `arduino-cli board list`.
