from tkinter import Button, Label
from kivy.app import App
from kivy.uix.screenmanager import ScreenManager, Screen
from kivy.properties import StringProperty, ObjectProperty, ListProperty
from kivy.uix.boxlayout import BoxLayout




class Task:
    def __init__(self, title, description, due_date, status="Pending"):
        self.title = title
        self.description = description
        self.due_date = due_date
        self.status = status


class MainScreen(Screen):
    task_list = ListProperty([])

    def on_pre_enter(self):
        self.refresh_tasks()

    def refresh_tasks(self):
        self.ids.task_container.clear_widgets()
        for idx, task in enumerate(self.task_list):
            self.ids.task_container.add_widget(
                TaskItem(title=task.title, due_date=task.due_date, status=task.status, task_index=idx)
            )


class TaskDetailScreen(Screen):
    task_index = None
    task = ObjectProperty(None)

    def on_pre_enter(self):
        if self.task:
            self.ids.title.text = self.task.title
            self.ids.description.text = self.task.description
            self.ids.due_date.text = self.task.due_date
            self.ids.status.text = self.task.status

    def save_task(self):
        self.task.title = self.ids.title.text
        self.task.description = self.ids.description.text
        self.task.due_date = self.ids.due_date.text
        self.task.status = self.ids.status.text
        self.manager.get_screen("main").refresh_tasks()
        self.manager.current = "main"

    def delete_task(self):
        if self.task_index is not None:
            self.manager.get_screen("main").task_list.pop(self.task_index)
        self.manager.get_screen("main").refresh_tasks()
        self.manager.current = "main"


class AddEditTaskScreen(Screen):
    is_edit = False
    task_index = None

    def on_pre_enter(self):
        if self.is_edit:
            task = self.manager.get_screen("main").task_list[self.task_index]
            self.ids.title.text = task.title
            self.ids.description.text = task.description
            self.ids.due_date.text = task.due_date
            self.ids.status.text = task.status
        else:
            self.ids.title.text = ""
            self.ids.description.text = ""
            self.ids.due_date.text = ""
            self.ids.status.text = "Pending"

    def save_task(self):
        title = self.ids.title.text
        description = self.ids.description.text
        due_date = self.ids.due_date.text
        status = self.ids.status.text

        if self.is_edit:
            task = self.manager.get_screen("main").task_list[self.task_index]
            task.title = title
            task.description = description
            task.due_date = due_date
            task.status = status
        else:
            new_task = Task(title, description, due_date, status)
            self.manager.get_screen("main").task_list.append(new_task)

        self.manager.get_screen("main").refresh_tasks()
        self.manager.current = "main"

class TaskItem(BoxLayout):
    title = StringProperty()
    due_date = StringProperty()
    status = StringProperty()
    task_index = ObjectProperty()

    def __init__(self, **kwargs):
        super().__init__(**kwargs)
        self.orientation = 'horizontal'
        self.size_hint_y = None
        self.height = 40

        self.add_widget(Label(text=self.title, size_hint_x=0.4))
        self.add_widget(Label(text=self.due_date, size_hint_x=0.3))
        self.add_widget(Label(text=self.status, size_hint_x=0.2))
        btn = Button(text="View", size_hint_x=0.1)
        btn.bind(on_press=self.view_task)
        self.add_widget(btn)

    def view_task(self, instance):
        sm = App.get_running_app().root
        main_screen = sm.get_screen("main")
        task = main_screen.task_list[self.task_index]
        detail_screen = sm.get_screen("detail")
        detail_screen.task_index = self.task_index
        detail_screen.task = task
        sm.current = "detail"


class TaskManagerApp(App):
    def build(self):
        sm = ScreenManager()
        sm.add_widget(MainScreen(name="main"))
        sm.add_widget(TaskDetailScreen(name="detail"))
        sm.add_widget(AddEditTaskScreen(name="add_edit"))
        return sm


if __name__ == '__main__':
    try:
     TaskManagerApp().run()
    except Exception as e:
        import traceback
        traceback.print_exc()
