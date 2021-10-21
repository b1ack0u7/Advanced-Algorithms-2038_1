# -*- coding: utf-8 -*-
"""
Created on Thu Sep  2 21:01:45 2021

@author: axelm
"""

from math import floor, ceil

def flt(obj):
    flat_list = []
    for sublist in obj:
            for item in sublist:
                flat_list.append(item)
    return flat_list

def move(data):
    postArr = len(data)-1
    while True:
        obj = list(set(flt(data)))
        #print("DBG: ", obj)
        if((obj == sortedArr) or (obj == sortedArr.reverse())):
            return True
        
        data.insert(postArr-1, data[postArr])
        data.pop(postArr+1)
        postArr -= 1
        
        
        if(postArr == 0):
            return False
        

def ops(calcs, data):
    tmpArr = []
    postArr = len(calcs)-1
    
    
    while True:
        tmpArr.clear()
        for i in range(0,len(calcs)):
            tmpArr.append(data[i:i+calcs[i]])
        
        #print("DBY: ", tmpArr)
        ret = move(tmpArr.copy())
        
        if(ret == True):
            print("YES")
            break
            
        
        calcs.insert(postArr-1, calcs[postArr])
        calcs.pop(postArr+1)
        calcs.insert(len(calcs), data[len(data)-1])
        postArr -= 1
        
        if(postArr == -1):
            print("NO")
            break
    
     
long = int(input())

infoArr = []
dataArr = []
calcs = []

for i in range(0, long):
    tmpInfo = str(input()).split(" ")
    infoArr.append(list(map(int, tmpInfo)))
    
    tmpData = str(input()).split(" ")
    dataArr.append(list(map(int, tmpData)))


for i in range(0, len(infoArr)):
    sortedArr = sorted(dataArr[i])
    
    if(infoArr[i][1] != 1):
        calcs.clear()
        
        calcUP = ceil(infoArr[i][0]/infoArr[i][1])
        calcDW = floor(infoArr[i][0]/infoArr[i][1])
        calcSM = calcUP+calcDW
        
        while True:
            calcs.append(calcDW)
            calcSM += calcDW
            if(calcSM >= infoArr[i][0]):
                break
            
        
        calcs.append(calcUP)
        
        ops(calcs,dataArr[0].copy())
        
    else:
        if((dataArr[i] == sortedArr) or (dataArr[i] == sortedArr.reverse())):
            print("YES")
        else:
            print("NO")
    
