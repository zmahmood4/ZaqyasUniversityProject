/*
 *Version 5 LCD Message Implementation
 *Automated Airfield Taxiway System
 *Zaqyas Ali Mahmood
 */
 
//global scope to declare variable names for pins

//A0-A8 are the 9 sensors of the system
const int takeoff_sensor = A0;
const int landing_sensor = A1;
const int emergency_sensor = A2;
const int gate_1 = A3;
const int gate_2 = A4;
const int gate_3 = A5;
const int gate_4 = A6;
const int gate_5 = A7;
const int gate_6 = A8;

//A9 is the emergency gate route button
const int e_button1 = A9;
//A10 is the takeoff route button
const int t_button1 = A10;

//Digital pins 27-47 are the LED strip sections across the airfield
//s1-s21 are mapped out across the airfield 
const int s1 = 47; //gate 1 entrance
const int s2 = 46; //gate 1 to 2 route
const int s3 = 45; //gate 2 entrance
const int s4 = 44; //gate 2 to 3 route
const int s5 = 43; //gate 3 entrance
const int s6 = 42; //gate 3 to 4 route
const int s7 = 41; //gate 4 entrance
const int s8 = 40; //gate 4 to 5 route
const int s9 = 39; //gate 5 entrance
const int s10 = 38; //gate 5 to 6 route
const int s11 = 37; //gate 6 entrance
const int s12 = 36; //route to emergency sensor or takeoff junction
const int s13 = 35; //route to emergency sensor from junction
const int s14 = 34; //route from emergency sensor and terminal gates juntion
const int s15 = 33; //route from landing sensor to emergency and terminal gate junction
const int s16 = 32; //route from runway landing slip 2 and taxiwayroute to landing sensor
const int s17 = 31; //taxiway route from runway slip 1 to landing sensor 
const int s18 = 30; //route to takeoff sensore from junction
const int s19 = 29; //runway slip 1
const int s20 = 28; //runway slip 2
const int s21 = 27; //runway

//LCD libraries and global configuration
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);


