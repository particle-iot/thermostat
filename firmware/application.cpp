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

int currentTemperature = 0;
int desiredTemperature = 0;
bool isHeatOn = false;
bool isFanOn = false;

int setTemperature(String t)
{
  return 1;
}

void setup()
{
  Wire.begin();
  matrix1.begin(0x70);
  matrix2.begin(0x71);
  matrix3.begin(0x72);

  Spark.function("set_temp", setTemperature);
  Spark.variable("current_temp", &currentTemperature, INT);
  Spark.variable("desired_temp", &desiredTemperature, INT);
  Spark.variable("is_heat_on", &isHeatOn, BOOLEAN);
  Spark.variable("is_fan_on", &isFanOn, BOOLEAN);
}

void loop()
{
  matrix3.clear();
  matrix3.drawBitmap(0, 0, smile, 8, 8, LED_ON);
  matrix3.writeDisplay();
  delay(500);
}
