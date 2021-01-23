import paho.mqtt.client as mqtt
import time
import random

host = "m24.cloudmqtt.com"
port = 15342
username = "qyuzvafp"
password = "0ynj_3e3rzJ6"
mqttc = mqtt.Client()


# Define event callbacks
def on_connect(client, userdata, flags, rc):
    print("rc: " + str(rc))

def on_message(client, userdata, message):
    print(str(message.topic),":",str(message.payload.decode("utf-8")))

def on_publish(client, obj, mid):
    print("mid: " + str(mid))

def on_subscribe(client, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))

def on_log(client, obj, level, string):
    print(string)

def setup():
    mqttc.username_pw_set(username,password)
    mqttc.connect(host,port)
    mqttc.on_message=on_message

def Tostr(dmy):
    text=[]
    for d in dmy:
        if 0 < d < 10:
            text.append("0"+str(d))
        else :
            text.append(str(d))
    return "".join(text)

def KeyGenerate():
    dmy = time.localtime()
    d = dmy.tm_mday
    m = dmy.tm_mon
    y = dmy.tm_year
    return Tostr((y,m,d))

def PublishPattern(topic,key,score,tsleep):
    dmy = time.localtime()
    d = time.strftime("%Y:%m:%d", time.localtime())
    t = time.strftime("%H:%M:%S", time.localtime())
    # key ,score ,time ,date
    mqttc.publish(topic, f"{str(key)},1,{t},{d}")
    time.sleep(tsleep)

def ScriptTest(tsleep=60):
    topic = "toys/test"
    key = KeyGenerate()
    for i in range(30):
        PublishPattern(topic,key,random.randint(1,10),tsleep)


def main():
    setup()
    while True:
        mqttc.loop_start()
        mqttc.subscribe("toys/#")
        time.sleep(1)
        cmd = input("CMD:").split()

        if len(cmd) > 0:
            if cmd[0].upper() == "EXIT":
                break
            elif cmd[0].upper() == "PUBLISH":
                mqttc.publish("toys/text", cmd[1])
            elif cmd[0].upper() == "SCRIPTTEST":
                if len(cmd) == 2:
                    ScriptTest(int(cmd[1]))
                else:
                    ScriptTest()
                print("Finished")
            elif cmd[0].upper() == "HELP":
                text="""
MQTT Client Testing System for project492 
make by Settawat Boriruklert 590612140
Command
Exit : Quit the program
Publish <SomeText> : publish text to mqtt system by topic 'toys/text' but system use 'toys/test'
ScriptTest <time> : Testing the publish data (random between 1 to 10) to the mqtt system thought mqtt server 
    by publish data follow pattern <time> per publish
    if blank <time> it's mean time is 60second by default
    Example ScriptTest 40 it's mean publish data 10 second per a publish
    *** Warnning it has double 't' --> Scrip'tT'est ***
                """
                print(text)
            else :
                print("UNKONW COMMAND\nIf you doesn't know how to use this program, type \'help\', \'HELP\' or \'Help\'")
        else :
            print("",end="")




    mqttc.loop_stop()


if __name__ == "__main__":
    main()