//setup and configure pin modes
void setup()
{
  //LCD program setup
  lcd.init();
  lcd.backlight();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Powering Up");
  lcd.setCursor(0,1);
  lcd.print("Please Wait...");
  delay(2500);
  
  //setting up the serial monitor to print messages through the system
  Serial.begin(9600);
  Serial.println(" --- Automated Airfield Taxiway System --- ");
  Serial.println();
  
  //LCD message
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Airfield Taxi");
  lcd.setCursor(0,1);
  lcd.print("System");
  delay(2500);
  
  //declaring the 3 key system control sensors as inputs
  pinMode(takeoff_sensor, INPUT);
  pinMode(landing_sensor, INPUT);
  pinMode(emergency_sensor, INPUT);

  //declaring each of the gate sensors as inputs
  pinMode(gate_1, INPUT);
  pinMode(gate_2, INPUT);
  pinMode(gate_3, INPUT);
  pinMode(gate_4, INPUT);
  pinMode(gate_5, INPUT);
  pinMode(gate_6, INPUT);

  //declaring the emergency and takeoff control buttons as input_pullup to use the built in pullup resistor on the arduino
  pinMode(e_button1, INPUT_PULLUP);
  pinMode(t_button1, INPUT_PULLUP);

  //declaring each of the sections for leds as outputs
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(s4, OUTPUT);
  pinMode(s5, OUTPUT);
  pinMode(s6, OUTPUT);
  pinMode(s7, OUTPUT);
  pinMode(s8, OUTPUT);
  pinMode(s9, OUTPUT);
  pinMode(s10, OUTPUT);
  pinMode(s11, OUTPUT);
  pinMode(s12, OUTPUT);
  pinMode(s13, OUTPUT);
  pinMode(s14, OUTPUT);
  pinMode(s15, OUTPUT);
  pinMode(s16, OUTPUT);
  pinMode(s17, OUTPUT);
  pinMode(s18, OUTPUT);
  pinMode(s19, OUTPUT);
  pinMode(s20, OUTPUT);
  pinMode(s21, OUTPUT);

  //test airfield LEDs

  Serial.println("LED Illumination Test in Progress");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LED Testing");
  lcd.setCursor(0,1);
  lcd.print("In Progress...");
  
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);
  digitalWrite(s8, HIGH);
  digitalWrite(s9, HIGH);
  digitalWrite(s10, HIGH);
  digitalWrite(s11, HIGH);
  digitalWrite(s12, HIGH);
  digitalWrite(s13, HIGH);
  digitalWrite(s14, HIGH);
  digitalWrite(s15, HIGH);
  digitalWrite(s16, HIGH);
  digitalWrite(s17, HIGH);
  digitalWrite(s18, HIGH);
  digitalWrite(s19, HIGH);
  digitalWrite(s20, HIGH);
  digitalWrite(s21, HIGH);

  delay(5000);

  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
  digitalWrite(s8, LOW);
  digitalWrite(s9, LOW);
  digitalWrite(s10, LOW);
  digitalWrite(s11, LOW);
  digitalWrite(s12, LOW);
  digitalWrite(s13, LOW);
  digitalWrite(s14, LOW);
  digitalWrite(s15, LOW);
  digitalWrite(s16, LOW);
  digitalWrite(s17, LOW);
  digitalWrite(s18, LOW);
  digitalWrite(s19, LOW);
  digitalWrite(s20, LOW);
  digitalWrite(s21, LOW);

  delay(2500);
  
  Serial.println("LED Illumination Test Complete");
  Serial.println();

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("LED Testing");
  lcd.setCursor(0,1);
  lcd.print("Completed");
  delay(2500);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Configuring");
  lcd.setCursor(0,1);
  lcd.print("System...");

  //start by turning required airfield lights on so an aircraft can land and go towards landing sensor 
  digitalWrite(s21, HIGH); //Turn runway lights on
  Serial.println("Runway Activated");
  digitalWrite(s20, HIGH); //Turn slip 2 on
  digitalWrite(s19, HIGH); //Turn slip 1 on
  digitalWrite(s17, HIGH); //Turn taxiway from slip 1 on
  digitalWrite(s16, HIGH); //Turn route from slip 2 and taxiway on
  Serial.println("Landing Taxiway Activated");
  Serial.println();
  delay(2500);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Runway Clear");
  lcd.setCursor(0,1);
  lcd.print("For Landing");

  Serial.println("Runway Clear for Landing - Follow the Reds");
  Serial.println();
  delay(250);
}


void loop()
{
  landing_takeoff(); //call landing takeoff function function

}


//this function checks to see if a plane is ready for takeoff, otherwise allows the program to land and guide planes
void landing_takeoff()
{
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  digitalWrite(s4, LOW);
  digitalWrite(s5, LOW);
  digitalWrite(s6, LOW);
  digitalWrite(s7, LOW);
  digitalWrite(s8, LOW);
  digitalWrite(s9, LOW);
  digitalWrite(s10, LOW);
  digitalWrite(s11, LOW);
  digitalWrite(s12, LOW);
  digitalWrite(s18, LOW);

  if(digitalRead(t_button1)==LOW) //takeoff button to route plane from gate to runway
  {
    takeoff(); //call takeoff function
  }
  else
  {
    landing(); //otherwise call landing funtion
  }
}


//landing function to control when a plane arrives
void landing()
{
  if(digitalRead(landing_sensor)==LOW) //check if plane arrives at landing sensor
  { 
    Serial.println("Aircraft Landed");
    delay(500);
    gate_check(); //call gate_check to see which gates are available
  }
  else
  {
    landing_takeoff(); //loop function if no plane detected
  }
  return;
}


