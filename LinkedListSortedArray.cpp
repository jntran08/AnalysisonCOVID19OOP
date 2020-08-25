#include <iostream>
#include <list>
#include <cstdlib>
using namespace std;

//------------------------------EXCEPTION CLASS-------------------------------------------------
class Exception {
};
class LinkedSortedArrayException : public Exception { //subclass
	// throw LinkedSortedArrayException inside the methods 
	// A try-block is used in the main program to catch the exceptions and program execution continues.
public:
	//if exception occurs, throw message 
	const char* msgError() throw() { return "-1 -1";};

};

//-----------------------------------SORTEDARRAY------------------------------------------------
template <class DT> class SortedArray;
//template<class DT> ostream& operator<< (ostream& os, SortedArray<DT>& obj);//ostream operator 
template <class DT>
class SortedArray {
	friend ostream& operator<< (ostream& os, SortedArray<DT>& obj) {//ostream operator 
		for (int i = 0; i < obj.size; i++) { // loop through the array 
			os << obj.elements[i] << " "; // Output the objects stored in the array in a single line, objects are separated by a spaceand followed by an “endl”
		}
		return os;
	};
private:
	int capacity; // capacity, which is K
	DT* elements; // array used to store the elements, size of K
public:
	int size; // num. of elements stored
	SortedArray(); //default constructor
	SortedArray(int k);// non-empty constructor
	DT& operator [] (int index); // overloaded operator
	int setSize(int s); // accesor size
	int getSize(); //getter size 
	int setCapacity(int c); // accesor capacity
	int getCapacity(); //getter capacity
	
	DT getMaximum() { //get maximum value or the last element in the array 
		return this->elements[size - 1];
	};

	DT getMinimum() { //get minimum value or the first element in the array
		return this->elements[0];
	};
	bool FullYet(); //check if the size of array reached capacity 
	bool EmptyYet();//check if array is empty
	
	int BinarySearch(DT& item); // binary search for insertion
	int find(DT& lookFor); //find method
	void insert(DT& newElement); //insert method
	void remove(DT& oldElement); //remove method
	SortedArray<DT>& split(int i); //split method
	void join(SortedArray<DT>& P); //join method

	virtual ~SortedArray(); //destructor
};

