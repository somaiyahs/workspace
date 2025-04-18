# from dessert import Candy
 
# my_candy1 = Candy("Twix", 3, 4.52)
# my_candy2 = Candy("Kit-Kat", 4, 4.5)
# my_candy3 = Candy("Snickers", 5, 5.67)

from dessert import Candy
import pytest
 
def test_candy_packaging():
  my_candy1 = Candy("Twix", 3, 4.52)
  assert my_candy1.packaging == "Bag", f"expected 'Bag', got {my_candy1.packaging}"
 
  my_candy2 = Candy("Twix", 2, 4.52)
  # Need help with how to test with Combinable methods