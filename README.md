# project492

##### Warning i am very weak grammer sorry.

This project is creating the toy collect data from autistic child to help doctor analytic to measure child development
and this project for my granduation project

### Client directory
1. cmdtest.py is simulation microcontroller push somedata to debug mqttserver.
2. project_hardware492 is platformio arduino framework develop microcontroller.
3. boardcreating_test is testing idea for coding ,that is not important.

### Client Hardware
first, this project must have sensor rpr-0521rs proximity senror 16pices and 2 tca9548a i2c multiplexer 2pices 
second, i recommend use firebeetle esp32-e becase use too much memory and it have 2 i2c port buildin
and finally, connect by following this picture
![Circuit Diagram](https://github.com/ZenitHTH/project492/blob/main/Client/Circuit-1.png?raw=true)
and dont forget connect 2-i2c to microcontroller and connect power to 16 proximity sensor, 2-i2c multiplexer and a microcontroller
 
### Server how to runserver
1. run setupDocker.sh by sudo and it create follow script if error i think you can fix yourself
2. when process is finish run sqlproject first, second run pymqtt and metabase ,and setting metabase yourself sqlproject's ip maybe is 10.10.0.2
3. use browser entry http://localhost:3000 to run metabase and setting yourself that is easy.

### how to use
1. running server first.
2. run hardware and use it
3. look data from metabase
