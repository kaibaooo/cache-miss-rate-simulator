#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "Set_.h"

using namespace std;

uint32_t hexstr_to_uint(string);
void setNewlyLRU(uint32_t, uint32_t);
void updateCache(uint32_t);
void generateCache();
void showCacheBlockInfo(uint32_t);

ifstream fin;
stringstream ss;
string tmp;
bool DebugMode = false;

char *trace_file_name;
uint32_t cache_size;
uint32_t block_size;
uint32_t set_degree;
uint32_t MissCount = 0;
uint32_t HitCount = 0;


vector<Set_> cache;

int main(int argc, char *argv[]) {
	// Init
	
	if (argc < 5) {
		cout << "argv error" << endl;
		return 0;
	}
	trace_file_name = argv[1];
	cache_size = atoi(argv[2]);
	block_size = atoi(argv[3]);
	set_degree = atoi(argv[4]);
	DebugMode = atoi(argv[5]);
	cache_size*=1024;
	printf("Trace File : %s\n"
	"Cache Size : %u Bytes\t"
	"Block Size : %u\t"
	"Set Degree : %u\n",
	trace_file_name, 
	cache_size, block_size, set_degree);

	generateCache();
	fin.open(trace_file_name);
	
	while (getline(fin, tmp)) {
		if (fin.eof()) break;
		//cout << hexstr_to_uint(tmp) << endl;
		uint32_t addr = hexstr_to_uint(tmp);
		uint32_t mem_block_num = floor(addr / block_size);
		uint32_t cache_block_num = mem_block_num % (cache_size / block_size / set_degree);
		updateCache(mem_block_num);
		if(DebugMode)
			showCacheBlockInfo(cache_block_num);
		
	}
	printf("Total Cache Operation : %u\n", HitCount + MissCount);
	printf("Hit : %u \t Miss : %u\n", HitCount, MissCount);
	double rate = (double)MissCount / (double)(HitCount + MissCount);
	printf("Miss Rate : %lf\n", rate);
	// printf("C_size: %u \t b_size: %u \t way: %u Miss Rate: %lf \n", cache_size/1024, block_size, set_degree, rate);
	return 0;
}

uint32_t hexstr_to_uint(string target) {
	// C++11 feature yeahhhhh
	uint32_t result = stoul(target, nullptr, 16);
	return result;
}

void generateCache() {
	uint32_t numSet = cache_size / block_size / set_degree;
	for (uint32_t i = 0; i < numSet; i++) {
		cache.push_back(Set_(set_degree));
	}
}
void updateCache(uint32_t mem_block) {
	uint32_t index = mem_block % (cache_size / block_size / set_degree);
	uint32_t tag = mem_block / (cache_size / block_size / set_degree);
	// Check same tag
	for (uint32_t i = 0; i < set_degree; i++) {
		if (cache[index].blocks[i].valid && cache[index].blocks[i].tag == tag) {
			HitCount++;
			//printf("Hit %u at set block %u\n", tag, i);
			setNewlyLRU(index, i);
			return;
		}
	}
	// Space availible and put new tag
	for (uint32_t i = 0; i < set_degree; i++) {
		if (!cache[index].blocks[i].valid) {
			for (uint32_t j = 0; j < set_degree; j++) {
				if (cache[index].blocks[j].lru) cache[index].blocks[j].lru++;
			}
			cache[index].blocks[i].valid = true;
			cache[index].blocks[i].tag = tag;
			cache[index].blocks[i].lru = 1;
			MissCount++;
			return;
		}
	}
	// Replace by LRU
	for (uint32_t i = 0; i < set_degree; i++) {
		if (cache[index].blocks[i].lru == set_degree) {
			cache[index].blocks[i].valid = true;
			cache[index].blocks[i].tag = tag;
			MissCount++;
			setNewlyLRU(index, i);
			return;
		}
	}
}

void setNewlyLRU(uint32_t index, uint32_t first_idx) {
	uint32_t targetLRU = cache[index].blocks[first_idx].lru;
	// �p��̷s��s��Index ��++ ��L����
	for (uint32_t i = 0; i < set_degree; i++) {
		if (cache[index].blocks[i].lru < targetLRU) {
			cache[index].blocks[i].lru++;
		}
		else if (cache[index].blocks[i].lru == targetLRU) {
			cache[index].blocks[i].lru = 1;
		}
		else continue;
	}

}

void showCacheBlockInfo(uint32_t index) {
	printf("=================================================================\n");
	printf("                          Cache Block %2d                        \n", index);
	printf("|Valid\t\tTag\t\tLRU\t\t|\n");
	for (uint32_t i = 0; i < set_degree; i++) {
		printf("|%u\t\t%u\t\t%u\t\t|\n", cache[index].blocks[i].valid, cache[index].blocks[i].tag, cache[index].blocks[i].lru);
	}
	printf("=================================================================\n");
}