//function to check through each of the 6 gates to see which is available or occupied
void gate_check()
{

  Serial.println("Checking for Available Gate");
  delay(250);

  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Checking for");
  lcd.setCursor(0,1);
  lcd.print("Available Gate...");
  delay(1500);
  
  if(digitalRead(gate_1)==HIGH)
  {
    Serial.println("Follow the Reds to Gate 1");
    delay(250);
    gate1_route();
  }
  else if(digitalRead(gate_1)==LOW)
  {
    if(digitalRead(gate_2)==HIGH)
    {
      Serial.println("Follow the Reds to Gate 2");
      delay(250);
      gate2_route();
    }
    else if(digitalRead(gate_2)==LOW)
    {
      if(digitalRead(gate_3)==HIGH)
      {
        Serial.println("Follow the Reds to Gate 3");
        delay(250);
        gate3_route();
      }
      else if(digitalRead(gate_3)==LOW)
      {
        if(digitalRead(gate_4)==HIGH)
        {
          Serial.println("Follow the Reds to Gate 4");
          delay(250);
          gate4_route();
        }
        else if(digitalRead(gate_4)==LOW)
        {
          if(digitalRead(gate_5)==HIGH)
          {
            Serial.println("Follow the Reds to Gate 5");
            delay(250);
            gate5_route();
          }
          else if(digitalRead(gate_5)==LOW)
          {
            if(digitalRead(gate_6)==HIGH)
            {
              Serial.println("Follow the Reds to Gate 6");
              delay(250);
              gate6_route();
            }
            else
            {
              Serial.println("GATES FULL - Hold Position");
              delay(250);
              lcd.clear();
              lcd.setCursor(0,0);
              lcd.print("GATES FULL");
              lcd.setCursor(0,1);
              lcd.print("PLEASE WAIT...");
              delay(500);
              gates_full();
            }
          }
        }
      }
    }
  }
}

////The next 6 functions route the plane from the landing sensor to the available gate

void gate1_route()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Follow the Reds");
  lcd.setCursor(0,1);
  lcd.print("To Gate 1...");
  delay(500);
  
  digitalWrite(s15, HIGH);
  digitalWrite(s14, HIGH);
  digitalWrite(s1, HIGH);

  if(digitalRead(gate_1)==LOW)
  {
    Serial.println("Plane Arrived to Gate 1");
    delay(250);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plane Arrived");
    lcd.setCursor(0,1);
    lcd.print("At Gate 1");
    
    digitalWrite(s15, LOW);
    digitalWrite(s14, LOW);
    digitalWrite(s1, LOW);
    delay(1500);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
  }
  else if(digitalRead(e_button1)==LOW)      
  {
    Serial.println("EMERGENCY REPORTED at Gate 1");
    delay(250);
    Serial.println("Follow the Reds & Ambers to Emergency Taxiway");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GATE 1 EMERGENCY");
    lcd.setCursor(0,1);
    lcd.print("FOLLOW LIGHTS");
    delay(250);
        
    digitalWrite(s1, LOW);
    digitalWrite(s2, HIGH);
    digitalWrite(s4, HIGH);
    digitalWrite(s6, HIGH);
    digitalWrite(s8, HIGH);
    digitalWrite(s10, HIGH);
    emergency();       
  }
  else
  {
    gate1_route();
  }
}

void gate2_route()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Follow the Reds");
  lcd.setCursor(0,1);
  lcd.print("To Gate 2...");
  delay(500);
  
  digitalWrite(s15, HIGH);
  digitalWrite(s14, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  
  if(digitalRead(gate_2)==LOW)
  {
    Serial.println("Plane Arrived to Gate 2");
    delay(250);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plane Arrived");
    lcd.setCursor(0,1);
    lcd.print("At Gate 2");
    
    digitalWrite(s15, LOW);
    digitalWrite(s14, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s3, LOW);
    delay(1500);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
    
  }
  else if(digitalRead(e_button1)==LOW)      
  {
    Serial.println("EMERGENCY REPORTED at Gate 2");
    delay(250);
    Serial.println("Follow the Reds & Ambers to Emergency Taxiway");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GATE 2 EMERGENCY");
    lcd.setCursor(0,1);
    lcd.print("FOLLOW LIGHTS");
    delay(250);
    
    digitalWrite(s3, LOW);
    digitalWrite(s4, HIGH);
    digitalWrite(s6, HIGH);
    digitalWrite(s8, HIGH);
    digitalWrite(s10, HIGH);
    emergency();       
  }
  
  else
  {
    gate2_route();
  }
}

