rm db/development.sqlite3
redis-cli FLUSHALL
bundle exec rake db:migrate
