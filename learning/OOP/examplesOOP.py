# Encapsolation ---------------------
class Car:
    def __init__(self, brand, speed):
        self.brand = brand  # Public attribute
        self.__speed = speed  # Private attribute (indicated by __)
    
    def accelerate(self, amount):
        self.__speed += amount
    
    def get_speed(self):
        return self.__speed

my_car = Car("Toyota", 100)
print(my_car.get_speed())  # Accessing speed safely through a method

# Abstraction -------------------
from abc import ABC, abstractmethod

class Animal(ABC):  # Abstract class
    @abstractmethod
    def make_sound(self):
        pass

class Dog(Animal):
    def make_sound(self):
        return "Bark"

my_dog = Dog()
print(my_dog.make_sound())  # Output: Bark

# Inheritence ----------------
class Animal:
    def __init__(self, name):
        self.name = name

    def speak(self):
        return "Some sound"

class Dog(Animal):  # Dog class inherits from Animal
    def speak(self):
        return "Bark"

my_dog = Dog("Buddy")
print(my_dog.speak())  # Output: Bark

# Polymorphism -------------------------------
class Animal:
    def speak(self):
        return "Some sound"

class Dog(Animal):
    def speak(self):
        return "Bark"

class Cat(Animal):
    def speak(self):
        return "Meow"

animals = [Dog(), Cat()]
for animal in animals:
    print(animal.speak())  # Output: Bark, Meow


