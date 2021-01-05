from django.db import models
from django.contrib.auth.models import User


class BasicNote(models.Model):
    user = models.ForeignKey(
        User,
        on_delete=models.CASCADE
    )
    title = models.CharField(
        'Title',
        max_length=100
    )
    description = models.CharField(
        'Description',
        max_length=300,
        blank=True
    )


class ToDoList(BasicNote):
    count = models.IntegerField(
        'Total items',
        default=0
    )


class ToDoItem(models.Model):
    list = models.ForeignKey(
        ToDoList,
        on_delete=models.CASCADE
    )
    item = models.CharField(
        'Item',
        max_length=200
    )
    checked = models.BooleanField(
        'Checked',
        default=False
    )


class Note(BasicNote):
    text = models.TextField(
        'Text'
    )