#include "pch.h"
#include "CppUnitTest.h"
#include "../lab2/TruthTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			TruthTable a("(a | b) & !c");
			a.Calculate();
			Assert::IsTrue(a.IndexForm() == 42);
		}

		TEST_METHOD(TestMethod2)
		{
			TruthTable a("a ~ !a");
			a.Calculate();
			Assert::IsTrue(a.NumericForm() == "(0,1)&\n()|");
		}

		TEST_METHOD(TestMethod3)
		{
			TruthTable a("a ~ !b -> (d & c)");
			a.Calculate();
			Assert::IsTrue(a.SDNF() == "(-a&b&d&c)|(a&-b&-d&-c)|(a&-b&-d&c)|(a&-b&d&-c)|(a&-b&d&c)|(a&b&-d&-c)|(a&b&-d&c)|(a&b&d&-c)");
			Assert::IsTrue(a.SKNF() == "(a|b|d|c)&(a|b|d|-c)&(a|b|-d|c)&(a|b|-d|-c)&(a|-b|d|c)&(a|-b|d|-c)&(a|-b|-d|c)&(-a|-b|-d|-c)");
		}
	};
}
