Joe's Scraps
============


curl desired_temp_change


### Models

rails g WebEvent name:string event_type:string integer_value:integer float_value:float string_value:string hash_value:text


rails g scaffold ActualTempReading value:float

WebUiEvent
  id
  name
  type
  integer_value
  float_value
  string_value
  hash_value
  created_at
  updated_at




/web_event

/temp/actual/last

/temp/actual/all

http://localhost:5000/actual_temp_readings.json?start=
[{"at":1389915239,"be":10.361936931053316},{"at":1389915248,"be":15.57860289462854},{"at":1389915263,"be":1.615778958290679},{"at":1389915290,"be":24.696159081644858},{"at":1389915569,"be":24.547704545023805},{"at":1389915590,"be":17.308683751584162},{"at":1389915595,"be":27.91387440758126},{"at":1389915608,"be":4.236242146202746},{"at":1389915620,"be":19.38217343720439},{"at":1389915635,"be":8.468154979014711},{"at":1389915638,"be":21.300351614921418},{"at":1389915665,"be":28.452938563880828},{"at":1389915683,"be":3.753132843415874},{"at":1389915710,"be":20.567780642068897},{"at":1389916103,"be":26.0},{"at":1389916124,"be":26.0},{"at":1389916145,"be":26.0}]
