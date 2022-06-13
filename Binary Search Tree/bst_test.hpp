#include <iostream>
#include "bst.hpp"
#include "unit_testing.hpp"

namespace bst_testing {
	using namespace std;
	using namespace bst;
	using namespace unit_testing;

	//random value generator seed (for consistantcy between tests)
	const int RAND_SEED = 1231548125718923;

	inline void bst_add(int count, BST<int>& bst) {
		for (int i = 0; i < count; i++) {
			bst.insert(rand() % 1000);
		}
	}

	inline void bst_remove(int count, BST<int>& bst) {
		for (int i = 0; i < count; i++) {
			bst.remove();
		}
	}

	inline void test_functionality() {
		UnitTest test = UnitTest(L"BST Functionality Test");

		//initalize random value seed
		srand(RAND_SEED);

		//create instance of a BST
		auto bst = BST<int>();

		test.assert<bool>(L"Removing a value from an empty BST.", [&bst]() {
			bst.remove(5);
			return true;
		}, true);

		test.assert<bool>(L"Adding duplicate values to the BST.", [&bst]() {
			bst.insert(5);
			bst.insert(5);
			return true;
		}, true);

		bst.remove_all();

		test.assert<bool>(L"Removing a node from the BST which has a right child.", [&bst]() {
			bst.insert(5);
			bst.insert(6);
			bst.remove(5);
			return true;
		}, true);

		bst.remove_all();

		test.assert<bool>(L"Removing a node from the BST which has a left child.", [&bst]() {
			bst.insert(5);
			bst.insert(6);
			bst.remove(5);
			return true;
			}, true);

		bst.remove_all();

		test.assert<bool>(L"Removing a node from the BST which has a left and right child.", [&bst]() {
			bst.insert(5);
			bst.insert(6);
			bst.insert(4);
			bst.remove(5);
			return true;
		}, true);


		bst_add(100, bst);

		test.assert<bool>(L"Print 100 items in tree view.", [&bst]() {
			bst.print();
			return true;
			}, true);

		test.assert<bool>(L"Print 100 items as an in-order list.", [&bst]() {
			bst.traverse(TraversalOrder::InOrder);
			return true;
			}, true);

		test.assert<bool>(L"Print 100 items as an pre-order list.", [&bst]() {
			bst.traverse(TraversalOrder::PreOrder);
			return true;
			}, true);

		test.assert<bool>(L"Print 100 items as an post-order list.", [&bst]() {
			bst.traverse(TraversalOrder::PostOrder);
			return true;
			}, true);

		bst.remove_all();

		//print results
		test.log_results();
	}

	inline void test_performance() {
		UnitTest test = UnitTest(L"BST Performance Test");

		//initalize random value seed
		srand(RAND_SEED);

		//create instance of a BST
		auto bst = BST<int>();

		//performance testing
		test.assert<bool>(L"Add 100 items.", [&bst]() {
			bst_add(100, bst);
			return true;
			}, true);

		test.assert<bool>(L"Remove 100 items.", [&bst]() {
			bst_remove(100, bst);
			return true;
			}, true);

		bst.remove_all();

		test.assert<bool>(L"Add 1,000 items.", [&bst]() {
			bst_add(1000, bst);
			return true;
		}, true);

		test.assert<bool>(L"Remove 1,000 items.", [&bst]() {
			bst_remove(1000, bst);
			return true;
		}, true);

		bst.remove_all();

		test.assert<bool>(L"Add 10,000 items.", [&bst]() {
			bst_add(10000, bst);
			return true;
			}, true);

		test.assert<bool>(L"Remove 10,000 items.", [&bst]() {
			bst_remove(10000, bst);
			return true;
			}, true);

		bst.remove_all();

		test.assert<bool>(L"Add 100,000 items.", [&bst]() {
			bst_add(100000, bst);
			return true;
			}, true);

		test.assert<bool>(L"Remove 100,000 items.", [&bst]() {
			bst_remove(100000, bst);
			return true;
		}, true);

		bst.remove_all();

		//print results
		test.log_results();
	}
}