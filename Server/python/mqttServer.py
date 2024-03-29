import paho.mqtt.client as mqtt
import mysqlConnect as sql
import time
import setup
host = setup.mqtt.host
port = setup.mqtt.port
username = setup.mqtt.username
password = setup.mqtt.password

mqttc = mqtt.Client()
todaykey=sql.Getlastdatekey()

# Define event callbacks
def on_connect(client, userdata, flags, rc):
    print("rc: " + str(rc))

def on_message(client, userdata, message):
    print(str(message.topic),":",str(message.payload.decode("utf-8")))
    try:
    	data = str(message.payload.decode("utf-8")).split(",")
    	sql.InsertRTD(datekey=data[0],score=data[1],time=data[2],dmy=data[3],prikey=(data[3]+data[2]).replace(":",""))
    except:
    	print("Format is Wrong")
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
        mqttc.loop_start()
        mqttc.subscribe("toys/test")
        
        if(
            time.localtime().tm_hour == setup.makeTD.hr and 
            time.localtime().tm_min == setup.makeTD.min and 
            time.localtime().tm_sec == setup.makeTD.second
            ):
            makeTD(todaykey)

        time.sleep(1)

            
    mqttc.loop_stop()

if __name__ == "__main__":
    main()
