#include <AS5147P.h>

int csn = 10;
int miso = 74;
int mosi = 75;
int sclk = 76;

AS5147P as5147p(csn, mosi, miso, sclk);

void setup() {
  Serial.begin(9600);
  as5147p.startup();
}

void loop() {
  int data = as5147p.getPosition();
  printf("%i\r\n",data);
}
