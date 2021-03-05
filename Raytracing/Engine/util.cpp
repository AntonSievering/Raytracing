#include "util.h"


// The fast 32-bit random generator
inline uint32_t Lehmer32(uint32_t &nSeed)
{
	nSeed += 0xe120fc15;
	uint64_t temp;
	temp = (uint64_t)nSeed * 0x4a39b70d;
	uint32_t m1 = (temp >> 32) ^ temp;
	temp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (temp >> 32) ^ temp;
	return m2;
}

uint32_t Lehmer32_(const uint32_t &nSeed)
{
	uint64_t temp;
	temp = (uint64_t)nSeed * 0x4a39b70d;
	uint32_t m1 = (temp >> 32) ^ temp;
	temp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (temp >> 32) ^ temp;
	return m2;
}

inline float Lehmer32f(uint32_t &nSeed)
{
	return (double)Lehmer32(nSeed) / (double)UINT32_MAX;
}