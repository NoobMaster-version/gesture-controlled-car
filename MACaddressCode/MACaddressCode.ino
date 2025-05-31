#include<WiFi.h>
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_MODE_STA);
  Serial.println(WiFi.macAddress());

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(WiFi.macAddress());
  delay(5000);
}
