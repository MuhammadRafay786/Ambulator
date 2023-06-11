/*
Semester Project (Ambulator)
------------------------------------------------------------------
This is C language program that controls the ball screw mechanism 
for various coditions of Tidal Volume, Respiratory Rate, And 
Inhale Exhale Ratio (IE Ratio), Allowing the user to select 27 
diiferent configurations for pressing AMBU bag.
------------------------------------------------------------------
Written by:
Hurraira Adrees         (2021-MC-01)
Muhammad Saad Yaseen    (2021-MC-37)
Muhammad Rafay          (2021-MC-38)
Muhammad Mujahid Iqbal  (2021-MC-39)
Abiam Asif Khalid       (2021-MC-40)
Compiler and IDE: Energia (A modified version of Ardiuno for Tiva C series Launchpad Kit)
*/

#include <LiquidCrystal.h> //Library for LCD module 

int Dir = 2;  //Direction Bit of Motor (PB5)
int Step = 3; //Steps for motor (PB0)

// On Board LED
#define LEDR RED_LED   //Onboard RED led
#define LEDB BLUE_LED  //Onboard BLUE led
#define LEDG GREEN_LED //Onboard GREEN led

//For External LED's
#define RS PB_1 //Register Selector
#define EN PD_0 //Enabe Pin of LCD 
#define D4 PD_1 //Data Pin 4
#define D5 PD_2 //Data Pin 5
#define D6 PD_3 //Data Pin 6
#define D7 PE_1 //Data Pin 7

LiquidCrystal lcd(RS, EN, D4, D5, D6, D7); //Initialising LCD 1602

int Steps = 0;      //Defines Steps for Tidal Volume
int stepDelay = 0;  //Time gap between each step
int Inhale = 0;     //Inhale Part of cycle
int Exhale = 0;     //Exhale Part of cycle
int stopAmbu =0 ;    //For Resetting

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(PB_2, INPUT_PULLUP);  //Tidal Volume of 200
  pinMode(PC_4, INPUT_PULLUP);  //Tidal Volume of 300
  pinMode(PA_2, INPUT_PULLUP);  //Tidal Volume of 400

  pinMode(PE_0, INPUT_PULLUP);  //Breath Cycle of 08 pm
  pinMode(PC_5, INPUT_PULLUP);  //Breath Cycle of 12 pm
  pinMode(PC_7, INPUT_PULLUP);  //Breath Cycle of 16 pm 

  pinMode(PB_3, INPUT_PULLUP);  //Inhale Exhale 1:2 
  pinMode(PC_6, INPUT_PULLUP);  //Inhale Exhale 1:3
  pinMode(PA_4, INPUT_PULLUP);  //Inhale Exhale 1:4

  pinMode(PA_3, INPUT_PULLUP);  //Reset
  
  pinMode(Step, OUTPUT);    //Step to Motor Driver
  pinMode(Dir, OUTPUT);     //Direction To Motor Driver
  pinMode(LEDR, OUTPUT);    //RED led
  pinMode(LEDB, OUTPUT);    //BLUE led
  pinMode(LEDG, OUTPUT);    //GREEN led

  lcd.begin(16, 2);       //Starting LCD
  lcd.setCursor(3, 0);    //Placing Cursor 
  lcd.print("AMBULATOR"); //Display Text
  delay(3500);
  lcd.clear();
}

