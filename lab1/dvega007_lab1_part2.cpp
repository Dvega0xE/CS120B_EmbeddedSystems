/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 1  Exercise 2

 *         Exercise Description: [optional - include for your own benefit]

 *         We are coding this system so we can control each LED light with its respective button. (in Binary)

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link: https://youtu.be/NjRnzGZpobY

 */

const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};

//Output buffer
int b_buf = 0x00;

//Input variables

//Serial monitor buffer
int s_buf = 0x00;

const int s_size = 8;
int s[s_size];

void readData(){
  if(Serial.available())
    s_buf = Serial.parseInt();
  
  for(int i = (s_size - 1); i >= 0; i--){
    s[i] = (s_buf >> i) & 0x01;
    //Serial.println(s[i]);
  }
}

void resetBuffer(){
  for(int i = 0; i < b_size; i++){
    digitalWrite(b[i], LOW);
    //Serial.println(b[i]);
  }
}

void writeBuffer(unsigned char b_temp, int size = b_size){
  for(int i = (size - 1); i >= 0; i--){
    if((b_temp >> i) & 0x01)
      digitalWrite(b[i], HIGH);
  }
}

void setup()
{
  for(int i = 0; i < b_size; i++){
    pinMode(b[i], OUTPUT);
  }
  
  Serial.begin(9600);
  // this line is essential for the arduino to communicate properly with your computer
}

void loop()
{
  readData();
  resetBuffer();
  if(s_buf <= 0x0F && s_buf >= 0x00){
    b_buf = s_buf;
  }else
    b_buf = 0x00;
  writeBuffer(b_buf);
  delay(250);
}