void gate3_route()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Follow the Reds");
  lcd.setCursor(0,1);
  lcd.print("To Gate 3...");
  delay(500);
  
  digitalWrite(s15, HIGH);
  digitalWrite(s14, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s5, HIGH);
  
  if(digitalRead(gate_3)==LOW)
  {
    Serial.println("Plane Arrived to Gate 3");
    delay(250);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plane Arrived");
    lcd.setCursor(0,1);
    lcd.print("At Gate 3");
    
    digitalWrite(s15, LOW);
    digitalWrite(s14, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s4, LOW);
    digitalWrite(s5, LOW);
    delay(1500);
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
    
  }
  else if(digitalRead(e_button1)==LOW)      
  {
    Serial.println("EMERGENCY REPORTED at Gate 3");
    delay(250);
    Serial.println("Follow the Reds & Ambers to Emergency Taxiway");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GATE 3 EMERGENCY");
    lcd.setCursor(0,1);
    lcd.print("FOLLOW LIGHTS");
    delay(250);
    
    digitalWrite(s5, LOW);
    digitalWrite(s6, HIGH);
    digitalWrite(s8, HIGH);
    digitalWrite(s10, HIGH);
    emergency();       
  }
  
  else
  {
    gate3_route();
  }
}

void gate4_route()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Follow the Reds");
  lcd.setCursor(0,1);
  lcd.print("To Gate 4...");
  delay(500);
  
  digitalWrite(s15, HIGH);
  digitalWrite(s14, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s7, HIGH);

  if(digitalRead(gate_4)==LOW)
  {
    Serial.println("Plane Arrived to Gate 4");
    delay(250);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plane Arrived");
    lcd.setCursor(0,1);
    lcd.print("At Gate 4");
    
    digitalWrite(s15, LOW);
    digitalWrite(s14, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s4, LOW);
    digitalWrite(s6, LOW);
    digitalWrite(s7, LOW);
    delay(1500);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
  }
  else if(digitalRead(e_button1)==LOW)      
  {
    Serial.println("EMERGENCY REPORTED at Gate 4");
    delay(250);
    Serial.println("Follow the Reds & Ambers to Emergency Taxiway");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GATE 4 EMERGENCY");
    lcd.setCursor(0,1);
    lcd.print("FOLLOW LIGHTS");
    delay(250);
    
    digitalWrite(s7, LOW);
    digitalWrite(s8, HIGH);
    digitalWrite(s10, HIGH);
    emergency();       
  }
  
  else
  {
    gate4_route();
  }
}

void gate5_route()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Follow the Reds");
  lcd.setCursor(0,1);
  lcd.print("To Gate 5...");
  delay(500);
  
  digitalWrite(s15, HIGH);
  digitalWrite(s14, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s8, HIGH);
  digitalWrite(s9, HIGH);

  if(digitalRead(gate_5)==LOW)
  {
    Serial.println("Plane Arrived to Gate 5");
    delay(250);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plane Arrived");
    lcd.setCursor(0,1);
    lcd.print("At Gate 5");
    
    digitalWrite(s15, LOW);
    digitalWrite(s14, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s4, LOW);
    digitalWrite(s6, LOW);
    digitalWrite(s8, LOW);
    digitalWrite(s9, LOW);
    delay(1500);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
  }
  else if(digitalRead(e_button1)==LOW)      
  {
    Serial.println("EMERGENCY REPORTED at Gate 5");
    delay(250);
    Serial.println("Follow the Reds & Ambers to Emergency Taxiway");
    
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GATE 5 EMERGENCY");
    lcd.setCursor(0,1);
    lcd.print("FOLLOW LIGHTS");
    delay(250);
    
    digitalWrite(s9, LOW);
    digitalWrite(s10, HIGH);
    emergency();       
  }
  else
  {
    gate5_route();
  }
}

