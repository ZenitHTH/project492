from django.shortcuts import render
from rest_framework import viewsets

from .serializers import *


class RTDAPI(viewsets.ModelViewSet):
    serializer_class = RTDSerializers
    queryset = Realtimedata.objects.all()


class TDAPI(viewsets.ModelViewSet):
    serializer_class = TDSerializers
    queryset = Timedata.objects.all()


    

