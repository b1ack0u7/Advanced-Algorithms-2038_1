# -*- coding: utf-8 -*-
"""
Created on Tue Aug 17 09:26:20 2021

@author: axelm
"""
        
inp=list(str(input()))

flag="NO"
arr=[]
arr.append(inp[0])
inp.pop(0)

for i in range(0, len(inp)):
    if(arr[0] == inp[i]):
        arr.append(inp[i])
    else:
        arr.clear()
        arr.append(inp[i])

    if(len(arr) >= 7):
        flag="YES"
        break

print(flag)        