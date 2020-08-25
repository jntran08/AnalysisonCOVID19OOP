#include <iostream>
using namespace std;
// Write all the classes here

//create a function to parse the data from reading line in command and csv files
int parseData(char* start, char* fields, int index, int startsize, int fieldsize, char deliminator) {
	int i = index; // the starting/ current index of line
	int j = 0;

	for (int k = 0; k < fieldsize; ++k) {
		fields[k] = '\0'; //declare as null
	}

	do {
		fields[j] = start[i];
		i++;
		j++;
	} while (start[i] != deliminator);  //if the line doesnt reach deliminator the stored into the fields

	fields[j] = '\0'; //the element at the last index declared as null 

	return i; // return the position of deliminator 
};


class COVID19 {
protected:
	char* date;
	char* county;
	char* state;
	int fips;
	int cases;
	int deaths;

public:
	COVID19(); //default constructor
	COVID19(char* da, char* co, char* s, int f,
		int ca, int de); //initializer
	void setDate(char* da);
	void setCounty(char* co);
	void setState(char* s);
	void setFips(int f);
	void setCases(int c);
	void setDeaths(int d);
	char* getDate();
	char* getState();
	char* getCounty();
	int getFips();
	int getCases();
	int getDeaths();
	void display(); //void
	//write all accessors and other methods as necessary
};

COVID19::COVID19() {
	date = nullptr;
	county = nullptr;
	state = nullptr;
	fips = 0;
	cases = 0;
	deaths = 0;
}; //default constructor

COVID19::COVID19(char* da, char* co, char* s, int f,
	int ca, int de) {

	date = new char[11];
	county = new char[50];
	state = new char[30];

	for (int i = 0; i < 11; i++) {
		date[i] = da[i];
	};
	for (int i = 0; i < 50; i++) {
		county[i] = co[i];
	};
	for (int i = 0; i < 30; i++) {
		state[i] = s[i];
	};
	fips = f;
	cases = ca;
	deaths = de;
}; //non-default constructor, initializer


void COVID19::setDate(char* da) {

	this->date = da;
};
void COVID19::setCounty(char* co) {

	this->county = co;
}
void COVID19::setState(char* s) {

	this->state = s;
};

void COVID19::setFips(int f) {
	this->fips = f;
};
void COVID19::setCases(int ca) {
	this->cases = ca;
};
void COVID19::setDeaths(int de) {
	this->deaths = de;
};

char* COVID19::getDate() {
	return date;
};

char* COVID19::getState() {
	return state;
};

char* COVID19::getCounty() {
	return county;
};

int COVID19::getFips() {
	return fips;
};

int COVID19::getCases() {
	return cases;
};

int COVID19::getDeaths() {
	return deaths;
}

void COVID19::display() {
	cout << this->getDate() << "," << this->getCounty() << "," << this->getState() << "," << this->getFips() << "," << this->getCases() << "," << this->getDeaths()<< endl;
};


class COVID19DataSet {
protected:
	COVID19* allData;
	int count; //number of COVID19 objects in allData
	int size; //maximum size of array
public:

	COVID19DataSet() {
		count = 0;
		size = 0;
		allData = nullptr;
	}; //default constructor
	COVID19DataSet(int initSize);
	//void display();
	void addRow(COVID19& oneData);

	int findTotalCasesByCounty(char* county, char* state);
	int findTotalDeathsByCounty(char* county, char* state);
	int findTotalCasesByState(char* state);
	int findTotalDeathsByState(char* state);
	int findTotalCasesBySateWithDateRange(char* state,
		char* startDate, char* endDate);
	int findTotalDeathsBySateWithDateRange(char* state,
		char* startDate, char* endDate);
	bool comparefields(char* field1, char* field2);
	//~ COVID19(); //destructor
};

COVID19DataSet::COVID19DataSet(int initSize) {
	allData = new COVID19[initSize];
	count = 0;
	size = initSize;
}; //non-default constructor, initializer

