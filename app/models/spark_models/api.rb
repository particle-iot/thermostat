module SparkModels
  class API
    include HTTParty
    debug_output $stderr # An HTTParty method
    base_uri DiyThermostat::Application.config.thermostat_settings.api_base_uri_prefix
    class << self
       # curl https://api.spark.io/v1/devices/55ff70064989495339432587/set_temp -d 'access_token=b5e5a49521def21d2f0a6c061fa4bf73cae7166e' -d 'param=66'
      def set_desired_temp(options={ })
        raise unless options[:param].kind_of?(Integer)
        device_id    = DiyThermostat::Application.config.thermostat_settings.device_id
        function_name = 'set_temp'
        options[:access_token] = DiyThermostat::Application.config.thermostat_settings.access_token
        post("/v1/devices/#{device_id}/#{function_name}", {
          :body => options
        })
      end

      # NOTE: BUGGY, if you specify options, it doesn't override correctly
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
