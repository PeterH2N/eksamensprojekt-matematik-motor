#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H
#include <vector>
#include <map>

template<typename T, int N>
inline bool arrayContains(T(&array)[N], T key)
{
	for (int i = 0; i < N; i++)
	{
		if (key == array[i])
			return true;
	}
	return false;
}

template<typename T1, typename T2>
inline bool mapContainsKey(std::map<T1, T2> Map, T1 key)
{
	for (auto it = Map.begin(); it != Map.end(); it++)
		if (it->first == key)
			return true;
	return false;
}

#endif HELPFUNCTIONS_H