// Assignment: ASU CSE310 Fall 2024 HW#3
// Name:PO-YI, LIN
// ASU ID:1228434521
// ASU Email Address:plin61@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

//----
//----
#include <iostream>
#include <iomanip>
#include <string>
#include "MaxHeap.h"
using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);
int index;
int main()
{
	char input1 = 'Z';
	string hotelName;
	string arrivalDate;
	int confirmNum;
	int newConfirmNum;
	int capacity;   //array capacity and index
	bool success = false;

	HotelBooking oneBooking;

	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		cin.ignore(20, '\n');	//flush the buffer whenever you enter a char, integer, double
		//if you have multiple char, integer, double entered, only flush once
		input1 = toupper(input1);

		// matches one of the cases
		switch (input1)
		{
		case 'C':	//create empty Heap with the relevant capacity
			cout << "\nPlease enter the heap capacity: ";
			cin >> capacity;
			cin.ignore(20, '\n');	//flush the buffer

			//Add your own code
			//----
			heap1 = new MaxHeap(capacity);//create a array list
			break;

		case 'D':	//delete the heap, call the destructor explicitly
			cout << "\nDelete the heap" << endl;
			//Add your own code
			//----
			if (heap1 != nullptr) {
				delete heap1;//delete the array list we create
				//re-initialize it with default capacity 4
				//----
				heap1 = new MaxHeap(4);//and create a new array list with default 4 capacity
			}
			break;

		case 'E':	//Extract the maximum node
			if (heap1 == nullptr || heap1->getSize() == 0)
				cout << "\nEmpty heap, can NOT extract max" << endl;
			else
			{
				//Add your own code
				//----
				cout << "\nBefore extract heap max operation: " << endl;
				heap1->printHeap();//print all heap
				heap1->extractHeapMax();//extract the root
				cout << "\nAfter extract heap max operation: " << endl;
				heap1->printHeap();
			}
			break;

		case 'F':	//Find a HotelBooking
			cout << "\nEnter the booking confirmation number you want to search: ";
			cin >> confirmNum;
			cin.ignore(20, '\n');	//flush the buffer

			//Add your own code
			//----
			if (heap1->isFound(confirmNum)>=0) {//is the confirm num is found
				cout << "\nBooking with confirmation number: " << confirmNum << " is found" << endl;
			}
			else {
				cout << "\nBooking with confirmation number: " << confirmNum << " is NOT found" << endl;
			}
			break;

		case 'I':	//Insert a HotelBooking
			if (heap1 == nullptr) {
				cout << "\nCreate a heap first!" << endl;
				break;
			}
			cout << "\nEnter the hotel name: ";
			getline(cin, hotelName);

			cout << "\nEnter the arrival date: ";
			getline(cin, arrivalDate);

			cout << "\nEnter the booking confirmation number: ";
			cin >> confirmNum;
			cin.ignore(20, '\n');	//flush the buffer

			//Add your own code
			//----
			success = heap1->heapInsert(hotelName,arrivalDate,confirmNum);//if success the heapInsert will return true
			if (success) {
				cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with"
					<< " confirmation No.: " << confirmNum << " is added" << endl;
			}
			else {
				cout << "\nHotel " << hotelName << ", arrival on: " << arrivalDate << ", with"
					<< " confirmation No.: " << confirmNum << " is NOT added" << endl;
			}
			break;

		case 'K':	//increase the confirmation num
			cout << "\nEnter the original confirmation number which you want to increase: ";
			cin >> confirmNum;
			cout << "\nEnter the new updated confirmation number: ";
			cin >> newConfirmNum;
			cin.ignore(20, '\n');	//flush the buffer

			//Add your own code
			//----
			

			oneBooking.confirmNum = newConfirmNum;//update the confirm num
			index = heap1->isFound(confirmNum);
			if (newConfirmNum < confirmNum) {
				cout << "\nIncrease error: new confirmation number is smaller than the current one" << endl;
				break;
			}
			else if (index < 0) {
				cout << "\nThe old confirmation number you try to increase does not exist" << endl;
				break;
			}
			else if (heap1->isFound(newConfirmNum) > 0) {
				cout << "\nThe new confirmation number you entered already exist, increase number operation failed" << endl;
				break;
			}
			cout << "\nBefore increase number operation: " << endl;
			heap1->printHeap();
			success = heap1->heapIncrease(heap1->isFound(confirmNum), oneBooking);//float the object in indix find by isFound() to the correct position 
			if (success) {
				cout << "\nBooking with old confirmation number: " <<confirmNum<<" is increased to new confirmation number: " <<newConfirmNum<< endl;
				cout << "\nAfter increase number operation:" << endl;
				heap1->printHeap();
			}
			break;

		case 'M':	//get maximum node

			//Add your own code
			//----
			if (heap1 == nullptr || heap1->getSize() == 0) {
				cout << "\nEmpty heap, can NOT get max node" << endl;
				break;
			}
			oneBooking = heap1->getHeapMax();//get the root value
			cout << "\nThe maximum heap node is:" << endl;
			cout << left;
			cout << left << setw(18) << oneBooking.hotelName
				<< setw(12) << oneBooking.arrivalDate
				<< setw(8) << oneBooking.confirmNum << endl;


			break;

		case 'P':	//Print heap contents
			if (heap1 == nullptr)
				cout << "\nEmpty heap, no elements" << endl;
			else
				//Add your own code
				//----
				heap1->printHeap();//print all heap
				break;

		case 'S':	//HeapSort
			cout << "\nHeap sort. Bookings will be sorted in increasing order of their confirmation numbers" << endl;
			//Add your own code
			//----
			heapSort(heap1);//sort the heap1 by calling function
			break;

		case 'Q':	//Quit
			//Add your own code
			//----
			if (heap1 != nullptr) {
				delete heap1;
				heap1 = nullptr;
			}
			break;

		case '?':	//Display Menu
			printMenu();
			break;

		default:
			cout << "\nUnknown action" << endl;
			break;
		} //end of switch
	} while (input1 != 'Q');
	return 0;
}

//*************************************************************************************
//Given a max heap, we want to sort it in increasing order of confirmation number, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap)
{
	//Add your own code
	//----
	int size = oneMaxHeap->getSize();//get size
	int oriSize = size;//setting the origin size due to size is going to change
	HotelBooking* bookingArr = oneMaxHeap->getHotelBookingArr();
	for (int i = oneMaxHeap->getSize()-1; i >= 1; i--) {
		swap(bookingArr[0],bookingArr[i]);//swap last to the first
		oneMaxHeap->dSize();//decrease size to hold the last element
		oneMaxHeap->heapify(0);//heapify to let root in correct position
	}
	oneMaxHeap->dSize();
	for (int i = 0; i < oriSize; i++) {
		cout << left << setw(18) << bookingArr[i].hotelName
			<< left << setw(12) << bookingArr[i].arrivalDate
			<< left << setw(8) << bookingArr[i].confirmNum << endl;
	}
}

//**The function displays the menu to the user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind a booking by confirmation number\n";
	cout << "I\t\tInsert a booking\n";
	cout << "K\t\tIncrease a booking confirmation number\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}