# -*- coding: utf-8 -*-
"""
Created on Tue Aug 17 20:32:46 2021

@author: axelm
"""

def refractor(root):
    tmpArr = []
    
    if root.left != None:
        tmpArr = tmpArr + refractor(root.left)
        
    tmpArr.append(root.data)
    
    if root.right != None:
        tmpArr = tmpArr + refractor(root.right)
        
    return tmpArr
    
def check_binary_search_tree_(root):
    retArr = refractor(root)
    
    if(retArr == sorted(set(retArr))): return True
    else: return False