void COVID19DataSet::addRow(COVID19& oneData)
{
	// get fields from one row
	char* dts = oneData.getDate(); // date
	char* ct = oneData.getCounty(); // county
	char* st = oneData.getState(); // state
	int fps = oneData.getFips(); // fips
	int cs = oneData.getCases(); // cases
	int dths = oneData.getDeaths(); // deaths
	// set fields to add rows
	allData[count].setDate(dts);
	allData[count].setCounty(ct);
	allData[count].setState(st);
	allData[count].setFips(fps);
	allData[count].setCases(cs);
	allData[count].setDeaths(dths);
	count++;

};

bool COVID19DataSet::comparefields(char* field1, char* field2) {
	int l1 = 0; // length of field 1
	int l2 = 0; // length of field 2
	while (field1[l1] != '\0') {
		l1++; // calculating length of field 1
	}
	while (field2[l2] != '\0') {
		l2++; // calculating length of field 1
	}
	bool check = false;

	//check betweek 2 fields if they are equal character-by-character
	for (int i = 0; i < l1; i++) {
		if (field1[i] == field2[i]) {
			check = true;
		}
		else {
			check = false;
			break;
		};
		
	};

	return check;
};

int COVID19DataSet::findTotalCasesByCounty(char* county, char* state) {
	int counting = 0;
	for (int i = 0; i < size; i++) {
		if (comparefields(allData[i].getState(), state)) { 
			if (comparefields(allData[i].getCounty(), county)) { 
				counting += allData[i].getCases();
			};
		};
	};
	return counting;
};

int COVID19DataSet::findTotalDeathsByCounty(char* county, char* state) {
	int counting = 0;
	for (int i = 0; i < size; i++) {
		if (comparefields(allData[i].getState(), state)) {
			if (comparefields(allData[i].getCounty(), county)) {
				counting += allData[i].getDeaths();
			};
		};
	};
	return counting;
};

int COVID19DataSet::findTotalCasesByState(char* state) {
	int counting = 0;
	for (int i = 0; i < size; i++) {
		if (comparefields(allData[i].getState(), state)) {
			counting += allData[i].getCases();
		};
	};
	return counting;
};

int COVID19DataSet::findTotalDeathsByState(char* state) {
	int counting = 0;
	for (int i = 0; i < size; i++) {
		if (comparefields(allData[i].getState(), state)) {
			counting += allData[i].getDeaths();
		};
	};
	return counting;
};


int COVID19DataSet::findTotalCasesBySateWithDateRange(char* state,
	char* startDate, char* endDate) {
	int counting = 0;

	// input
	char year[5];
	char month[3];
	char day[3];

	int idx_p = 0;
	int idx_p1 = 0;
	int idx_p2 = 0;

	// parse the input start date
	int len = 0;
	while (startDate[len] != '\0') {
		len++;
	};

	idx_p = parseData(startDate, year, idx_p, len, 5, '-');
	int yS = atoi(year);

	idx_p1 = parseData(startDate, month, idx_p + 1, len, 3, '-');
	int mmS = atoi(month);

	idx_p2 = parseData(startDate, day, idx_p1 + 1, len, 3, '\0');
	int ddS = atoi(day);

	// parse the input end date
	char yearE[5];
	char monthE[3];
	char dayE[3];

	int idxE = 0;

	int lenE = 0;
	while (endDate[len] != '\0') {
		lenE++;
	};

	idxE = parseData(endDate, yearE, idxE, lenE, 5, '-');
	int yE = atoi(yearE);

	idxE = parseData(endDate, monthE, idxE + 1, lenE, 3, '-');
	int mmE = atoi(monthE);

	idxE = parseData(endDate, dayE, idxE + 1, lenE, 3, '\0');
	int ddE = atoi(dayE);

	// initialize the temp characters for year, month, date from the data
	char* temp_year;
	temp_year = new char[5];
	char* temp_month;
	temp_month = new char[3];
	char* temp_day;
	temp_day = new char[3];
	int y_temp = 0;
	int m_temp = 0;
	int d_temp = 0;

	// run loop through data, do calculation 
	for (int i = 0; i < size; i++) {
		
		for (int j = 0; j < 4; j++) {
			temp_year[j] = allData[i].getDate()[j];
		};
		temp_year[4] = '\0';

		for (int j = 5; j < 7; j++) {
			temp_month[j - 5] = allData[i].getDate()[j];
		};
		temp_month[2] = '\0';
		for (int j = 8; j < 10; j++) {
			temp_day[j - 8] = allData[i].getDate()[j];
		};
		temp_day[2] = '\0';
		int y_temp = atoi(temp_year);
		int m_temp = atoi(temp_month);
		int d_temp = atoi(temp_day);


		if (comparefields(allData[i].getState(), state) ) {
			if (y_temp >= yS && y_temp <= yE) { // within start and end years
				if (m_temp >= mmS && m_temp <= mmE) { // within start and end months
					if (d_temp >= ddS) { // after start date
						if (d_temp <= ddE) { // before end date
							counting += allData[i].getCases();
						}
						else if (d_temp > ddE && mmS != mmE) { // if after end date and start month is not end month 
							counting += allData[i].getCases();
						}
					}
				}
			}
		}

	};
	return counting;

};

