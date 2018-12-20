#include <Wire.h>
#include <string.h>
#include <stdio.h>
#define SLAVE 0x04

unsigned int pwm_motor_vals[8];


void setup() {
  Serial.begin(30720); //Start Serial output and commmunication at baud of 30720
  Wire.begin(SLAVE); //begin wired communication

  Wire.onReceive(receiveDataStream); //Define a cqallback function
}

void loop() {
  delay(10); //Delay, not necessary in all cases
}

void receiveDataStream(int byteCount) {
  char str[32]; //cstring for all hex characters


  //Start populating the new array of hex values
  while (Wire.available()) {
    int i = 0;
    str[i] = Wire.read();
    i++;
  }

  //begin delimiter use, declare the token char and the delimiter used
  char* token;
  const char s[2] = "-";
  token = strtok(str, s);
  int j = 0;
  while (token != NULL) {

    pwm_motor_vals[j] = Hex_to_UInt(token);
    token = strtok(NULL, s);

    j++;
  }
  return (0);

}

int Hex_to_UInt(char str[])
{
  return (int) strtol(str, 0, 16);
}
