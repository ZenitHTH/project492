import paho.mqtt.client as mqtt
import mysqlConnect as sql

host = "m24.cloudmqtt.com"
port = 15342
username = "qyuzvafp"
password = "0ynj_3e3rzJ6"
mqttc = mqtt.Client()
todaykey=sql.Getlastdatekey()

def on_connect(client, userdata, flags, rc):
    print("rc: " + str(rc))

def on_message(client, userdata, message):
    print(str(message.topic),":",str(message.payload.decode("utf-8")))
    data = str(message.payload.decode("utf-8")).split(",")
    global todaykey
    if todaykey != data[0]:
        todaykey = data[0]

def on_publish(client, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(client, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_log(client, obj, level, string):
    print(string)

def Setup():
    mqttc.username_pw_set(username,password)
    mqttc.connect(host,port)
    mqttc.on_message=on_message

def makeTD(datekey=todaykey):
    data = sql.ShowRTD(datekey)
    l = len(data)
    s = sum(d[0] for d in data)
    #print(data)
    dmy = data[0][1]
    #print(datekey,"{0:.4f}".format(s/l),dmy)
    sql.InsertTD(datekey,"{0:.4f}".format(s/l),dmy)

def main():
    Setup()
    while True:
        cmd = input("CMD:").split()
        if len(cmd) > 0:    
            if cmd[0].upper() == "EXIT":
                break
            elif len(cmd) > 1 and cmd[0].upper() == "PUBLISH":
                mqttc.publish("toys/test",cmd[1])
            elif cmd[0].upper() == "TDTEST":

                if len(cmd) > 1 :
                    makeTD(int(cmd[1]))
                else :
                    makeTD(todaykey)

            elif cmd[0].upper() == "HELP":
                text="""
MQTT Server for project492 make by Settawat Boriruklert 590612140
Command
Exit : Quit the program
Publish <SomeText> : publish text to mqtt system
TDTest <datekey> : Testing the average system and put it in the TimeData table
    if you blank <datekey> system use 'todaykey' automatic
                """
                print(text)
            else :
                print("UNKONW COMMAND\nIf you doesn't know how to use this program, type \'help\', \'HELP\' or \'Help\'")
        else :
            print("",end="")
