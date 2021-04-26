CREATE DATABASE data;
USE data;
CREATE TABLE RealTimeData(
    datekey INTEGER NOT NULL,
    score INT,
    dtime TIME,
    dmy DATE,
    prikey VARCHAR(100),
    PRIMARY KEY(prikey));
CREATE TABLE TimeData(
    datekey INTEGER,
    scorepermin FLOAT(9,4),
    dmy DATE,
    PRIMARY KEY(datekey));
