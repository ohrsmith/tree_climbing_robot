#include <IRremote.h>             // include the IRremote library
#include <Wire.h>                 // code library for I2C intercase to motor shield ( via SDA / SDL pins )
#include <Adafruit_MotorShield.h> // code library for the motor shield
//
//------------------------------------------------------------------------------------------------------------------------
//
//  set up motorshield for brushed DC & stepper motors
//
Adafruit_MotorShield AFMS;     // designate motors for motor shield library code 
Adafruit_DCMotor *myMotorL=AFMS.getMotor(1);          // designate motors for motor shield library code
Adafruit_DCMotor *myMotorR=AFMS.getMotor(2);          // designate motors for motor shield library code
Adafruit_StepperMotor *myStepper = AFMS.getStepper(2048, 2);
//
//------------------------------------------------------------------------------------------------------------------------
//
//  definitions for IR remote control
//
#define RECV_PIN 11            //  define the DIO pin used for the receiver
decode_results results;        //  structure containing received data
IRrecv irrecv(RECV_PIN);     // Create an instance of the IRrecv library 


void setup() {
// start IR receiver monitoring
  irrecv.enableIRIn();      // Start receiving codes
}

 

void loop() {
//  control of motion start by IR remote key press
//
  if (irrecv.decode(&results))        // Has a new code been received? */
    {   
        if (GetIRIndex(results.value) =="UP")
        {
          status_flag = 1;
        }
        else
        {
          status_flag = 0;
        }
      Serial.println(status_flag);     // use serial monitor to debug if neccessary by inspecting status
      Serial.println(GetIRIndex(results.value));     
      irrecv.resume();                 // Start receiving codes again    
    } 
  
  
  
  
    
  //  define function for intepreting IR remote codes
  //  function returns the button name relating to the received code 
  //
  String GetIRIndex(unsigned long code)
  {
    char CodeName[3];                     // Character array used to hold the received button name 
    if (code == 0xFFFFFFFF)               // Is the received code is a repeat code (NEC protocol)?
    {
      code = LastCode;                    // If so then we need to find the button name for the last button pressed 
    }
    switch (code)                         // Find the button name for the received code 
    {
  //
  //   Received code is for the UP button
  //
      case 0xFF18E7: 
        strcpy (CodeName, "UP");
        break;
  //      
  //   Received code is for the DOWN button
  //
      case 0xFF4AB5: 
        strcpy (CodeName, "DN");
        break;
  //        
  //   Received code is for the LEFT button
  //
      case 0xFF10EF: 
        strcpy (CodeName, "L");
        break;
  //              
  //   Received code is for the RIGHT button
  //          
      case 0xFF5AA5: 
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


      

}