//----------------------------------------------------------------------------------------------
//constructor
template<class DT>
SortedArray<DT>::SortedArray() { //default constructor
	size = 0; //initial size
	capacity = 0; //initial capacity 
	elements = NULL; //initial elements set to NULL

};
//----------------------------------------------------------------------------------------------
template<class DT>
SortedArray<DT>::SortedArray(int k) { //non-default constructor 
	elements = new DT[k]; // create an array of DT and return address of the first box  
	size = 0; // intial size of elements
	capacity = k; // total number of elements in array is K
};
//----------------------------------------------------------------------------------------------
template<class DT>
int SortedArray<DT>::setSize(int s) { // accesor size
	return this->size = s;
};
//----------------------------------------------------------------------------------------------
template<class DT>
int SortedArray<DT>::setCapacity(int c) { // setter capacity
	return this->capacity = c;
};
//----------------------------------------------------------------------------------------------
template<class DT>
int SortedArray<DT>::getSize() { // getter size
	return this->size;
};
//----------------------------------------------------------------------------------------------
template<class DT>
int SortedArray<DT>::getCapacity() { // getter capacity
	return this->capacity;
}
//----------------------------------------------------------------------------------------------
template<class DT>
bool SortedArray<DT>::FullYet() { //check if the size of array reached capacity 
	return (size == capacity);
};
//----------------------------------------------------------------------------------------------
template<class DT>
bool SortedArray<DT>::EmptyYet() { //check if array is empty
	return (size == 0);
};
//----------------------------------------------------------------------------------------------
template<class DT>
DT& SortedArray<DT>::operator[](int index) { //overload method returns the element (by box) at position index of the array
	return elements[index];
}
//----------------------------------------------------------------------------------------------
template<class DT>
int SortedArray<DT>::BinarySearch(DT& item) { // do binary search to locate position to insert 
	int left = 0;
	int right = size - 1;
	int loc = -1; //location to searching item 
	while (left <= right && loc == -1) { // searching toward left and location not found 
		int mid = left + (right - left) / 2;
		if (item > elements[mid]) {
			left = mid + 1; // target is larger continue right half
		}
		if (item < elements[mid]) {
			right = mid - 1; // target is smaller continue left half
		}
		else if (elements[mid] == item) {
			mid = loc; //locate it
		}
	}
	if (loc == -1) { // the item is  not in, locate the position for insertion
		loc = left;
		if (loc < right && elements[loc] < item) {
			loc++; // insert after the location
		}
	}
	return loc;

};
//----------------------------------------------------------------------------------------------
template<class DT>
int SortedArray<DT>::find(DT& lookFor) {
	int le = 0; // position starts at the left 
	int ri = size - 1; //position ends at the right
	if (elements == NULL) throw LinkedSortedArrayException();
	while (le <= ri) { //searching toward left, performs binary search to return the reference to the element at location
		int mid = le + (ri - le) / 2;
		if (elements[mid] == lookFor) {
			return mid; //found it
		}
		else if (elements[mid] < lookFor) {
			le = mid + 1; // target is larger continue right half
		}
		else if (elements[mid] > lookFor) {
			ri = mid - 1; // target is smaller continue left half
		}
	}
	return le; // return left to keep searching toward left
}
//----------------------------------------------------------------------------------------------
template<class DT>
void SortedArray<DT>::insert(DT& newElement) { //use binary search to locate insert position and iterate through elements to move to the right after insert new position 

	int pos = BinarySearch(newElement); // Binary Search to locate the insert position
	size++;
	for (int i = size; i >= (pos); i--) {
		elements[i] = elements[i - 1]; // move array to the right as we insert new position 
	}
	elements[pos] = newElement; //inserts newElement
};
//----------------------------------------------------------------------------------------------
template<class DT>
void SortedArray<DT>::remove(DT& oldElement) {
	int pos = find(oldElement);// locate position to remove elements
	if (elements[pos] != oldElement) throw LinkedSortedArrayException(); // throws exception for non-exisiting elements
	for (int i = pos; i < size; i++) {
		elements[i] = elements[i + 1]; // removes the element by shifting the elements to the left by
	};
	size--;
};
//----------------------------------------------------------------------------------------------
template<class DT>
SortedArray<DT>& SortedArray<DT>::split(int i) { // create new object array, copy elements from position i through the last element of the array, remove elements from position i to last array and adjust size
	SortedArray<DT>* newobjarr = new SortedArray<DT>(capacity); // create new object array
	
	for (int j = 0; j < this->size; j++) {
		(*newobjarr)[j] = this->elements[i]; // copy elements from position index through the last element of the array
		newobjarr->size= newobjarr->size+1; //adjust the size of new object array 
		remove(elements[i]); //remove elements from index to last elements removed 
	}

	return (*newobjarr); //returns a SortedArray 
};
//----------------------------------------------------------------------------------------------
template<class DT>
void SortedArray<DT>::join(SortedArray<DT>& P) { //join method running through the loop of array and copies the elements from array P to current array and ensure the elements are in sorted array.

	for (int j = 0; j < P.size; j++) { // looping through array 
		this->elements[j] = P.elements[j]; //Copies the elements from array P to this array making sure that the elements are in sorted array.
	}
	//delete[] P;  //destroyed after the copy

};
//----------------------------------------------------------------------------------------------
template<class DT>
SortedArray<DT>::~SortedArray() {//destructor, clear size, capacity and all elements in array
	size = 0;
	capacity = 0;
	if (elements != NULL)
		delete[] elements;
};

