from django.contrib import admin

from .models import User, Reminder

class ReminderInline(admin.StackedInline):
	model = Reminder
	extra = 1

class UserAdmin(admin.ModelAdmin):
	fieldsets = [
		(None, {'fields': ['email', 'password']}),
		('Personal info', {'fields': ['first_name', 'last_name', 'gender'], 'classes' : ['collapse']}),
	]
	inlines = [ReminderInline]
	list_display = ('email', 'first_name', 'last_name')
	search_fields = ['email', 'first_name', 'last_name']

admin.site.register(User, UserAdmin)