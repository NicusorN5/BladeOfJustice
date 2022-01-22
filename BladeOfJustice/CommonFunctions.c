#include "CommonFunctions.h"

int Clamp(int a, int t, int b)
{
	if(t >= b) return b;
	if(t <= a) return a;
	else return t;
}