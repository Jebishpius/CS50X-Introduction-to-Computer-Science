from cs50 import get_float
import math
while True:
    i = get_float("Change Owed: ")
    if i > 0:
        break
c = round(i * 100)
quater = math.floor(c / 25)
rem = c % 25
dime = math.floor(rem / 10)
rem1 = c - (quater * 25) - (dime * 10)
nickel = math.floor(rem1/5)
penny = c - (quater * 25) - (dime * 10) - (nickel * 5)
totcoins = quater + dime + nickel + penny
print(totcoins)
