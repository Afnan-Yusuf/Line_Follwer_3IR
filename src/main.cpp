#include <Arduino.h>
#include <Ramp.h>
#define motlf 18 // motor pins
#define motlb 5
#define motrf 19
#define motrb 12
// #define _DEBUG_

const int freqm = 5000; // motor pwm frequency
const int mrfc = 0;     // Motor Right Forward Channel (mrfc)
const int mrbc = 2;     // Motor Right Backward Channel (mrbc)
const int mlfc = 4;     // Motor Left Forward Channel (mlfc)
const int mlbc = 6;     //
const int mpwmr = 8;    // motor pwm resolution(8bit)

int turnspeed = 170;
int threshold = 200;
int basespeed = 210;

bool oncenter = false;
bool onleft = false;
bool onright = false;
int leftsensor = 25;
int rightsensor = 27;
int centersensor = 26;
int csval = 0;
int lsval = 0;
int rsval = 0;

void fd();
void rt();
void lt();

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

}
void loop()
{
  csval = analogRead(centersensor);
  lsval = analogRead(leftsensor);
  rsval = analogRead(rightsensor);
  csval > threshold ? oncenter = true : oncenter = false;
  lsval > threshold ? onleft = true : onleft = false;
  rsval > threshold ? onright = true : onright = false;
  if (oncenter == true && onleft == false && onright == false)
  {
    digitalWrite(LED_BUILTIN, HIGH);

    fd();
  }
  else
  {
    digitalWrite(LED_BUILTIN, LOW);

    if (onleft == true && oncenter == false && onright == false)
    {
      lt();
    }
    if (onright == true && oncenter == false && onleft == false)
    {

      rt();
    }
  }
  if (onright == true && oncenter == true && onleft == true)
  {
    fd();
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

}
void fd()
{
  ledcWrite(mrfc, basespeed);
  ledcWrite(mrbc, 0);
  ledcWrite(mlfc, basespeed);
  ledcWrite(mlbc, 0);
}
void rt()
{
  ledcWrite(mrfc, 0);
  ledcWrite(mrbc, turnspeed);
  ledcWrite(mlfc, turnspeed);
  ledcWrite(mlbc, 0);
}
void lt()
{

  ledcWrite(mrfc, turnspeed);
  ledcWrite(mrbc, 0);
  ledcWrite(mlfc, 0);
  ledcWrite(mlbc, turnspeed);
}
