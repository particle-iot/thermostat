module SparkModels
  class API
    include HTTParty
    debug_output $stderr # An HTTParty method
    base_uri DiyThermostat::Application.config.thermostat_settings.api_base_uri_prefix
    class << self
      # curl https://api.spark.io/v1/devices/55ff6a064989495321172587/desired_temp\?access_token=8bfa9efde28f2d73017510a068ed6b9db05ad478
      def read_current_temp
        device_id    =  DiyThermostat::Application.config.thermostat_settings.device_id
        access_token = DiyThermostat::Application.config.thermostat_settings.access_token
        var_name = 'current_temp'
        get("/v1/devices/#{device_id}/#{var_name}", :query => {
          :access_token => access_token
        })
      end
      # DOCS implementation
      # curl https://api.spark.io/v1/devices/55ff6a064989495321172587/set_temp -d access_token=8bfaefde28f2d73017510a068ed6b9db05ad478 -d t=55
      def set_desired_temp(options={ })
        raise unless options[:param].kind_of?(Integer)
        device_id    =  DiyThermostat::Application.config.thermostat_settings.device_id
        options[:access_token] = DiyThermostat::Application.config.thermostat_settings.access_token
        function_name = 'set_temp'
        post("/v1/devices/#{device_id}/#{function_name}", {
          :body => options
        })
      end

      # JOES WORKING IMPLEMENTATION with https://www.spark.io/build/52d839189cbfb28c9600087e
      # curl https://api.spark.io/v1/devices/55ff70064989495339432587/set_temp -d 'access_token=b5e5a49521def21d2f0a6c061fa4bf73cae7166e' -d 'param=66'
      # def set_desired_temp(options={ })
      #   raise unless options[:param].kind_of?(Integer)
      #   device_id    = DiyThermostat::Application.config.thermostat_settings.device_id
      #   function_name = 'set_temp'
      #   options[:access_token] = DiyThermostat::Application.config.thermostat_settings.access_token
      #   post("/v1/devices/#{device_id}/#{function_name}", {
      #     :body => options
      #   })
      # end

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
