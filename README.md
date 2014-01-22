Spark Open Source Thermostat
============================

This repo contains all of the software goodies produced in a Spark Team Hackaton described in detail on the [Spark Blog](http://blog.spark.io/2014/01/17/open-source-thermostat).

## Hardware

The thermostat display is composed of 3
[Adafruit Mini 8x8 LED Matrix boards](http://www.adafruit.com/products/870#Technical_Details).

The temperature and humidity are sensed using a
[Honeywell HIH6131-021-001](http://www.digikey.com/product-detail/en/HIH6131-021-001/480-3652-6-ND/2704706).

These are all controlled by the Spark Core using a
common I2C bus where pin D0 is SDA and pin D1 is SCL.
The displays (from left to right) are on I2C addresses
0x70, 0x71, and 0x72.

## Firmware

To build firmware for this product, you'll first need to be able to build Spark Core firmware by following the instructions
[shown here](https://github.com/spark/core-firmware).

Once you have that working, you can simply copy all of the files from `/firmware` in this repo into `core-firmware/src` and run `make` again to build.  (i.e. `cp thermostat/firmware/* core-firmware/src`)

## Server Setup

The server components are:
* a Rails 3.2 app
* Sidekiq and Redis for background job processing

Development was done on OS X.

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

    bash script/start_server.sh

* Note: You might need to change the SPARK_CORE_DEVICE_ID and SPARK_CORE_ACCESS_TOKEN env vars in this .sh file
  for this to work.

Hit `http://localhost:5000` in a browser

### Dev tips

You can put `binding.pry` pretty much anywhere in the code to bring up an interative debuging console.
Then hit a brower make or whatever, and in the terminal where the start_server.sh script ran, you can type commands (like a var name) and see their value, etc.

The "SQLite Professional Read-Only" OS X app is a nice free app to look at the data the app is generating in real time.

When developing, it's nice to be able to destroy everything and start fresh when you are hacking:

    bash script/bomb_and_rebuild.sh

### What's Next?

Get your hack on, :), have fun. If you do something cool with anything in here, consider sharing it on the [community site](http://community.sparkdevices.com).

Check out some of these other related open thermostat projects:

* https://github.com/science/openthermo
* http://www.adafruit.com/blog/2014/01/13/ardustat-web-controlled-wireless-arduino-based-thermostat-featuring-adafruit-cc3000-arduino/
* http://thermostatmonitor.com/
