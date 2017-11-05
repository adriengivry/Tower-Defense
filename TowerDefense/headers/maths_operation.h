#ifndef _MATHS_OPERATION_
#define _MATHS_OPERATION_

inline int random_between(const int min, const int max)
{
	return static_cast<int>(min + rand() % static_cast<int>(max - min + 1));
}


#endif // !_MATHS_OPERATION_