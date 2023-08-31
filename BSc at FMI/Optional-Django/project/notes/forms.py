from django import forms
from . import models
from django.contrib.auth.models import User


class EmailChangeForm(forms.ModelForm):
    class Meta:
        model = models.User
        fields = ['email']
        exclude = ['username', 'first_name', 'last_name', 'password']


class NoteForm(forms.ModelForm):
    class Meta:
        model = models.Note
        fields = ['title', 'description', 'text']
        exclude = ['account']


class ToDoListForm(forms.ModelForm):
    class Meta:
        model = models.ToDoList
        fields = ['title', 'description']
        exclude = ['account', 'count']


class TodoItemForm(forms.ModelForm):
    class Meta:
        model = models.ToDoItem
        fields = ['item']
        exclude = ['list', 'checked']


class UserCreationForm(forms.ModelForm):
    username = forms.CharField(max_length=100)
    e_mail = forms.EmailField(max_length=100)
    first_name = forms.CharField(max_length=100)
    last_name = forms.CharField(max_length=100)
    password1 = forms.CharField(max_length=100)
    password2 = forms.CharField(max_length=100)

    class Meta:
        model = User
        fields = ['username', 'first_name', 'last_name', 'password']
