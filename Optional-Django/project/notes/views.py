import django.views.generic as generic
import django.contrib.auth.mixins as mixins
from django.shortcuts import render, redirect
from django.views.decorators.csrf import csrf_protect
from django.urls import reverse_lazy, reverse
from .models import ToDoList, Note, Account, ToDoItem
from .forms import TodoItemForm, ToDoListForm
from django.contrib.auth.models import User
# from .forms import UserCreationForm


class HomePageView(generic.TemplateView):
    template_name = 'notes/home-page.html'


class ToDoListIndexView(mixins.LoginRequiredMixin, generic.ListView):
    template_name = 'notes/todo-lists.html'
    context_object_name = 'todo_lists'

    def get_queryset(self):
        return ToDoList.objects.filter(account__user=self.request.user)


class ToDoListView(mixins.LoginRequiredMixin, generic.DetailView):
    model = ToDoList
    template_name = 'notes/todo-list-edit.html'

    def get_context_data(self, **kwargs):
        context = super(ToDoListView, self).get_context_data(**kwargs)
        context['form1'] = ToDoListForm
        context['form2'] = TodoItemForm
        return context


class ToDoListEditView(mixins.LoginRequiredMixin, generic.UpdateView):
    model = ToDoList
    fields = ['title', 'description']
    pk_url_kwarg = 'pk'
    template_name = 'notes/todo-list-edit.html'

    def form_valid(self, form):
        todo = ToDoList.objects.get(pk=self.kwargs['pk'])
        form = form.cleaned_data
        todo.title = form['title']
        todo.description = form['description']
        todo.save()
        return redirect(reverse_lazy("notes:todo_list", kwargs={"pk": self.kwargs['pk']}))


class TodoItemCreateView(mixins.LoginRequiredMixin, generic.CreateView):
    model = ToDoItem
    fields = ['item']

    def form_valid(self, form):
        todo_list = ToDoList.objects.get(id=self.kwargs['pk'])
        ToDoItem.objects.create(
            list=todo_list,
            **form.cleaned_data
        )
        return redirect(reverse_lazy("notes:todo_list", kwargs={"pk": self.kwargs['pk']}))


class TodoItemEditView(mixins.LoginRequiredMixin, generic.UpdateView):
    model = ToDoItem
    fields = ['item']
    pk_url_kwarg = 'pk_item'
    template_name = 'notes/todo-list-edit.html'

    def form_valid(self, form):
        item = ToDoItem.objects.get(pk=self.kwargs['pk_item'])
        item.item = form.cleaned_data['item']
        item.save()
        return redirect(reverse_lazy("notes:todo_list", kwargs={"pk": self.kwargs['pk']}))


class TodoItemDeleteView(mixins.LoginRequiredMixin, generic.DeleteView):
    template_name = 'notes/todo-list-edit.html'
    model = ToDoItem
    pk_url_kwarg = 'pk_item'

    def get_success_url(self):
        return reverse("notes:todo_list", kwargs={"pk": self.kwargs['pk']})

    def get(self, request, *args, **kwargs):
        return self.post(request, *args, **kwargs)


class NoteIndexView(mixins.LoginRequiredMixin, generic.ListView):
    template_name = 'notes/notes.html'
    context_object_name = 'notes'

    def get_queryset(self):
        return Note.objects.filter(account__user=self.request.user)


@csrf_protect
def register_user(request):
    template_path = 'registration/register.html'
    if not request.POST:
        return render(request, template_path)

    data = request.POST
    try:
        print(data['username'])
        user = User.objects.get(username=data['username'])
    except User.DoesNotExist:
        if data['password1'] == data['password2']:
            user = User.objects.create_user(data['username'], data['email'], data['password1'])
            user.first_name = data['first_name']
            user.last_name = data['last_name']
            user.save()
            account = Account.objects.create(user)
            account.save()
            context = {'message': 'User registered successfully!'}
        else:
            context = {'error_message': 'The passwords don\'t match!'}
    else:
        context = {'error_message': "The username is already taken!"}

    return render(request, template_path, context)


# class RegisterView(generic.CreateView):
#     template_name = 'registration/register.html'
#     form_class = UserCreationForm
#     model = User
#
#     def form_valid(self, form):
#         data = form.cleaned_data
#         user = User.objects.create_user(username=data['username'],
#                                         password=data['password1'],
#                                         first_name=data['first_name'],
#                                         last_name=data['last_name'])
#         Account.objects.create(user=user)
#         return render(self.request, self.template_name, {'message': 'User registered successfully!'})
