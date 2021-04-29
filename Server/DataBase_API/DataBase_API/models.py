# This is an auto-generated Django model module.
# You'll have to do the following manually to clean this up:
#   * Rearrange models' order
#   * Make sure each model has one field with primary_key=True
#   * Make sure each ForeignKey and OneToOneField has `on_delete` set to the desired behavior
#   * Remove `managed = False` lines if you wish to allow Django to create, modify, and delete the table
# Feel free to rename the models, but don't rename db_table values or field names.
from django.db import models


class Realtimedata(models.Model):
    datekey = models.IntegerField()
    score = models.IntegerField(blank=True, null=True)
    dtime = models.TimeField(blank=True, null=True)
    dmy = models.DateField(blank=True, null=True)
    prikey = models.CharField(primary_key=True, max_length=100)

    class Meta:
        managed = False
        db_table = 'RealTimeData'


class Timedata(models.Model):
    datekey = models.IntegerField(primary_key=True)
    scorepermin = models.FloatField(blank=True, null=True)
    dmy = models.DateField(blank=True, null=True)

    class Meta:
        managed = False
        db_table = 'TimeData'
