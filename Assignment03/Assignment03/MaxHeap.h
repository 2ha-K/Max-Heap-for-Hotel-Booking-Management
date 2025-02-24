#pragma once
// Assignment: ASU CSE310 HW#3 Fall 2024
// Your Name:PO-YI, LIN		
// ASU ID:1228434521
// ASU Email address:plin61@asu.edu
// Description: A head file of function of heap and hotelbooking function for assignment04
//********************************************************
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;
bool insert = false;

//Each HotelBooking has a unique confirmNum
struct HotelBooking
{
	string hotelName;
	string arrivalDate;
	int confirmNum;
};

//class MaxHeap represents a max heap that contains HotelBooking objects. The underline data structure
//is a one dimensional array of HotelBooking.
class MaxHeap
{
private:
	struct HotelBooking* bookingArr;	//an array of HotelBookings
	int capacity, size;

public:
	MaxHeap(int capacity);
	~MaxHeap();

	HotelBooking* getHotelBookingArr();
	int getSize();
	int getCapacity();
	int isFound(int oneConfirmNum);
	bool heapIncrease(int index, HotelBooking oneNewBooking);
	bool heapInsert(string hotelName, string arrivalDate, int confirmNum);
	void heapify(int index);
	HotelBooking getHeapMax();
	void extractHeapMax();
	int leftChild(int parentIndex);
	int rightChild(int parentIndex);
	int parent(int childIndex);
	void printHeap();
	void dSize();
};

//Constructor to create a heap with the specified capacity
MaxHeap::MaxHeap(int capacity)
{
	//----
	this->capacity = capacity;
	this->bookingArr = new HotelBooking[capacity];// create new dinamic array with size of capacity
	this->size = 0;//initail there is nothing in there
}

//Destructor
//Before termination, the destructor is called to free the associated memory occupied by the heap.
//and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap()
{
	//----
	int num = size;
	delete[] bookingArr;//delete the dinamic array with all heap point inside
	cout << "\nThe number of deleted bookings is: " << num << endl;
}
//heapify( ) lets the node at index "float down" so that the subtree rooted at index obeys the max-heap properties.
void MaxHeap::heapify(int index) {
	int l = leftChild(index);
	int r = rightChild(index);
	int largest = index;
	if (l < size && bookingArr[l].confirmNum > bookingArr[largest].confirmNum) {
		largest = l;
	}
	if (r < size && bookingArr[r].confirmNum > bookingArr[largest].confirmNum) {
		largest = r;
	}
	if (largest != index) {
		swap(bookingArr[index], bookingArr[largest]);
		heapify(largest);
	}

}

//Insert the relevant HotelBooking object inside the heap at the correct location
bool MaxHeap::heapInsert(string hotelName, string arrivalDate, int confirmNum)
{
	//if the booking already exist, return false
	if (isFound(confirmNum) != -1)
	{
		cout << "\nDuplicated booking. Not added" << endl;
		return false;
	}
	//----
	//----
	//In case the heap's size reaches its capacity, i.e. size equals capacity, you should dynamically re-allocate memory 
	// for the heap and double its original capacity, then insert the new HotelBooking object inside. Inside this function, 
	// it should show the following message on screen. During the procedure, the original heap elements and properties should be kept.
	HotelBooking oneNewBooking;//setting object oneNewBooking and its data
	oneNewBooking.arrivalDate = arrivalDate;
	oneNewBooking.confirmNum = confirmNum;
	oneNewBooking.hotelName = hotelName;
	if (size == capacity) {//if array is full. 
		cout << "\nReach the capacity limit, double the capacity now." << endl;
		int newCapacity = capacity * 2;
		HotelBooking* newArray = new HotelBooking[newCapacity];
		for (int i = 0; i < size;i++) {
			newArray[i] = bookingArr[i];
		}
		delete[] bookingArr;
		bookingArr = newArray;
		capacity = newCapacity;
		cout << "\nThe new capacity now is "<<capacity<< endl;
	}
	size++;
	bookingArr[size - 1].confirmNum = -40000;//set the dummy booking's confirmNum to be -40000 at index size-1 
	//call above heapIncrease( ) function to increase the dummy booking's confirmNum to be the new confirmNum 
	insert = true;
	heapIncrease(size-1,oneNewBooking);
	return true;
}
//print the all heap using for loop for each object
void MaxHeap::printHeap()
{
	//----
	//----
	if (size == 0) {
		cout << "\nEmpty heap, no elements"<< endl;
		return;
	}
	cout << "\nHeap capacity = "<<capacity<<endl;
	cout << "\nHeap size = " << size << "\n" << endl;
	for (int i = 0; i < size; i++) {
		cout << left <<setw(18) << bookingArr[i].hotelName
			<< left << setw(12) << bookingArr[i].arrivalDate
			<< left << setw(8) << bookingArr[i].confirmNum << endl;
	}	
}

//design all other functions according to the function definition and the resulting output testing cases
//----
//----
HotelBooking* MaxHeap::getHotelBookingArr() {//This is the accessor of the instance variable bookingArr.
	return bookingArr;
}
int MaxHeap::getSize() {//This is the accessor of the instance variable size.
	return size;
}
int MaxHeap::getCapacity() {//This is the accessor of the instance variable capacity.
	return capacity;
}
int MaxHeap::isFound(int oneConfirmNum) {//The function finding is there the specific confirm number in the array
	for (int i = 0; i < size; i++) {
		if (bookingArr[i].confirmNum == oneConfirmNum) {
			return i;
		}
	}
	return -1;
}
bool MaxHeap::heapIncrease(int index, HotelBooking oneNewBooking) {//The function increase the confirm number for the specific object inside the heap
	if (oneNewBooking.confirmNum < bookingArr[index].confirmNum) {
		cout << "\nIncrease confirmation number error: new confirmation number is smaller than the current number\n";
		return false;
	}
	if (insert) {
		bookingArr[index].arrivalDate = oneNewBooking.arrivalDate;
		bookingArr[index].hotelName = oneNewBooking.hotelName;
		insert = false;
	}
	bookingArr[index].confirmNum = oneNewBooking.confirmNum;
	while (index > 0 && bookingArr[parent(index)].confirmNum < bookingArr[index].confirmNum) {
		swap(bookingArr[index], bookingArr[parent(index)]);
		index = parent(index);
	}
	return true;
}
//return the root value
HotelBooking MaxHeap::getHeapMax() {
	if (size > 0) {
		return bookingArr[0];
	}
	return {};
}
//extract the root node by copy value of last one and heapify down
void MaxHeap::extractHeapMax() {
	if (size<1) {
		cout << "\nheap underflow\n";
		return;
	}
	bookingArr[0] = bookingArr[size - 1];
	size--;
	heapify(0);
}
//left child calculation
int MaxHeap::leftChild(int parentIndex) {
	return 2 * parentIndex + 1;
}
//right child calculation
int MaxHeap::rightChild(int parentIndex) {
	return 2 * parentIndex + 2;
}
//parent node calculation
int MaxHeap::parent(int childIndex) {
	return (childIndex - 1) / 2;
}
//decrease the size for sorting
void MaxHeap::dSize(){
	this->size--;
}
