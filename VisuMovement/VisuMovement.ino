#include <ESP8266WiFi.h>
#include <WebSocketsServer.h>
#include <Wire.h>
#include <MPU6050.h>

const char* ssid = "YOUR_SSID";
const char* password = "YOUR_PASSWORD";

MPU6050 mpu;
WebSocketsServer webSocket = WebSocketsServer(81);

unsigned long lastSend = 0;
const unsigned long sendInterval = 50; // milliseconds

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }

  Wire.begin(D2, D1); // SDA, SCL
  mpu.initialize();
  mpu.setSleepEnabled(false);
  mpu.setFullScaleAccelRange(MPU6050_ACCEL_FS_2);
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);

  webSocket.begin();
  webSocket.onEvent(webSocketEvent);
}

void webSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // handle incoming messages if needed
}

void loop() {
  webSocket.loop();

  if (millis() - lastSend >= sendInterval) {
    lastSend = millis();

    int16_t ax, ay, az;
    int16_t gx, gy, gz;
    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

    String msg = "{";
    msg += "\"ax\":" + String(ax) + ",";
    msg += "\"ay\":" + String(ay) + ",";
    msg += "\"az\":" + String(az) + ",";
    msg += "\"gx\":" + String(gx) + ",";
    msg += "\"gy\":" + String(gy) + ",";
    msg += "\"gz\":" + String(gz) + "}";

    webSocket.broadcastTXT(msg);
  }
}