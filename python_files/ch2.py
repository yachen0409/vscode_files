# -*- coding: utf-8 -*-
"""
Created on Sat Aug 28 07:56:22 2021

@author: yo
"""
import numpy as np
from map_printer import MapPrinter, vis_map
import cv2

class maze():
    def __init__(self, size):
        self.size = size
        self.cur_pos = [0, 0, 0]
        self.cur_maze = []

    def gen_map(self, obs_list):
        empty_map = np.empty([self.size[1], self.size[0]], dtype=str)
        for w in range(self.size[0]):
            for h in range(self.size[1]):
                if h == 0 or h == self.size[1]-1 or w == 0 or w == self.size[0]-1:
                    empty_map[h, w] = "1"
                else:
                    empty_map[h, w] = "0"
        empty_map[self.size[1]-2, self.size[0]-2] = "x"
        empty_map[self.cur_pos[0]+1, self.cur_pos[1]+1] = "*"
        for obs in obs_list:
            map = empty_map.copy()
            for i in obs:
                map[i[1]+1, i[0]+1] = "1"
            self.cur_maze.append(map)
        
    def show_maze(self):
        printer = MapPrinter()
        while True:
            for i in self.cur_maze:
                # print(i)
                printer.print_maze(i)
                k = cv2.waitKey(1000)
            if k == "q":
                
                printer.finish()
                
    def handle_cmd(self, cmd):
        self.cur_maze[self.cur_pos[2]][self.cur_pos[0]+1, self.cur_pos[1]+1] = "0"
        if cmd == "w":
            self.cur_pos[0] -= 1
        elif cmd == "a":
            self.cur_pos[1] -= 1
        elif cmd == "s":
            self.cur_pos[0] += 1
        elif cmd == "d":
            self.cur_pos[1] += 1
            
        dest = self.cur_maze[self.cur_pos[2]][self.cur_pos[0]+1, self.cur_pos[1]+1]
        # print(self.cur_maze[self.cur_pos[2]])
        if dest == "2":
            self.cur_pos[2] += 1
            return True
        elif dest == "1":
            if cmd == "w":
                self.cur_pos[0] += 1
            elif cmd == "a":
                self.cur_pos[1] += 1
            elif cmd == "s":
                self.cur_pos[0] -= 1
            elif cmd == "d":
                self.cur_pos[1] -= 1
        self.cur_maze[self.cur_pos[2]][self.cur_pos[0]+1, self.cur_pos[1]+1] = "*"
        print(f'{cmd}: ({self.cur_pos[1]}, {self.cur_pos[0]}, {self.cur_pos[2]})')
                
               
if __name__ == '__main__':        
    file = open("maze_info.txt")
    info = file.readline().split()
    info = list(map(int, info))  # 字串轉整數
    width = info[0]+2
    height = info[1]+2
    num = info[2]
    
    maze_size = (width, height)
    maze = maze(maze_size)
    obs_list = []
    for i in range(num):
        temp = file.readline().split("&")
        obs = []
        for j in temp:
            j = list(map(int, j.split()))
            obs.append(j)
        obs_list.append(obs)
    file.close()
    
    maze.gen_map(obs_list)
    for i in maze.cur_maze:
        while True:
            img = vis_map(i)
            cv2.imshow('Maze main1', img)
            k = cv2.waitKey(0)
            if k == ord('q'):
                exit(0)
            elif maze.handle_cmd(chr(k)):
                maze.cur_pos[0:2] = [0, 0]
                break
    print("goal!!")

        
    



    