#include <wiringPi.h>
#include <stdio.h>

void TurnOnL(){
	int gpio = 3;
	digitalWrite(gpio,HIGH);
	pinMode(gpio,OUTPUT);
	printf("turn on light");
}

void TurnOffL(){
	int gpio =3;
	pinMode(gpio,OUTPUT);
	digitalWrite(gpio,LOW);
	printf("turn off light");
}

