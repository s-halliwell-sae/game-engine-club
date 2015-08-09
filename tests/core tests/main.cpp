/*
	basic test of gec-core
*/

#include "jem_STL_Alloc.h"
#include "LinearAllocator.h"

#include <vector>

class TestClass1{protected: int a; float b; char c[20]; };
class TestClass2{ int a[2]; float b; char c[10]; TestClass1 tc1; };
class TestClass3 :public TestClass1{ public:TestClass3(int A, float B){ a = A; b = B; } private: int d; };

void main()
{
	std::vector<int> intreg;
	std::vector<int, GEC::JemAllocator<int>> intjem;
	std::vector<int, GEC::JemAllocatorPOD<int>> intjemPOD;

	intjem.push_back(1);

	intjemPOD.push_back(2);



	GEC::LinearAllocator<GEC::JemAllocator<uint8_t>> la(sizeof(TestClass2) * 10);

	auto tc3p = la.New<TestClass3>(1, 3.14f);

	TestClass1* tc1 = nullptr;

	do
	{
		tc1 = la.New<TestClass1>();
	} while (tc1 != nullptr);

	la.Clear();

}