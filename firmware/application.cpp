#include "application.h"
#include "Adafruit_LEDBackpack.h"

Adafruit_8x8matrix matrix1;
Adafruit_8x8matrix matrix2;
Adafruit_8x8matrix matrix3;

static const uint8_t smile[] = {
  0b00111100,
  0b01000010,
  0b10100101,
  0b10000001,
  0b10100101,
  0b10011001,
  0b01000010,
  0b00111100
};

void setup()
{
  Wire.begin();
  matrix1.begin(0x70);
  matrix2.begin(0x71);
  matrix3.begin(0x72);
}

void loop()
{
  matrix1.clear();
  delay(500);
  matrix1.drawBitmap(0, 0, smile, 8, 8, LED_ON);
  matrix1.writeDisplay();
  delay(500);
}
