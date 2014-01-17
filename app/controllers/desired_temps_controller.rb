class DesiredTempsController < ApplicationController
  def index
    if params[:start].nil?
      t0 = "0"
    else
      t0 = params[:start]
    end

    if params[:end].nil?
      t1 = "9999999999"
    else
      t1 = params[:end]
    end
    start_date = DateTime.strptime(t0,'%s')
    end_date = DateTime.strptime(t1,'%s')
    range = start_date..end_date
    @desired_temps = WebEvent.where(:event_type => "desired_temp_change", :created_at => range).order("created_at ASC")
    return_this = @desired_temps.map {|x| [x.created_at.to_i, x.integer_value] }
    respond_to do |format|
      format.json { render json: return_this }
    end
  end

  def last
    r = WebEvent.where(:event_type => 'desired_temp_change').last
    return_this = [r.created_at.to_i, r.value]
    respond_to do |format|
      format.json { render json: return_this }
    end
  end
end
