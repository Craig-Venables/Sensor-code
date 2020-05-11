/*****************************************************************************
  BM1422AGMV.ino

 Copyright (c) 2017 ROHM Co.,Ltd.

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
******************************************************************************/
#include <Wire.h>
#include <BM1422AGMV.h>

BM1422AGMV bm1422agmv(BM1422AGMV_DEVICE_ADDRESS_0E);
void bm1422agmv_isr(void);
int i = 0;
void setup() {
  byte rc;

  Serial.begin(9600);  //defines byte speed of 9600
  while (!Serial);
 
  Wire.begin();   //Initiate the Wire library and join the I2C bus as a master or slave
 
  rc = bm1422agmv.init();


  Serial.println("CLEARSHEET");  
 
  // define 5 columns named "Date", "Time", "Counter" and "millis"
  Serial.println("LABEL,Date,Timer,X_Data,Y_Data,Z_Data,Sq(z+y),H");
 
  if (rc != 0) {
    Serial.println(F("BM1422AGMV initialization failed"));
    Serial.flush();  
  }
  bm1422agmv.isr_func(0, bm1422agmv_isr);
  
}



void loop() {
  byte rc;        //store rc as the byte number
  float mag[5];
  rc = bm1422agmv.get_val(mag);   //set rc as the sensor output vlaue called mag? I2c_1
  if (rc == 0) {     //if rc does not equal zero continue      
      Serial.print("DATA,DATE,TIMER,");
        Serial.print(mag[0],5); Serial.print(",");   //x
        Serial.print(mag[1],5); Serial.print(",");   //y
        Serial.print(mag[2],5); Serial.print(",");   //z
        Serial.println(sqrt(sq(mag[0])+sq(mag[1])+sq(mag[2])),5); Serial.println(",");  //Resultant F
        

        Serial.print(","); Serial.println("SCROLLDATA_20");
   
  }

  delay(500);   // delays by 500 milliseconds
}

void bm1422agmv_isr(void)
{
  bm1422agmv.set_drdy_flg();
}
