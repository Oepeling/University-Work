import django.views.generic as generic
import django.contrib.auth.mixins as mixins
from django.http import HttpResponse, HttpResponseRedirect
from django.template import loader
from django.shortcuts import render
from django.views.decorators.csrf import csrf_protect
from .models import ToDoList, Note
from django.contrib.auth.models import User


def home_page(request):
    template = loader.get_template('notes/home-page.html')
    if request.user.is_authenticated:
        context = {'user': request.user.username}
    else:
        context = {'user': None}
    return HttpResponse(template.render(context))


class ToDoListIndexView(mixins.LoginRequiredMixin, generic.ListView):
    template_name = 'notes/todo-lists.html'
    context_object_name = 'todo_lists'

    def get_queryset(self):
        return ToDoList.objects.filter(account__user=self.request.user)


class NoteIndexView(mixins.LoginRequiredMixin, generic.ListView):
    template_name = 'notes/notes.html'
    context_object_name = 'notes'

    def get_queryset(self):
        return Note.objects.filter(account__user=self.request.user)


@csrf_protect
def register_user(request):
    template_path = 'registration/login.html'
    data = request.POST
    try:
        user = User.objects.get(username=data['username'])
    except User.DoesNotExist:
        if data['password1'] == data['password2']:
            user = User.objects.create_user(data['username'], data['email'], data['password1'])
            user.first_name = data['first_name']
            user.last_name = data['last_name']
            user.save()
            context = {'message': 'User registered successfully!'}
        else:
            context = {'error_message': 'The passwords don\'t match!'}
    else:
        context = {'error_message': "The username is already taken!"}

    return render(request, template_path, context)