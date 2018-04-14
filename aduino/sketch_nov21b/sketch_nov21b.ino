#include <SoftwareSerial.h>
#include <dht11.h>
#include <Servo.h>
#include "U8glib.h"

#define BT_TXD 2
#define BT_RXD 3
#define HOT_LED 4
#define COOL_LED 5
#define LIHGT_LED 6
#define DHT11PIN 7
#define RUN_VALVE 8
#define RUN_HOT 9
#define VALUE_LOCK 74

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE);
SoftwareSerial BTSerial(BT_TXD, BT_RXD); //블루투스 클래스
unsigned int rst;
//unsigned int rst2;
dht11 DHT11;  //온습도 센서 클래스
int temperature;
Servo s;
char tooth;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  pinMode(HOT_LED,OUTPUT);
  pinMode(LIHGT_LED,OUTPUT);
  pinMode(COOL_LED,OUTPUT);
  pinMode(RUN_HOT,OUTPUT);
  rst=0;
  //rst2=0;
  if(DHT11.read(DHT11PIN)==0){
    temperature=DHT11.temperature;
  }
  s.attach(RUN_VALVE, 544, 2400);

  //digitalWrite(LIHGT_LED, HIGH);
}

void loop() {
  u8g.firstPage();
  
  int chk=DHT11.read(DHT11PIN);
  if(chk==0){
    
     do{
        u8g.setFont(u8g_font_unifont);
        u8g.setPrintPos(0,10);
        u8g.print("!!!Smart Home!!!");
        u8g.drawStr(0,30, "properTmp:");
        u8g.setPrintPos(100,30); //픽셀단위라 x를 작게 잡아주면 글씨가 겹칩니다
        u8g.print(temperature);
         u8g.drawStr(0,50, "currentTmp:");
        u8g.setPrintPos(100,50); //픽셀단위라 x를 작게 잡아주면 글씨가 겹칩니다
        u8g.print(DHT11.temperature);
    }while(u8g.nextPage());
    
    //Serial.println(temperature);
  //Serial.println(DHT11.humidity);
  //  Serial.println(DHT11.temperature);
  }
  tooth=BTSerial.read();
  
  if(tooth=='a'){
    s.detach();
    tooth=NULL;
    Serial.write(BTSerial.read());    
    digitalWrite(LIHGT_LED, HIGH);
    rst=0;
    //rst2=0;

    if(chk==0){
     if( DHT11.temperature >= temperature+1){
      Serial.println("1111111");
      digitalWrite(COOL_LED, HIGH);
      digitalWrite(HOT_LED, LOW);
      digitalWrite(RUN_HOT, LOW);
      }
     else if( DHT11.temperature <= temperature-1){
      Serial.println("1222222");
      digitalWrite(HOT_LED, HIGH);
      digitalWrite(RUN_HOT, HIGH);
      digitalWrite(COOL_LED, LOW);
     }
     else{
      Serial.println("33333333");
      digitalWrite(COOL_LED, LOW);
      digitalWrite(HOT_LED, LOW);
      digitalWrite(RUN_HOT, LOW);
     }
    }
  }
  else{
    Serial.println(rst);
     rst++;
     if(rst==100)
      s.attach(RUN_VALVE, 544, 2400);
     else if(rst>100){
      digitalWrite(LIHGT_LED, LOW);
      digitalWrite(COOL_LED, LOW);
      digitalWrite(HOT_LED, LOW);
      s.write(VALUE_LOCK);
     }
  }
}

