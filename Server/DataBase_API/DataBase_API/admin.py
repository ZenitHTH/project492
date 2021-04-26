
from django.contrib import admin


# Register your models here.
from . import models


admin.site.register(models.Realtimedata)
admin.site.register(models.Timedata)
