# -*- coding: utf-8 -*-
"""
Created on Tue Aug 17 20:15:03 2021

@author: axelm
"""

dataArr=[]
def core():
    count=0
    for i in dataArr:
        for j in dataArr:
            if(i[0] == j[1]):
                count+=1
    return count

n=int(input())

for i in range(n):
    dataArr.append(str(input()).split(" "))

print(core())
    