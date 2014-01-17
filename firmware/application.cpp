#include "application.h"
#include "Adafruit_LEDBackpack.h"
#include <math.h>

#define TEMP_SENSOR 0x27
#define FAN_PIN     A0
#define HEAT_PIN    A1
#define POT_PIN     A2
#define PIR_PIN     A3
#define DESIRED_TEMP_FLASH_ADDRESS 0x80000

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
bool motionDetected = false;

int lastChangedPot = -80;

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
  sFLASH_EraseSector(DESIRED_TEMP_FLASH_ADDRESS);
  Serial.println("Saving temperature to flash");
  uint8_t values[2] = { (uint8_t)desiredTemperature, 0 };
  sFLASH_WritePage(values, DESIRED_TEMP_FLASH_ADDRESS, 2);
}

void loadTemperature()
{
  Serial.println("Loading and displaying temperature from flash");
  uint8_t values[2];
  sFLASH_ReadBuffer(values, DESIRED_TEMP_FLASH_ADDRESS, 2);
  desiredTemperature = values[0];
  displayTemperature();
}

int setTemperature(int t)
{
  desiredTemperature = t;
  displayTemperature();
  saveTemperature();
  return desiredTemperature;
}

int setTemperatureFromString(String t)
{
  // TODO more robust error handling
  //      what if t is not a number
  //      what if t is outside 50-90 range

  Serial.print("Setting desired temp from web to ");
  Serial.println(t);

  return setTemperature(t.toInt());
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

  Spark.function("set_temp", setTemperatureFromString);

  Spark.variable("current_temp", &currentTemperature, INT);
  Spark.variable("desired_temp", &desiredTemperature, INT);
  Spark.variable("is_heat_on", &isHeatOn, BOOLEAN);
  Spark.variable("is_fan_on", &isFanOn, BOOLEAN);

  Serial.begin(9600);

  loadTemperature();

  pinMode(FAN_PIN, OUTPUT);
  pinMode(HEAT_PIN, OUTPUT);
  pinMode(POT_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
}

void loop()
{
  static int wait = 0;
  if (!wait)
  {
    wait = 1000;

    Wire.beginTransmission(TEMP_SENSOR);
    Wire.endTransmission();
    delay(40);
    Wire.requestFrom(TEMP_SENSOR, 4);
    uint8_t b = Wire.read();
    Serial.print("I2C Status bits are ");
    Serial.println(b >> 6);

    int humidity = (b << 8) & 0x3f00;
    humidity |= Wire.read();
    float percentHumidity = humidity / 163.83;
    Serial.print("Relative humidity is ");
    Serial.println(percentHumidity);

    int temp = (Wire.read() << 6) & 0x3fc0;
    temp |= Wire.read() >> 2;
    temp *= 165;
    float fTemp = temp / 16383.0 - 40.0;
    fTemp = fTemp * 1.8 + 32.0; // convert to fahrenheit
    currentTemperature = roundf(fTemp);
    Serial.print("Temperature is ");
    Serial.println(fTemp);
  }

  int pot = 4095 - analogRead(POT_PIN);
  if (1000 == wait)
  {
    Serial.print("Potentiometer reading: ");
    Serial.println(pot);

    Serial.print("PIR reading: ");
    Serial.println(analogRead(PIR_PIN));
  }

  if (3550 < analogRead(PIR_PIN))
  {
    motionDetected = true;
    // lean more toward comfort than energy efficiency
  }

  // If user has adjusted the potentiometer
  if (fabsf(pot - lastChangedPot) > 64)
  {
    // Don't set temp on boot
    if (lastChangedPot >= 0)
    {
      // map 0-4095 pot range to 50-90 temperature range
      int t = roundf(pot * (40.0/4095.0) + 50.0);
      setTemperature(t);
      Serial.print("Setting desired temp based on potentiometer to ");
      Serial.println(t);
    }
    lastChangedPot = pot;
  }

  isHeatOn = desiredTemperature > currentTemperature;
  digitalWrite(HEAT_PIN, isHeatOn);

  // just run them at the same time for now
  isFanOn = isHeatOn;
  digitalWrite(FAN_PIN, isFanOn);

  --wait;
}
