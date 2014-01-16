class CreateWebEvents < ActiveRecord::Migration
  def change
    create_table :web_events do |t|
      t.string :name
      t.string :event_type
      t.integer :integer_value
      t.float :float_value
      t.string :string_value
      t.text :hash_value

      t.timestamps
    end
  end
end
