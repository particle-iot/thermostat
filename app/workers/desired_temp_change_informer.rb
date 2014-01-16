class DesiredTempChangeInformer
  include Sidekiq::Worker

  def perform(web_event_id)
    we = WebEvent.find(web_event_id)
    begin
      the_response = SparkModels::API.set_desired_temp(:param => we.integer_value)
      json = the_response.to_hash
      we.core_json_http_status = the_response.header.code.to_i
      we.core_json_response = json
      we.save!
    rescue Exception => e
      raise "could not call API #{e.class}: #{e.message}"
    end
  end
end
