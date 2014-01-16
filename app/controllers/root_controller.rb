class RootController < ApplicationController
  def index
  end

  def web_event
    return_this = {
      ok: nil
    }
    case params[:web_event][:event_type]
    # curl -d 'web_event[name]=poo' -d 'web_event[type]=desired_temp_change' -d 'web_event[integer_value]=22' http://localhost:5000/web_event
    when 'desired_temp_change'
      we=WebEvent.create(params[:web_event])
      if we.new_record?
        return_this[:ok] = false
        return_this[:error] = "Could not save web event"
      else
        return_this[:ok] = true
      end
    else
    end
    render :json => return_this
  end
end
