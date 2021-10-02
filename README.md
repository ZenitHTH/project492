# project492

##### Warning i am very weak grammer sorry.

### Client directory
1. cmdtest.py is simulation microcontroller push somedata to debug mqttserver.
2. project_hardware492 is platformio arduino framework develop microcontroller.
3. boardcreating_test is testing idea for coding ,that is not important.

### Client Hardware
first, this project must have sensor rpr-0521rs proximity senror 16pices and 2 tca9548a i2c multuplexer 2pices 
second, i recommend use firebeetle esp32-e becase use too much memory 
and finally, connect by following this picture
![Circuit Diagram](https://github.com/ZenitHTH/project492/blob/main/Client/Circuit-1.png?raw=true)
and dont forget connect 2-i2c to microcontroller and connect power to 16 proximity sensor, 2-i2c multiplexer and a microcontroller
 
### Server how to runserver
1. create docker image form dockerfile but create a password for your database in that file.
2. add your host mqtt server , username , password and port for mqttserver in file setting.json for running python3 file
3. if have an error add database and run it yourself run command "python3 /root/mqttserver.py" and "java -jar /root/metabase.jar".
4. use browser entry http://localhost:3000 to run metabase and setting yourself that is easy.

### how to use
1. running server first.
2. run hardware and use it
3. look data from metabase
