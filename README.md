DIY Internet-Connected Thermostat
=================================

## What we need

* Hardware
  * Enclosure
    * Wooden case
    * Mounting backplate
    * Acrylic faceplate
  * Electronics
    * Sensor board
    * Relay board
    * Display
    * Spark Core
* Firmware
  * PID loop
  * Sensors
    * Temperature
    * Humidity
    * PIR
  * User input
  * Display
  * Communications
* Server
  * Web UI
  * Thermostat controller
  * Thermostat listener
  * Machine learning

## Hardware

The thermostat display is composed of 3
[Adafruit Mini 8x8 LED Matrix boards](http://www.adafruit.com/products/870#Technical_Details).

The temperature and humidity are sensed using a
[Honeywell HIH6131-021-001](http://www.digikey.com/product-detail/en/HIH6131-021-001/480-3652-6-ND/2704706).

These are all controlled by the Spark Core using a
common I2C bus where pin D0 is SDA and pin D1 is SCL.
The displays (from left to right) are on I2C addresses
0x70, 0x71, and 0x72.

### Testing/Integrationy things

### Summary/Retrospective time ( 10-11:30pm )

Where we reflect on the badass shiz we did, write up blog stuff, etc

