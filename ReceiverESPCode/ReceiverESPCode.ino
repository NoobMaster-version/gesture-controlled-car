#include <esp_now.h>
#include <WiFi.h>
#include <Wire.h>
//-------------------------------------------------------------------------------------
typedef struct RxStruct
{
  int x_direction;
  // int y_direction;
}RxStruct;
RxStruct receivedData;
//-------------------------------------------------------------------------------------
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len)
{
  memcpy(&receivedData, incomingData, sizeof(receivedData));
}
//======================================================================================
void setup()
{
  Serial.begin(9600);
 
  //-------------------------------------------------------------------------------------
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK)
  {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);
}
//======================================================================================
void loop()
{
  Serial.print("X Direction: ");
  Serial.println(receivedData.x_direction);
  // Serial.print("Y Direction: ");
  // Serial.println(receivedData.y_direction);

  delay(100);
}
