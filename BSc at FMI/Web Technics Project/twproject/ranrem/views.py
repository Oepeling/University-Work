from django.http import HttpResponse, Http404, HttpResponseRedirect, JsonResponse
from django.shortcuts import render
from django.template import loader
from django.urls import reverse

from .models import User, Reminder

def index(request):
	if (request.COOKIES.get('email') == None):
		template = loader.get_template('ranrem/index.html')
		context = {}
	else:
		user = User.objects.get(email = request.COOKIES['email'])
		random_reminders = Reminder.objects.filter(user = user, random = True)
		normal_reminders = Reminder.objects.filter(user = user, random = False)
		template = loader.get_template('ranrem/loggedin.html')
		context = {
			'random_reminders': list(random_reminders),
			'normal_reminders': list(normal_reminders),
		}
	response = HttpResponse(template.render(context, request))
	return response

def login(request):
	try:
		user = User.objects.get(email = request.POST['email'])
	except (KeyError, User.DoesNotExist):
		return render(request, 'ranrem/index.html', {
			'error_message': "Wrong email",})
	else:
		if (user.password == request.POST['password']):
			response = HttpResponseRedirect(reverse('ranrem:index'))
			response.set_cookie(key="email", value=user.email)
			return response
		else:
			return render(request, 'ranrem/index.html', {
				'error_message': "Wrong password",
			})

def register(request):
	try:
		user = User.objects.get(email = request.POST['email'])
	except User.DoesNotExist:
		if (request.POST['password'] == request.POST['confirm-password']):
			user = User(
				email = request.POST['email'],
				password = request.POST['password'],
				first_name = request.POST['first-name'],
				last_name = request.POST['last-name'],
				gender = 'N',
			)
			user.save()
			return HttpResponseRedirect(reverse('ranrem:index') + '#login')
		else:
			return render(request, 'ranrem/index.html' , {
				'error_message': "Passwords don't match",
				})
	else:
		return render(request, 'ranrem/index.html', {
			'error_message': "Already exists",
			})

def createnew(request):
	user = User.objects.get(email = request.COOKIES['email'])
	reminder = Reminder(
		user = user,
		title = request.POST['title'],
		description = request.POST['description'],
		date = request.POST['date'],
		time = request.POST['time'],
		random = bool(request.POST['random'] == 'on'),
	)
	reminder.save();
	return HttpResponseRedirect(reverse('ranrem:index') + '#myreminders')

def logout(request):
	response = HttpResponseRedirect(reverse('ranrem:index'))
	response.delete_cookie(key="email")
	return response

def showmore(request):
	return JsonResponse({'load': 'Some more text'})