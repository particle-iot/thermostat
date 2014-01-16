class DesiredTempChangeInformer
  include Sidekiq::Worker

  def perform(web_event_id)
    we = WebEvent.find(web_event_id)
    puts 'AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA'
    puts we.inspect
  end
end
