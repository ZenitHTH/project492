from rest_framework import serializers
from .models import *

class RTDSerializers(serializers.ModelSerializer):
    class Meta:
        model=Realtimedata
        fields = "__all__"

class TDSerializers(serializers.ModelSerializer):
    class Meta:
        model=Timedata
        fields = "__all__"

    