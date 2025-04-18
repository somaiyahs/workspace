from desertshop import Customer
import pytest

def test_customer():
    c1 = Customer("David")
    c2 = Customer("John")
    c3 = Customer("Dave")

    assert c1.id != c2.id, "Expected to be true "
    assert c1.id != c3.id, "expected to be true"
    assert c2.id != c3.id, "Expected to be true"