int COVID19DataSet::findTotalDeathsBySateWithDateRange(char* state,
	char* startDate, char* endDate) {
	int counting = 0;

	// parse the input start date
	char year[5];
	char month[3];
	char day[3];

	int idx_p = 0;
	int idx_p1 = 0;
	int idx_p2 = 0;

	int len = 0;
	while (startDate[len] != '\0') {
		len++;
	};

	idx_p = parseData(startDate, year, idx_p, len, 5, '-');
	int yS = atoi(year);

	idx_p1 = parseData(startDate, month, idx_p + 1, len, 3, '-');
	int mmS = atoi(month);

	idx_p2 = parseData(startDate, day, idx_p1 + 1, len, 3, '\0');
	int ddS = atoi(day);

	// parse the input end date
	char yearE[5];
	char monthE[3];
	char dayE[3];

	int idxE = 0;

	int lenE = 0;
	while (endDate[len] != '\0') {
		lenE++;
	};

	idxE = parseData(endDate, yearE, idxE, lenE, 5, '-');
	int yE = atoi(yearE);

	idxE = parseData(endDate, monthE, idxE + 1, lenE, 3, '-');
	int mmE = atoi(monthE);

	idxE = parseData(endDate, dayE, idxE + 1, lenE, 3, '\0');
	int ddE = atoi(dayE);

	// initialize the temp characters for year, month, date from the data
	char* temp_year;
	temp_year = new char[5];
	char* temp_month;
	temp_month = new char[3];
	char* temp_day;
	temp_day = new char[3];
	int y_temp = 0; 
	int m_temp = 0;
	int d_temp = 0;

	// run in loop execute calculations
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < 4; j++) {
			temp_year[j] = allData[i].getDate()[j]; //read year month 
		};
		temp_year[4] = '\0';

		for (int j = 5; j < 7; j++) {
			temp_month[j - 5] = allData[i].getDate()[j]; //read current month 
		};
		temp_month[2] = '\0';
		for (int j = 8; j < 10; j++) {
			temp_day[j - 8] = allData[i].getDate()[j]; //read current day
		};
		temp_day[2] = '\0';
		int y_temp = atoi(temp_year);
		int m_temp = atoi(temp_month);
		int d_temp = atoi(temp_day);


		if (comparefields(allData[i].getState(), state) == 1) {
			if (y_temp >= yS && y_temp <= yE) { // within start and end years
				if (m_temp >= mmS && m_temp <= mmE) { // within start and end months
					if (d_temp >= ddS) { // after start date
						if (d_temp <= ddE) { // before end date
							counting += allData[i].getDeaths();
						}
						else if (d_temp > ddE && mmS != mmE) { // if after end date and start month is not end month 
							counting += allData[i].getDeaths();
						}
					}
				}
			}
		}

	};
	return counting;
};