//-----------------------------------LINKEDSORTEDARRAYS-----------------------------------------
template <class DT>
class LinkedSortedArrays; //call front LinkedSortedArrays
/*template<class DT>
ostream& operator<< (ostream& os, LinkedSortedArrays<DT>& SA);//ostream operator */
//----------------------------------------------------------------------------------------------
template <class DT>
class LinkedSortedArrays
{
	//friend ostream& operator << (ostream& os, LinkedSortedArrays<DT>& SA);//ostream operator 
private:
	list<SortedArray<DT> > nameIT;//using the list data structure
	int ArraySizeFactor; //The maximum size of the array in the SortedArray
	int node; //total number of nodes
	 
public:
	LinkedSortedArrays(); //default constructor
	LinkedSortedArrays(int sizeFac); //non-default/ size-only constructor
	LinkedSortedArrays(const LinkedSortedArrays<DT>& other); //constructor to another link of LinkedList 

	void display(); //display function
	DT& operator[](int idx) { //overload operator returns the element (by box) at position index of the array
		return nameIT[idx]; 
	};

	void find(DT& key); //find 
	int searchNode(DT& searchTerm); //search for correct node to insert 
	int searchInsert(DT& newEl); //search for location in proper node to insert
	void insert(DT& newOne); // insert
	void remove(DT& X); //remove 

