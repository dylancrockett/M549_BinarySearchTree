#include <iostream>
#include <io.h>
#include <fcntl.h>
#include "bst_test.hpp"

using namespace bst_testing;

//menu functions
void main_menu();
void bst_playground();
void testing_menu();

int main()
{
	//enable unicode in wcout
	_setmode(_fileno(stdout), _O_U16TEXT);

	//start menus
	main_menu();
}

//main menu
void main_menu() {
main_menu:

	wcout << "<> Main Menu <>\n\n";
	wcout << "[1] BST Playground\n";
	wcout << "[2] Testing Menu\n";
	wcout << "[3] Exit\n\n";
	wcout << "Please enter your selection: ";

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		system("cls");
		bst_playground();
		goto main_menu;
	case 2:
		system("cls");
		testing_menu();
		goto main_menu;
	case 3:
		return;
	default:
		system("cls");
		wcout << "INVALID OPTION: Please select one of the valid options below (1-3).\n\n";
		goto main_menu;
	}
}

//bst playground menu
void bst_playground() {
	//create BST
	auto bst = bst::BST<int>();

	//node var
	bst::BST<int>::Node* node = nullptr;

	//reset random
	srand(time(0));

	//add some random values
	for (int i = 0; i < 5; i++) bst.insert(rand() % 100 + 1);

bst_playground:
	wcout << "BST: \n";
	bst.print();
	wcout << "\n\n";

	wcout << "<> Modify BST <>\n\n";
	wcout << "[1] Add\n";
	wcout << "[2] Remove\n";
	wcout << "[3] Find\n";
	wcout << "[4] Find Min\n";
	wcout << "[5] Find Max\n";
	wcout << "[6] Exit\n\n";
	wcout << "Please enter your selection: ";

	int choice;
	cin >> choice;

	switch (choice) {
	case 1:
		//get new value
		int newVal;
		wcout << "\n\nPlease enter the value to add: ";
		cin >> newVal;

		//add value to bst
		bst.insert(newVal);
		system("cls");

		goto bst_playground;
	case 2:
		//get value to remove
		int valToRemove;
		wcout << "\n\nPlease enter the value to be removed: ";
		wcin >> valToRemove;

		//remove specified value if it exists
		bst.remove(valToRemove);
		system("pause");
		system("cls");
		goto bst_playground;
	case 3:
		// get value to find
		int valToFind;
		wcout << "\n\nPlease enter the value to be found: ";
		cin >> valToFind;

		//find specified value if it exists
		node = bst.find(valToFind);

		//if the node was found show it's pointer
		if (node != nullptr) wcout << "\nNode Found! Location: " << node << endl;
		else wcout << "No node could be found with the specified value." << endl;
		system("cls");
		goto bst_playground;
	case 4:
		// find node with min value
		node = bst.minimum();

		if (node != nullptr) wcout << "The minimum value in the tree is: " << node->value << endl;
		else wcout << "The tree is empty." << endl;
		system("pause");
		system("cls");
		goto bst_playground;
	case 5:
		// find node with max value
		node = bst.maximum();

		if (node != nullptr) wcout << "The maximum value in the tree is: " << node->value << endl;
		else wcout << "The tree is empty." << endl;
		system("pause");
		system("cls");
		goto bst_playground;
	case 6:
		system("cls");
		return;
	default:
		system("cls");
		wcout << "INVALID OPTION: Please select one of the valid options below (1-3).\n\n";
		goto bst_playground;
	}
}

//testing menu
void testing_menu() {

testing_menu:
	wcout << "<> Testing Menu <>\n\n";
	wcout << "[1] BST Functionality Test\n";
	wcout << "[2] BST Performance Test\n";
	wcout << "[3] Exit\n\n";
	wcout << "Please enter which test you would like to run: ";

	int choice;
	cin >> choice;

	system("cls");

	switch (choice) {
	case 1:
		bst_testing::test_functionality();
		system("pause");
		system("cls");
		goto testing_menu;
	case 2:
		bst_testing::test_performance();
		system("pause");
		system("cls");
		goto testing_menu;
	case 3:
		return;
	default:
		wcout << "INVALID OPTION: Please select one of the valid options below (1-3).\n\n";
		goto testing_menu;
	}
}