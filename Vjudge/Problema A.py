# -*- coding: utf-8 -*-
"""
Created on Mon Aug 16 15:44:34 2021

@author: axelm
"""

l1 = int(input())
l2 = str(input())

nums=list(map(int, l2.split(" ")))
nums.sort(reverse=True)

def op():
    altArr=[]
    altArr.append(nums[0])
    nums.pop(0)
    altSum=sum(altArr)
    mainSum=sum(nums)
    while mainSum+1 > altSum:
        altArr.append(nums[0])
        nums.pop(0)
        altSum=sum(altArr)
        mainSum=sum(nums)
    return len(altArr)
    
print(op())