# from abc import ABC, abstractmethod
 
# # Order Class
# class Order():
#   def __init__(self):
#     """default constructor that takes no arguments and instantiates the order
#     instance variable to a new list of DessertItem."""
#     self.order = []
 
#   def add(self, dessert):
#     """takes a single DessertItem and adds it to the empty list 'order'."""
#     self.dessert = dessert
#     self.order.append(dessert)
 
#   def __len__(self):
#     """magic method that returns the number of items in the list 'order'."""
#     return len(self.order)
 
#   def order_cost(self):
#     """Calculates and returns the total cost for all items in the order."""
#     return sum(dessert.calculate_cost() for dessert in self.order)
 
#   def order_tax(self):
#     """Calculates and returns the total tax for all items in the order."""
#     return sum(dessert.calculate_tax() for dessert in self.order)
 
#   def __str__(self):
#     return "\n".join(str(item) for item in self.order)
 
#   def to_list(self):
#     return [line.split(", ") for line in (self).split("\n")]
 
# # DessertItem Superclass
# class DessertItem(ABC):
#   def __init__(self, name='', tax_percent=.0725):
#     self.name = name
#     self.tax_percent = tax_percent
 
#   # add a new abstract method, calculate_cost()
#   @abstractmethod
#   def calculate_cost(self):
#     pass
 
#   def calculate_tax(self):
#     return self.calculate_cost() * self.tax_percent
 
# # Candy Class
# class Candy(DessertItem):
#   def __init__(self, name='', candy_weight=0.0, price_per_pound=0.0):
#     super().__init__(name)
#     self.candy_weight = candy_weight
#     self.price_per_pound = price_per_pound
 
#   def calculate_cost(self):
#     return self.candy_weight * self.price_per_pound
 
#   def __str__(self):
#     candy_cost = self.calculate_cost()
#     candy_tax = self.calculate_tax()
#     return f"{self.name}\n"
#     return f"-\t{self.candy_weight} lbs. @ ${self.price_per_pound:.2f}/lb:, ${candy_cost:.2f}, [Tax: ${candy_tax:.2f}]\n"
 
# # Cookie Class
# class Cookie(DessertItem):
#   def __init__(self, name='', cookie_quantity=12, price_per_dozen=3):
#     super().__init__(name)
#     self.cookie_quantity = cookie_quantity
#     self.price_per_dozen = price_per_dozen
 
#   def calculate_cost(self):
#     return self.cookie_quantity * (((self.price_per_dozen * 100) / 12) / 100)
 
#   def __str__(self):
#     cookie_cost = self.calculate_cost()
#     cookie_tax = self.calculate_tax()
#     return f"{self.name} Cookies\n"
#     return f"-\t{self.cookie_quantity} cookie(s). @ ${self.price_per_dozen:.2f}/dozen:, ${self.cookie_cost:.2f}, [Tax: ${cookie_tax:.2f}]\n"
 
 
# # IceCream Class
# class IceCream(DessertItem):
#   def __init__(self, name='', scoop_count=0, price_per_scoop=0.0):
#     super().__init__(name)
#     self.scoop_count = scoop_count
#     self.price_per_scoop = price_per_scoop
 
#   def calculate_cost(self):
#     return self.scoop_count * self.price_per_scoop
 
#   def __str__(self):
#     ice_cream_cost = self.calculate_cost()
#     ice_cream_tax = self.calculate_tax()
#     return f"{self.name} Ice Cream\n"
#     return f"-\t{self.scoop_count} scoop(s). @ ${self.price_per_scoop:.2f}/dozen:, ${self.ice_cream_cost_cost:.2f}, [Tax: ${self.ice_cream_tax:.2f}]\n"
 
# # Sundae Class
# class Sundae(DessertItem):
#   def __init__(self, name='', scoop_count=1, price_per_scoop=2, topping_name='', topping_price=0.5):
#     super().__init__(name)
#     self.scoop_count = scoop_count
#     self.price_per_scoop = price_per_scoop
#     self.topping_name = topping_name
#     self.topping_price = topping_price
 
