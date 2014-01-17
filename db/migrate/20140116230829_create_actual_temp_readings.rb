class CreateActualTempReadings < ActiveRecord::Migration
  def change
    create_table :actual_temp_readings do |t|
      t.float :value

      t.timestamps
    end
  end
end