void loop() {
  // put your main code here, to run repeatedly:
  
  if (Steps == 0)   //Red LED Will Be On Until Tidal Volume Is Selected
  {
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDB, LOW);
    digitalWrite(LEDG, LOW);
    lcd.setCursor(0, 0); //Placing Cursor 
    lcd.print("Tidal Volume: "); //Display Text
    delay(500);
  }

  if ((digitalRead(PB_2) == LOW) && (Steps==0)) //Tidal Volume Corresponding to 200
  {
    Steps = 20480;        //3.2 revolutions = 3.2*6400 = 20480
    lcd.setCursor(6, 1);  //Placing Cursor 
    lcd.print("200");     //Display Text
    delay(1000);
    lcd.clear();
    
  } 

  if ((digitalRead(PC_4) == LOW) && (Steps==0)) //Tidal Volume Corresponding of 300
  {
    Steps = 30720;       //4.8 revolutions = 4.8*6400 = 30720
    lcd.setCursor(6, 1); //Placing Cursor 
    lcd.print("300");    //Display Text
    delay(1000);
    lcd.clear();
  }

  if ((digitalRead(PA_2) == LOW) && (Steps==0)) //Tidal Volume Correspinding of 400
  {
    Steps = 40960;       //6.4 revolutions = 6.4*6400 = 40960
    lcd.setCursor(6, 1); //Placing Cursor 
    lcd.print("400");    //Display Text
    delay(1000);
    lcd.clear();
    
  }

  if ((Steps != 0) && (stepDelay==0)) //Blue LED Will Be On Until Breaths Per Minute Is Selected
  {
    digitalWrite(LEDB, HIGH);
    digitalWrite(LEDR, LOW);
    digitalWrite(LEDG, LOW);
    lcd.setCursor(0, 0);        //Placing Cursor 
    lcd.print("Breaths PM: ");  //Display Text
    delay(500);
  }

  if ((digitalRead(PE_0) == LOW) && (stepDelay==0) && (Steps != 0))   //Based on the previous choice the Delay will be selected 
  {                                                                   //for 8 Breath Per Minute
    lcd.setCursor(7, 1); //Placing Cursor 
    lcd.print("08");     //Display Text
    delay(1000);
    lcd.clear();
   switch (Steps)             //8 BPM = 7.5seconds for each breath
   {                          //Delay for each breath = 7.5/(2*Steps)
    case 20480:               //For Tidal Volume 200
      stepDelay = 184;
      break;
    case 30720:               //For Tidal Volume 300
      stepDelay = 122;
      break;
    case 40960:               //For Tidal Volume 200
      stepDelay = 92;       
      break;
    default:
      break;
   }
  }

  if ((digitalRead(PC_5) == LOW) && (stepDelay==0) && (Steps != 0)) //Based on the previous choice the Delay will be selected 
  {                                                                 //for 12 Breath Per Minute
    lcd.setCursor(7, 1); //Placing Cursor 
    lcd.print("12");     //Display Text
    delay(1000);
    lcd.clear();
    switch (Steps)            //12 BPM = 5 seconds for each breath
   {                          //Delay for each breath = 5/(2*Steps)
    case 20480:               //For Tidal Volume 200
      stepDelay = 122;
      break;
    case 30720:               //For Tidal Volume 300
      stepDelay = 82;
      break;
    case 40960:               //For Tidal Volume 400
      stepDelay = 62;
      break;
    default:
      break;
   }
  }

  if ((digitalRead(PC_7) == LOW) && (stepDelay==0) && (Steps != 0)) //Based on the previous choice the Delay will be selected
  {                                                                 //for 16 Breath Per Minute
    lcd.setCursor(7, 1); //Placing Cursor 
    lcd.print("16");     //Display Text
    delay(1000);
    lcd.clear();
   switch (Steps)           //16 BPM = 3.75 seconds for each breath
   {                        //Delay for each breath = 3.75/(2*Steps)
    case 20480:             //For Tidal Volume 200
      stepDelay = 92;
      break;
    case 30720:             //For Tidal Volume 300
      stepDelay = 62;
      break;
    case 40960:             //For Tidal Volume 400
      stepDelay = 46;
      break;
    default:
      break;
   }
  }

 if ((stepDelay !=0)&&(Steps !=0))  //Green LED Will Be On Until Tidal Volume Is Selected
 {
  lcd.setCursor(0, 0);      //Placing Cursor 
  lcd.print("IE Ratio: ");  //Display Text
  delay(500);
  digitalWrite(LEDG, HIGH);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDB, LOW);
 }

  if ((digitalRead(PB_3)==LOW) && (Inhale==0) && (stepDelay !=0)) //Divison of breath in Inhale And Exhale Part Ratio 1:2
  {
    Inhale = stepDelay/3;  //Inhale part = Delay/(1+2)
    Exhale = Inhale*2;     //EXhale part = Inhale*2
    lcd.setCursor(7, 1);   //Placing Cursor 
    lcd.print("1:2");      //Display Text
    delay(1000);
    lcd.clear();

  }

  if ((digitalRead(PC_6)==LOW) && (Inhale==0) && (stepDelay !=0)) //Divison of breath in Inhale And Exhale Part Ratio 1:3
  {
    Inhale = stepDelay/4;  //Inhale part = Delay/(1+3)
    Exhale = Inhale*3;     //EXhale part = Inhale*3 
    lcd.setCursor(7, 1);   //Placing Cursor 
    lcd.print("1:3");      //Display Text
    delay(1000);
    lcd.clear();
  }

  if ((digitalRead(PA_4)==LOW)&& (Inhale==0) && (stepDelay !=0)) //Divison of breath in Inhale And Exhale Part Ratio 1:4
  {
    Inhale = stepDelay/5;   //Inhale part = Delay/(1+4)
    Exhale = Inhale*4;      //EXhale part = Inhale*4
    lcd.setCursor(7, 1);    //Placing Cursor 
    lcd.print("1:4");       //Display Text
    delay(1000);
    lcd.clear();
  }

  if (digitalRead(PA_3) == LOW) //Reset Condition for All Variables
  {
    delay(1000);
    Steps = 0;
    stopAmbu = 0;
    stepDelay = 0;
    Inhale = 0;
    Exhale = 0;
    lcd.begin(16, 2);       //Starting LCD
    lcd.setCursor(3, 0);    //Placing Cursor 
    lcd.print("AMBULATOR"); //Display Text
    delay(1000);
    lcd.clear();
   }

  while ((Steps != 0)&&(stepDelay != 0)&&(Inhale != 0)) 
  {
    if (Inhale < 20)
    {
        Inhale = 20;
    }
    
    digitalWrite(LEDG, HIGH);       //Purple Colour for inhale
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDB, LOW);
    
    digitalWrite(Dir, HIGH);        //Inhale cycle has High Direction
    for (int x=0; x< Steps; x++)
    {
      if (digitalRead(PA_3) == LOW) //Stopping Condition
      {
        stopAmbu = 1;
        lcd.print("Stopping...");
        lcd.setCursor(0, 0);
      }
      
      digitalWrite(Step, HIGH);     //Stepping Part
      delayMicroseconds(Inhale);
      digitalWrite(Step, LOW);
      delayMicroseconds(Inhale);
    }

    digitalWrite(LEDG, LOW);        //Yellow Colour for inhale
    digitalWrite(LEDR, HIGH);
    digitalWrite(LEDB, HIGH);
   
    digitalWrite(Dir, LOW);         //Exhale cycle has Low Direction
    for (int x=0; x< Steps; x++)
    {
      if (digitalRead(PA_3) == LOW) //Stopping Condition
      {
        stopAmbu = 1;
        lcd.print("Stopping...");
        lcd.setCursor(0, 0);
      }
     
      digitalWrite(Step, HIGH);    //Stepping Part
      delayMicroseconds(Exhale);
      digitalWrite(Step, LOW);
      delayMicroseconds(Exhale);
    }

    if (stopAmbu == 1)      //Resetting Variables after Stopping
    {
      Steps = 0;
      stopAmbu = 0;
      stepDelay = 0;
      Inhale = 0;
      Exhale = 0;
      lcd.clear();
      break;
    }
  }
}
