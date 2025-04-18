from typing import runtime_checkable, Protocol
 
@runtime_checkable
class Combinable(Protocol):
 
  def can_combine(self, other: "Combinable")->bool:
    pass
 
  def combine(self, other: "Combinable") -> "Combinable":
    pass
 