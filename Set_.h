#ifndef SET_H
#define SET_H
#include <iostream>
#include <vector>
#include "CacheBlock.h"
using namespace std;

class Set_
{
public:
	Set_(int);
	vector<CacheBlock> blocks;
	~Set_();
};
#endif

