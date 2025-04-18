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
