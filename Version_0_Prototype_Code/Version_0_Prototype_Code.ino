/*
 * Version 0 is a working initial prototype code that implements the key operation of the automated aircraft taxiway system
 * This code was written to test key functions of the system and identify potential bugs that can be eliminated at an early stage
 */

//global scope

const int RW_Sensor = A0;
const int G1_Sensor = A1;
const int EStop_1 = A2;
const int EStop_Sensor = A3;
const int G2_Sensor = A4;
const int G3_Sensor = A5;
const int G4_Sensor = A6;
const int G5_Sensor = A7;
const int G6_Sensor = A8;


const int RW_LED = 13;
const int EGate_LED = 12;
const int Gate1_LED = 11;
const int Gate2_LED = 10;
const int Gate3_LED = 9;
const int Gate4_LED = 8;
const int Gate5_LED = 7;
const int Gate6_LED = 6;


void setup() {
  Serial.begin(9600);
  Serial.print("System Loading");
  
  pinMode(RW_LED, OUTPUT);
  pinMode(RW_Sensor, INPUT);
  
  pinMode(EGate_LED, OUTPUT);
  pinMode(EStop_Sensor, INPUT);
  pinMode(EStop_1, INPUT_PULLUP);
  
  pinMode(G1_Sensor, INPUT);
  pinMode(Gate1_LED, OUTPUT);  
  
  pinMode(Gate2_LED, OUTPUT);
  pinMode(G2_Sensor, INPUT);
  
  pinMode(Gate3_LED, OUTPUT);
  pinMode(G3_Sensor, INPUT);
  
  pinMode(Gate4_LED, OUTPUT);
  pinMode(G4_Sensor, INPUT);
  
  pinMode(Gate5_LED, OUTPUT);
  pinMode(G5_Sensor, INPUT);
  
  pinMode(Gate6_LED, OUTPUT);
  pinMode(G6_Sensor, INPUT);

  delay(500);
  Serial.println();
  Serial.println();
  Serial.print("System Loaded");
  
}


void loop(){
  digitalWrite(RW_LED, HIGH);
  delay(1000);
  Serial.println();
  Serial.println();
  Serial.print("Runway Clear for landing...");
  menu();
}


void menu(){
  if(digitalRead(RW_Sensor)==LOW)      
  {
    Serial.println();
    Serial.println();
    Serial.print("Plane Landed, Wait for guidance to gate");
    digitalWrite(RW_LED, LOW); 
    delay(1000);                      
    digitalWrite(RW_LED, HIGH);  
    delay(1000);
    check();
  }
  
  else
  {
    menu();
  }
  return;
}



void check(){

  if (digitalRead(G1_Sensor)==HIGH)
  {
    Serial.println();
    Serial.println();
    Serial.print("Taxi to Gate 1");
    gate_1();
  }
  
  else if (digitalRead(G1_Sensor)==LOW)
  {
    if(digitalRead(G2_Sensor)==HIGH)
    {
      Serial.println();
      Serial.println();
      Serial.print("Taxi to Gate 2");
      gate_2();
    }
    else if (digitalRead(G2_Sensor)==LOW)
    {
      if(digitalRead(G3_Sensor)==HIGH)
      {
        Serial.println();
        Serial.println();
        Serial.print("Taxi to Gate 3");
        gate_3();
      }
      else if (digitalRead(G3_Sensor)==LOW)
      {
        if(digitalRead(G4_Sensor)==HIGH)
        {
          Serial.println();
          Serial.println();
          Serial.print("Taxi to Gate 4");
          gate_4();
        }
        else if (digitalRead(G4_Sensor)==LOW)
        {
          if(digitalRead(G5_Sensor)==HIGH)
          {
            Serial.println();
            Serial.println();
            Serial.print("Taxi to Gate 5");
            gate_5();
          }
          else if (digitalRead(G5_Sensor)==LOW)
          {
            if(digitalRead(G6_Sensor)==HIGH)
            {
              Serial.println();
              Serial.println();
              Serial.print("Taxi to Gate 6");
              gate_6();
            }
            else
            {
              gates_full();
            }
          }
        }
      }
    }
  }    
}



void gate_1(){
  digitalWrite(Gate1_LED, HIGH);
  digitalWrite(RW_LED, LOW); 
 
  if(digitalRead(G1_Sensor)==LOW)
  {
    Serial.println();
    Serial.println();
    Serial.print("Plane Arrived to Gate");
    digitalWrite(Gate1_LED, LOW);
  }
  else if(digitalRead(EStop_1)==LOW)      
  {
    digitalWrite(Gate1_LED, LOW);
    Serial.println();
    Serial.println();
    Serial.print("EMERGENCY AT GATE!!!");
    Serial.println();
    Serial.println();
    Serial.print("GO TO EMERGENCY GATE");
    emergency();       
  }
  else
  {
    gate_1(); 
  }
}



