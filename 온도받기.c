#ifndef SENSORVALUE_C
#define SENSORVALUE_C

#include wiringPi.h
#include stdio.h
#include stdlib.h
#include stdint.h




int Read_SensorValue()
{
   int dht11_dat[5] = { 0, };

   uint8_t laststate = HIGH;
   uint8_t counter = 0;
   uint8_t j = 0, i;
   uint8_t flag = HIGH;
   uint8_t state = 0;
   float f;

   dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
   pinMode(7, OUTPUT);
   digitalWrite(7, LOW);
   delay(18);
   digitalWrite(7, HIGH);
   delayMicroseconds(30);
   pinMode(7, INPUT);

   for (i = 0; i  83; i++) {
      counter = 0;
      while (digitalRead(7) == laststate) {
         counter++;
         delayMicroseconds(1);
         if (counter == 200) break;
      }

      laststate = digitalRead(7);

      if (counter == 200) break; 
      if ((i = 4) && (i % 2 == 0)) {
         dht11_dat[j  8] = 1;
         if (counter  20) dht11_dat[j  8] = 1;
         j++;
      }
   }
   if ((j = 40) && (dht11_dat[4] == ((dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xff))) {
      return dht11_dat[2];
   }
   else {
      printf(Data get failed ! n);
      return;
   }
}

#endif 