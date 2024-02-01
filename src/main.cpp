#include <Arduino.h>
#define motlf 18 // motor pins
#define motlb 5
#define motrf 19
#define motrb 12
#define _DEBUG_

const int freqm = 5000; // motor pwm frequency
const int mrfc = 0;     // Motor Right Forward Channel (mrfc)
const int mrbc = 2;     // Motor Right Backward Channel (mrbc)
const int mlfc = 4;     // Motor Left Forward Channel (mlfc)
const int mlbc = 6;     //
const int mpwmr = 8;    // motor pwm resolution(8bit)
int rpwm = 0;           // pwm value to right motor
int lpwm = 0;

int turnspeed = 210;
int threshold = 500;
int basespeed = 210;
int minspeed = (0);
int maxspeed = 255;
int lmotspeed = 0;
int rmotspeed = 0;

bool oncenter = false;
bool onleft = false;
bool onright = false;
int leftsensor = 25;
int rightsensor = 27;
int centersensor = 26;
int crspeed = 0;
int clspeed = 0;
int csval = 0;
int lsval = 0;
int rsval = 0;
int error = 0;
int lasterror = 0;
int derror = 0;

void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  ledcSetup(mrfc, freqm, mpwmr); // pwm channel and frequency and resolution setup
  ledcSetup(mrbc, freqm, mpwmr);
  ledcSetup(mlfc, freqm, mpwmr);
  ledcSetup(mlbc, freqm, mpwmr);
  ledcAttachPin(motrf, mrfc); // attach motor pins pwm channels
  ledcAttachPin(motrb, mrbc);
  ledcAttachPin(motlf, mlfc);
  ledcAttachPin(motlb, mlbc);
  ledcWrite(mrfc, 0); // write all pwmm channel 0
  ledcWrite(mrbc, 0);
  ledcWrite(mlfc, 0);
  ledcWrite(mlbc, 0);
#ifdef _DEBUG_
  Serial.begin(9600);
#endif
}
void loop()
{
  csval = analogRead(centersensor);
  lsval = analogRead(leftsensor);
  rsval = analogRead(rightsensor);
  csval > threshold ? oncenter = true : oncenter = false;
  lsval > threshold ? onleft = true : onleft = false;
  rsval > threshold ? onright = true : onright = false;
  error = (rsval - lsval);
  if (oncenter == true && onleft == false && onright == false)
  {
    digitalWrite(LED_BUILTIN, HIGH);

    crspeed = basespeed - error;
    clspeed = basespeed + error;

    crspeed > maxspeed ? crspeed = maxspeed : crspeed = crspeed;
    crspeed < basespeed ? crspeed = basespeed : crspeed = crspeed;

    clspeed < basespeed ? clspeed = basespeed : clspeed = clspeed;
    clspeed > maxspeed ? clspeed = maxspeed : clspeed = clspeed;

    ledcWrite(mrfc, crspeed);
    ledcWrite(mrbc, 0);
    ledcWrite(mlfc, clspeed);
    ledcWrite(mlbc, 0);
  }else{
    digitalWrite(LED_BUILTIN, LOW);
  }
  if (onleft == true && oncenter == false && onright == false)
  {
    ledcWrite(mrfc, turnspeed);
    ledcWrite(mrbc, 0);
    ledcWrite(mlfc, 0);
    ledcWrite(mlbc, turnspeed);
    derror = 1;
  }
  if (onright == true && oncenter == false && onleft == false)
  {
    ledcWrite(mrfc, 0);
    ledcWrite(mrbc, turnspeed);
    ledcWrite(mlfc, turnspeed);
    ledcWrite(mlbc, 0);
    derror = 2;
  }
  if (onright == true && oncenter == true && onleft == true)
  {
    ledcWrite(mrfc, basespeed);
    ledcWrite(mrbc, 0);
    ledcWrite(mlfc, basespeed);
    ledcWrite(mlbc, 0);
  }
  /*if (onleft == false && oncenter == false && onright == false)
  {
    if (derror == 1)
    {
      ledcWrite(mrfc, turnspeed);
      ledcWrite(mrbc, 0);
      ledcWrite(mlfc, 0);
      ledcWrite(mlbc, turnspeed);
    }
    if (derror == 2)
    {
      ledcWrite(mrfc, 0);
      ledcWrite(mrbc, turnspeed);
      ledcWrite(mlfc, turnspeed);
      ledcWrite(mlbc, 0);
    }
  }*/
#ifdef _DEBUG_
  Serial.print(crspeed);
  Serial.print("\t");
  Serial.print(clspeed);
  Serial.print("\t");
  Serial.print(derror);
  Serial.print("\t");
  Serial.print(error);
  Serial.println("\t");
#endif
}
