/*        Your Name & E-mail: Diego Vega - dvega007@ucr.edu

 *         Discussion Section: B21

 *         Assignment: Lab 2  Exercise 3

 *         Exercise Description: [optional - include for your own benefit]

 *         I acknowledge all content contained herein, excluding template or example code, is my own original work.

 *         Demo Link: https://youtu.be/8e0DnjjzevE

 */

int btn1 = 8;
int btn2 = 9;
int btn3 = 10;
int btn4 = 11;
int led1 = 2;
int led2 = 3;
int led3 = 4;
int led4 = 5;

//assigning names to the pins that are in use
int leds[4] = {led1, led2, led3, led4};

int btn1_state = 0;
int btn2_state = 0;
int btn3_state = 0;
int btn4_state = 0;
int led1_state = 0;
int led2_state = 0;
int led3_state = 0;
int led4_state = 0;

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(led4, OUTPUT);
  pinMode(btn1, INPUT);
  pinMode(btn2, INPUT);
  pinMode(btn3, INPUT);
  pinMode(btn4, INPUT);

// this is how we initialize our pins in arduino, the LEDS are outputs and the buttons are intputs
  Serial.begin(9600); 
}
enum States{INIT,MOD1, S0, S1, MOD2, S3, S4, S5, WAIT} SM1_state = INIT;

int blink(int x){
  //Serial.println(x);
  if(x > 240){
    delay(1000);
  }
  else if(x >= 200 && x <= 240){
    delay(500);
  }
  else if(x >= 150 && x <= 199){
    delay(250);
  }
  else if(x <= 149){
    delay(50);
  }
}

int SM1_Tick(int state){
    int led = 0;
    //Serial.println(b_buf);
    switch(state){ // State transitions
      case INIT:
        state = MOD1;
        break;
      case MOD1:
        if(btn1_state == HIGH){
          state = S0;
        }
        else if(btn2_state == HIGH){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          state = MOD2;
        }
        break;
      case S0:
        if(analogRead(A0) >= 240 || analogRead(A0) <= 100){
            state = S0;
        }
        else{
            state = S1;
        }

        if(btn2_state == HIGH){
          digitalWrite(led1, HIGH);
          digitalWrite(led2, LOW);
          digitalWrite(led3, LOW);
          digitalWrite(led4, LOW);
          state = MOD2;
        }
        break;
      case S1:
        if(analogRead(A0) >= 240 || analogRead(A0) <= 100){
            state = S0;
        }
        else{
            state = S1;
        }
        break;
        case MOD2:
          Serial.println(btn4_state);
          if(btn3_state == HIGH){
            state = S4;
          }else if(btn4_state == HIGH){
            state = S3;
          }
          break;
        case S3:
          Serial.println(btn4_state);
          if((led1_state == HIGH)&&(btn4_state == HIGH)){
            digitalWrite(led1, LOW);
            digitalWrite(led2, HIGH);
            state = S3;
          }else if((led2_state == HIGH)&&(btn4_state == HIGH)){
            digitalWrite(led2, LOW);
            digitalWrite(led3, HIGH);
            state = S3;
          }else if((led3_state == HIGH)&&(btn4_state == HIGH)){
            digitalWrite(led3, LOW);
            digitalWrite(led4, HIGH);
            state = S3;
          }else if((led4_state == HIGH)&&(btn4_state == HIGH)){
            digitalWrite(led4, LOW);
            digitalWrite(led1, HIGH);
            state = S3;
          }else{
            state = S5;
          }
          break;
        case S4:
          if((led1_state == HIGH)&&(btn3_state == HIGH)){
            digitalWrite(led1, LOW);
            digitalWrite(led4, HIGH);
            state = S4;
          }else if((led4_state == HIGH)&&(btn3_state == HIGH)){
            digitalWrite(led4, LOW);
            digitalWrite(led3, HIGH);
            state = S4;
          }else if((led3_state == HIGH)&&(btn3_state == HIGH)){
            digitalWrite(led3, LOW);
            digitalWrite(led2, HIGH);
            state = S4;
          }else if((led2_state == HIGH)&&(btn3_state == HIGH)){
            digitalWrite(led2, LOW);
            digitalWrite(led1, HIGH);
            state = S4;
          }else{
            state = S5;
          }
          break;
        case S5:
          if(btn4_state == HIGH){
            state = S3;
          }else if(btn3_state == HIGH){
            state = S4;
          }else if((btn1_state == HIGH)||(btn2_state == HIGH)){
            state = MOD1;
          }else{
            //state = S0;
          }
          break;
        default:
          state = MOD1;
          break;
    }
    switch(state){ // State Action
      case INIT:
        break;
      case MOD1:
        //state = S0;
        break;
      case S0:
        for(int i = 0; i < 4; i++){
          digitalWrite(leds[i],HIGH);
        }
        break;
      case S1:
        for(int i = 0; i < 4; i++){
          digitalWrite(leds[i],LOW);
        }
        break;
      case MOD2:
        break;
      case S3:
        break;
      case S4:
        break;
      default:
        break;
    }
    //Serial.println(analogRead(A0));
    blink(analogRead(A0));
    return state;
}
void loop() {
  btn1_state = digitalRead(btn1);
  btn2_state = digitalRead(btn2);
  btn3_state = digitalRead(btn3);
  btn4_state = digitalRead(btn4);
  led1_state = digitalRead(led1);
  led2_state = digitalRead(led2);
  led3_state = digitalRead(led3);
  led4_state = digitalRead(led4);

  //this state machine reads the photoresistor every second and turns on the leds if it is "dark"
  SM1_state = (States)SM1_Tick(SM1_state);
  //Serial.println(btn4_state);
}