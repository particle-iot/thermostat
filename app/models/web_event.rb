class WebEvent < ActiveRecord::Base
  attr_accessible :name, :event_type, :float_value, :hash_value, :integer_value, :string_value
  serialize :core_json_response, JSON
end
