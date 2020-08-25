#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for ceil and floor functions in adaptive sort
#include<ctime> // used for measuring time

using namespace std;

class sortElements {
protected:
	int numElements; //Number of elements of the array
	int* elements; //dynamic array with the elements of type int
public:
	sortElements(); // default constructor
	sortElements(int n); // non-default constructor
	~sortElements(); // destructor
	void generateRandom(int seed, int lower, int upper); // will generate numElement set of elements randomly with the seed and range from lower to upper
	void displayElements(int* arr); // display the given set
	int* getElementsArray(); // return the entire array of elements
	int getnumElements(); // return the number of elements
	// Necessary methods for each of the sorting algorithm
	int gsize(int* arr); //return size
	bool sortYet(int* arr); //check if Sorted
	void swap(int* xs, int* ys); //swap method
	//int partition(int* arr, int lo, int hi); //partition method
	int partition(int lo, int hi); //partition method
	int* mergeArr(int* arr1, int* arr2); //merge array 
	//Bubble and Quick sort
	void bubbleSort(int* arr); //Bubble Sort
	void quickSort(int lo, int hi); //quick sort
	// Extra credit – Shell and Adaptive sort methods
	void shellSort1(); //Shell Sort
	int* adaptiveSort(int* arr); //Adaptive Sort
};
//------------------------------------------------------------------------------------------
sortElements::sortElements() { // default constructor
	numElements = 0;
	elements = NULL;
}
//------------------------------------------------------------------------------------------
sortElements::sortElements(int n) { // non-default constructor
	numElements = n;
	elements = new int[n]; //change later
}
//------------------------------------------------------------------------------------------
sortElements::~sortElements() { //destructor
	numElements = 0;
	if (elements != NULL)
		delete[] elements;
}
//------------------------------------------------------------------------------------------
//build elements array 
void sortElements::generateRandom(int seed, int lower, int upper) { //generate random elemens 
	srand(seed);// set seet to random generator
	int range=upper-lower+1; //keep value within range 
	for (int i = 0; i < numElements; i++) { //loop through the array 
		elements[i] = rand() % range + lower; //random generate 
	}
}
//------------------------------------------------------------------------------------------
void sortElements::displayElements(int* arr) { //display the given set
	for (int i = 0; i < numElements; i++) { //loop through the array and display each element in the array 
		cout << arr[i] << " ";
	}
	cout << endl;
}
//------------------------------------------------------------------------------------------
int* sortElements::getElementsArray() { //return entire array of elements
	return elements;
}
//------------------------------------------------------------------------------------------
int sortElements::getnumElements() { //return the number of elements in array
	return numElements;
}
//------------------------------------------------------------------------------------------
void sortElements::swap(int* xs, int* ys) { // swap method to change position of xs and ys 
	int temp = *xs; // assign xs to temporaty number to store its memory 
	*xs = *ys; //assign ys to xs, now xs has address and memory of ys
	*ys = temp; //now ys is assigned to temp, which is initially stored address and memory of xs 
}
//------------------------------------------------------------------------------------------
void sortElements::bubbleSort(int* arr) { //bubble sort method 
	int i = 0; 
	while (i < numElements - 1) { // while index is within the array numbers
		for (int j = 0; j < numElements - i - 1; j++) { // run for loop of the remaining array from index i
			if (arr[j] > arr[j + 1]) { // if array at left more than right 
				swap(&arr[j], &arr[j + 1]); // swap position between the array 
			}
		}
		i++;
	}
}
//------------------------------------------------------------------------------------------
int sortElements::partition(int lo, int hi) { //partion method 
	int pivot = elements[hi]; //pivot value
	int i = (lo - 1); // assign index to smaller element position
	for (int j = lo; j <= hi - 1; j++) {
		if (elements[j] < pivot) { // if current elements smaller than pivot
			i++; // increment up index
			swap(&elements[i], &elements[j]); // then swap between smaller and current value, smaller elements are in the left of pivot
		}
	}
	swap(&elements[i + 1], &elements[hi]); // the greater elements is swaped to the right side of the pivot 
	return i + 1;
}
//------------------------------------------------------------------------------------------
void sortElements::quickSort(int lo, int hi) {
	if (lo < hi) { // while lower value is smaller than upper vlaue 
		int pval = partition(lo, hi); //obtain pivot value
		quickSort(lo, pval - 1); // sort elements before partition by recursive
		quickSort(pval + 1, hi); // sort elements after partition by recursive
	}
}
//------------------------------------------------------------------------------------------
void sortElements::shellSort1() { //shell sort method 
	for (int disc = int(numElements / 2); disc > 0; disc = int(disc / 2)) { // loop starts with large distance (gap) between element then reduce its by half
		for (int i = disc; i < numElements; i++) { //loop through within distance to numElements
			int temp = elements[i]; //save elements[i] in temp to hold at position i 
			int j;
			j = i - disc; // shift earlier sorted elements
			while ((j >= 0) && (elements[j] > temp)) { // while element is sorted
				elements[j + disc] = elements[j]; // shift the earlier sorted elements up while it meets condition of whke loop
				j = j - disc; // location for elements[i] is found 
			}
			elements[j + disc] = temp; // put temp in its corresponding location 
		} //end for loop for insertion
	}//end for loop for reducing increment
}
//------------------------------------------------------------------------------------------
int* sortElements::mergeArr(int* arr1, int* arr2) { //merging between array
	int i, j; // index for 2 corresponding array
	int* arr = new int[gsize(arr1) + gsize(arr2)]; //create new array of size of array 1 and array 2
	for (i = 0; i < gsize(arr1); i++) { //loop through array 1
		arr[i] = arr1[i]; //copy array 1 to the first arr1 size
	}
	for (j = 0; j < gsize(arr2); j++) { //loop through array 2
		arr[j + gsize(arr1)] = arr2[j]; //copy array 2 to the next size
	}
	return arr;
}
//------------------------------------------------------------------------------------------
int sortElements::gsize(int* array) { //return size of the arrray dynamically
	int _size;
	return _size = (array + 1) - array;
}
//------------------------------------------------------------------------------------------
bool sortElements::sortYet(int* arr) {//check if the array is sorted 
	if (gsize(arr) < 2) return true; //if its dynamic size is less than 2 the array is sorted
	int* prev = &(arr[0]); // assign previous element at position 0 of the array
	for (int i = 1; i < gsize(arr); i++) //run loop throughout the array starting from position 1
	if (*prev > arr[i]) return false; //if previous element is larger, the array is not sorted 
	return true;
}
//------------------------------------------------------------------------------------------
int* sortElements::adaptiveSort(int* arr) { //adaptive sort returns sorted array
	int len = gsize(arr); //get dynamic size of the array 
	if (len < 2) return arr; //exist when size is less than two
	//split positions and sizes
	int odds, evens;
	evens = int(ceil(gsize(arr) / 2.0)); // even size
	odds = int(floor(gsize(arr) / 2.0)); // odd size
	//generate new array with odd and even sizes
	int* evenarr = new int[evens];
	int* oddarr = new int[odds];

	int limit = len/ 2; //limit of subarray should not be more than half of the array size
	for (int i = 0, i2 = 0; i < limit; i++, i2++) { //run through loop if both array and subarray
		evenarr[i] = arr[i2]; //the subarray having even size get elements at even positions
		i2++; //increment index i2 of subarray
		oddarr[i] = arr[i2]; //the subarray having odd size get elements at odd positions
	}
	if (gsize(arr) % 2 > 0) { // if the size of array is not even 
		evenarr[gsize(evenarr) - 1] = arr[gsize(arr) - 1]; //the element before the last element of even subarray will get the element before last element of array (with even position)
	}
	//recursive
	if (!sortYet(evenarr)) adaptiveSort(evenarr); //if the even subarray is not sorted then the adaptive sort is conducted by recursive 
	if (!sortYet(oddarr)) adaptiveSort(oddarr); //if the odd subarray is not sorted then the adaptive sort is conducted by recursive 
	arr = mergeArr(evenarr, oddarr); //merge both even and odd array to the final sorted array
	return arr; //return sorted array 
}
//------------------------------------------------------------------------------------------
//----------------------------MAINPROGRAM---------------------------------------------------
//------------------------------------------------------------------------------------------
int main() {
	
	int n; //numbers of elements
	cin >> n;
	//n = 5000;
	//n=10000;
	//n=50000;
	//n=100000;
	cout << "Number of elements: "<< n << endl;
	sortElements* ar = new sortElements(n);
	int s1; //seed
	int l1; //lower bound
	int u1; //upper bound
	cin >> s1; //read in seed
	cin >> l1; //read in lower bound
	cin >> u1; //read in upper bound 
	ar->generateRandom(s1, l1, u1);//generate random set of element array
	int* A = ar->getElementsArray(); //the entire elements of array is store in A
	cout << "Pseudorandom elements: " << endl;
	ar->displayElements(ar->getElementsArray());
	//Bubble Sort
	clock_t Bt= clock(); //start time
	ar->bubbleSort(ar->getElementsArray()); //Bubble Sort
	clock_t BEt = clock(); //end time
	//printf("It took me %d clicks (%f seconds).\n", BEt-Bt, ((float)(BEt-Bt)) / CLOCKS_PER_SEC);
	cout << "Bubble Sort:" << endl; 
	ar->displayElements(ar->getElementsArray()); //display sorted array
	//Quick Sort
	ar->generateRandom(s1, l1, u1);//generate random set of element array
	clock_t Qt = clock(); //start time
	ar->quickSort(0, ar->getnumElements()-1); //Quick Sort
	clock_t QEt = clock(); //end time
	//printf("It took me %d clicks (%f seconds).\n", QEt-Qt, ((float)(QEt-Qt)) / CLOCKS_PER_SEC);
	cout << "Quick Sort:" << endl;
	ar->displayElements(ar->getElementsArray()); //display sorted array
	//Shell Sort
	ar->generateRandom(s1, l1, u1);//generate random set of element array
	clock_t St = clock(); //start time
	ar->shellSort1(); //shell sort
	clock_t SEt = clock(); //end time
	//printf("It took me %d clicks (%f seconds).\n", SEt-St, ((float)(SEt-St)) / CLOCKS_PER_SEC);
	cout << "Shell Sort:" << endl;
	ar->displayElements(ar->getElementsArray()); //display sorted array
	//Adaptive Sort
	clock_t At = clock(); //start time
	int* adaptSortA= ar->adaptiveSort(A); //adaptive sort
	clock_t AEt = clock(); //end time
	//printf("It took me %d clicks (%f seconds).\n", AEt-At, ((float)(AEt-At)) / CLOCKS_PER_SEC);
	cout << "Adaptive Sort:" << endl;
	ar->displayElements(adaptSortA); //display sorted array
	return 0;
}