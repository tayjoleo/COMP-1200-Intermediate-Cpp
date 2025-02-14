#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

//Taylor Evans
// 
// Assignment 3: Reservation system for a local airline. The program opens two
// files, one which has some reservations stored already, and another
// where all of the reservations are written to. The program uses five
// separate fuctions to make a reservation. One loads the arrays needed for the
// reservation, ensuring that it does not go beyond the maximum number of
// seats available on the aircraft. The second prints a report to the output
// file detailing the passenger's name and their seat assignment. The third
// locates the passenger within the reservation's parallel array. The fourth
// reserves the particular seat for the passenger. The fifth validates this
// selected seat, ensuring that it has not been assigned to another passenger
// already. 

const int SIZE = 30;
const int MAX_ROWS = 10;
const int SEATS_PER_ROW = 3;

int loadArrays(ifstream&, string[], int[][2]);
void printReport(ofstream&, const string[], const int[][2], int);
void findPassenger(const string&, const string[], int&, int);
bool reserveSeat(string[], int[][2], int&);
bool validateSeat(int, int);

int main()
{
	int reservation[SIZE][2];
	string name[SIZE];
	int noPassengers = 0;
	int position;
	ifstream fin("reservations.dat");
	if (!fin.is_open())
	{
		cout << "error opening reservations.dat file - contact systems";
		system("pause");
		exit(-1);
	}
	ofstream fout("reservations.rpt");
	if (!fout.is_open())
	{
		cout << "error opening reservations.rpt file - contact systems";
		system("pause");
		exit(-2);
	}
	cout << "Search for non passenger \n";
	findPassenger("Superman", name, position, noPassengers);
	cout << "Passenger: Superman";
	if (position < noPassengers)
		cout << " is seated in row " << reservation[position][0]
		<< " seat " << reservation[position][1];
	else
		cout << " is not found ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);
	cout << "Load arrays\n";
	noPassengers = loadArrays(fin, name, reservation);
	printReport(fout, name, reservation, noPassengers);
	cout << "Search for existing passenger \n";
	findPassenger("J. Doe", name, position, noPassengers);
	cout << "Passenger: J. Doe";
	if (position < noPassengers)
		cout << " is seated in row " << reservation[position][0]
		<< " seat " << reservation[position][1];
	else
		cout << " is not found ";
	cout << endl;
	cout << "#1 Reserve for Superman in unoccupied seat (4, 1) : \n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);

	cout << "#1 Reserve for Batman in Superman's seat (4, 1): \n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);

	cout << "#1 Reserve for Batman again in unoccupied seat (4, 2):\n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);

	cout << "#1 Reserve for Cat woman in unoccupied seat (4, 3)\n";
	if (reserveSeat(name, reservation, noPassengers))
		cout << "reservation made ";
	else
		cout << "reservation not made ";
	cout << endl;
	printReport(fout, name, reservation, noPassengers);
	cout << "program ended successfully" << endl;
	cout << "\nDump of Reservations.dat file\n";
	system("type reservations.dat");
	cout << "\nPrintout of Reservations Report\n";
	system("type reservations.rpt");
	system("pause");
}

int loadArrays(ifstream& inputFile, string names[], 
	           int rowSeatNbr[][2]) 
{
	int arrayLength = 0;

	while (arrayLength < SIZE) 
	{
		getline(inputFile, names[arrayLength]);

		if (inputFile.eof()) break;

		for (int column = 0; column < 2; column++) 
		{ 
			inputFile >> rowSeatNbr[arrayLength][column];
		}

		if (inputFile.fail()) 
		{
			inputFile.clear(); 
			inputFile.ignore(80, '\n'); 
			break;
		}
		else 
		{
			inputFile.ignore(80, '\n'); 
		}
		arrayLength++;
	}
	return arrayLength;
}

bool validateSeat(int row, int seat) 
{
	if (row < 1 || row > MAX_ROWS) 
	{
		cout << "Invalid row number. It must be between 1 and " 
			 << MAX_ROWS << endl;
		return false;
	}

	if (seat < 1 || seat > SEATS_PER_ROW) 
	{
		cout << "Invalid seat number. It must be between 1 and " 
			 << SEATS_PER_ROW << endl;
		return false;
	}
	return true; 
}

