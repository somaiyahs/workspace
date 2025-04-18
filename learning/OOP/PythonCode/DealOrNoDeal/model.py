from kivy.app import App
from kivy.uix.boxlayout import BoxLayout
from kivy.properties import ObjectProperty
from kivy.uix.popup import Popup
from kivy.uix.label import Label
from kivy.uix.button import Button


import random 
from typing import List

##################### Model ####################
"""
Class Name:     Box
Description:    This class represents a case with number, 
                amount and status(open/closed) 
"""
class Box():
    # Constructor: initializing the attributes 
    def __intit__(self, num: int, amt: int):
        self.number = num       # indicate the number of the box 
        self.amount = amt       # indicates the unique amount/prize the box contains 
        self.is_opened = False  # the status of the box being closed when the object is initially created 

    # this method opens the box that is called upon and
    # reveals the ampunt it contains 
    def open(self) -> int:
        self.is_open = True
        return self.amount
    
"""
Name:           Banker
Description:    The person who runs the game and makes the offers
"""
class Banker():
    @staticmethod
    def make_offer(remaining_boxes: List['Box']) -> int:
        remaining_amounts = [box.amount for box in remaining_boxes]
        if not remaining_amounts:
            return 0
        average = sum(remaining_amounts) / len(remaining_amounts)
        # for a more sufficticated game:
        # multiplier = random.uniform(0.4, 0.8)
        # return int(multiplier * average)
        return average

class DealOrNoDealModel():
    PRIZE_AMOUNTS = [0, 1, 5, 10, 25, 50, 75, 100, 200, 300, 400, 500, 750, 1000, 5000, 10000, 25000, 50000, 75000, 100000, 200000, 300000, 400000, 500000, 750000, 1000000]

    def __init__(self):
        self.boxes = self._create_boxes()
        self.player_box = None
        self.rounds = [6, 5, 4, 3, 2, 1]

    def _create_boxes(self) -> List[Box]:
        amounts = random.sample(self.PRIZE_AMOUNTS, len(self.PRIZE_AMOUNTS))
        return [Box(i+1, amount) for i, amount in enumerate(amounts)]
    
    def choose_player_box(self, box_number: int):
        self.player_box = self.boxes[box_number - 1]

    def get_box_by_number(self, number: int) -> Box:
        return self.boxes[number - 1]
    
    def get_remaining_boxes(self) -> List[Box]:
        return [box for box in self.boxes if not box.is_opened and box != self.player_box]
    
    def get_bank_offer(self) -> int:
        return Banker.make_offer(self.get_remaining_boxes())
    
    def reveal_player_box(self) -> int:
        return self.player_box.amount if self.player_box else 0
    

############################ view #####################
class DealOrNoDealView(BoxLayout):
    controller = ObjectProperty(None)
    info_lable = ObjectProperty(None)
    offer_label = ObjectProperty(None)
    grid = ObjectProperty(None)
    deal_btn = ObjectProperty(None)
    no_deal_btn = ObjectProperty(None)

    def set_controller(self, controller):
        self.controller = controller
        for i, btn in enumerate(self.grid.children[::-1]):
            box_number = i + 1 
            btn.text = str(box_number)
            btn.bind(on_release=lambda btn, idx=box_number:self.handle_box_selection(idx))


    def buildLayout(self):
        dm = DealOrNoDealModel()
        
        layout = GridLayout(cols=3)
        for box in dm.boxes:
            layout.add_widget(Button(box.number))