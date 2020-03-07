#define closed 350
#define nowater 70
#define motor 8
#define low_led 6
#define high_led 5
#define warn_led 7
#define volt 12
#define delayled 2
#define voltled 3
#define time1 250
#define time2 250
int top = 0, bottom = 0, flag = 5, trigger = 0;
int pin1();
int pin2();
void control(int top, int bottom);    //
//ARDUINO UNO CODE FOR AUTOMATIC WATER PUMP CONTROLLER. WRITTEN BY ABDULLAH AL MAMUN. || abdullahalmamun@iut-dhaka.edu || //
void setup() {
  Serial.begin(9600);
  pinMode(motor, OUTPUT);
  pinMode(low_led, OUTPUT);
  pinMode(high_led, OUTPUT);
  pinMode(warn_led, OUTPUT);
  pinMode(volt, OUTPUT);
  pinMode(voltled, OUTPUT);
  pinMode(delayled, OUTPUT);
}
void loop()
{
  digitalWrite(volt, HIGH);
  digitalWrite(voltled, HIGH);
  //Serial.println(" HELLO MAMUN! INITIALIZING YOUR FIRST COOL AUTOMATION CODE. [[ volt=high ]]");
  delay(10);
  if (pin1() > closed)
  {
    delay(250);
    if (pin1() > closed)
    {
      delay(250);
      if (pin1() > closed)
        top = 10;
    }
  }
  if (pin1() < nowater)
  {
    delay(250);
    if (pin1() < nowater)
    {
      delay(250);
      if (pin1() < nowater)
        top = 5;
    }
  }
  if (pin2() > closed)
  {
    delay(250);
    if (pin2() > closed)
    {
      delay(250);
      if (pin2() > closed)
        bottom = 10;
    }
  }
  if (pin2() < nowater)
  {
    delay(250);
    if (pin2() < nowater)
    {
      delay(250);
      if (pin2() < nowater)
        bottom = 5;
    }
  }
Serial.println(" NOW TRANSFERRING TO THE CONTROL FUNCTION FROM INSIDE OF LOOP ");
  control(top, bottom);
  if (trigger == 10)            //    motor=low, tank full flag
  {
    digitalWrite(volt, LOW);
    digitalWrite(voltled, LOW);
    for (int b = 0; b <= 40; b++) {
      Serial.println(" inside 1500ms x40 = 60 sec longest delay LOOP for TANK FULL, MOTOR LOW FLAG, volt=low ");
      digitalWrite(delayled, HIGH);
      delay(1000);
      digitalWrite(delayled, LOW);
      delay(500);
    }
    Serial.println(" end of delay,  ");
  }
  if (trigger == 5)         //      motor high
  {
    digitalWrite(volt, LOW);
    digitalWrite(voltled, LOW);
    digitalWrite(delayled, HIGH);
    Serial.println(" inside 1 sec shortest delay, volt=low ");
    delay(1000);
    digitalWrite(delayled, LOW);
    Serial.print(" end of delay, ");
    Serial.println();
  }
  digitalWrite(volt, HIGH);
  digitalWrite(voltled, HIGH);
}
//ARDUINO UNO CODE FOR AUTOMATIC WATER PUMP CONTROLLER. WRITTEN BY ABDULLAH AL MAMUN. IUT. EEE. 152477 //
void control(int top, int bottom)
{
  if (top == 10 && bottom == 10)
  {
    flag = 1;
    digitalWrite(high_led, LOW);
    digitalWrite(warn_led, LOW);
    digitalWrite(low_led, HIGH);
  }
  if (bottom == 10 && flag == 1)
  {
    digitalWrite(motor, LOW);     //================  MOTOR LOW  =================
    digitalWrite(volt, LOW);
    digitalWrite(voltled, LOW);
    Serial.println(" INSIDE MOTOR CONTROL. MOTOR=OFF ");
    delay(1000);
    trigger = 10;
  }
  if (top == 5 && bottom == 5)
  {
    flag = 2;
    digitalWrite(warn_led, LOW);
    digitalWrite(low_led, LOW);
    digitalWrite(high_led, HIGH);
  }
  if (top == 5 && flag == 2)
  {
    digitalWrite(motor, HIGH);      //================  MOTOR HIGH  ================
    digitalWrite(volt, LOW);
    digitalWrite(voltled, LOW);
    Serial.println(" INSIDE MOTOR CONTROL. MOTOR=HIGH ");
    delay(1000);  
    trigger = 5;
  }
  if (flag != 1 && flag != 2) // If no condition matches for some reason.
  {
    digitalWrite(low_led, LOW);
    digitalWrite(high_led, LOW);
    digitalWrite(warn_led, HIGH);
    digitalWrite(volt, LOW);
    digitalWrite(voltled, LOW);
    for (int a = 0; a <= 5; a++) {
      Serial.println(" inside 1000ms x5 sec delay loop for == NO FLAG/CONDITION, volt=low ");
      digitalWrite(delayled, HIGH);
      delay(500);
      digitalWrite(delayled, LOW);
      delay(500);
    }
    Serial.println(" end of delay, ");
  }
}
int pin1()
{
  int read1 = analogRead(A0);
  Serial.print(read1);
  Serial.print(" top ");
  Serial.println();
  return read1;
}
int pin2()
{
  int read2 = analogRead(A2);
  Serial.print(read2);
  Serial.print(" bottom ");
  Serial.println();
  return read2;
}
//ARDUINO UNO CODE FOR AUTOMATIC WATER PUMP CONTROLLER. WRITTEN BY ABDULLAH AL MAMUN. IUT. || abdullahalmamun@iut-dhaka.edu || //
