from django.contrib import admin
from .models import ToDoList, ToDoItem, Note, Account


class NoteInLine(admin.StackedInline):
    model = Note
    extra = 0


class ToDoItemInLine(admin.TabularInline):
    model = ToDoItem
    extra = 1


class ToDoListInLine(admin.StackedInline):
    inlines = [ToDoItemInLine]
    model = ToDoList
    extra = 0


class AccountAdmin(admin.ModelAdmin):
    readonly_fields = ['username', 'email', 'full_name']
    list_display = ('username', 'email', 'full_name')
    inlines = [NoteInLine, ToDoListInLine]


admin.site.register(Account, AccountAdmin)