int main() {

	int counts; // number of records in Filename.CSV
	int command;
	char* covid = new char[28];
	COVID19 oneRow;

	cin >> counts; //read the first integer in the file that contains the number of rows

	FILE* myFile;//read the filename, for example, Filename.csv
	cin >> covid;
	//open the Filename.csv using fopen (google it for C++ to find out)
	myFile = fopen(covid, "r");//assume that you named this file as myFile

	COVID19DataSet* myData = new COVID19DataSet(counts);

	// create buffer variables  
	char dateB[11];
	char countyB[50];
	char stateB[30];
	char fipsB[10];
	char casesB[30];
	char deathsB[20];

	char currentLine[256]; //character array to hold csv files
	fgets(currentLine, 256, myFile); // reading 1st line of csv file <- name of columns 

	for (int i = 0; i < counts; i++) {

		int idx = 0; // index location in currentLine where we previously stoped parsing
		int idx1 = 0;
		int idx2;
		fgets(currentLine, 256, myFile); // get currentLine in csv

		//read the values in each row
		idx1 = parseData(currentLine, dateB, idx, 256, 11, ','); // parse buffer date
		idx1 = parseData(currentLine, countyB, idx1 + 1, 256, 50, ','); // parse buffer county
		idx1 = parseData(currentLine, stateB, idx1+1, 256, 30, ','); // parse buffer state

		if (currentLine[idx1 + 1] != ',') {
			idx1 = parseData(currentLine, fipsB, idx1 + 1, 256, 10, ','); //parse buffer fips
			idx1 = parseData(currentLine, casesB, idx1 + 1, 256, 30, ','); // parse buffer cases
			idx1 = parseData(currentLine, deathsB, idx1 + 1, 256, 20, '\n'); // parse buffer deaths
		} 
		if (currentLine[idx1 + 1] == ',') { // if fips is missing in teh data
			//idx1 = parseData(currentLine, fipsB, idx1 + 1, 256, 10, ',');
			fipsB[0] = currentLine[idx + 1];
			idx2 = parseData(currentLine, casesB, idx1 + 2, 256, 30, ',');
			idx2 = parseData(currentLine, deathsB, idx2 + 1, 256, 20, '\n');
		};
		
		oneRow = COVID19(dateB, countyB, stateB, atoi(fipsB), atoi(casesB), atoi(deathsB)); // store in oneRow and use setters to set the fields in oneRow
		(*myData).addRow(oneRow);

		//oneRow.display(); // read my Data

	} //end for loop

	fclose(myFile); // close the file

	cin >> command;

	while (!cin.eof()) {

		switch (command) {
		case 1: {
			// read the rest of the row
			char line[100]; //current line in command file
			int iter = 0;
			char rd;
			cin.get(rd); //parsing random character from command file 
			do {
				cin.get(rd);
				line[iter] = rd; // parse the current line
				iter++; //length of current line
			} while (rd != '\n');

			char county[50];
			char state[30];
			int idx_command = 0;
			//parse county and state
			idx_command = parseData(line, county, idx_command, iter, 50, ',');
			idx_command = parseData(line, state, idx_command + 2, iter, 30, '\n');

			//do what is needed for command 1
			int result1 = (*myData).findTotalCasesByCounty(county, state);
			cout << county << " County, " << state << ", " << result1 << " CASES" << endl;

			break;
		}
		case 2: {
			char line[100]; // current line in command file
			int iter = 0;
			char rd;
			cin.get(rd); // parsing random character from command file 
			do {
				cin.get(rd);
				line[iter] = rd; // parse the current line
				iter++; // length of current line
			} while (rd != '\n');
			
			//parse county and state
			char county[50];
			char state[30];
			int idx_command = 0;
			idx_command = parseData(line, county, idx_command, iter, 50, ',');
			idx_command = parseData(line, state, idx_command + 2, iter, 30, '\n');

			//do what is needed for command 2
			int result2 = (*myData).findTotalDeathsByCounty(county, state);
			cout << county << " County, " << state << ", " << result2 << " DEATHS" << endl;

			break;
		}
		case 3: {
			char line[100]; // current line in command file
			int iter = 0;
			char rd;
			cin.get(rd); // parsing random character from command file 
			do {
				cin.get(rd);
				line[iter] = rd; // parse the current line
				iter++; // length of current line
			} while (rd != '\n');

			//parse state
			char state[30];
			int idx_command = 0;
			idx_command = parseData(line, state, idx_command, iter, 30, '\n');
			state[idx_command + 1] = '\0';
			//do what is needed for command 3
			int result3 = (*myData).findTotalCasesByState(state);
			cout << state << ", " << result3 << " CASES" << endl;
		
			break;
		}
		case 4: {
			char line[100]; // current line in command file
			int iter = 0;
			char rd;
			cin.get(rd); // parsing random character from command file 
			do {
				cin.get(rd);
				line[iter] = rd; // parse the current line
				iter++; // length of current line
			} while (rd != '\n');

			//parse state
			char state[30];
			int idx_command = 0;
			idx_command = parseData(line, state, idx_command, iter, 30, '\n');
			state[idx_command + 1] = '\0';

			//do what is needed for command 4
			int result4 = (*myData).findTotalDeathsByState(state);
			cout << state << ", " << result4 << " DEATHS" << endl;

			break;
		}
		case 5: {
			char line[100]; // current line in command file
			int iter = 0;
			char rd;
			cin.get(rd); // parsing random character from command file 
			do {
				cin.get(rd);
				line[iter] = rd; // parse the current line
				iter++; // length of current line
			} while (rd != '\n');

			char state[30];
			char startDate[11];
			char endDate[11];
			int idx_c = 0;
			int idx_c1 = 0;
			int idx_c2 = 0;

			idx_c = parseData(line, state, idx_c, iter, 30, ' ');

			if (line[idx_c + 1] == '2') { //one-worded state
				idx_c = parseData(line, startDate, idx_c + 1, iter, 11, ' '); //parse start date
				idx_c = parseData(line, endDate, idx_c + 1, iter, 11, '\n'); //parse end date
				int result5 = (*myData).findTotalCasesBySateWithDateRange(state, startDate, endDate);
				cout << state << ", " << startDate << " to " << endDate << ", " << result5 << " CASES" << endl;
			}
			else { //two-worded state
				char statet[10];
				idx_c1 = parseData(line, statet, idx_c + 1, iter, 10, ' '); // parse remaining name
				char statess[30];
				for (int i = 0; i < idx_c1 + 1; i++) {
					statess[i] = line[i]; // parse both words
				}
				statess[idx_c1] = '\0';
				idx_c1 = parseData(line, startDate, idx_c1 + 1, iter, 11, ' ');
				idx_c1 = parseData(line, endDate, idx_c1 + 1, iter, 11, '\n');
				int result5 = (*myData).findTotalCasesBySateWithDateRange(statess, startDate, endDate);
				cout << statess << ", " << startDate << " to " << endDate << ", " << result5 << " CASES" << endl;
			};

			break;
		}
		case 6: {
			char line[100];
			int iter = 0;
			char rd; //reading char
			cin.get(rd);
			while (rd != '\n') {
				cin.get(rd);
				line[iter] = rd;// parse the current line in command character-by-character
				iter++;
			};

			char state[30];
			char startDate[11];
			char endDate[11];
			int idx_c = 0;
			int idx_c1 = 0;
			int idx_c2 = 0;

			char statess[30]; //two name state

			idx_c = parseData(line, state, idx_c, iter, 30, ' ');
			if (line[idx_c + 1] == '2') {
				idx_c = parseData(line, startDate, idx_c + 1, iter, 11, ' ');
				idx_c = parseData(line, endDate, idx_c + 1, iter, 11, '\n');
				int result5 = (*myData).findTotalDeathsBySateWithDateRange(state, startDate, endDate);
				cout << state << ", " << startDate << " to " << endDate << ", " << result5 << " DEATHS" << endl;
			}
			else {
				char statet[10];
				idx_c1 = parseData(line, statet, idx_c + 1, iter, 10, ' ');
				for (int i = 0; i < idx_c1 + 1; i++) {
					statess[i] = line[i]; // parse both words
				}
				statess[idx_c1] = '\0';
				idx_c1 = parseData(line, startDate, idx_c1 + 1, iter, 11, ' '); // parse start date
				idx_c1 = parseData(line, endDate, idx_c1 + 1, iter, 11, '\n'); // parse end date
				int result5 = (*myData).findTotalDeathsBySateWithDateRange(statess, startDate, endDate);
				cout << statess << ", " << startDate << " to " << endDate << ", " << result5 << " DEATHS" << endl;
			};

			break;
		}

		} //end switch

		cin >> command;

		if (cin.eof() && cin.fail()) {
			break; // make sure it reached end-of-file and exist
		}

	} //end while

	delete myData;
	return 0;
}