void gate6_route()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Follow the Reds");
  lcd.setCursor(0,1);
  lcd.print("To Gate 6...");
  delay(500);
  
  digitalWrite(s15, HIGH);
  digitalWrite(s14, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s8, HIGH);
  digitalWrite(s10, HIGH);
  digitalWrite(s11, HIGH);

  if(digitalRead(gate_6)==LOW)
  {
    Serial.println("Plane Arrived to Gate 6");
    delay(250);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plane Arrived");
    lcd.setCursor(0,1);
    lcd.print("At Gate 6");
    
    digitalWrite(s15, LOW);
    digitalWrite(s14, LOW);
    digitalWrite(s2, LOW);
    digitalWrite(s4, LOW);
    digitalWrite(s6, LOW);
    digitalWrite(s8, LOW);
    digitalWrite(s10, LOW);
    digitalWrite(s11, LOW);
    delay(1500);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
  }
  else if(digitalRead(e_button1)==LOW)      
  {
    Serial.println("EMERGENCY REPORTED at Gate 6");
    delay(250);
    Serial.println("Follow the Reds & Ambers to Emergency Taxiway");

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("GATE 6 EMERGENCY");
    lcd.setCursor(0,1);
    lcd.print("FOLLOW LIGHTS");
    delay(250);
    
    digitalWrite(s11, LOW);
    emergency();       
  }
  else
  {
    gate6_route();
  }
}

//this function checks to see if any gates are available
//if the gates are all full the planes will have to queue on the taxiway until a gate is available
void gates_full()
{
  while ((digitalRead(gate_1)==LOW) and (digitalRead(gate_2)==LOW) and (digitalRead(gate_3)==LOW) and (digitalRead(gate_4)==LOW) and (digitalRead(gate_5)==LOW) and (digitalRead(gate_6)==LOW))
  {
    ;
  }
  delay(500);
  lcd.clear();
}

//the emergency funtion guides a plane to the emergency gate incase there is an emergency
void emergency()
{
  digitalWrite(s12, HIGH);
  digitalWrite(s13, HIGH);
  if(digitalRead(emergency_sensor)==LOW)
  {
    Serial.println("Plane Arrived to Emergency Taxiway");
    delay(500);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Plane at");
    lcd.setCursor(0,1);
    lcd.print("Emergency Gate");
    delay(1500);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Please Wait");
    lcd.setCursor(0,1);
    lcd.print("For Guidance...");
    delay(2500);
    
    digitalWrite(s2, LOW);
    digitalWrite(s4, LOW);
    digitalWrite(s6, LOW);
    digitalWrite(s8, LOW);
    digitalWrite(s10, LOW);
    digitalWrite(s12, LOW);
    digitalWrite(s13, LOW);
    gate_check();
  }
  else
  {
    emergency();
  }
}


//The takeoff function checks to see which gate has a plane and its ready to go to the runway
void takeoff()
{
  Serial.println("Terminal Requesting Takeoff");
  delay(500);
 
  if(digitalRead(gate_1)==LOW)
  {
    Serial.println("Aircraft at Gate 1");
    delay(250);
    Serial.println("Pushback and Follow the Reds");
    delay(500);
    gate1_takeoff();
  }
  else if(digitalRead(gate_2)==LOW)
  {
    Serial.println("Aircraft at Gate 2");
    delay(250);
    Serial.println("Pushback and Follow the Reds");
    delay(500);
    gate2_takeoff();
  }
  else if(digitalRead(gate_3)==LOW)
  {
    Serial.println("Aircraft at Gate 3");
    delay(250);
    Serial.println("Pushback and Follow the Reds");
    delay(500);
    gate3_takeoff();
  }
  else if(digitalRead(gate_4)==LOW)
  {
    Serial.println("Aircraft at Gate 4");
    delay(250);
    Serial.println("Pushback and Follow the Reds");
    delay(500);
    gate4_takeoff();
  }
  else if(digitalRead(gate_5)==LOW)
  {
    Serial.println("Aircraft at Gate 5");
    delay(250);
    Serial.println("Pushback and Follow the Reds");
    delay(500);
    gate5_takeoff();
  }
  else if(digitalRead(gate_6)==LOW)
  {
    Serial.println("Aircraft at Gate 6");
    delay(250);
    Serial.println("Pushback and Follow the Reds");
    delay(500);
    gate6_takeoff();
  }
  else
  {
    Serial.println("No Planes at Terminal");
    delay(250);
  }
  
}


