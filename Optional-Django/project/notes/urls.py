from django.urls import path, include
import django.contrib.auth.views as auth_views

from . import views

app_name = 'notes'
urlpatterns = [
    path('', views.home_page, name='home_page'),
    path('todos/', views.ToDoListIndexView.as_view(), name='todo_lists'),
    path('notes/', views.NoteIndexView.as_view(), name='notes'),
    path('accounts/logout/', auth_views.LogoutView.as_view(next_page='notes:home_page')),
    path('accounts/', include('django.contrib.auth.urls')),
    path('accounts/register/', views.register_user, name='register'),
]
