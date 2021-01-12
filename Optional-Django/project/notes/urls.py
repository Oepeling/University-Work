from django.urls import path, include
import django.contrib.auth.views as auth_views

from . import views

app_name = 'notes'
urlpatterns = [
    path('', views.HomePageView.as_view(), name='home_page'),

    path('todos/', views.ToDoListIndexView.as_view(), name='todo_lists'),
    path('todo/<int:pk>/', views.ToDoListView.as_view(), name='todo_list'),
    path('todo/<int:pk>/edit/', views.ToDoListEditView.as_view(), name='todo_list_edit'),

    path('post/<int:pk>/item/add/', views.TodoItemCreateView.as_view(), name='todo_item_add'),
    path('todo/<int:pk>/item/<int:pk_item>/edit/', views.TodoItemEditView.as_view(), name='todo_item_edit'),
    path('todo/<int:pk>/item/<int:pk_item>/delete/', views.TodoItemDeleteView.as_view(), name='todo_item_delete'),

    path('notes/', views.NoteIndexView.as_view(), name='notes'),

    path('accounts/logout/', auth_views.LogoutView.as_view(next_page='notes:home_page'), name='logout'),
    path('accounts/register/', views.register_user, name='register'),
    # path('accounts/register/', views.RegisterView.as_view(), name='register'),
    path('accounts/', include('django.contrib.auth.urls')),
]
