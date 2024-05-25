#include "pch.h"
#include "CppUnitTest.h"
#include "../lab7/AssociativeProcessor.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			AssociativeProccessor x;
			Assert::IsTrue(x.GetWord(2) == "0011100000010000");
			x.Disparity(x.GetWord(2), x.GetWord(3), 15);
			Assert::IsTrue(x.GetWord(15) == "1110011111011110");
		}

		TEST_METHOD(TestMethod2)
		{
			AssociativeProccessor x;
			x.Equivalence(x.GetWord(2), x.GetWord(3), 14);
			Assert::IsTrue(x.GetWord(14) == "0001100000100001");
		}

		TEST_METHOD(TestMethod3)
		{
			AssociativeProccessor x;
			x.ProhibSecEl(x.GetWord(2), x.GetWord(3), 13);
			Assert::IsTrue(x.GetWord(13) == "1111111111011110");
		}

		TEST_METHOD(TestMethod4)
		{
			AssociativeProccessor x;
			x.ImplFromSecToFirst(x.GetWord(2), x.GetWord(3), 12);
			Assert::IsTrue(x.GetWord(12) == "0000000000100001");
		}

		TEST_METHOD(TestMethod5)
		{
			AssociativeProccessor x;
			x.Disparity(x.GetWord(2), x.GetWord(3), 15);
			x.Equivalence(x.GetWord(2), x.GetWord(3), 14);
			x.ProhibSecEl(x.GetWord(2), x.GetWord(3), 13);
			x.ImplFromSecToFirst(x.GetWord(2), x.GetWord(3), 12);
			Assert::IsTrue(x.GetWord(0) == "1111100001110000");
			x.FindStarting("111");
			Assert::IsTrue(x.GetWord(0) == "1111100001101111");
		}

		TEST_METHOD(TestMethod6)
		{
			AssociativeProccessor x;
			x.Disparity(x.GetWord(2), x.GetWord(3), 15);
			x.Equivalence(x.GetWord(2), x.GetWord(3), 14);
			x.ProhibSecEl(x.GetWord(2), x.GetWord(3), 13);
			x.ImplFromSecToFirst(x.GetWord(2), x.GetWord(3), 12);
			x.FindStarting("111");
			x.Sort();
			Assert::IsTrue(x.GetWord(0) == "0000000000100001");
			Assert::IsTrue(x.GetWord(15) == "1111111111011101");

		}
		
	};
}
