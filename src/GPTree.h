#ifndef GPTREE_H
#define GPTREE_H

#include <time.h>
#include <stdio.h>
#include <iostream>

using namespace std;

class GPTree
{
public:
    GPTree();
    ~GPTree();

	void init();
	void read();
	void save();
	void load();
	void build_tree();

	int get_min_distance(int S, int T);

	//void test();
	void read_node();
	void output();
    
    void test_cmake();
};

#endif