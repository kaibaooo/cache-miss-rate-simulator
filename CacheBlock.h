#ifndef CACHE_BLOCK_H
#define CACHE_BLOCK_H
class CacheBlock
{
public:
	CacheBlock();
	~CacheBlock();
	unsigned int tag;
	unsigned int lru;
	bool valid;
};

#endif