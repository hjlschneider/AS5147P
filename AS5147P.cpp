/*
  AS5147P device library code is place under the MIT License
  Copyright (c) 2016 H.J.L. Schneider

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.  
*/

#include <AS5147P.h>

AS5147P::AS5147P(uint8_t csn, uint8_t si, uint8_t so, uint8_t clk) {
  pinMode(csn, OUTPUT);
  pinMode(si, OUTPUT);
  pinMode(so, INPUT);
  pinMode(clk, OUTPUT);

  _csn = csn;
  _si = si;
  _so = so;
  _clk = clk;
}

void AS5147P::startup() {
  digitalWrite(_csn, HIGH);
  SPI.begin();
}

uint16_t AS5147P::getPosition() {
  SPI.beginTransaction(SPISettings(10000000, MSBFIRST, SPI_MODE1));

  // Send command
  digitalWrite(_csn, LOW);
  delayMicroseconds(1);
  SPI.transfer16(0xFFFF);
  digitalWrite(_csn, HIGH);

  // Read data
  digitalWrite(_csn, LOW);
  delayMicroseconds(1);
  angle = SPI.transfer16(0xC000);
  digitalWrite(_csn, HIGH);
  SPI.endTransaction();

  angle = (angle & (0x3FFF));

  uint16_t pos = ( (unsigned long) angle)*360UL/1638UL;
  return pos;
}
