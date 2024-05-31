#include "pch.h"
#include "CppUnitTest.h"
#include "../lab3/TabularMethod.h"
#include "../lab3/KarnoMethod.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			string example = "(-a|-b|c) & (-a|b|-c) & (-a|b|c) & (a|b|-c)";
			CalculationMethod a(example);
			a.Show();
			Assert::IsTrue(a.GetMinimize() == "(!a|c)&(b|!c)");
		}

		TEST_METHOD(TestMethod2)
		{
			string example = "(-a|-b|c) & (-a|b|-c) & (-a|b|c) & (a|b|-c)";
			TabularMethod a(example);
			Assert::IsTrue(a.GetMinimize() == "(!a|c)&(b|!c)");
		}

		TEST_METHOD(TestMethod3)
		{
			string example = "(!a|!b|c) & (!a|b|!c) & (!a|b|c) & (a|b|!c)";
			KarnoMethod a(example);
			Assert::IsTrue(a.GetMinimizeKNF() == "(b|!c)&(!a|c)");
		}

		TEST_METHOD(TestMethod4)
		{
			string example = "(!a|!b|c|d) & (!a|b|!c|d) & (!a|b|c|d) & (a|b|!c|d)";
			CalculationMethod a(example);
			TabularMethod b(example);
			KarnoMethod c(example);
			Assert::IsTrue(a.GetMinimize() == "(!a|c|d)&(b|!c|d)");
			Assert::IsTrue(b.GetMinimize() == "(!a|c|d)&(b|!c|d)");
			Assert::IsTrue(c.GetMinimizeKNF() == "(b|!c|d)&(!a|c|d)");
		}

		TEST_METHOD(TestMethod5)
		{
			string example = "(!a|!b|c|d) & (!a|b|!c|d) & (!a|b|c|d) & (a|b|!c|d)";
			KarnoMethod a(example);

			Assert::IsTrue(a.GetMinimizeDNF() == "(d)|(!a&!c)|(b&c)");
		}

		TEST_METHOD(TestMethod6)
		{
			string example = "(!a|!b) & (!a|b)";
			CalculationMethod a(example);
			TabularMethod b(example);
			KarnoMethod c(example);
			Assert::IsTrue(a.GetMinimize() == "(!a)");
			Assert::IsTrue(b.GetMinimize() == "(!a)");
			Assert::IsTrue(c.GetMinimizeKNF() == "(!a)");
		}

		
	};
}