void gate_2(){
  digitalWrite(Gate2_LED, HIGH);
  digitalWrite(RW_LED, LOW); 
  
  if(digitalRead(G2_Sensor)==LOW)
  {
    Serial.println();
    Serial.println();
    Serial.print("Plane Arrived to Gate");
    digitalWrite(Gate2_LED, LOW);
  }
  else if(digitalRead(EStop_1)==LOW)      
  {
    digitalWrite(Gate2_LED, LOW);
    Serial.println();
    Serial.println();
    Serial.print("EMERGENCY AT GATE!!!");
    Serial.println();
    Serial.println();
    Serial.print("GO TO EMERGENCY GATE");
    emergency();       
  }
  else
  {
    gate_2(); 
  }
}



void gate_3(){
  digitalWrite(Gate3_LED, HIGH);
  digitalWrite(RW_LED, LOW); 
  
  if(digitalRead(G3_Sensor)==LOW)
  {
    Serial.println();
    Serial.println();
    Serial.print("Plane Arrived to Gate");
    digitalWrite(Gate3_LED, LOW);
  }
  else if(digitalRead(EStop_1)==LOW)      
  {
    digitalWrite(Gate3_LED, LOW);
    Serial.println();
    Serial.println();
    Serial.print("EMERGENCY AT GATE!!!");
    Serial.println();
    Serial.println();
    Serial.print("GO TO EMERGENCY GATE");
    emergency();       
  }
  else
  {
    gate_3(); 
  }
}



void gate_4(){
  digitalWrite(Gate4_LED, HIGH);
  digitalWrite(RW_LED, LOW); 
  
  if(digitalRead(G4_Sensor)==LOW)
  {
    Serial.println();
    Serial.println();
    Serial.print("Plane Arrived to Gate");
    digitalWrite(Gate4_LED, LOW);
  }
  else if(digitalRead(EStop_1)==LOW)      
  {
    digitalWrite(Gate4_LED, LOW);
    Serial.print("EMERGENCY AT GATE!!!");
    Serial.println();
    Serial.println();
    Serial.print("GO TO EMERGENCY GATE");
    emergency();       
  }
  else
  {
    gate_4(); 
  }
}

void gate_5(){
  digitalWrite(Gate5_LED, HIGH);
  digitalWrite(RW_LED, LOW); 
  
  if(digitalRead(G5_Sensor)==LOW)
  {
    Serial.println();
    Serial.println();
    Serial.print("Plane Arrived to Gate");
    digitalWrite(Gate5_LED, LOW);
  }
  else if(digitalRead(EStop_1)==LOW)      
  {
    digitalWrite(Gate5_LED, LOW);
    Serial.print("EMERGENCY AT GATE!!!");
    Serial.println();
    Serial.println();
    Serial.print("GO TO EMERGENCY GATE");
    emergency();       
  }
  else
  {
    gate_5(); 
  }
}



void gate_6(){
  digitalWrite(Gate6_LED, HIGH);
  digitalWrite(RW_LED, LOW); 
  
  if(digitalRead(G6_Sensor)==LOW)
  {
    Serial.println();
    Serial.println();
    Serial.print("Plane Arrived to Gate");
    digitalWrite(Gate6_LED, LOW);
  }
  else if(digitalRead(EStop_1)==LOW)      
  {
    digitalWrite(Gate6_LED, LOW);
    Serial.println();
    Serial.println();
    Serial.print("EMERGENCY AT GATE!!!");
    Serial.println();
    Serial.println();
    Serial.print("GO TO EMERGENCY GATE");
    emergency();       
  }
  else
  {
    gate_6(); 
  }
}



void emergency(){ 
  digitalWrite(EGate_LED, HIGH);
  digitalWrite(RW_LED, LOW); 
  if (digitalRead(EStop_Sensor)==LOW)
  {
    digitalWrite(EGate_LED, LOW);
    delay(500);
    digitalWrite(EGate_LED, HIGH);
    delay(500);
    digitalWrite(EGate_LED, LOW);
    delay(500);
    Serial.println();
    Serial.println();
    Serial.print("Wait to be redirected to a Gate");
    check();
  }
  else
  {
    emergency();
  }
}

void gates_full(){
  Serial.println();
  Serial.println();
  Serial.print("ALL GATES OCCUPIED, PLEASE WAIT!!!");
  while ((digitalRead(G1_Sensor)==LOW) and (digitalRead(G2_Sensor)==LOW) and (digitalRead(G3_Sensor)==LOW) and (digitalRead(G4_Sensor)==LOW) and (digitalRead(G5_Sensor)==LOW) and (digitalRead(G6_Sensor)==LOW))
  {
    ;
  }
  delay(500);
  check();
}
