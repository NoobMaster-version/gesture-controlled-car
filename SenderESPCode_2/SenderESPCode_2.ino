#include <WiFi.h>
#include <esp_now.h>
#include <MPU6050.h>

MPU6050 mpu;

int x_direction;
int y_direction;

uint8_t broadcastAddress[] = {0xAC, 0x67, 0XB2, 0X72, 0XA6, 0XD0};
//A8:42:E3:A9:E2:88
//AC:67:B2:72:A6:D0

int16_t ax, ay, az;
int16_t gx, gy, gz;
int sensitivity = 16384;

typedef struct struct_message {
  float a;
  float b;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

void OnDataSent(const uint8_t *macAddr, esp_now_send_status_t status)
{
  Serial.print("Last Packet Send Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}
 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  delay(100);
  Wire.begin();
  mpu.initialize();
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);

   WiFi.mode(WIFI_STA);
 if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
   esp_now_register_send_cb(OnDataSent);
 
 
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;
 
  if (esp_now_add_peer(&peerInfo) != ESP_OK) {
    Serial.println("Failed to add peer");
    return;
  }

}

void loop() {
  // put your main code here, to run repeatedly:
   mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Calculate angles from accelerometer data
  float accel_angle_x = atan2(ay, az) * 180 / M_PI;
  float accel_angle_y = atan2(ax, az) * 180 / M_PI;

  // Print angles to serial monitor
  Serial.print("X Angle: ");
  Serial.println(accel_angle_x);
  Serial.print("Y Angle: ");
  Serial.println(accel_angle_y);

  // Determine movement direction
  int x_direction;
  int y_direction;
  if (accel_angle_x > 40) //move right
    x_direction = 1;
  else if (accel_angle_x < -40) // move left
    x_direction = -1;
  else
    x_direction = 0;


  if (accel_angle_y > 40)  // move backward
    y_direction = 1;
  else if (accel_angle_y < -40) //move forward
    y_direction = -1;
  else
    y_direction = 0;

  // Print movement direction
  Serial.print("X Direction: ");
  Serial.println(x_direction);
  Serial.print("Y Direction: ");
  Serial.println(y_direction);

  myData.a = x_direction;
  myData.b = y_direction;

   esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));
 delay(50);
}