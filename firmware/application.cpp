#include "application.h"
#include "Adafruit_LEDBackpack.h"

#define TEMP_SENSOR 0x27

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

void displayTemperature(void)
{
  char ones = desiredTemperature % 10;
  char tens = (desiredTemperature / 10) % 10;

  matrix1.clear();
  matrix1.setCursor(0, 0);
  matrix1.write(tens + '0');
  matrix1.writeDisplay();

  matrix2.clear();
  matrix2.setCursor(0, 0);
  matrix2.write(ones + '0');
  matrix2.writeDisplay();
}

int setTemperature(String t)
{
  desiredTemperature = t.toInt();

  displayTemperature();

  // TODO save desired temperature to external flash

  return desiredTemperature;
}

void setupMatrix(Adafruit_8x8matrix m)
{
  m.clear();
  m.writeDisplay();
  m.setTextSize(1);
  m.setTextWrap(false);
  m.setTextColor(LED_ON);
  m.setRotation(0);
  m.setCursor(0, 0);
}

void setup()
{
  Wire.begin();

  matrix1.begin(0x70);
  matrix2.begin(0x71);
  matrix3.begin(0x72);

  setupMatrix(matrix1);
  setupMatrix(matrix2);
  setupMatrix(matrix3);

  Spark.function("set_temp", setTemperature);

  Spark.variable("current_temp", &currentTemperature, INT);
  Spark.variable("desired_temp", &desiredTemperature, INT);
  Spark.variable("is_heat_on", &isHeatOn, BOOLEAN);
  Spark.variable("is_fan_on", &isFanOn, BOOLEAN);

  // TODO read desired temperature from external flash

  Serial.begin(9600);
}

void loop()
{
  Wire.requestFrom(TEMP_SENSOR, 4);
  Serial.print("Read temp sensor: ");
  while (Wire.available())
  {
    unsigned char b = Wire.read();
    Serial.print(b);
    Serial.write(' ');
  }
  Serial.println("");
  // currentTemperature = ??
  delay(800);
}
