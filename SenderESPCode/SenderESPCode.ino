#include <Wire.h>
#include <MPU6050.h>
#include<esp_now.h>
#include<WiFi.h>

MPU6050 mpu;

uint8_t RxMACaddress[]={0xD8, 0xBC, 0X38, 0XFD, 0X82, 0XC0};
//D8:BC:38:FD:82:C0 -- WROOM
//AC:67:B2:71:5C:1C -- WROVER 
int16_t ax, ay, az;
int16_t gx, gy, gz;
int sensitivity = 16384; // Sensitivity scale factor for MPU6050

typedef struct TxStruct
{
  int x_direction;
  //int y_direction;
}TxStruct;
TxStruct sentData;

void OnDataSent (const uint8_t *mac_addr, esp_now_send_status_t status)
{
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}


void setup() {
  Serial.begin(9600);
  Wire.begin();
  WiFi.mode(WIFI_STA);
  
  // Initialize MPU6050
  mpu.initialize();
  mpu.setFullScaleGyroRange(MPU6050_GYRO_FS_250);

  if(esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
   esp_now_register_send_cb(OnDataSent);
  esp_now_peer_info_t peerInfo;
  memcpy(peerInfo.peer_addr, RxMACaddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  if(esp_now_add_peer(&peerInfo) != ESP_OK)
  {
    Serial.println("Failed to add peer");
    return;
  }


}


void loop() {
  // Read accelerometer and gyroscope data
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
  

  sentData.x_direction = x_direction;
  sentData.y_direction = y_direction;
  
  esp_err_t result = esp_now_send(RxMACaddress, (uint8_t *) &sentData, sizeof(sentData));

    if (result == ESP_OK) Serial.println("Sent with success");
  else Serial.println("Error sending the data");

  delay(100);
}