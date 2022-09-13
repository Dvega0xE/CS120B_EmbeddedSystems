/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 1  Exercise 4

 *         Exercise Description: [optional - include for your own benefit]

 *         We are coding this system so we can control each LED light with its respective buttons.
 		   (button 1 toggles on/off LED 1, button 2 toggles on/off LED2, etc.)

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *

 *         Demo Link: https://youtu.be/_naEq-VqmNY

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
int lastBtn_state1 = 0;

//Serial monitor buffer
int s_buf = 0x00;

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

enum LED_States{LED_start, LED_unlit1, LED_lit1, LED_unlit2, LED_lit2,
               LED_unlit3, LED_lit3, LED_unlit4, LED_lit4} LED_state;

void Tick_LED(){
  switch(LED_state){
    case LED_start:
    if(btn1_state == HIGH)
    	LED_state = LED_lit1;
    if(btn2_state == HIGH)
      	LED_state = LED_lit2;
    if(btn3_state == HIGH)
    	LED_state = LED_lit3;
    if(btn4_state == HIGH)
      	LED_state = LED_lit4;
    	break;
    case LED_unlit1:
    if(btn1_state == LOW){
      LED_state = LED_start;
    }
    else
      LED_state = LED_lit1;
    	break;
    case LED_lit1:
    if(btn1_state == HIGH){
      LED_state = LED_unlit1;
    }
    else{
      LED_state = LED_lit1;
    }
    	break;
    case LED_unlit2:
    if(btn2_state == LOW){
      LED_state = LED_start;
    }
    else
      LED_state = LED_lit2;
    	break;
    case LED_lit2:
    if(btn2_state == HIGH){
      LED_state = LED_unlit2;
    }
    else
      LED_state = LED_lit2;
    	break;
    case LED_unlit3:
    if(btn3_state == LOW){
      LED_state = LED_start;
    }
    else
      LED_state = LED_lit3;
    	break;
    case LED_lit3:
    if(btn3_state == HIGH){
      LED_state = LED_unlit3;
    }
    else
      LED_state = LED_lit3;
    	break;
    case LED_unlit4:
    if(btn4_state == LOW){
      LED_state = LED_start;
    }
    else
      LED_state = LED_lit4;
    	break;
    case LED_lit4:
    if(btn4_state == HIGH){
      LED_state = LED_unlit4;
    }
    else
      LED_state = LED_lit4;
    	break;
    default:
    	LED_state = LED_start;
    	break;
  }//Transition
  
  switch(LED_state){
    case LED_start:
    	break;
    case LED_unlit1:
    	b_buf = 0x00;
    	break;
    case LED_lit1:
    	b_buf = 0x01;
    	break;
    case LED_unlit2:
    	b_buf = 0x00;
    	break;
    case LED_lit2:
    	b_buf = 0x02;
    	break;
    case LED_unlit3:
    	b_buf = 0x00;
    	break;
    case LED_lit3:
    	b_buf = 0x04;
    	break;
    case LED_unlit4:
    	b_buf = 0x00;
    	break;
    case LED_lit4:
    	b_buf = 0x08;
    	break;
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
  resetBuffer();
  writeBuffer(b_buf);
  delay(250);
  //Serial.println(LED_state);
}