#include "pch.h"
#include "CppUnitTest.h"
#include "../BinaryNum/FixBinaryNum.h"
#include "../BinaryNum/BinaryNum.h"
#include "../BinaryNum/FloatBinaryNum.h"
using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			BinaryNum a(14);
			BinaryNum b(23);
			BinaryNum c;
			c = a.SumInDirectCode(b);
			Assert::IsTrue(37 == c.BinaryToInt());
		}
		TEST_METHOD(TestMethod2)
		{
			BinaryNum a(-14);
			BinaryNum b(23);
			BinaryNum c;
			c = a.SumInInverseCode(b);
			Assert::IsTrue(9 == c.BinaryToInt());
		}
		TEST_METHOD(TestMethod3)
		{
			BinaryNum a(14);
			BinaryNum b(-23);
			BinaryNum c;
			c = a.SumInInverseCode(b);
			Assert::IsTrue(-9 == c.BinaryToInt());
		}
		TEST_METHOD(TestMethod4)
		{
			BinaryNum a(-14);
			BinaryNum b(-23);
			BinaryNum c;
			c = a.SumInInverseCode(b);
			Assert::IsTrue(-37 == c.BinaryToInt());
		}
		TEST_METHOD(TestMethod5)
		{
			BinaryNum a(-14);
			BinaryNum b(23);
			BinaryNum c;
			c = a.SumInAdditionalCode(b);
			Assert::IsTrue(9 == c.BinaryToInt());
		}
		TEST_METHOD(TestMethod6)
		{
			BinaryNum a(14);
			BinaryNum b(-23);
			BinaryNum c;
			c = a.SumInAdditionalCode(b);
			Assert::IsTrue(-9 == c.BinaryToInt());
		}
		TEST_METHOD(TestMethod7)
		{
			BinaryNum a(-14);
			BinaryNum b(-23);
			BinaryNum c;
			c = a.SumInAdditionalCode(b);
			Assert::IsTrue(-37 == c.BinaryToInt());
		}
		TEST_METHOD(TestMethod8)
		{
			BinaryNum a(14);
			BinaryNum b(23);
			FixBinaryNum c;
			c = a.Divide(b);
			Assert::IsTrue(0.59375 == c.FixBinaryToFloat());
		}
		TEST_METHOD(TestMethod9)
		{
			BinaryNum a(23);
			BinaryNum b(14);
			FixBinaryNum c;
			c = a.Divide(b);
			Assert::IsTrue(1.625 == c.FixBinaryToFloat());
		}

		TEST_METHOD(TestMethod10)
		{
			BinaryNum a(23);
			BinaryNum b(14);
			BinaryNum c;
			c = a.Multiply(b);
			Assert::IsTrue(322 == c.BinaryToInt());
		}
		TEST_METHOD(TestMethod11)
		{
			FloatBinaryNum a(23.14);
			FloatBinaryNum b(14.23);
			FloatBinaryNum c;
			c = a.Sum(b);
			Assert::IsTrue(37.369998931884766 == c.BinaryToFloat());
		}
		TEST_METHOD(TestMethod12)
		{
			FloatBinaryNum a(14.23);
			FloatBinaryNum b(23.14);
			FloatBinaryNum c;
			c = a.Sum(b);
			Assert::IsTrue(37.369998931884766 == c.BinaryToFloat());
		}
	};
}
