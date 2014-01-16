module SparkModels
  class API
    include HTTParty
    debug_output $stderr # An HTTParty method
    base_uri DiyThermostat::Application.config.thermostat_settings.spark_api_base_uri_prefix
    class << self
      def refresh_access_token(options={
        :username => DiyThermostat::Application.config.thermostat_settings.sparkcore_username,
        :password => DiyThermostat::Application.config.thermostat_settings.sparkcore_password
      })
        options.symbolize_keys!
        options.assert_valid_keys( :username, :password )
        options[:grant_type] = 'password'
        post('/oauth/token', {
          :body => options,
          :basic_auth => {
            :username => 'spark',
            :password => 'spark'
          }
        })
      end
    end
  end
end