#   def calculate_cost(self):
#         return (self.scoop_count * self.price_per_scoop) + self.topping_price
 
#   def __str__(self):
#     sundae_cost = self.calculate_cost()
#     sundae_tax = self.calculate_tax()
#     return f"{self.topping_name} {self.name} Sundae\n"
#     return f"-\t{self.scoop_count} scoop(s). @ ${self.price_per_scoop:.2f}/scoop\n"
#     return f"-\t{self.topping_name} topping @ ${self.topping_price:.2f}:, ${self.sundae_cost:.2f}, [Tax: ${self.sundae_tax:.2f}]\n"
 
from abc import ABC, abstractmethod
from packaging import Packaging
from payment import Payable
from combine import Combinable
 
# Order Class
class Order:
  def __init__(self):
    """default constructor that takes no arguments and instantiates the order
    instance variable to a new list of DessertItem."""
    self.order = []
    self.payment_method = "CASH"
    self._index = 0
 
  def get_pay_type(self):  
    return self.payment_method
 
  def set_pay_type(self, payment_method):
    if self.payment_method not in ["CASH", "CARD", "PHONE"]:
      raise ValueError(f"Invalid payment method: {self.payment_method}. Must be 'CASH', 'CARD', or 'PHONE'.")
   
    self.payment_method = payment_method
 
  def add(self, dessert):
    """takes a single DessertItem and adds it to the empty list 'order'."""
    for item in self.order:
      if not isinstance(dessert, Combinable) or not item.can_combine(dessert):
        self.order.append(dessert)
      else:
        item.combine(dessert)
 
  def __len__(self):
    """magic method that returns the number of items in the list 'order'."""
    return len(self.order)
 
  def order_cost(self):
    """Calculates and returns the total cost for all items in the order."""
    return sum(dessert.calculate_cost() for dessert in self.order)
 
  def order_tax(self):
    """Calculates and returns the total tax for all items in the order."""
    return sum(dessert.calculate_tax() for dessert in self.order)
 
  def __str__(self):
    order_str = ""
    cost_list = []
    taxes_list = []
    for dessert in self.order:
      order_str += dessert.__str__()
      cost_list.append(dessert.calculate_cost())
      taxes_list.append(dessert.calculate_tax())
    cost_subtotals = self.order_cost()
    tax_subtotals = self.order_tax()
    order_str += "--------------------\n"
    order_str += f"Total number of items in order:, {len(self.order)}\n"
    order_str += f"Order Subtotals:, ${round(cost_subtotals, 2):.2f}, [Tax: ${round(tax_subtotals, 2):.2f}]\n"
    order_str += f"Order Total:, , ${round((cost_subtotals + tax_subtotals), 2):.2f}\n"
    order_str += "--------------------\n"
    order_str += f"Paid with {self.payment_method}\n"
    return order_str
 
  def sort_order(self):
    self.order.sort()
 
  def __iter__(self):
    self._index = 0
    return self
 
  def __next__(self):
    if self._index >= len(self.order):
      raise StopIteration
 
    item = self.order[self._index]
    self._index += 1
    return item
 
  def to_list(self):
    return [line.split(", ") for line in str(self).split("\n")]
 
# DessertItem Superclass
class DessertItem(ABC):
  def __init__(self, name='', tax_percent=.0725):
    self.name = name
    self.tax_percent = tax_percent
 
  # add a new abstract method, calculate_cost()
  @abstractmethod
  def calculate_cost(self):
    pass
 
  def calculate_tax(self):
    return self.calculate_cost() * self.tax_percent
 
  def __eq__(self, price2):
    return self.calculate_cost() == price2.calculate_cost()
 
  def __ne__(self, price2):
    return self.calculate_cost() != price2.calculate_cost()
 
  def __lt__(self, price2):
    return self.calculate_cost() < price2.calculate_cost()
 
  def __gt__(self, price2):
    return self.calculate_cost() > price2.calculate_cost()
 
  def __ge__(self, price2):
    return self.calculate_cost() >= price2.calculate_cost()
 
  def __le__(self, price2):
    return self.calculate_cost() <= price2.calculate_cost()
 
