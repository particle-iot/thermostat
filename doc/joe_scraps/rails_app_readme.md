About
=====

Instructions below are for OS X.

Dependencies
------------

* Ruby 2.0 (recommended to use rvm, rbenv, chruby, or other ruby version manager)
* bundler: `gem install bundler`
* Install redis: `brew install redis`
* Install foreman: download package from here https://github.com/ddollar/foreman

Run
---

In one terminal:

    redis-server

In another terminal:

    foreman start

Hit `http://localhost:5000` in a browser (NOTE, NOT :3000 like normal rails apps)
