import pyperclip
import pyautogui
import time
import winsound
from datetime import datetime


refresh_position = 1271, 279
start_position = 430, 513
end_position = 515, 513
count: int = 0
previous_question: tuple = ()
updated_previous: list[tuple] = list(())
filepath = r"C:\Code\Python\AskAssist\build-clipboardlistener-Desktop_Qt_6_5_0_MinGW_64_bit-Debug\timestamp.txt"

def read_last_line_simple():
    with open(filepath, 'r') as file:
        lines = file.readlines()
        line = ""
        if lines:
            line = (lines[-1]).strip()
        return line

line1 = read_last_line_simple()

line2 = read_last_line_simple()

print(line1 == line2)