///The next 6 functions set the system lights to the runway depending on the gate which has the plane
void gate1_takeoff()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gate 1 Takeoff");
  lcd.setCursor(0,1);
  lcd.print("Follow the Reds");
  delay(2500);
  digitalWrite(s1, HIGH);
  digitalWrite(s2, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s8, HIGH);
  digitalWrite(s10, HIGH);
  digitalWrite(s12, HIGH);
  digitalWrite(s18, HIGH);
  if(digitalRead(takeoff_sensor)==LOW)
  {
    Serial.println("Runway Clear for Takeoff");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear for");
    lcd.setCursor(0,1);
    lcd.print("Takeoff");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
    landing_takeoff();
  }
  else
  {
    gate1_takeoff();
  }
}

void gate2_takeoff()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gate 2 Takeoff");
  lcd.setCursor(0,1);
  lcd.print("Follow the Reds");
  delay(2500);
  digitalWrite(s3, HIGH);
  digitalWrite(s4, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s8, HIGH);
  digitalWrite(s10, HIGH);
  digitalWrite(s12, HIGH);
  digitalWrite(s18, HIGH);
  if(digitalRead(takeoff_sensor)==LOW)
  {
    Serial.println("Runway Clear for Takeoff");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear for");
    lcd.setCursor(0,1);
    lcd.print("Takeoff");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
    landing_takeoff();
  }
  else
  {
    gate2_takeoff();
  }
}

void gate3_takeoff()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gate 3 Takeoff");
  lcd.setCursor(0,1);
  lcd.print("Follow the Reds");
  delay(2500);
  digitalWrite(s5, HIGH);
  digitalWrite(s6, HIGH);
  digitalWrite(s8, HIGH);
  digitalWrite(s10, HIGH);
  digitalWrite(s12, HIGH);
  digitalWrite(s18, HIGH);
  if(digitalRead(takeoff_sensor)==LOW)
  {
    Serial.println("Runway Clear for Takeoff");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear for");
    lcd.setCursor(0,1);
    lcd.print("Takeoff");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
    landing_takeoff();
  }
  else
  {
    gate3_takeoff();
  }
}

void gate4_takeoff()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gate 4 Takeoff");
  lcd.setCursor(0,1);
  lcd.print("Follow the Reds");
  delay(2500);
  digitalWrite(s7, HIGH);
  digitalWrite(s8, HIGH);
  digitalWrite(s10, HIGH);
  digitalWrite(s12, HIGH);
  digitalWrite(s18, HIGH);
  if(digitalRead(takeoff_sensor)==LOW)
  {
    Serial.println("Runway Clear for Takeoff");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear for");
    lcd.setCursor(0,1);
    lcd.print("Takeoff");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
    landing_takeoff();
  }
  else
  {
    gate4_takeoff();
  }
}

void gate5_takeoff()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gate 5 Takeoff");
  lcd.setCursor(0,1);
  lcd.print("Follow the Reds");
  delay(2500);
  digitalWrite(s9, HIGH);
  digitalWrite(s10, HIGH);
  digitalWrite(s12, HIGH);
  digitalWrite(s18, HIGH);
  if(digitalRead(takeoff_sensor)==LOW)
  {
    Serial.println("Runway Clear for Takeoff");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear for");
    lcd.setCursor(0,1);
    lcd.print("Takeoff");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
    landing_takeoff();
  }
  else
  {
    gate5_takeoff();
  }
}

void gate6_takeoff()
{
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Gate 6 Takeoff");
  lcd.setCursor(0,1);
  lcd.print("Follow the Reds");
  delay(2500);
  digitalWrite(s11, HIGH);
  digitalWrite(s12, HIGH);
  digitalWrite(s18, HIGH);
  if(digitalRead(takeoff_sensor)==LOW)
  {
    Serial.println("Runway Clear for Takeoff");
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear for");
    lcd.setCursor(0,1);
    lcd.print("Takeoff");
    delay(5000);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Runway Clear");
    lcd.setCursor(0,1);
    lcd.print("For Landing");
    landing_takeoff();
  }
  else
  {
    gate6_takeoff();
  }
}
