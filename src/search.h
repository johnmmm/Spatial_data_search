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

using namespace std;

const char car_file[] = "./../data/car.txt";

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

    void init();

    void clear();
    void read_cars();
    void print_cars();

};

#endif