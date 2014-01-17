# Continuously polls the core for the actual temp
class ActualTempReadingPoller
  include Sidekiq::Worker

  sidekiq_options :retry => false
  include Sidetiq::Schedulable
  recurrence { minutely }

  def perform #(last_occurrence, current_occurrence)
    the_response = SparkModels::API.read_current_temp
    the_value = the_response.to_hash['result']
    if the_value.kind_of?(Numeric)
      ActualTempReading.create(:value => the_value)
    else
      puts "COULD NOT READ ACTUAL TEMP FROM CORE, #{the_response.inspect}"
    end
  rescue Exception => e
    puts "Failed due to #{e.message}"
  ensure
    # ActualTempReadingPoller.perform_in(15.seconds)
  end
end
