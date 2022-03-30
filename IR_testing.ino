#include <Wire.h>                 // code library for I2C intercase to motor shield ( via SDA / SDL pins )
#include <Adafruit_MotorShield.h> // code library for the motor shield

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *brMotor = AFMS.getMotor(1);
Adafruit_DCMotor *blMotor = AFMS.getMotor(2);
Adafruit_DCMotor *frMotor = AFMS.getMotor(3);
Adafruit_DCMotor *flMotor = AFMS.getMotor(4);


//-------------------------FUNCTIONS-------------------------------------------------------------------------
char button_pressed;
uint8_t i;
unsigned long LastCode;
  
// function to move up tree 
void up(uint8_t i) {
  flMotor->run(FORWARD);
  flMotor->setSpeed(i);
    
  brMotor->run(FORWARD);
  brMotor->setSpeed(i);
    
  frMotor->run(BACKWARD);
  frMotor->setSpeed(i);
    
  blMotor->run(BACKWARD);
  blMotor->setSpeed(i);

  delay(3000);

  flMotor->run(RELEASE);
  brMotor->run(RELEASE);
  frMotor->run(RELEASE);
  blMotor->run(RELEASE);
}
  
// function to move down tree
void down(uint8_t i) {
  flMotor->run(BACKWARD);
  flMotor->setSpeed(i);
    
  brMotor->run(BACKWARD);
  brMotor->setSpeed(i);
    
  frMotor->run(FORWARD);
  frMotor->setSpeed(i);
    
  blMotor->run(FORWARD);
  blMotor->setSpeed(i);

  delay(3000);

  flMotor->run(RELEASE);
  brMotor->run(RELEASE);
  frMotor->run(RELEASE);
  blMotor->run(RELEASE);
    
}
  
// function to move anticlockwise 
void right(uint8_t i) {
  flMotor->run(FORWARD);
  flMotor->setSpeed(i);
    
  brMotor->run(FORWARD);
  brMotor->setSpeed(i);
      
  frMotor->run(FORWARD);
  frMotor->setSpeed(i);
      
  blMotor->run(FORWARD);
  blMotor->setSpeed(i);

  delay(3000);

  flMotor->run(RELEASE);
  brMotor->run(RELEASE);
  frMotor->run(RELEASE);
  blMotor->run(RELEASE); 
}
  
// function to move clockwise
void left(uint8_t i) {
  flMotor->run(BACKWARD);
  flMotor->setSpeed(i);
      
  brMotor->run(BACKWARD);
  brMotor->setSpeed(i);
      
  frMotor->run(BACKWARD);
  frMotor->setSpeed(i);
      
  blMotor->run(BACKWARD);
  blMotor->setSpeed(i);

  delay(3000);

  flMotor->run(RELEASE);
  brMotor->run(RELEASE);
  frMotor->run(RELEASE);
  blMotor->run(RELEASE);
}


void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps


  if (!AFMS.begin()) { // create with the default frequency 1.6KHz
   Serial.println("Could not find Motor Shield. Check wiring.");
   while (1);
  }

  Serial.println("Motor Shield found.");

}


void loop() {
  
  uint8_t motor_speed = 50;
  int btn_code;
  
  //  control of motion start by IR remote key press
  if (Serial.available() > 0) {
    int inByte = Serial.read(); 

    
    switch(inByte) {
     
      case '0': {
        Serial.println("Error: Press a direction button on the remote");
        break;
      }
      
      case 'w': {
        up(motor_speed);
        break;
      }

      case 's': {
        down(motor_speed);
        break;
      }

      case 'a': {
        left(motor_speed);
        break;
      }

      case 'd': {
        right(motor_speed);
        break;
      }
      


  }
        
}
}