	~LinkedSortedArrays(); //destructor 
};
//----------------------------------------------------------------------------------------------
template <class DT>
LinkedSortedArrays<DT>::LinkedSortedArrays() {//default constructors
	ArraySizeFactor = 0; //initialie ArraySizeFactor
	node = 0; //intialize total number of node 
	nameIT = NULL; //intialize linked list nameIT
};
//----------------------------------------------------------------------------------------------
template <class DT>
LinkedSortedArrays<DT>::LinkedSortedArrays(int sizeFac) {//size-only constructor
	ArraySizeFactor = sizeFac; //set ArraySizeFactor as the given capacity parameter
	node = 1; // intial next node is 1 
	SortedArray<DT>* InsertArray = new SortedArray<DT>(ArraySizeFactor); // create an sorted array of DT and return address of the first box
	nameIT.push_back((*InsertArray)); //push the array to the linked list 
};
//----------------------------------------------------------------------------------------------
template <class DT>
LinkedSortedArrays<DT>::LinkedSortedArrays(const LinkedSortedArrays<DT>& other) { //linked list to other nodes
	ArraySizeFactor = other.ArraySizeFactor; 
	node = other.node;
	nameIT = other.nameIT;
};
//----------------------------------------------------------------------------------------------
template <class DT>
ostream& operator << (ostream& os, LinkedSortedArrays<DT>& SA) { //ostream operator to output
	SA.display(); //display sorted array 
	return os;
}
//----------------------------------------------------------------------------------------------
template <class DT>
void LinkedSortedArrays<DT>::display() { //display method, start iterate over the linked list structure to display the node 
	typename list <SortedArray<DT> >::iterator itr;
	for (itr = nameIT.begin(); itr != nameIT.end(); ++itr) {
		cout << *itr;
	};
	cout << endl;
};
//----------------------------------------------------------------------------------------------
template<class DT>
LinkedSortedArrays<DT>::~LinkedSortedArrays() { //destructor, clear all memory of ArraySizeFactor, node and linked list nameIT
	ArraySizeFactor = 0; 
	node = 0;
	if (nameIT != NULL)
		nameIT.clear();
};
//----------------------------------------------------------------------------------------------
template <class DT>
void LinkedSortedArrays<DT>::find(DT& key) { //start iterate over the linked list structure until either the element is found or all the nodes of the linked list has been searched
	int getIt = 0; //location where key locate
	int nde = 0; //node
	DT parseval = 0; //DT value to parse
	typename list<SortedArray<DT> >::iterator ar; //iterator node array 
	for (ar = nameIT.begin(); ar != nameIT.end(); ar++) { //iterate unil either the element is found or all the nodes of Linked List searched
		getIt = (*ar).find(key); //find the location 
		parseval = (*ar)[getIt]; //parse value in the node array that match the key 
		if ((*ar)[getIt] == key) { //if the key/elements is found in the list structure 
			cout << "F(" << key << "): " << nde << " " << getIt << endl;
			break;
		}
		nde++;
	}
	if (parseval != key) throw LinkedSortedArrayException(); // if the key is not in the linkedlist, exception is thrown 
};
//----------------------------------------------------------------------------------------------
template <class DT>
int LinkedSortedArrays<DT>::searchInsert(DT& newEl) { //if search proper position associate with node iterator to insert, alternative search in more than 2 nodes
	int getIt = 0; //intialize position getIT to insert 
	for (SortedArray<DT>& arIT : nameIT) {
		DT min = arIT.getMinimum(); //minimum value of array 
		DT max = arIT.getMaximum(); // maximum value of array
		if ((newEl > max) || (newEl < min)) { // if out of bound in the array node
			continue; // move to the next node of the linked list and continues process
		}
		getIt = arIT.find(newEl); //fuse find to locate the new element in the linked list 
	}
	return getIt;
}
//----------------------------------------------------------------------------------------------
template<class DT>
int LinkedSortedArrays<DT>::searchNode(DT& searchTerm) { // search node to insert 
	int nde = 0;
	typename list <SortedArray<DT> >::iterator beginA; // begin iterator array node 
	typename list <SortedArray<DT> >::iterator currA; // first iterator array node
	typename list <SortedArray<DT> >::iterator nextA; // next iterator array node 
	beginA = nameIT.begin(); //begin iterator node of linkedlist
	DT minBegin = (*beginA).getMinimum(); //minimum value of begin iterator node 
	for (currA = nameIT.begin(); currA != nameIT.end(); currA++) {
		DT maxA = (*currA).getMaximum(); //maximum value of current node array 
		DT minA = (*currA).getMinimum(); //minimum value of current node array  
		if (searchTerm < minBegin) { //if the search term is less than the min value of first node 
			return nde=1; // update to 1 node and exist the loop 
		}
		else if(searchTerm<minA|| searchTerm >maxA) { //if search term less than min value of first node 
			nextA = next(currA); //next node of iterator
			if (nextA != nameIT.end()) {
				if (searchTerm < (*nextA).getMinimum()) { //search term out of bound of minimum next node and maximum of current node 
					if (searchTerm > (*currA).getMaximum()) {
						nde+=1; //new node created and exist the loop
						break;
					}
				}
			}
			nde+=1; //update node
			continue; //skip current node and jump to next iteration node
		}
		nde+=1;//otherwise, update node
		break;//exist the loop 
	}
	return nde;
};
//----------------------------------------------------------------------------------------------
template <class DT>
void LinkedSortedArrays<DT>::insert(DT& newOne) {
	int nde = 0; //node
	typename list <SortedArray<DT> >::iterator firstA2;//set up the iterator node array A2
	nde = searchNode(newOne) - 1;//search for proper node 
	firstA2 = nameIT.begin();
	firstA2=next(firstA2, (nde)); //move the iterator to the proper node 

	int pos = (*firstA2).find(newOne); //find locaiton in SortedArray where newOne is located
	if ((*firstA2)[pos] == newOne) throw LinkedSortedArrayException(); //the element is already in the data structure (thrown an exception)

															//find a SortedArray (in the linked list) where the element has to be inserted and has space
	if ((*firstA2).getSize() < (*firstA2).getCapacity()) { //size of node array is smaller than its capacity 
		(*firstA2).insert(newOne);
		cout << "I(" << newOne << "): " << nde << " " << pos << endl;
	}
	else if ((*firstA2).FullYet()) { //find a SortedArray where the element has to be inserted, but it does not have space.
		SortedArray<DT>* newarrnode = &(*firstA2).split(ArraySizeFactor / 2); //create new temporary object node 
		(*newarrnode).setSize((ArraySizeFactor / 2)); //split it by in half  of array size factor
		DT max = (*firstA2).getMaximum(); // maximum value of current node array A2
		if (newOne <= max) { //if new element is smaller or equal the maximum value of current node
			(*firstA2).insert(newOne); //then insert to current node
		}
		else {
			(*newarrnode).insert(newOne); //insert to new node
		}
		firstA2 = next(firstA2);  //after split, advance iterator by 1 position 
		nameIT.insert(firstA2, *newarrnode); //insert first iterator before new node to extend the linked list nameIT
		node++; //total number of node increase by 1 
		cout << "I(" << newOne << "): " << searchNode(newOne)-1 << " " << searchInsert(newOne) << endl; 
	}

	//look for possible merging 
	typename list<SortedArray<DT> >::iterator firstit; //first iterator node
	typename list<SortedArray<DT> >::iterator secondit; //second iterator node 

	firstit = nameIT.begin();
	secondit = nameIT.begin();
	for (firstit = nameIT.begin(); firstit != nameIT.end(); firstit++) { //loop through the first iterator 
		secondit = nameIT.begin();
		if (node >= 2) { //total number of node found 
			advance(secondit, 1); //second iterator moves to next node 
			int num1 = (*firstit).getSize(); //get numbers of elements 1
			int num2 = (*secondit).getSize(); //get numbers of elements 2
			if (num1 + num1 < ArraySizeFactor) { //summation of elements less that capacity 
				(*firstit).join((*secondit)); //first iterator joins second iterator, join forward  
				nameIT.erase(secondit); //erase second iterator
				node--; //deduct total number of node 
			}
		}
	}

};
//----------------------------------------------------------------------------------------------
template <class DT>
void LinkedSortedArrays<DT>::remove(DT& X) { //iterate through LinkedList to remove the value 
	int nde = 0; //node
	int pos = -1; //initial position
	typename list<SortedArray<DT> >::iterator A; //iterator node array 
	for (A = nameIT.begin(); A != nameIT.end(); A++) {
		int pos = (*A).find(X); //find position of value X
		if ((*A)[pos] != X) throw LinkedSortedArrayException(); //throw exception if the x is not in the array 
		if (pos != -1 && (*A)[pos] == X) { // if the value X is not exist in the LinkedSortedArrays
			(*A).remove(X); //remove value X
			cout << "R(" << X << "): " << nde << " " << pos << endl;
			break;
		}
		nde++; //update node 
	}
};
//--------------------------------------------------------------------------------------------
//---------------------------MAIN PROGRAM------------------------------------------------------
//----------------------------------------------------------------------------------------------
int main() {
	int cap;  //capacity
	char command;
	int value;
	cin >> cap; //read in capacity
	SortedArray<int>* SA = new SortedArray<int>(cap); //create a Sorted Array
	LinkedSortedArrays<int>* LSA = new LinkedSortedArrays<int>(cap); // create a Linked Sorted Arrays
	while (!cin.eof()) {
		cin >> command; //read in command
		if (cin.eof()) break; // make sure it reached end-of-file and exist

		switch (command) { //switch in different commands
		
		case 'I': { 
			try {// A try-block is used to catch the exceptions and program execution continues.
				cin >> value; //read in value 
				(*LSA).insert(value); //insert
			}
			catch (LinkedSortedArrayException& except) {
				cout << except.msgError() << endl; 
			}
			break;
		}
		case 'R': {
			try {// A try-block is used to catch the exceptions and program execution continues.
				cin >> value; //read in value 
				(*LSA).remove(value); //remove
			}
			catch (LinkedSortedArrayException& except) {
				cout << except.msgError() << endl;
			};
			break;
		}
		case 'F': { 
			try {// A try-block is used to catch the exceptions and program execution continues.
				cin >> value; //read in value 
				(*LSA).find(value); //find
			}
			catch (LinkedSortedArrayException& except) {
				cout << except.msgError() << endl;
			};
			break;
		}
		case 'O': { //display 
			cout << *LSA;
			break;
		}
		} //end switch

	} //end while

 	return 0;
}

