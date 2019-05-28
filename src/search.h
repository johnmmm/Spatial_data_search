#ifndef SEARCH_H
#define SEARCH_H

#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdio>
#include <sstream>
#include <cstdlib>
#include <stdlib.h>
#include <cstring>
#include <stdio.h>
#include <algorithm>

#include "GPTree.h"

using namespace std;

const char car_file[] = "./../data/car.txt";
const int MAXN = 1364355283;
const int MAX_PASS = 4;

// 存储汽车信息
struct Car
{
    int pos;
    int pass_num;
    vector<int> tar_pos;
};

class Search
{
public:
    Search();
    ~Search();

    void init_tree();  // 读取建立树
    void init();       // 运行启动
    void init_dis_matrix(int car_pos, vector<int>& tar_pos_vec); // 在每次计算前生成距离矩阵
    int delivery_dis(int car_pos, vector<int>& tar_pos_vec); // 计算送完当前车上所有人的距离
    void search_cars(int cur_pos, int tar_pos, vector<int>& res);  // 寻找合适的车

    void clear();
    void build_permutation();
    void read_cars();
    void print_cars();

    GPTree gptree;
    int dis_matrix[MAX_PASS+1][MAX_PASS+1]; // 0代表和car的距离，i，j为i-1和j-1个乘客的距离
};

#endif