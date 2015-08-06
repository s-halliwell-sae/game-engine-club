/*
	basic test of gec-core
*/

#include "jem_STL_Alloc.h"
#include "LinearAllocator.h"

#include <vector>

class TestClass1{ int a; float b; char c[20]; };
class TestClass2{ int a[2]; float b; char c[10]; TestClass1 tc1; };

void main()
{
	std::vector<int> intreg;
	std::vector<int, GEC::JemAllocator<int>> intjem;
	std::vector<int, GEC::JemAllocatorPOD<int>> intjemPOD;

	intjem.push_back(1);

	intjemPOD.push_back(2);



	GEC::LinearAllocator la(sizeof(TestClass2) * 10);

	TestClass1* tc1 = nullptr;

	do
	{
		TestClass1* tc1 = new(la.RequestSpace(sizeof(TestClass1))) TestClass1();
	} while (tc1 != nullptr);

	la.Clear();

}