/*
 * Arduino Yun - External LED Blink
 * Wiring: D13 -> 220/330 ohm resistor -> LED anode (+)
 *         LED cathode (-) -> GND
 * Target board FQBN: arduino:avr:yun
 *
 * The Arduino Yun uses an ATmega32U4 for the Arduino sketch.
 */

const byte LED_PIN = 13;
const unsigned long BLINK_DELAY_MS = 1000;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  delay(BLINK_DELAY_MS);
  digitalWrite(LED_PIN, LOW);
  delay(BLINK_DELAY_MS);
}