bool reserveSeat(string names[], int reservations[][2], int& noPassengers) 
{
	if (noPassengers >= SIZE) 
	{
		cout << "The reservation list is full." << endl;
		return false;
	}

	
	string passengerName;
	int row, seat;
	cout << "Enter passenger's name: ";
	getline(cin, passengerName);
	cout << "Enter row number: ";
	cin >> row;
	cout << "Enter seat number: ";
	cin >> seat;
	cin.ignore(80, '\n');


	if (!validateSeat(row, seat)) 
	{
		return false;
	}

	for (int index = 0; index < noPassengers; index++) 
	{
		if (reservations[index][0] == row && reservations[index][1] == seat) 
		{
			cout << "This seat is already taken." << endl;
			return false;
		}
	}

	names[noPassengers] = passengerName;
	reservations[noPassengers][0] = row;
	reservations[noPassengers][1] = seat;
	noPassengers++;
	cout << "Seat reserved for " << passengerName << "." << endl;
	return true;
}

void printReport(ofstream& outputFile, const string names[], 
				const int rowSeatNbr[][2], int arrayLength)
{
	outputFile << left << setw(15) << "Passenger" << setw(6) << "Row" 
			   << "Seat" << endl << endl;

	for (int index = 0; index < arrayLength; index++) 
	{
		outputFile << left << setw(15) << names[index]
			<< right << setw(6) << rowSeatNbr[index][0]
			<< setw(6) << rowSeatNbr[index][1] << endl;
	}

	outputFile << endl << "Number of passengers = " << arrayLength << endl;
}

void findPassenger(const string& passengerName, const string names[],
	               int& position, int noPassengers)
{
	position = noPassengers;

	for (int index = 0; index < noPassengers; index++) 
	{
		if (names[index] == passengerName)
		{
			
			position = index;
			return;
		}
	}
}

/*
Search for non passenger
Passenger: Superman is not found
Load arrays
Search for existing passenger
Passenger: J. Doe is seated in row 1 seat 2
#1 Reserve for Superman in unoccupied seat (4, 1) :
Enter passenger's name: Clark Day
Enter row number: 7
Enter seat number: 2
Seat reserved for Clark Day.
reservation made
#1 Reserve for Batman in Superman's seat (4, 1):
Enter passenger's name: Person Person
Enter row number: 8
Enter seat number: 1
Seat reserved for Person Person.
reservation made
#1 Reserve for Batman again in unoccupied seat (4, 2):
Enter passenger's name: Dude Dude
Enter row number: 2
Enter seat number: 3
Seat reserved for Dude Dude.
reservation made
#1 Reserve for Cat woman in unoccupied seat (4, 3)
Enter passenger's name: Blagh Blagh
Enter row number: 9
Enter seat number: 2
Seat reserved for Blagh Blagh.
reservation made
program ended successfully

Dump of Reservations.dat file
J. Doe
1 2
P. Smith
5       3
T. Jones
3       1
T. Evans
3 2
R. Wieczorek
4 3
E. Allen
5 1
Printout of Reservations Report
Passenger      Row   Seat


Number of passengers = 0
Passenger      Row   Seat

J. Doe              1     2
P. Smith            5     3
T. Jones            3     1
T. Evans            3     2
R. Wieczorek        4     3
E. Allen            5     1

Number of passengers = 6
Passenger      Row   Seat

J. Doe              1     2
P. Smith            5     3
T. Jones            3     1
T. Evans            3     2
R. Wieczorek        4     3
E. Allen            5     1
Clark Day           7     2

Number of passengers = 7
Passenger      Row   Seat

J. Doe              1     2
P. Smith            5     3
T. Jones            3     1
T. Evans            3     2
R. Wieczorek        4     3
E. Allen            5     1
Clark Day           7     2
Person Person       8     1

Number of passengers = 8
Passenger      Row   Seat

J. Doe              1     2
P. Smith            5     3
T. Jones            3     1
T. Evans            3     2
R. Wieczorek        4     3
E. Allen            5     1
Clark Day           7     2
Person Person       8     1
Dude Dude           2     3

Number of passengers = 9
Passenger      Row   Seat

J. Doe              1     2
P. Smith            5     3
T. Jones            3     1
T. Evans            3     2
R. Wieczorek        4     3
E. Allen            5     1
Clark Day           7     2
Person Person       8     1
Dude Dude           2     3
Blagh Blagh         9     2

Number of passengers = 10
Press any key to continue . . .
*/