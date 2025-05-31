#include <WiFi.h>
#include <esp_now.h>

#define rightmotor1 12 
#define rightmotor2 14 
#define rightmotorEn 33 
#define leftmotor1 27 
#define leftmotor2 26 
#define leftmotorEn 32 

int x_direction;
int y_direction;

typedef struct struct_message {
    float a;
    float b;
} struct_message;
 struct_message myData;
void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) 
{
   memcpy(&myData, incomingData, sizeof(myData));
  Serial.print("X_direction : ");
  Serial.println(myData.a); 
  Serial.print("Y_Direction : ");
  Serial.println(myData.b); 
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  esp_now_register_recv_cb(OnDataRecv);

  pinMode(rightmotor1,OUTPUT); 
  pinMode(rightmotor2,OUTPUT);
  pinMode(rightmotorEn,OUTPUT); 
  pinMode(leftmotor1,OUTPUT); 
  pinMode(leftmotor2,OUTPUT);
  pinMode(leftmotorEn,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
 x_direction=myData.a;
 y_direction=myData.b;
 
  if (y_direction==-1)
  {
    if(x_direction==1)
    {
    forward();
    delay(100);
    right();
    }
    else if(x_direction==-1)
   { 
    forward();
    delay(100);
    left();
  }
    else if(x_direction==0)
    {
    forward();
    }
  } 
 else if (y_direction==1)
  {
     if(x_direction==1)
   {
    backward();
    delay(100);
    right();
   }
    else if(x_direction==-1)
    {
    backward();
    delay(100);
    left();
    }
    else if(x_direction==0)
    backward();
    //digitalWrite(leftmotorEn,LOW);
  }
 else if (y_direction==0)
 {
   if(x_direction==1)
     right();
    else if(x_direction==-1)
     left();
    else if(x_direction==0)
   {
    digitalWrite(leftmotorEn,LOW);
    digitalWrite(rightmotorEn,LOW);
 }
 }

}

void forward()
 {
  digitalWrite(rightmotor1,HIGH);
  digitalWrite(rightmotor2,LOW);
  digitalWrite(rightmotorEn,HIGH);
  
  digitalWrite(leftmotor1,HIGH);
  digitalWrite(leftmotor2,LOW);
  digitalWrite(leftmotorEn,HIGH);
 }
void backward()
 {
  digitalWrite(rightmotor1,LOW);
  digitalWrite(rightmotor2,HIGH);
  digitalWrite(rightmotorEn,HIGH);
  
  digitalWrite(leftmotor1,LOW);
  digitalWrite(leftmotor2,HIGH);
  digitalWrite(leftmotorEn,HIGH);
 }
void left()
 {
  digitalWrite(rightmotor1,HIGH);
  digitalWrite(rightmotor2,LOW);
  digitalWrite(rightmotorEn,HIGH);
  
  digitalWrite(leftmotor1,LOW);
  digitalWrite(leftmotor2,LOW);
  digitalWrite(leftmotorEn,LOW);
 }
void right()
 {
  digitalWrite(rightmotor1,LOW);
  digitalWrite(rightmotor2,LOW);
  digitalWrite(rightmotorEn,LOW);
  
  digitalWrite(leftmotor1,HIGH);
  digitalWrite(leftmotor2,LOW);
  digitalWrite(leftmotorEn,HIGH);
 }
