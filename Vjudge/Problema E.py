# -*- coding: utf-8 -*-
"""
Created on Tue Aug 17 10:17:02 2021

@author: axelm
"""
tokenizedArr = []
nodesDict = []
converge = "0"

def pather():
    global converge
    for i in range(0, len(nodesDict[0])):
        for j in range(0, len(nodesDict[1])):
            if(nodesDict[0][i] == nodesDict[1][j]):
                converge = nodesDict[0][i]
                break
    
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
    

class Node:
    def __init__(self, data):
        self.left = None
        self.right = None
        self.data = data
    
    def insert(self, data):
        if self.data:
            if data < self.data:
                if self.left is None:
                    self.left = Node(data)
                else:
                    self.left.insert(data)
            elif data > self.data:
                if self.right is None:
                    self.right = Node(data)
                else:
                    self.right.insert(data)
        else:
            self.data = data
    
    def LCA(self):
        msc={}
        msc["M"] = self.data
        try: 
            msc["L"] = self.left.data
        except:
            msc["L"] = "-"
        try:
            msc["R"] = self.right.data
        except:
            msc["R"] = "-"
        
        tokenizedArr.append(msc)
        if(self.left != None):
            self.left.LCA()
        if(self.right != None):
            self.right.LCA()
            
    def revFinder(self, CNV):
        global memADR
        if(self.data == CNV):
            print(self.data)
            
        if(self.left != None):
            self.left.revFinder(CNV)
            
        if(self.right != None):
            self.right.revFinder(CNV)
        
        

n=int(input())
nodes=str(input()).split(" ")
targets=str(input()).split(" ")

core = Node(nodes[0])
nodes.pop(0)

for i in range(0, len(nodes)):
    core.insert(nodes[i])


core.LCA()
refract(targets)
core.revFinder(converge)