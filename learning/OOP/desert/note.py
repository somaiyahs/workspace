# dessert.py
class Order:
    def __init__(self):
        self.items = []
    
    def add_item(self, item):
        self.items.append(item)
    
    def __str__(self):
        return "\n".join(str(item) for item in self.items)

class Dessert:
    TAX_RATE = 0.0725
    
    def __init__(self, name):
        self.name = name
    
    def get_cost(self):
        return 0.0
    
    def get_tax(self):
        return self.get_cost() * Dessert.TAX_RATE
    
    def __str__(self):
        return self.name

class Candy(Dessert):
    def __init__(self, name, weight, price_per_pound):
        super().__init__(name)
        self.weight = weight
        self.price_per_pound = price_per_pound
    
    def get_cost(self):
        return self.weight * self.price_per_pound
    
    def __str__(self):
        cost = self.get_cost()
        tax = self.get_tax()
        return f"{self.name} Candy\n- {self.weight:.2f} lbs. @ ${self.price_per_pound:.2f}/lb:, ${cost:.2f}, [tax: ${tax:.2f}]"

class Cookie(Dessert):
    def __init__(self, name, quantity, price_per_dozen):
        super().__init__(name)
        self.quantity = quantity
        self.price_per_dozen = price_per_dozen
    
    def get_cost(self):
        return (self.quantity / 12) * self.price_per_dozen
    
    def __str__(self):
        cost = self.get_cost()
        tax = self.get_tax()
        return f"{self.name} Cookie\n- {self.quantity} cookies @ ${self.price_per_dozen:.2f}/dozen, ${cost:.2f}, [tax: ${tax:.2f}]"

class IceCream(Dessert):
    def __init__(self, name, price):
        super().__init__(name)
        self.price = price
    
    def get_cost(self):
        return self.price
    
    def __str__(self):
        cost = self.get_cost()
        tax = self.get_tax()
        return f"{self.name} Ice Cream\n- ${cost:.2f}, [tax: ${tax:.2f}]"

class Sundae(IceCream):
    def __init__(self, name, price, topping, topping_price):
        super().__init__(name, price)
        self.topping = topping
        self.topping_price = topping_price
    
    def get_cost(self):
        return self.price + self.topping_price
    
    def __str__(self):
        cost = self.get_cost()
        tax = self.get_tax()
        return f"{self.name} Sundae with {self.topping}\n- ${cost:.2f}, [tax: ${tax:.2f}]"

# dessertShop.py
def main():
    order = Order()
    order.add_item(Cookie("Chocolate", 5, 4.99))
    order.add_item(Candy("Gummy Bears", 1.5, 2.99))
    order.add_item(IceCream("Vanilla", 1.99))
    order.add_item(Sundae("Strawberry", 2.99, "Whipped Cream", 0.50))
    
    print(order)

if __name__ == "__main__":
    main()
