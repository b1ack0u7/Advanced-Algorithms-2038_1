# -*- coding: utf-8 -*-
"""
Created on Tue Aug 17 16:21:48 2021

@author: axelm
"""
import ctypes
tokenizedArr = []
tokenizedMemory = {}
nodesDict = []
converge = "0"

class Node:
    def __init__(self, data): 
        self.data = data  
        self.left = None  
        self.right = None 
        self.level = None 

    def __str__(self):
        return str(self.data) 

class BinarySearchTree:
    def __init__(self): 
        self.root = None

    def create(self, val):  
        if self.root == None:
            self.root = Node(val)
        else:
            current = self.root
         
            while True:
                if val < current.data:
                    if current.left:
                        current = current.left
                    else:
                        current.left = Node(val)
                        break
                elif val > current.data:
                    if current.right:
                        current = current.right
                    else:
                        current.right = Node(val)
                        break
                else:
                    break

def pather():
    global converge
    #Stage 1 same tokenized
    for i in range(0,len(tokenizedArr)):
        if(tokenizedArr[i]["M"] == v[0]):
            if((tokenizedArr[i]["L"] == v[1]) or (tokenizedArr[i]["R"] == v[1])):
                converge = str(v[0])
                return
    
    #Stage 2
    for i in range(0, len(nodesDict[0])):
        for j in range(0, len(nodesDict[1])):
            if(nodesDict[0][i] == nodesDict[1][j]):
                converge = str(nodesDict[0][i])
                return
    
    
def AUXrefract(var):
    for i in range(0,len(tokenizedArr)):
        if(tokenizedArr[i]["L"] == var):
            #print("ArrL: ",tokenizedArr[i])
            return tokenizedArr[i]["M"]
        elif(tokenizedArr[i]["R"] == var):
            #print("ArrR: ",tokenizedArr[i])
            return tokenizedArr[i]["M"] 
    return None


def refract(targets):    
    tmpArr=[]
    for i in range(0,len(targets)):
        tmpArr.clear()
        tmpArr.append(AUXrefract(targets[i]))
        while True:
            returned = AUXrefract(tmpArr[len(tmpArr)-1])
            if(returned == None):
                break
            else:
                tmpArr.append(returned)
        nodesDict.append(tmpArr.copy())
    
    pather()

    
def subLCA(root, v1, v2):
    msc={}
    msc["M"] = root.data
    tokenizedMemory[str(root.data)] = id(root)
    try: 
        msc["L"] = root.left.data
    except:
        msc["L"] = "-"
    try:
        msc["R"] = root.right.data
    except:
        msc["R"] = "-"
    
    tokenizedArr.append(msc)
    
    if(root.left != None):
        subLCA(root.left, v1, v2)
    if(root.right != None):
        subLCA(root.right, v1, v2)
        
        
def lca(root, v1, v2):
    global converge
    subLCA(root, v1, v2)
    refract([v1,v2])
    
    if(converge == "0"): converge = str(v1)
    r=ctypes.cast(tokenizedMemory[converge], ctypes.py_object)
    endNode = Node(r.value)
    return endNode
    

tree = BinarySearchTree()
t = 8

arr = [8, 4, 9, 1, 2, 3, 6, 5]

for i in range(t):
    tree.create(arr[i])

v = [1, 2]

ans = lca(tree.root, v[0], v[1])
print(ans.data)