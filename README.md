# Arduino Yún LED Blink — VS Code Beginner Project

A fully documented **first hardware project**: blink an external LED on a breadboard using the **Arduino Yún**, edit code in **Visual Studio Code**, compile/upload with **Arduino CLI**, and track the project with **Git/GitHub**.

> **Hardware status:** The blink sketch has already been successfully demonstrated by the project owner in Arduino IDE. The VS Code task configuration in this repository has not been independently tested on the owner's computer; check your USB port before uploading.

## Learning objectives
- Identify the LED anode (+), cathode (−), digital pin 13, and ground.
- Use a 220–330 Ω current-limiting resistor in series.
- Understand Arduino `setup()`, `loop()`, `pinMode()`, `digitalWrite()`, and `delay()`.
- Compile and upload from VS Code with Arduino CLI.
- Publish source files to GitHub.

## Project layout

```text
arduino-yun-led-blink/
├── ArduinoYunLedBlink/
│   └── ArduinoYunLedBlink.ino   # Main Arduino sketch
├── .vscode/
│   ├── tasks.json               # VS Code Compile / Upload tasks
│   └── extensions.json          # Optional C++ editor support
├── docs/
│   └── WIRING.md                # Detailed breadboard connections
├── .gitignore
├── LICENSE
└── README.md
```

## Parts needed

| Component | Quantity | Purpose |
|---|---:|---|
| Arduino Yún | 1 | Microcontroller board |
| Breadboard | 1 | Solderless circuit connections |
| LED | 1 | Visible output |
| 220 Ω or 330 Ω resistor | 1 | Limits LED current |
| Jumper wires | 2 | D13 and GND connections |
| Micro-USB data cable | 1 | Power and program over USB |

## Wiring

**Power off / disconnect USB before wiring.**

```text
Arduino Yún digital D13
      |
      +---- [330 Ω resistor] ---- (+) LED (-) ---- Arduino Yún GND
```

On the LED, the **longer lead is typically the positive anode**, while the **shorter lead/flat edge marks the negative cathode**. The wiring must include a series resistor. See [the exact breadboard-row example](docs/WIRING.md).

## Main code

Open [`ArduinoYunLedBlink/ArduinoYunLedBlink.ino`](ArduinoYunLedBlink/ArduinoYunLedBlink.ino):

```cpp
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
```

`setup()` runs once; `loop()` runs continuously. `HIGH` switches D13 on; `LOW` switches it off. `delay(1000)` waits **1000 milliseconds (1 second)**. Each cycle is 2 seconds (1 on + 1 off), or about **30 on/off cycles per minute**.

## Run in Visual Studio Code

### 1. Install the software

1. Install **Visual Studio Code** from https://code.visualstudio.com/.
2. Install the official **Arduino CLI** following https://docs.arduino.cc/arduino-cli/installation/.
3. In a new terminal (VS Code: **Terminal → New Terminal**) run:

   ```sh
   arduino-cli version
   arduino-cli core update-index
   arduino-cli core install arduino:avr
   ```

   `arduino:avr` installs the AVR board support package. The board **FQBN** (Fully Qualified Board Name) for the original Yún is **`arduino:avr:yun`**.

4. Connect the Yún using a micro-USB **data** cable.

### 2. Open the repository folder in VS Code

1. Download/extract the project archive.
2. In VS Code select **File → Open Folder...**.
3. Open the outer folder **`arduino-yun-led-blink`** (not just the `.ino` file).
4. In the left-hand **Explorer**, click **`ArduinoYunLedBlink` → `ArduinoYunLedBlink.ino`** to see and edit the Arduino code. Save using **Ctrl+S** (Windows/Linux) or **Cmd+S** (macOS).

### 3. Find the USB port

Open **Terminal → Run Task... → Arduino: list connected boards**, or run:

```sh
arduino-cli board list
```

Record the detected port, e.g., `COM3` (Windows) or `/dev/ttyACM0` (Linux). The port depends on your computer; **do not assume COM3**. On macOS it may be `/dev/cu.usbmodem...`.

### 4. Compile (verify)

