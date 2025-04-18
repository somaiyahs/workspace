# from dessert import Cookie
 
# my_cookie1 = Cookie("oatmeal raisin", 4, 3.45)
# my_cookie2 = Cookie("chocolate chip", 6, 3.99)
# my_cookie3 = Cookie("Snicker Doodle", 7, 5.99)
 

from dessert import Cookie
import pytest
 
def test_cookie_packaging():
  my_cookie1 = Cookie("oatmeal raisin", 4, 3.45)
  assert my_cookie1.packaging == "Box", f"expected 'Box', got {my_cookie1.packaging}"