#include <Servo.h>

#include <Wire.h>                 // code library for I2C intercase to motor shield ( via SDA / SDL pins )
#include <Adafruit_MotorShield.h> // code library for the motor shield

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *brMotor = AFMS.getMotor(1);
Adafruit_DCMotor *blMotor = AFMS.getMotor(2);
Adafruit_DCMotor *frMotor = AFMS.getMotor(3);
Adafruit_DCMotor *flMotor = AFMS.getMotor(4);

// Define servo pin
int servoPin = 11;

// Create servo object
Servo Servo1;


//-------------------------FUNCTIONS-------------------------------------------------------------------------
char button_pressed;
uint8_t i;
unsigned long LastCode;
uint8_t angle;



// function to rotate camera module
void rotate_camera(uint8_t angle) {
  // Add 10 degrees to servo position
  Servo1.write(angle);
  delay(1500); 
}
  
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

  delay(1500);

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

  delay(1500);

  flMotor->run(RELEASE);
  brMotor->run(RELEASE);
  frMotor->run(RELEASE);
  blMotor->run(RELEASE);
    
}


// function to move up tree - small step
void upsmall(uint8_t i) {
  flMotor->run(FORWARD);
  flMotor->setSpeed(i);
    
  brMotor->run(FORWARD);
  brMotor->setSpeed(i);
    
  frMotor->run(BACKWARD);
  frMotor->setSpeed(i);
    
  blMotor->run(BACKWARD);
  blMotor->setSpeed(i);

  delay(750);

  flMotor->run(RELEASE);
  brMotor->run(RELEASE);
  frMotor->run(RELEASE);
  blMotor->run(RELEASE);
}
  
// function to move down tree - small step
void downsmall(uint8_t i) {
  flMotor->run(BACKWARD);
  flMotor->setSpeed(i);
    
  brMotor->run(BACKWARD);
  brMotor->setSpeed(i);
    
  frMotor->run(FORWARD);
  frMotor->setSpeed(i);
    
  blMotor->run(FORWARD);
  blMotor->setSpeed(i);

  delay(400);

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

  delay(1500);

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

  // Set up servo pin
  Servo1.attach(servoPin);


  
  if (!AFMS.begin()) { // create with the default frequency 1.6KHz
   Serial.println("Could not find Motor Shield. Check wiring.");
   while (1);
  }

  Serial.println("Motor Shield found.");

}


void loop() {
  
  uint8_t motor_speed = 100;
  int btn_code;
  
  // Set up camera angle;
  uint8_t angle = 0;

  //  keyboard control motion 
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

      case 'r': {
        upsmall(motor_speed);
        break;
      }

      case 'f': {
        downsmall(motor_speed);
        break;
      }

     
      case '1': {      
        rotate_camera(0);
        break;
      }

      case '2': {
        rotate_camera(45);
        break;
      }

      case '3': {
        rotate_camera(90);
        break;
      }

      case '4': {
        rotate_camera(135);
        break;
      }

      case '5': {
        rotate_camera(180);
        break;
      }
        


  }
        
}
}
