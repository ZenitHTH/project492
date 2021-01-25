import pymysql 
username = "doadmin"
password = "aikpwj1y19gty8hc"
host = "db-mysql-sgp1-95265-do-user-5938604-0.b.db.ondigitalocean.com"
port = 25060
database = "defaultdb"
#Docker Connect
db = pymysql.connect(host=host,
                    user=username,
                    password=password,
                    database=database,
                    port=port)

#GCloud SQL Connect
"""
	db = pymysql.connect(host="",
			    user="",
			    password="",
			    database="data",
			    ssl={'ca':'xxx/xxx/server-ca.pem',
			    'cert':'xxx/xxx/client-cert.pem',
			    'key':'xxx/xxx/client-key.pem'}
"""			    
			    
cursor = db.cursor()
def InsertRTD(datekey,score,time,dmy,prikey):
    if datekey == None or score == None or time == None or dmy == None:
        print("ERROR")
    else : 
        # New DataBase score int,time time,dmy date, datekey unsigned(uniqukey),prikey varchar100(primerykey)
        #sql = f"INSERT INTO RealTimeData(datekey,score,time,dmy) VALUES({(datakey)},{(score)},\"{str(time)}\",\"{str(dmy)}\");"
        sql = f"INSERT INTO RealTimeData(score,dtime,dmy,datekey,prikey) VALUES({str(score)},\'{str(time)}\',\'{str(dmy)}\',{str(datekey)},{str(prikey)});"
        print(sql)
        cursor.execute(sql)
        db.commit()

def InsertTD(datakey,score,dmy):
    if datakey == None or score == None or dmy == None:
        print("ERROR")
    else :
        # new DataBase datekey int unsigned (primarykey) ,scorepermin float , dmy date~
        sql = f"INSERT INTO TimeData(datekey,scorepermin,dmy) VALUES({datakey},{scorepermin},\'{dmy}\');"
        cursor.execute(sql)
        db.commit()

def ShowRTD(datekey):
    sql = f"SELECT score,dmy FROM RealTimeData WHERE datekey = \'{str(datekey)}\';"
    cursor.execute(sql)
    return cursor.fetchall()
    
    


