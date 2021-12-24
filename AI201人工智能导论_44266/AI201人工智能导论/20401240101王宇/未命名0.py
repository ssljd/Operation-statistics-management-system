# -*- coding: utf-8 -*-
"""
Created on Sun May 16 20:07:59 2021

@author: DJ MR.L
"""

"""A星算法解决八数码问题"""
import numpy as np
import copy
import time
from operator import itemgetter

goal = {}

def get_location(vec, num):    #找到num对应的位置
    row_num = vec.shape[0]     #行
    line_num = vec.shape[1]    #列
    
    for i in range(row_num):
        for j in range(line_num):
            if num == vec[i][j]:
                return i, j

def get_actions(vec):    #判断下一步能移动的位置
    row_num = vec.shape[0]
    line_num = vec.shape[1]
    
    (x, y) = get_location(vec, 0)    #获取0的位置
    action = [(0, 1), (0, -1), (1, 0), (-1, 0)]

    #判断下一步可以移动的位置
    if x == 0:    #0在第一行，不能上移
        action.remove((-1, 0))
    if y == 0:   #不能左移
        action.remove((0, -1))
    if x == row_num - 1:  #不能下移
        action.remove((1, 0))
    if y == line_num - 1:  #不能右移
        action.remove((0, 1))
        
    return list(action)

def result(vec, action):    #移动元素，做矩阵变换
    (x, y) = get_location(vec, 0)    #获取0的位置
    (a, b) = action    #获取可以移动的位置
                                 
    n = vec[x+a][y+b]    #移动位置，交换元素
    s = copy.deepcopy(vec)
    s[x+a][y+b] = 0
    s[x][y] = n
     
    return s
    
def get_ManhattanDis(vec1, vec2):    #vcc1时目标矩阵，vcc2是当前矩阵  计算曼哈顿距离
    row_num = vec1.shape[0]
    line_num = vec1.shape[1]
    dis = 0
    
    for i in range(row_num):
        for j in range(line_num):
            if vec1[i][j] != vec2[i][j] and vec2[i][j] != 0:
                k, m = get_location(vec1, vec2[i][j])
                d = abs(i - k) + abs(j - m)
                dis += d
                
    return dis

def expand(p, actions, step):           #Actions是可以移动的方向, P是当前矩阵,step是所花的步数
    children = []  #存储当前节点扩展的矩阵
    for action in actions:
        child = {}
        child['parent'] = p
        child['vec'] = (result(p['vec'], action))
        child['dis'] = get_ManhattanDis(goal['vec'], child['vec'])
        child['step'] = step + 1
        child['dis'] = child['dis'] + child['step']    #更新节点的代价值，步数+曼哈顿距离  f=g+h（step+child[dis]）
        child['action'] = get_actions(child['vec'])
        children.append(child)
    
    return children

def node_sort(nodelist):    #对列表从大到小排序
    return sorted(nodelist, key=itemgetter('dis'), reverse=True)

#获取输入
def get_input(num):
    A = []
    for i in range(num):
        temp = []
        p = []
        s = input()
        temp = s.split(' ')
        for t in temp:
            t = int(t)
            p.append(t)
        A.append(p)
   
    return A  

def get_parent(node):
    q = {}
    q = node['parent']   
    return q
        
def main():
    openlist = []    #open表
    close = []       #存储父节点的扩展列表
    
    print('请输入阶数')
    num = int(input())
    print("请输入初始的矩阵，以空格分开")
    A = get_input(num)

    print("请输入目标矩阵，以空格分开")
    B = get_input(num)

    #存储步骤的文件
    #resultfile = input('请输入文件名：\n')
    resultfile = "a.txt"

    goal['vec'] = np.array(B)
   
    p = {}
    p['vec'] = np.array(A)
    p['dis'] = get_ManhattanDis(goal['vec'], p['vec'])
    p['step'] = 0
    p['action'] = get_actions(p['vec'])
    p['parent'] = {}

    if (p['vec'] == goal['vec']).all():
        return
    
    openlist.append(p)
    
    #start_CPU = time.clock()  #执行时间
    
    while openlist:
        
        children = []
        
        node = openlist.pop()    #取出open表里的最后一个
        close.append(node)  #把它放到close表
      
        if (node['vec'] == goal['vec']).all():    #检查当前矩阵和目标矩阵是否相同
            #end_CPU = time.clock()    #执行完成时间

            #将步骤写入文件
            h = open(resultfile, 'w', encoding='utf-8',)
            h.write('Size of the search tree:' + str(len(openlist)+len(close)) + '\n')
            h.write('close：' + str(len(close)) + '\n')
            h.write('openlist：' + str(len(openlist)) + '\n')
            #h.write('CPU running time：' + str(end_CPU - start_CPU) + '\n')
            h.write('The path length:' + str(node['dis']) + '\n')
            h.write('The path of the solution: ' + '\n')
            i = 0
            way = []
            while close:
                way.append(node['vec'])
                node = get_parent(node)
                if(node['vec'] == p['vec']).all():
                    way.append(node['vec'])
                    break
            while way:
                i += 1
                h.write(str(i) + '\n')
                h.write(str(way.pop()) + '\n')
            h.close()
            f = open(resultfile,'r',encoding='utf-8',)
            print(f.read())
            
            return
        
        children = expand(node, node['action'], node['step'])    #如果不是目标矩阵, 扩展节点

        for child in children:    
            f = False
            flag = False
            j = 0
            for i in range(len(openlist)):
                if (child['vec'] == openlist[i]['vec']).all():
                    j = i
                    flag = True
                    break
            for i in range(len(close)): #是否在close表
                if(child['vec'] == close[i]).all():
                    f = True
                    break
            if f == False and flag == False :# 如果新节点不在close表或open表中，则插入open表
                openlist.append(child)
                
            elif flag == True: #比较代价值,保留小的
                if child['dis'] < openlist[j]['dis']:
                    del openlist[j]
                    openlist.append(child)
                    
        
        openlist = node_sort(openlist)   #排序
    
if __name__ == '__main__':
    main()

