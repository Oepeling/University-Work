from django.db import models

class User(models.Model):
	email = models.EmailField(
		'E-mail',
		max_length = 254,
		primary_key = True,
		unique = True)
	password = models.CharField(
		'Password Hash',
		max_length = 100)
	first_name = models.CharField(
		'First Name',
		max_length = 30)
	last_name = models.CharField(
		'Last Name',
		max_length = 30)

	class Gender(models.TextChoices):
		FEMALE = 'F', ('Female')
		MALE = 'M', ('Male')
		NONE = 'N', ('Not Declared')
	gender = models.CharField(
		max_length = 20,
		choices = Gender.choices,
		default = Gender.NONE)

class Reminder(models.Model):
	user = models.ForeignKey(
		User,
		on_delete = models.CASCADE)
	title = models.CharField(
		'Title',
		max_length = 100)
	description = models.CharField(
		'Description',
		max_length = 300,
		blank = True)
	date = models.DateField('Date')
	time = models.TimeField('Time')
	random = models.BooleanField('Random Type', default = False)