Press **Ctrl+Shift+B** (Windows/Linux) / **Cmd+Shift+B** (macOS), or choose **Terminal → Run Task... → Arduino Yún: compile**.

Equivalent terminal command (run from the outer project directory):

```sh
arduino-cli compile --fqbn arduino:avr:yun ArduinoYunLedBlink
```

This checks/builds the code; it does not upload to the board.

### 5. Upload to Arduino Yún

In VS Code, select **Terminal → Run Task... → Arduino Yún: compile and upload (USB)**. When prompted, enter the actual detected USB port (`COM3` is only an example).

Equivalent command (replace `COM3` with your port):

```sh
arduino-cli compile --fqbn arduino:avr:yun --upload --port COM3 ArduinoYunLedBlink
```

The Yún will run the new sketch once upload completes. The external LED should blink one second ON, then one second OFF, repeatedly.

**Note:** We use Arduino CLI rather than relying on a specific VS Code Arduino extension, so that the build steps work independently of extension availability. The optional C/C++ extension improves editing but is **not required** to compile.

## Experiment: change the blink rate

Open the `.ino` file and change:

```cpp
const unsigned long BLINK_DELAY_MS = 1000;
```

to `500` (half-second ON and half-second OFF) or `200` (fast blinking). Save, compile, then **upload again** to observe the change. Editing alone does not update the board.

## Troubleshooting

| Symptom | What to check |
|---|---|
| `Missing FQBN` | Compile using `--fqbn arduino:avr:yun` or the included task |
| `arduino-cli: command not found` | Install Arduino CLI, then restart VS Code / confirm it is on PATH |
| `platform not installed` | Run `arduino-cli core update-index` and `arduino-cli core install arduino:avr` |
| `No port found` | USB data cable, USB connection, `arduino-cli board list`, device permissions |
| Upload fails | Correct USB port, Yún board selection, other applications holding the port |
| LED dark | LED polarity, series resistor, D13 pin, GND connection, upload success |
| LED never changes | Make sure you **uploaded**, not only compiled; check wiring |

## Publish to GitHub

### Option A: GitHub website (easiest)

1. Sign in to https://github.com/.
2. Click **New repository** and name it `arduino-yun-led-blink`.
3. Choose **Public** or **Private** and create the empty repository (do not pre-add a README/license because this project already contains them).
4. On the repository page select **Add file → Upload files**. Upload the extracted project contents, retaining the `ArduinoYunLedBlink`, `docs`, and `.vscode` directories. Some browser upload flows may not retain hidden `.vscode` folder reliably; use Option B if needed.
5. Select **Commit changes**.

### Option B: Git command line (recommended)

From the project root in VS Code **Terminal**:

```sh
git init
git add .
git commit -m "Initial commit: Arduino Yun LED blink"
git branch -M main
git remote add origin https://github.com/YOUR_USERNAME/arduino-yun-led-blink.git
git push -u origin main
```

Create an **empty** GitHub repository first and replace `YOUR_USERNAME` with your username. Authenticate using Git Credential Manager / browser login or an appropriate GitHub credential method; do not paste a password/token into this project.

## Scope and important notes

- This project uses the Yún's **ATmega32U4 Arduino microcontroller**, not its Linux environment, Wi-Fi, or Bridge library.
- Works with an **original Arduino Yún** and the corresponding `arduino:avr:yun` board package; other variants may need different settings.
- Always disconnect USB when changing circuit connections.
- The VS Code project is designed to compile and upload using Arduino CLI; a successful upload on your actual PC depends on correct tool installation, drivers, and port selection.

## Official references

- [Arduino CLI getting started](https://docs.arduino.cc/arduino-cli/getting-started/)
- [Arduino CLI compile command](https://docs.arduino.cc/arduino-cli/commands-reference/arduino-cli_compile/)
- [Arduino CLI upload command](https://docs.arduino.cc/arduino-cli/commands-reference/arduino-cli_upload/)
- [Visual Studio Code download](https://code.visualstudio.com/)

## License

MIT — see [LICENSE](LICENSE).
