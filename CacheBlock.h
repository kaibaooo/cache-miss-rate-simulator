#ifndef CACHE_BLOCK_H
#define CACHE_BLOCK_H
class CacheBlock
{
public:
	CacheBlock();
	void setTag(unsigned int);
	void setValid(bool);
	~CacheBlock();
	unsigned int tag;
	unsigned int lru;
	bool valid;
};

#endif