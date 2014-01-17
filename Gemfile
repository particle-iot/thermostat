source 'https://rubygems.org'

ruby '2.0.0'

gem 'rails', '3.2.14'
gem 'sqlite3' # todo replace with gem 'mongoid' or postgres
gem 'jquery-rails'
gem 'sidekiq'
gem 'sidetiq'
gem 'httparty'

group :assets do
  gem 'sass-rails',   '~> 3.2.3'
  # gem 'coffee-rails', '~> 3.2.1'
  gem 'uglifier', '>= 1.0.3'
end

group :development do
  gem 'quiet_assets'
  gem 'awesome_print'
  gem 'pry-byebug' # NOTE: use with `binding.pry`
  gem 'letter_opener'
end

group :development, :test do
  gem 'pry-rails'
  gem 'factory_girl_rails', require: false
  gem 'rspec-rails'
end
