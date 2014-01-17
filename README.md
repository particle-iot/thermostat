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

## Server Setup

The server components of this app is a Rails 3.2 app designed to be deployed to Heroku.
We use sidekiq for background job processing.
Instructions below are for OS X.

### Dependencies

* Ruby 2.0 (recommended to use rvm, rbenv, chruby, or other ruby version manager) (this app is ruby-2.0.0-p247)
* bundler: `gem install bundler`
* Install redis: `brew install redis`
* Install foreman: download package from here https://github.com/ddollar/foreman
* `bundle install`

### Run Locally

In one terminal:

    redis-server /usr/local/etc/redis.conf

(following instructions from homebrew install)

In another terminal:

    script/start_server.sh

* Note: You might need to change the SPARK_CORE_DEVICE_ID and SPARK_CORE_ACCESS_TOKEN env vars in this .sh file
  for this to work.

Hit `http://localhost:5000` in a browser


### Bomb and rebuild dev environment


Remove sqlite database:

    rm db/development.sqlite3

Flush everything from Redis

    redis-cli FLUSHALL

Rebuild the database

    bundle exec rake db:migrate

Fire up the server again

Note: this is encapsulated in script/bomb_and_rebuild.sh

### Dev tips

You can put `binding.pry` pretty much anywhere in the code to bring up an interative debuging console.
Then hit a brower make or whatever, and in the terminal where the start_server.sh script ran, you can type commands (like a var name) and see their value, etc.

The "SQLite Professional Read-Only" OS X app is a nice free app to look at the data the app is generating in real time.
