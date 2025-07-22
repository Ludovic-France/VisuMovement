VisuMovement is a simple demo that visualizes motion data from an ESP8266 connected to an MPU6050 inertial sensor. The ESP8266 streams orientation and acceleration information over a WebSocket and the browser renders a 3D model using Three.js.

![Visualization screenshot](screenshot.png)

## Architecture

1. **ESP8266 + MPU6050** – reads sensor data and sends JSON packets over a WebSocket on port `81`.
2. **WebSocket** – packets contain roll, pitch, yaw and raw acceleration values.
3. **Browser** – `index.html` connects to the ESP8266 WebSocket and updates a 3D box to match the orientation.

## Prerequisites

- Arduino IDE with **ESP8266** board support installed.
- Libraries: `ESP8266WiFi`, `WebSocketsServer`, `Wire`, and `MPU6050_tockn` (available via the Arduino Library Manager).
- Connect the MPU6050:
  - `VCC` → `3.3V`
  - `GND` → `G`
  - `SCL` → `D1`
  - `SDA` → `D2`

## Flashing the ESP8266

1. Open `firmware/esp8266_mpu6050_websocket/esp8266_mpu6050_websocket.ino` in the Arduino IDE.
2. Update `ssid` and `password` with your Wi‑Fi credentials.
3. Select your ESP8266 board and the correct COM/USB port.
4. Click **Upload** to flash the firmware.

Once the board is connected to Wi‑Fi, note its IP address from the serial monitor.

## Serving the Web UI

Run a small web server in this directory and open the page in your browser:

```bash
python3 -m http.server 8000
```

Then browse to `http://<your-computer-ip>:8000/index.html`. The page will attempt to connect to `ws://<esp8266-ip>:81/` automatically. When the connection is established you should see the 3D box move as you move the sensor. Use the slider to filter acceleration and the **Réinitialiser** button to calibrate.
