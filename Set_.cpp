#include "Set_.h"

Set_::Set_(int sd){
	//cout << "Constructor is called" << endl;
	for (int i = 0; i < sd; i++) {
		blocks.push_back(CacheBlock());
	}
	
}







Set_::~Set_(){

}
