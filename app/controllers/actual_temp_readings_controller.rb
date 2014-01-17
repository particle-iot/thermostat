class ActualTempReadingsController < ApplicationController
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
    @actual_temp_readings = ActualTempReading.where(:created_at => range).order("created_at ASC")
    return_this = @actual_temp_readings.map {|x| [x.created_at.to_i, x.value] }
    respond_to do |format|
      format.json { render json: return_this }
    end
  end

  def last
    r = ActualTempReading.last
    return_this = [r.created_at.to_i, r.value]
    respond_to do |format|
      format.json { render json: return_this }
    end
  end
end
