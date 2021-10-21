# -*- coding: utf-8 -*-
"""
Created on Tue Aug 17 08:52:32 2021

@author: axelm
"""

import sys
coins = []
coinsValueTotal = 0
n = 8
inputs = "1 2 8 4 5 9 7 8 7".split()

for i in range(len(inputs)):
    coin = int(inputs[i])
    coins.append(coin)
    coinsValueTotal += coin
    coins.sort(reverse = True)
    minCoins = 0
    halfCoinsValueTotal = coinsValueTotal / 2
for i in range(len(coins)):
    minCoins +=  coins[i]
    if(minCoins > halfCoinsValueTotal):
        print (i+1)
        break