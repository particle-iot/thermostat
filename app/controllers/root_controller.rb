class RootController < ApplicationController
  def index
  end

  # POSTed to when widgets change on the web site.
  def web_event
    return_this = {
      ok: nil
    }
    catch(:done) do
      case params[:web_event][:event_type]
      # curl -d 'web_event[name]=poo' -d 'web_event[type]=desired_temp_change' -d 'web_event[integer_value]=22' http://localhost:5000/web_event
      when 'desired_temp_change'
        we=WebEvent.create(params[:web_event])
        if we.new_record?
          return_this[:ok] = false
          return_this[:error] = "Could not save web event"
          throw :done
        else
          return_this[:ok] = true
          DesiredTempChangeInformer.perform_async(we.id)
          throw :done
        end
      else
      end
    end
    render :json => return_this
  end

end
