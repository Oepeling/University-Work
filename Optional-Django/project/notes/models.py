from django.db import models
from django.contrib.auth.models import User


class Account(models.Model):
    user = models.OneToOneField(
        User,
        primary_key=True,
        on_delete=models.CASCADE
    )

    @property
    def username(self):
        return self.user.username

    @property
    def full_name(self):
        return self.user.first_name + ' ' + self.user.last_name

    @property
    def email(self):
        return self.user.email


class BasicNote(models.Model):
    account = models.ForeignKey(
        Account,
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
        'Text',
        blank=True
    )
