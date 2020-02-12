#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define Q31_1_BASE (1LL<<30)
#define Q31_1_MAX  ((1LL<<30)-1)
#define Q31_1_MIN  (-1LL<<30)

int32_t saturate64(int64_t num)
{
	if (num < (int64_t)Q31_1_MIN)
		return Q31_1_MIN;

	else if (num > (int64_t)Q31_1_MAX)
		return Q31_1_MAX;

	return num;
}

int32_t add_32(int32_t num_1, int32_t num_2)
{
	return saturate64((int64_t)num_1 + num_2);
}

int32_t sub_32(int32_t num_1, int32_t num_2)
{
	return saturate64((int64_t)num_1 - num_2);
}

int32_t mult_32(int32_t num_1, int32_t num_2)
{
	int32_t res;
	if (num_1 == Q31_1_MIN && num_2 == Q31_1_MIN)
	{
		return (int64_t)Q31_1_MAX;
	}
	res = saturate64(((int64_t)num_1 * (int64_t)num_2) >> 30);
	return res;
}

int32_t flt2fixd(float num)
{
	if (num >= 1)
		return Q31_1_MAX;
	else if (num < -1)
		return Q31_1_MIN;

	int32_t res = num * (float)Q31_1_BASE;
	return res;
}

float fixd2flt(int32_t num)
{
	float res = (float)(num) / ((float)Q31_1_BASE);
	return res;
}

void main() {

	float one;
	int32_t int_one;
	printf("Enter number\n");
	scanf_s("%f", &one);
	int_one = flt2fixd(one);
	printf("%x \n", int_one);

	float two;
	int32_t int_two;
	printf("One more\n");
	scanf_s("%f", &two);
	int_two = flt2fixd(two);
	printf("%x \n", int_two);

	int64_t reslt;
	reslt = mult_32(int_one, int_two);
	printf("Fixed result %d \n", reslt);
	float flo_reslt;
	flo_reslt = fixd2flt(reslt);
	printf("Float result %f \n", flo_reslt);

	system("pause");
}
