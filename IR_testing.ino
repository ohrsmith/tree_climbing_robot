#include <IRremote.h>             // include the IRremote library
#include <Wire.h>                 // code library for I2C intercase to motor shield ( via SDA / SDL pins )
#include <Adafruit_MotorShield.h> // code library for the motor shield

// Create the motor shield object with the default I2C address
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
// Select which 'port' M1, M2, M3 or M4. In this case, M1
Adafruit_DCMotor *brMotor = AFMS.getMotor(1);
Adafruit_DCMotor *blMotor = AFMS.getMotor(2);
Adafruit_DCMotor *frMotor = AFMS.getMotor(3);
Adafruit_DCMotor *flMotor = AFMS.getMotor(4);

//  definitions for IR remote control
#define RECV_PIN 11           //  define the DIO pin used for the receiver
decode_results results;        //  structure containing received data
IRrecv irrecv(RECV_PIN);     // Create an instance of the IRrecv library 

//-------------------------FUNCTIONS-------------------------------------------------------------------------
char button_pressed;
uint8_t i;
unsigned long LastCode;
  
// function to move up tree 
void up(uint8_t i) {
//  flMotor->run(FORWARD);
//  flMotor->setSpeed(i);
//    
//  brMotor->run(FORWARD);
//  brMotor->setSpeed(i);
    
  frMotor->run(BACKWARD);
  frMotor->setSpeed(i);
    
//  blMotor->run(BACKWARD);
//  blMotor->setSpeed(i);

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

//  function for intepreting IR remote codes
//  returns the button name relating to the received code 
String GetIRIndex(unsigned long code) {
  char CodeName[3];                     // Character array used to hold the received button name 
  if (code == 0xFFFFFFFF)               // Is the received code is a repeat code (NEC protocol)?
  {
    code = LastCode;                    // If so then we need to find the button name for the last button pressed 
  }
  switch (code)                         // Find the button name for the received code 
  {
//
//  Received code is for the UP button
//
    case 0xFD807F: 
      strcpy (CodeName, "UP");
      break;
//      
//   Received code is for the DOWN button
//
    case 0xFD906F: 
      strcpy (CodeName, "DN");
      break;
//        
//   Received code is for the LEFT button
//
    case 0xFD20DF: 
      strcpy (CodeName, "L");
      break;
//              
//   Received code is for the RIGHT button
//          
    case 0xFD609F: 
      strcpy (CodeName, "R");
      break;
//              
//   Received code is for the OK button
//
    case 0xFF38C7: 
      strcpy (CodeName, "OK");
      break;
//              
//   Received code is for the number 1 button
//
    case 0xFFA25D: 
      strcpy (CodeName, "1");
      break;
//              
//   Received code is for the number 2 button
//
    case 0xFF629D: 
      strcpy (CodeName, "2");
      break;
//              
//   Received code is for the number 3 button
//
    case 0xFFE21D: 
      strcpy (CodeName, "3");
      break;
//              
//   Received code is for the number 4 button
//
    case 0xFF22DD: 
      strcpy (CodeName, "4");
      break;
//              
//   Received code is for the number 5 button
//
    case 0xFF02FD: 
      strcpy (CodeName, "5");
      break;
//              
//   Received code is for the number 6 button
//
    case 0xFFC23D: 
      strcpy (CodeName, "6");
      break;
//
//   Received code is for the number 7 button
//
    case 0xFFE01F:
      strcpy (CodeName, "7");
      break;        
//        
//   Received code is for the number 8 button
//
    case 0xFFA857: 
      strcpy (CodeName, "8");
      break;  
//
//   Received code is for the number 9 button
//
    case 0xFF906F: 
      strcpy (CodeName, "9");
      break;  
//        
//   Received code is for the number 0 button
//
    case 0xFF9867: 
      strcpy (CodeName, "0");
      break;  
//                             
//   Received code is for the number * button
//
    case 0xFF6897: 
      strcpy (CodeName, "*");
      break;  
//                             
//   Received code is for the number # button
//
    case 0xFFB04F: 
      strcpy (CodeName, "#");
      break; 
//         
//   Received code is an error or is unknown
//
    default:
      strcpy (CodeName, "??");
      break;
  }
//
//   Save this code incase we get a repeat code next time
//       
    LastCode = code;
//
//   Return the button name for the received code */
//
    return CodeName;   
}


//--------------------------------------------------------------------------------------------------------------------------------------------


void setup() {
  Serial.begin(9600); // set up Serial library at 9600 bps

  // start IR receiver monitoring
  irrecv.enableIRIn();      // Start receiving codes

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
  if (irrecv.decode(&results))        // Has a new code been received? */
    {   
        String button_pressed = GetIRIndex(results.value);
        if (button_pressed == "UP") {
          btn_code = 1;
        }
        else if (button_pressed == "DN") {
          btn_code = 2;
        }
        else if (button_pressed == "L") {
          btn_code = 3;
        }
        else if (button_pressed == "R") {
          btn_code = 4;
        }
        else {
          btn_code = 0;
        }    
        
        switch(btn_code) {
         
          case 0: {
            Serial.println("Error: Press a direction button on the remote");
            break;
          }
          
          case 1: {
            up(motor_speed);
            break;
          }
  
          case 2: {
            down(motor_speed);
            break;
          }
  
          case 3: {
            left(motor_speed);
            break;
          }
  
          case 4: {
            right(motor_speed);
            break;
          }
          
      Serial.println(GetIRIndex(results.value));     
      irrecv.resume();                 // Start receiving codes again    

      }
        
}
}
