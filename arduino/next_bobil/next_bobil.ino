/**
 * @example CompGpio.ino
 *
 * @par How to Use
 * This example shows that In nextion screen displays the current 
 * IO mouth level change, to show how to use the API.
 *
 * @author  huangxiaoming (email:<xiaoming.huang@itead.cc>)
 * @date    2016/12/8
 * @copyright 
 * Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 */

#include "Nextion.h"

NexGpio gpio;
NexNumber n0 = NexNumber(0,2,"n0");
NexNumber n1 = NexNumber(0,3,"n1");
//NexText tState = NexText(0, 4, "U1val"); 
/*
NexPage page0 = NexPage(0, 0, "page0");  // Page added as a touch event
NexPage page1 = NexPage(1, 0, "page1");  // Page added as a touch event
NexPage page2 = NexPage(2, 0, "page1");  // Page added as a touch event

#define   GPIO_PUSH_PORT          1
#define   GPIO_PWM_PORT           2
#define   GPIO_PUSH_OUTPUT_MODE   2
#define   GPIO_PWM_OUT_MODE       3
#define   CONTROLS_ID             0           //when the modeel is 1 to be valid
*/
uint32_t pwm_value = 0;

void setup() 
{  
    Serial2.begin(9600);
  // gpio.pin_mode(GPIO_PUSH_PORT,GPIO_PUSH_OUTPUT_MODE,CONTROLS_ID);
   // gpio.pin_mode(GPIO_PWM_PORT,GPIO_PWM_OUT_MODE,CONTROLS_ID);
//   tState.setText("ttt");
 //  n0.val("34");

}

void loop() 
{  Serial2.print("n0.val=12");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial2.write(0xff);
  Serial2.write(0xff);

   Serial2.print("n1.val=50");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial2.write(0xff);
  Serial2.write(0xff);
 
  Serial2.print("U1.val=120");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial2.write(0xff);
  Serial2.write(0xff);

   Serial2.print("U1val.txt=");  // This is sent to the nextion display to set what object name (before the dot) and what atribute (after the dot) are you going to change.
  Serial2.write("\"");
  Serial2.write("12V");  
   Serial2.write("\"");
   Serial2.write(0xff);  // We always have to send this three lines after each command sent to the nextion display.
  Serial2.write(0xff);
  Serial2.write(0xff);
 
  

    delay(1000);
}
