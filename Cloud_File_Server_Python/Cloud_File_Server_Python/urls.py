"""
URL configuration for Cloud_File_Server_Python project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/5.0/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from Server import views

urlpatterns = [
    path('admin/', admin.site.urls),
    path('GetFileInfo/',views.getfileinfo),
    path('UploadFile/', views.uploadfile),
    path('RegisterUser/',views.reg_account),
    path('SignIn/',views.user_sign_in),
    path('GetUserInfo/',views.getUserInfo),
    path('CheckFile/',views.chech_file)
]
