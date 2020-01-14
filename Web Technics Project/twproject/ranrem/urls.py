from django.urls import path

from . import views

app_name = 'ranrem'
urlpatterns = [
    path('', views.index, name='index'),
    path('login/', views.login, name='login'),
    path('register/', views.register, name='register'),
    path('createnew/', views.createnew, name='createnew'),
    path('logout/', views.logout, name='logout'),
    path('showmore/', views.showmore, name='showmore'),
]