# Candy Class
class Candy(DessertItem):
  def __init__(self, name='', candy_weight=0.0, price_per_pound=0.0):
    super().__init__(name)
    self.candy_weight = candy_weight
    self.price_per_pound = price_per_pound
    self.packaging = "Bag"
 
  def calculate_cost(self):
    return self.candy_weight * self.price_per_pound
 
  def can_combine(self, other:"Candy") -> bool:
    return isinstance(self, Candy) and self.name == other.name and self.price_per_pound == other.price_per_pound
 
  def combine(self, other: "Candy") -> "Candy":
    if not isinstance(other, Candy):
      raise TypeError(f"Argument provided must of type 'Candy', got {type(other)}")
    else:
      self.candy_weight += other.candy_weight
      return self.candy_weight
 
  def __str__(self):
    candy_cost = self.calculate_cost()
    candy_tax = self.calculate_tax()
    return f"{self.name} ({self.packaging})\n-    {self.candy_weight} lbs. @ ${self.price_per_pound:.2f}/lb:, ${candy_cost:.2f}, [Tax: ${candy_tax:.2f}]\n"
 
# Cookie Class
class Cookie(DessertItem):
  def __init__(self, name='', cookie_quantity=12, price_per_dozen=3):
    super().__init__(name)
    self.cookie_quantity = cookie_quantity
    self.price_per_dozen = price_per_dozen
    self.packaging = "Box"
 
  def calculate_cost(self):
    return self.cookie_quantity * (((self.price_per_dozen * 100) / 12) / 100)
 
  def can_combine(self, other:"Cookie") -> bool:
    return isinstance(self, Cookie) and self.name == other.name and self.price_per_dozen == other.price_per_dozen
 
  def combine(self, other: "Cookie") -> "Cookie":
    if not isinstance(other, Cookie):
      raise TypeError(f"Argument provided must of type 'Cookie', got {type(other)}")
    else:
      self.cookie_quantity += other.cookie_quantity
      return self.cookie_quantity
 
  def __str__(self):
    cookie_cost = self.calculate_cost()
    cookie_tax = self.calculate_tax()
    return f"{self.name} Cookies ({self.packaging})\n-    {self.cookie_quantity} cookie(s). @ ${self.price_per_dozen:.2f}/dozen:, ${cookie_cost:.2f}, [Tax: ${cookie_tax:.2f}]\n"
 
# IceCream Class
class IceCream(DessertItem):
  def __init__(self, name='', scoop_count=0, price_per_scoop=0.0):
    super().__init__(name)
    self.scoop_count = scoop_count
    self.price_per_scoop = price_per_scoop
    self.packaging = "Bowl"
 
  def calculate_cost(self):
    return self.scoop_count * self.price_per_scoop
 
  def __str__(self):
    ice_cream_cost = self.calculate_cost()
    ice_cream_tax = self.calculate_tax()
    return f"{self.name} Ice Cream ({self.packaging})\n-    {self.scoop_count} scoop(s). @ ${self.price_per_scoop:.2f}/scoop:, ${ice_cream_cost:.2f}, [Tax: ${ice_cream_tax:.2f}]\n"
 
# Sundae Class
class Sundae(DessertItem):
  def __init__(self, name='', scoop_count=1, price_per_scoop=2, topping_name='', topping_price=0.5):
    super().__init__(name)
    self.scoop_count = scoop_count
    self.price_per_scoop = price_per_scoop
    self.topping_name = topping_name
    self.topping_price = topping_price
    self.packaging = "Boat"
 
  def calculate_cost(self):
        return (self.scoop_count * self.price_per_scoop) + self.topping_price
 
  def __str__(self):
    sundae_cost = self.calculate_cost()
    sundae_tax = self.calculate_tax()
    return f"{self.topping_name} {self.name} Sundae ({self.packaging})\n-    {self.scoop_count} scoop(s). @ ${self.price_per_scoop:.2f}/scoop\n-\t{self.topping_name} topping @ ${self.topping_price:.2f}:, ${sundae_cost:.2f}, [Tax: ${sundae_tax:.2f}]\n"
 