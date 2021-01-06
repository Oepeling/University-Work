from django.urls import path, include

from . import views

app_name = 'notes'
urlpatterns = [
    path('', views.home_page, name='home_page'),
    path('todos/', views.ToDoListIndexView.as_view(), name='todo_lists'),
    path('notes/', views.NoteIndexView.as_view(), name='notes'),
    path('accounts/', include('django.contrib.auth.urls')),
    path('accounts/register/', views.register_user, name='register'),
]
