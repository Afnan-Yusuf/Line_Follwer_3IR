#include <Arduino.h>
#include <Ramp.h>
#define motlf 13 // motor pins
#define motlb 12
#define motrf 25
#define motrb 33
// #define _DEBUG_

const int freqm = 5000; // motor pwm frequency
const int mrfc = 0;     // Motor Right Forward Channel (mrfc)
const int mrbc = 2;     // Motor Right Backward Channel (mrbc)
const int mlfc = 4;     // Motor Left Forward Channel (mlfc)
const int mlbc = 6;     //
const int mpwmr = 8;    // motor pwm resolution(8bit)

int turnspeed = 150;
int threshold = 200;
int basespeed = 190;

bool oncenter = false;
bool onleft = false;
bool onright = false;
int leftsensor = 17;
int rightsensor = 34;
int centersensor = 39;
int center1sensor = 18;
int farleftsensor = 4;
int farrightsensor = 32;
int csval = 0;
int lsval = 0;
int rsval = 0;
int error = 0;

void fd();
void rt();
void lt();

const int irPins[8] = {4, 16, 17, 18, 39, 34, 35, 32}; // Adjust according to your setup

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
  pinMode(centersensor, INPUT);
  pinMode(leftsensor, INPUT);
  pinMode(rightsensor, INPUT);
  pinMode(center1sensor, INPUT);
  pinMode(farleftsensor, INPUT);
  pinMode(farrightsensor, INPUT);

}
void loop()
{
  if(digitalRead(centersensor) == HIGH && digitalRead(center1sensor) == HIGH){
    oncenter = true;
    error = 0;
  }else{
    oncenter = false;
  }


  if(digitalRead(leftsensor) == HIGH){
    onleft = true;
    error = -1;
  }else{
    onleft = false;
  }

  if(digitalRead(rightsensor) == HIGH){
    onright = true;
    error = 1;
  }else{
    onright = false;
  }

  if(digitalRead(farleftsensor) == HIGH){
    onleft = true;
    error = -1;
  }else{
    onleft = false;
  }

  if(digitalRead(farrightsensor) == HIGH){
    onright = true;
    error = 1;
  }else{
    onright = false;
  }


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
