#include "application.h"
#include "Adafruit_LEDBackpack.h"
#include <math.h>

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

void saveTemperature()
{
  uint8_t values[2] = { 0, desiredTemperature & 0xff };
  sFLASH_WriteBuffer(values, 0x80000, 2);
}

void loadTemperature()
{
  uint8_t values[2];
  sFLASH_ReadBuffer(values, 0x80000, 2);
  desiredTemperature = values[1];
  displayTemperature();
}

int setTemperature(String t)
{
  // TODO more robust error handling
  //      what if t is not a number
  //      what if t is outside a sensible range, e.g., 55-85
  desiredTemperature = t.toInt();
  displayTemperature();
  saveTemperature();
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

  loadTemperature();

  pinMode(A0, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);

  Serial.begin(9600);
}

void loop()
{
  static int wait = 1000;
  if (!wait)
  {
    wait = 1000;

    Wire.requestFrom(TEMP_SENSOR, 4);

    int humidity = (Wire.read() << 8) & 0x3f00;
    humidity |= Wire.read();
    float percentHumidity = humidity / 163.83;
    Serial.print("Relative humidity is ");
    Serial.println(percentHumidity);

    int temp = (Wire.read() << 6) & 0x3fc0;
    temp |= Wire.read() >> 2;
    temp *= 165;
    float fTemp = temp / 16383.0 - 40.0;
    currentTemperature = roundf(fTemp);
    Serial.print("Temperature is ");
    Serial.println(fTemp);
  }

  int pot = analogRead(A2);
  digitalWrite(A0, pot >> 11);
  digitalWrite(A1, digitalRead(A3));

  --wait;
}
