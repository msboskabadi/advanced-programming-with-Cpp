#include "stdafx.h"

float mean(float* data, int N)
{
	float m = 0;
	for (size_t i = 0; i < N; i++)
	{
		m += data[i];
	}

	if (N)
		return m / N;
	
	return 0;
}