/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 2  Exercise 1

 *         Exercise Description: [optional - include for your own benefit]

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *         Demo Link: https://youtu.be/RtrAS8Pe7oU

 */

const int b_size = 4;
const int b[b_size] = {2, 3, 4, 5};

//Output buffer
int b_buf = 0x00;

//Input variables
const int button1 = 8; //LED 1
const int button2 = 9; //LED 2
const int button3 = 10; //LED 3
const int button4 = 11; //LED 4
int btn1_state = 0;
int btn2_state = 0;
int btn3_state = 0;
int btn4_state = 0;

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

enum LED_States{LED_start, LED_OFF, LED_ON} LED_state;

int led = 0;

void Tick_LED(){//Transition
  switch(LED_state){
    case LED_start:
      LED_state = LED_OFF;
      break;
    case LED_OFF:
      if((btn1_state||btn2_state||btn3_state||btn4_state) == LOW){
        LED_state = LED_OFF;
      }
      else if(btn1_state == HIGH){
        LED_state = LED_ON;
        led = 0x01;
      }
      else if(btn2_state == HIGH){
        LED_state = LED_ON;
        led = 0x02;
      }
      else if(btn3_state == HIGH){
        LED_state = LED_ON;
        led = 0x04;
      }
      else if(btn4_state == HIGH){
        LED_state = LED_ON;
        led = 0x08;
      }
      break;
    case LED_ON:
      if((btn1_state||btn2_state||btn3_state||btn4_state) == HIGH){
        LED_state = LED_OFF;
      }
      else{
        LED_state = LED_ON;
      }
      break;
    default:
      LED_state = LED_start;
      break;
  }
  
  switch(LED_state){//State Actions
    case LED_start:
      break;
    case LED_OFF:
      resetBuffer();
      break;
    case LED_ON:
      writeBuffer(led);
    default:
      break;
  }
}

void setup()
{
  for(int i = 0; i < b_size; i++){
    pinMode(b[i], OUTPUT);
  }
  
  pinMode(button1, INPUT);
  pinMode(button2, INPUT);
  pinMode(button3, INPUT);
  pinMode(button4, INPUT);
  
  Serial.begin(9600);
  // this line is essential for the arduino to communicate properly with your computer
}

void loop()
{
  btn1_state = digitalRead(button1);
  btn2_state = digitalRead(button2);
  btn3_state = digitalRead(button3);
  btn4_state = digitalRead(button4);
  
  Tick_LED();
  delay(200);
}