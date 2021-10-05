import json
import os

home = "/root/"
file_nameJson = "setting.json"

with open(home+file_nameJson) as f:
    data = json.load(f)


class MqttSetup():

    def __init__(self,host,username,password,port):
        self.host = host
        self.username = username
        self.password = password
        if type(port) == int:
            self.port = int(port)
        else :
            print("port is not int, port is 1883")
            self.port = 1883

    def host(self):
        return self.host
    
    def port(self):
        return self.port
    
    def username(self):
        return self.username

    def password(self):
        return self.password
    
    def port(self):
        return self.port

class MakeTD():
    def __init__(self,hr,min,second,subscribe):
        if type(hr) == type(min) == type(second) == int:
            self.hr = hr
            self.min = min
            self.second = second
        else :
            print("all these must int")

        self.subscribe = subscribe

    def hr(self):
        return self.hr

    def min(self):
        return self.min

    def second(self):
        return self.second

    def subscribe(self):
        return self.subscribe

class MysqlSetup():

    def __init__(self, username, password, name,host,port):
        self.username = username
        self.password = password
        self.name = name
        self.host = host
        if type(port) == int:
            self.port = port
        else :
            print("port is not int, port is 3306")
            self.port = 3306

    def username(self):
        return self.username

    def password(self):
        return self.password
    
    def host(self):
        return self.host
    
    def port(self):
        return self.port

    def name(self):
        return self.name

mqtt = MqttSetup(
    host = data["mqttServer"]["login"]["host"],
    port = int(data["mqttServer"]["login"]["port"]),
    username = data["mqttServer"]["login"]["username"],
    password = data["mqttServer"]["login"]["password"]
)

mysql = MysqlSetup(
    host = data["database"]["host"],
    port = int(data["database"]["port"]),
    name = data["database"]["name"],
    username = data["database"]["username"],
    password = data["database"]["password"]
)

makeTD = MakeTD(
    hr = int(data["mqttServer"]["makeTDTime"]["hr"]),
    min = int(data["mqttServer"]["makeTDTime"]["min"]),
    second = int(data["mqttServer"]["makeTDTime"]["second"]),
    subscribe = data["mqttServer"]["subscribe"]

)

