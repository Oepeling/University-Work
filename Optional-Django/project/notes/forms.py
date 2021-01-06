from django import forms
from django.contrib.auth.models import User


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
