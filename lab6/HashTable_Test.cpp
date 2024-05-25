#include "pch.h"
#include "CppUnitTest.h"
#include "../lab6/HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTest
{
	TEST_CLASS(HashTableTest)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			HashTable x;
			x.InsertNode("anemia", "A condition in which there is a deficiency of red cells or of hemoglobin in the blood.");
			x.InsertNode("bronchitis", "Inflammation of the mucous membrane in the bronchial tubes.");
			x.InsertNode("diabetes", "A group of diseases that result in too much sugar in the blood.");
			x.InsertNode("hypertension", "A condition in which the force of the blood against the artery walls is too high.");
			x.InsertNode("asthma", "A condition in which a person's airways become inflamed, narrow and swell, and produce extra mucus.");
			x.InsertNode("hepatitis", "Inflammation of the liver, usually caused by a viral infection.");
			x.InsertNode("stroke", "A condition where poor blood flow to the brain results in cell death.");
			x.InsertNode("osteoarthritis", "A type of arthritis that occurs when flexible tissue at the ends of bones wears down.");
			x.InsertNode("pneumonia", "Infection that inflames air sacs in one or both lungs, which may fill with fluid.");
			x.InsertNode("migraine", "A headache of varying intensity, often accompanied by nausea and sensitivity to light and sound.");
			x.InsertNode("allergy", "A condition in which the immune system reacts abnormally to a foreign substance.");
			x.InsertNode("pancreatitis", "Inflammation of the pancreas.");
			x.InsertNode("osteoporosis", "A condition in which bones become weak and brittle.");
			x.InsertNode("scoliosis", "A sideways curvature of the spine.");
			Assert::AreEqual(x.GetSize(), 14);
			Assert::IsTrue(x.SearchTable("stroke") == "A condition where poor blood flow to the brain results in cell death.");
			x.RemoveNode("stroke");
			Assert::IsTrue(x.SearchTable("stroke") == "Key not found.\n");
		}
	};
}
