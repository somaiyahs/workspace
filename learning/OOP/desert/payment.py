from enum import Enum
from typing import Protocol
 
class PayType(Enum):
  CASH = 'CASH'
  CARD = 'CARD'
  PHONE = 'PHONE'
 
class Payable(Protocol):
 
  def get_pay_type(self) -> PayType:
    pass
 
  def set_pay_type(self, payment_method: PayType) -> None:
    pass
 