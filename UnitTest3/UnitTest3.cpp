#include "pch.h"
#include "CppUnitTest.h"
#include "Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:

		TEST_METHOD(newDot_contains)
		{
			SpSm test;
			test.newDot("City1");
			test.newDot("City2");
			test.newDot("City3");
			test.newDot("City4");
			test.newDot("City5");
			test.newEdge("City1", "City2", 45);
			test.newEdge("City1", "City3", 785);
			test.newEdge("City1", "City4", 7);
			test.newEdge("City2", "City3", 68);
			test.newEdge("City2", "City5", 45);
			test.newEdge("City3", "City4", 58);
			test.newEdge("City3", "City5", 589);

			Assert::AreEqual(true, test.contains("City5"));
			Assert::AreEqual(false, test.contains("City324234"));
			try
			{
				test.newDot("City5");
			}
			catch (const std::exception & ex)
			{
				Assert::AreEqual(ex.what(), "Attempt to add a new dot with the same name");
			}
		}

		TEST_METHOD(dkstra_newEdge)
		{
			SpSm test;
			test.newDot("City1");
			test.newDot("City2");
			test.newDot("City3");
			test.newDot("City4");
			test.newDot("City5");
			test.newEdge("City1", "City2", 45);
			test.newEdge("City1", "City3", 785);
			test.newEdge("City1", "City4", 7);
			test.newEdge("City2", "City3", 68);
			test.newEdge("City2", "City5", 45);
			test.newEdge("City3", "City4", 58);
			test.newEdge("City3", "City5", 589);

			Assert::AreEqual(90.0, test.dkstra("City1", "City5"));
			try
			{
				test.dkstra("City1", "City5");
			}
			catch (const std::exception & ex)
			{
				Assert::AreEqual(ex.what(), "Couldn't find any path");
			}
			try
			{
				test.dkstra("City0", "City10");
			}
			catch (const std::exception & ex)
			{
				Assert::AreEqual(ex.what(), "Couldn't find such dot");
			}
		}
	};
}