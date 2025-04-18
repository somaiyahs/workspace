from dessert import Order, Candy, Cookie, IceCream, Sundae
from tabulate import tabulate
from typing import Dict
 
class Customer():
  NEXT_ID = 0
  customer_name: str
  order_history: list[Order]
  customer_id: int
 
  def __init__(self, customer_name):
    self.customer_name = customer_name
    self.customer_id = Customer.NEXT_ID + 1
    Customer.NEXT_ID += 1
    self.order_history = []
 
  def add2history(order:Order)-> "Customer":
    self.order_history.append(order)
    return self
 
  def __str__(self):
    return f"Customer Name: {self.customer_name}       Customer ID: {self.customer_id}\n"
 
customer_db: Dict[str,"Customer"] = {}
 
class DessertShop():
 
  @staticmethod
  def user_prompt_candy():
    name = input("Enter the type of Candy: ")
    weight = float(input("Enter the weight: "))
    price_per_pound = float(input("Enter the price per pound: "))
    return Candy(name, weight, price_per_pound)
 
  @staticmethod
  def user_prompt_cookie():
    name = input("Enter the type of Cookie: ")
    quantity = int(input("Enter the quantity purchased: "))
    price_per_dozen = float(input("Enter the price per dozen: "))
    return Cookie(name, quantity, price_per_dozen)
 
  @staticmethod
  def user_prompt_icecream():
    name = input("Enter the type of Ice Cream: ")
    scoops = int(input("Enter the number of scoops: "))
    price_per_scoop = float(input("Enter the price per scoop: "))
    return IceCream(name, scoops, price_per_scoop)
 
  @staticmethod
  def user_prompt_sundae():
    name = input("Enter the type of Sundae: ")
    scoops = int(input("Enter the number of scoops: "))
    price_per_scoop = float(input("Enter the price per scoop: "))
    topping_name = input("Enter the type of topping: ")
    topping_price = float(input("Enter the topping price: "))
    return Sundae(name, scoops, price_per_scoop, topping_name, topping_price)
 
  @staticmethod
  def user_prompt_payment(order:Order):
    payment_type = input("1:CASH\n2:CARD\n3:PHONE\nEnter payment method): ")
    match payment_type:
      case '1':
        order.set_pay_type("CASH")
      case '2':
        order.set_pay_type("CARD")
      case '3':
        order.set_pay_type("PHONE")
      case _:
        payment_type = input("Invalid response. Try: '1', '2', or '3'. ")
    return order.payment_method
 
  @staticmethod
  def prompt_customer_name():
    name = input("\nEnter customer name: ")
    if name in customer_db:
      return customer_db.get(name).customer_name
    else:
      new_customer = Customer(name)
      customer_db[name] = new_customer
      return new_customer.customer_name
 
def main():
  shop = DessertShop()
  order = Order()
 
  """
  order.add(Candy('Candy Corn', 1.5, 0.25))
  order.add(Candy('Gummy Bears', 0.25, 0.35))
  order.add(Cookie('Chocolate Chip', 6, 3.99))
  order.add(IceCream('Pistachio', 2, 0.79))
  order.add(Sundae('Vanilla', 3, 0.69, 'Hot Fudge', 1.29))
  order.add(Cookie('Oatmeal Raisin', 2, 3.45))
  """
 
  # boolean done = false
  main_exit: bool = False
#  admin_done: bool = False
  new_order: bool = False
  # build the prompt string once
  main_menu = '\n'.join([ '\n',
          '1: Start a new order',
          '2: Admin Module',
          '\nWhat would you like to do? (1-2, or Enter for done): '
    ])
  admin_menu = '\n'.join([ '1: Shop Customer List',
                '2: Customer Order History',
                '3: Exit Admin Module',
                'What would you like to do? (1-3): '
  ])
  order_menu = '\n'.join([ '\n',
          '1: Candy',
          '2: Cookie',
          '3: Ice Cream',
          '4: Sundae',
          '\nWhat would you like to add to the order? (1-4, Enter for done): '
    ])
 
  while not done:
    main_choice = input(prompt)
    match main_choice:
      case '':
        main_exit = True
      case '1':
        name = ""
        new_order = False
        while not order_done:
          order_choice = input(order_prompt)
          match order_choice:
            case '':
              order.sort_order()
              name = shop.prompt_customer_name()
              customer_db.get(name).order_history.append(order)
#?????              payment_method = shop.user_prompt_payment(order)
 #?????          #   order_done = True
            case '1':
              item = shop.user_prompt_candy()
              order.add(item)
              print(f'{item.name} has been added to your order.')
            case '2':
              item = shop.user_prompt_cookie()
              order.add(item)
              print(f'{item.name} has been added to your order.')
            case '3':
              item = shop.user_prompt_icecream()
              order.add(item)
              print(f'{item.name} has been added to your order.')
            case '4':
              item = shop.user_prompt_sundae()
              order.add(item)
              print(f'{item.name} has been added to your order.')
            case _:
              print('Invalid response:  Please enter a choice from the menu (1-4) or Enter ')
       
        print(customer_db.get(name))
        print(f"Total Order: {len(customer_db.get(name).order_history)}")
        print(tabulate(order.to_list(), tablefmt="fsql"))
      case '2':
        admin_done = False
        while not admin_done:
          admin_choice = input(admin_prompt)
          match admin_choice:
            case '1':
              print("\n")
              for c in customer_db.values():
                print(c)
            case '2':
              name = input("Enter the name of the customer: ")
              customer = customer_db.get(name)
              if not customer:
                print(f"No customer bound with name: {name}\n")
              elif not customer.order_history:
                print(f"{name} has not previous orders.\n")
              else:
                print(customer)
                for i, order in enumerate(customer.order_history, start = 1):
                  print(f"Order #: {i}\n")
                  print(order)
            case '3':
              admin_done = True
            case _:
              print("Invalid response. Please enter a choice: (1-3) ")
 
      case _:
        print("Invalid response. Please enter a choice: '1' or Enter ")
 
if __name__=="__main__":
  main()
