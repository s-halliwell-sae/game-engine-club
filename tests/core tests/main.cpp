/*
	basic test of gec-core
*/

#include "jem_STL_Alloc.h"

#include <vector>

void main()
{
	std::vector<int> intreg;
	std::vector<int, GEC::JemAllocator<int>> intjem;
	std::vector<int, GEC::JemAllocatorPOD<int>> intjemPOD;

	intjem.push_back(1);

	intjemPOD.push_back(2);


}