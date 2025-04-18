# from dessert import Order, Candy, Cookie, IceCream, Sundae

# class DessertShop:
#     """Handles user input for different dessert items."""
#     @staticmethod
#     def user_prompt_candy():
#         name = input("Enter the candy name: ")
#         weight = float(input("Enter the weight in pounds: "))
#         price_per_pound = float(input("Enter the price per pound: "))
#         return Candy(name, weight, price_per_pound)

#     @staticmethod
#     def user_prompt_cookie():
#         name = input("Enter the cookie name: ")
#         quantity = int(input("Enter the number of cookies: "))
#         price_per_dozen = float(input("Enter the price per dozen: "))
#         return Cookie(name, quantity, price_per_dozen)

#     @staticmethod
#     def user_prompt_icecream():
#         name = input("Enter the ice cream name: ")
#         scoop_count = int(input("Enter the number of scoops: "))
#         price_per_scoop = float(input("Enter the price per scoop: "))
#         return IceCream(name, scoop_count, price_per_scoop)

#     @staticmethod
#     def user_prompt_sundae():
#         name = input("Enter the sundae name: ")
#         scoop_count = int(input("Enter the number of scoops: "))
#         price_per_scoop = float(input("Enter the price per scoop: "))
#         topping_name = input("Enter the topping name: ")
#         topping_price = float(input("Enter the topping price: "))
#         return Sundae(name, scoop_count, price_per_scoop, topping_name, topping_price)

# def main():
#     shop = DessertShop()
#     order = Order()
    
#     done = False
#     prompt = '\n'.join([
#         '\n',
#         '1: Candy',
#         '2: Cookie',
#         '3: Ice Cream',
#         '4: Sundae',
#         '\nWhat would you like to add to the order? (1-4, Enter for done): '
#     ])

#     while not done:
#         choice = input(prompt)

#         if choice == '':
#             done = True
#         elif choice == '1':
#             item = shop.user_prompt_candy()
#             order.add(item)
#             print(f'{item.name} has been added to your order.')
#         elif choice == '2':
#             item = shop.user_prompt_cookie()
#             order.add(item)
#             print(f'{item.name} has been added to your order.')
#         elif choice == '3':
#             item = shop.user_prompt_icecream()
#             order.add(item)
#             print(f'{item.name} has been added to your order.')
#         elif choice == '4':
#             item = shop.user_prompt_sundae()
#             order.add(item)
#             print(f'{item.name} has been added to your order.')
#         else:
#             print('Invalid response: Please enter a choice from the menu (1-4) or press Enter to finish.')

#     print('\nYour Order Summary:\n')
#     print(order)

# if __name__ == "__main__":
#     main()




from dessert import Order, Candy, Cookie, IceCream, Sundae
from tabulate import tabulate

class Customer():
   NEXT_ID = 0
   name: str
   order_history: list[Order]
   id: int

   def __init__(self, name):
      self.name = name 
      order_history = []
      id = NEXT_ID + 1 
      NEXT_ID += 1 

   def add2history(order:Order) -> "Customer":
      self.order_history.append(order)
      return self
      
 
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
  def user_prompt_payment():
    payment_type = input("Enter type of payment: ")
    while payment_type not in ["CASH", "CARD", "PHONE"]:
      payment_type = input("Invalid payment type. Try: 'CASH', 'CARD', or 'PHONE'. ")
    return payment_type
 
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
  done: bool = False
  # build the prompt string once
  prompt = '\n'.join([ '\n',
          '1: Candy',
          '2: Cookie',
          '3: Ice Cream',
          '4: Sundae',
          '\nWhat would you like to add to the order? (1-4, Enter for done): '
    ])
 
#   while not done:
#     choice = input(prompt)
#     match choice:
#       case '':
#         order.sort_order()
#         payment_method = shop.user_prompt_payment()
#         order.set_pay_type(payment_method)
#         done = True
#       case '1':
#         item = shop.user_prompt_candy()
#         order.add(item)
#         print(f'{item.name} has been added to your order.')
#       case '2':
#         item = shop.user_prompt_cookie()
#         order.add(item)
#         print(f'{item.name} has been added to your order.')
#       case '3':
#         item = shop.user_prompt_icecream()
#         order.add(item)
#         print(f'{item.name} has been added to your order.')
#       case '4':
#         item = shop.user_prompt_sundae()
#         order.add(item)
#         print(f'{item.name} has been added to your order.')
#       case _:
#         print('Invalid response:  Please enter a choice from the menu (1-4) or Enter')
 

  while not done:
        choice = input(prompt)

        if choice == '':
            done = True
        elif choice == '1':
            item = shop.user_prompt_candy()
            order.add(item)
            print(f'{item.name} has been added to your order.')
        elif choice == '2':
            item = shop.user_prompt_cookie()
            order.add(item)
            print(f'{item.name} has been added to your order.')
        elif choice == '3':
            item = shop.user_prompt_icecream()
            order.add(item)
            print(f'{item.name} has been added to your order.')
        elif choice == '4':
            item = shop.user_prompt_sundae()
            order.add(item)
            print(f'{item.name} has been added to your order.')
        else:
            print('Invalid response: Please enter a choice from the menu (1-4) or press Enter to finish.')

  print(tabulate(order.to_list(), tablefmt="fsql"))
 
if __name__=="__main__":
  main()
 