import django.views.generic as generic
import django.contrib.auth.mixins as mixins
from django.contrib.auth import authenticate
from django.shortcuts import render, redirect
from django.views.decorators.csrf import csrf_protect
from django.urls import reverse_lazy, reverse
from .models import ToDoList, Note, Account, ToDoItem
from .forms import TodoItemForm, ToDoListForm, NoteForm, EmailChangeForm
from django.contrib.auth.models import User
from django.contrib.auth.forms import PasswordChangeForm


# from .forms import UserCreationForm


class HomePageView(generic.TemplateView):
    template_name = 'notes/home-page.html'


class ToDoListIndexView(mixins.LoginRequiredMixin, generic.ListView):
    template_name = 'notes/todo-list/index.html'
    context_object_name = 'todo_lists'

    def get_queryset(self):
        return ToDoList.objects.filter(account__user=self.request.user)

    def get_context_data(self, **kwargs):
        context = super(ToDoListIndexView, self).get_context_data(**kwargs)
        context['form1'] = ToDoListForm
        return context


class ToDoListView(mixins.LoginRequiredMixin, generic.DetailView):
    model = ToDoList
    template_name = 'notes/todo-list/edit.html'

    def get_context_data(self, **kwargs):
        context = super(ToDoListView, self).get_context_data(**kwargs)
        context['form1'] = ToDoListForm
        context['form2'] = TodoItemForm
        return context


class ToDoListCreateView(mixins.LoginRequiredMixin, generic.CreateView):
    model = ToDoList
    fields = ['title', 'description']

    def form_invalid(self, form):
        return redirect(reverse_lazy("notes:todo_lists"))

    def form_valid(self, form):
        account = Account.objects.get(user=self.request.user)
        todo = ToDoList(
            account=account,
            **form.cleaned_data
        )
        todo.save()
        return redirect(reverse_lazy("notes:todo_list", kwargs={"pk": todo.id}))


class ToDoListEditView(mixins.LoginRequiredMixin, generic.UpdateView):
    model = ToDoList
    fields = ['title', 'description']
    pk_url_kwarg = 'pk'
    template_name = 'notes/todo-list/edit.html'

    def form_valid(self, form):
        todo = ToDoList.objects.get(pk=self.kwargs['pk'])
        form = form.cleaned_data
        todo.title = form['title']
        todo.description = form['description']
        todo.save()
        return redirect(reverse_lazy("notes:todo_list", kwargs={"pk": self.kwargs['pk']}))


class ToDoListDeleteView(mixins.LoginRequiredMixin, generic.DeleteView):
    template_name = 'notes/todo-list/index.html'
    model = ToDoList
    pk_url_kwarg = 'pk'

    def get_success_url(self):
        return reverse("notes:todo_lists")

    def get(self, request, *args, **kwargs):
        return self.post(request, *args, **kwargs)


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
    template_name = 'notes/todo-list/edit.html'

    def form_valid(self, form):
        item = ToDoItem.objects.get(pk=self.kwargs['pk_item'])
        item.item = form.cleaned_data['item']
        item.save()
        return redirect(reverse_lazy("notes:todo_list", kwargs={"pk": self.kwargs['pk']}))


class TodoItemDeleteView(mixins.LoginRequiredMixin, generic.DeleteView):
    template_name = 'notes/todo-list/edit.html'
    model = ToDoItem
    pk_url_kwarg = 'pk_item'

    def get_success_url(self):
        return reverse("notes:todo_list", kwargs={"pk": self.kwargs['pk']})

    def get(self, request, *args, **kwargs):
        return self.post(request, *args, **kwargs)


class NoteIndexView(mixins.LoginRequiredMixin, generic.ListView):
    template_name = 'notes/note/index.html'
    context_object_name = 'notes'

    def get_queryset(self):
        return Note.objects.filter(account__user=self.request.user)

    def get_context_data(self, **kwargs):
        context = super(NoteIndexView, self).get_context_data(**kwargs)
        context['form'] = NoteForm
        return context


class NoteView(mixins.LoginRequiredMixin, generic.DetailView):
    model = Note
    template_name = 'notes/note/edit.html'

    def get_context_data(self, **kwargs):
        context = super(NoteView, self).get_context_data(**kwargs)
        context['form'] = NoteForm
        return context


class NoteCreateView(mixins.LoginRequiredMixin, generic.CreateView):
    model = Note
    fields = ['title', 'description', 'text']

    def form_invalid(self, form):
        return redirect(reverse_lazy("notes:notes"))

    def form_valid(self, form):
        account = Account.objects.get(user=self.request.user)
        note = Note(
            account=account,
            **form.cleaned_data
        )
        note.save()
        return redirect(reverse_lazy("notes:note", kwargs={"pk": note.id}))


class NoteEditView(mixins.LoginRequiredMixin, generic.UpdateView):
    model = Note
    fields = ['title', 'description', 'text']
    pk_url_kwarg = 'pk'
    template_name = 'notes/note/edit.html'

    def form_valid(self, form):
        note = Note.objects.get(pk=self.kwargs['pk'])
        form = form.cleaned_data
        note.title = form['title']
        note.description = form['description']
        note.text = form['text']
        note.save()
        return redirect(reverse_lazy("notes:note", kwargs={"pk": self.kwargs['pk']}))


class NoteDeleteView(mixins.LoginRequiredMixin, generic.DeleteView):
    template_name = 'notes/note/index.html'
    model = Note
    pk_url_kwarg = 'pk'

    def get_success_url(self):
        return reverse("notes:notes")

    def get(self, request, *args, **kwargs):
        return self.post(request, *args, **kwargs)


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


class UserProfileView(mixins.LoginRequiredMixin, generic.DetailView):
    template_name = 'account/profile.html'
    context_object_name = 'user'

    def get_object(self):
        return self.request.user

    def get_context_data(self, **kwargs):
        context = super(UserProfileView, self).get_context_data(**kwargs)
        context['form1'] = PasswordChangeForm
        context['form2'] = EmailChangeForm
        return context


class UserEmailChangeView(mixins.LoginRequiredMixin, generic.UpdateView):
    model = User
    fields = ['email']

    def get_object(self):
        return self.request.user

    def form_valid(self, form):
        user = self.request.user
        user.email = form.cleaned_data['email']
        user.save()
        return redirect(reverse_lazy("notes:profile"))


class UserNameChangeView(mixins.LoginRequiredMixin, generic.UpdateView):
    model = User
    fields = ['first_name', 'last_name']

    def get_object(self):
        return self.request.user

    def form_valid(self, form):
        user = self.request.user
        form = form.cleaned_data
        user.first_name = form['first_name']
        user.last_name = form['last_name']
        user.save()
        return redirect(reverse_lazy("notes:profile"))