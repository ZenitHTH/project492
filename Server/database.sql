CREATE DATABASE data;
USE data;
CREATE TABLE RealTimeData(datekey INTEGER NOT NULL,score INT,time TIME,dmy DATE);
CREATE TABLE TimeData(datekey INTEGER,scorepermin FLOAT(9,4),dmy DATE,PRIMARY KEY(datekey));
