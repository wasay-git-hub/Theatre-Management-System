#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <sstream>
using namespace std;

int generateToken();


// load seats from a txt file
void loadSeats(int seats[6][8], const string& filename);

//  save seats to the txt file
void saveSeats(int seats[6][8], const string& filename);

// display seats
void displaySeats(int seats[6][8]);

bool bookSeat(int seats[6][8], string& name, string& phone, int& token);

void readMovieNames(string filename, string& movie1, string& movie2, string& movie3);

void ticket_booking(int seats[6][8], const string& filename);

int main() {
    // Separate seating arrays for each movie
    int seats2[6][8], seats3[6][8], seats1[6][8];
    int option;

    // File for storing seat data
    string file1 = "seats_1.txt";
    string file2 = "seats_2.txt";
     string file3 = "seats_3.txt";

     string movie1, movie2, movie3, movie4;

    readMovieNames("movies.txt", movie1, movie2, movie3);
    // Load seat data for each movie
    loadSeats(seats1, file1);
    loadSeats(seats2, file2);
    loadSeats(seats3, file3);

    do {
        cout << "\n WELCOME TO MOVIE BOOKING RESERVATION SYSTEM\n";
        cout << " 1. View Movies\n";
        cout << " 2. Book a Seat\n";
        cout<<  " 3. View your booking\n";
        cout << " 4. Exit\n";
        cout << " Enter your choice: ";
        cin >> option;
        switch(option) {
            case 1: {
                string st;
                ifstream in("movies.txt");
                while(getline(in, st)) {  // get movie name
                    cout << "----------------\n";
                    cout << "Movie: " << st << endl;

                    getline(in, st);      // get time
                    cout << "Time: " << st << endl;

                    getline(in, st);      // get date
                    cout << "Date: " << st << endl;

                    getline(in, st);      // get price
                    cout << "Price: " << st << endl;

                    cout << "----------------\n";
                }
                in.close();
                break;
            }
            case 2: {
                int movie;
                cout << "Select a movie: \n 1. "<<movie1<<" \n 2."<<movie2<<" \n 3."<<movie3<<"\n Enter your choice : ";
                cin >> movie;
                int n;
                cout<<"enter the number of seats you want to book : ";
                cin>>n;
                for(int i=1;i<=n;i++){

                if (movie == 1) {
                    ticket_booking(seats1, file1);
                    ofstream out("booking.txt", ios::app);
                    out<<movie1<<"\n";
                } else if (movie == 2) {
                    ticket_booking(seats2, file2);
                    ofstream out("booking.txt", ios::app);
                    out<<movie1<<"\n";
                } else if (movie == 3) {
                    ticket_booking(seats3, file3);
                    ofstream out("booking.txt", ios::app);
                    out<<movie3<<"\n";
                } else {
                    cout << "Invalid movie selection!\n";
                }
                }
                break;
            }
            case 3:{
                {
				int token;
				string name;
				string phone_number;
				string row_number;
				string seat_number;		// Variables to be used
				string movie_name;

				string line;
				int InputToken;
				bool found = false;
				cout << "Enter the token number: ";
				cin >> InputToken;

				ifstream in("booking.txt");	// Opens the file and reads it
				while (getline(in, line)) {		// Reads every line and stores in variable 'line'
					stringstream ss(line);		// Creates an object ss that lets us read what's stored in 'line' word by word

					ss >> name >> phone_number >> row_number >> seat_number >> token >> movie_name;

					// Stores first word in the line in variable 'name'. Second word after space in 'phone_number' and so on

					if (token == InputToken) {
						cout << "BOOKING FOUND!" << endl;
						cout << "Name: " << name << endl;
						cout << "Phone Number: " << phone_number << endl;
						cout << "Row Number: " << row_number << endl;
						cout << "Seat Number: " << seat_number << endl;
						cout << "Token Number: " << token << endl;
						cout << "Movie Name: " << movie_name << endl << endl;
						found = true;
					}
					else if (found = false) {	 // If token doesn't matches for any customer after reading file, 'found' remains false
						cout << "No bookings with Token Number " << InputToken << "." << endl << endl;
					}

				}

                    break;
			}

            }
            case 4 :{
                cout << "Thank you for using our system!\n";
                break;
            }
            default:
                cout << "Invalid input! Please try again.\n";
        }
    } while(option != 4);

    return 0;
}


void loadSeats(int seats[6][8], const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        for (int i = 0; i < 6; i++) {
            for (int j = 0; j < 8; j++) {
                inFile >> seats[i][j];
            }
        }
        inFile.close();
    } else {
        cout<<"unable to load seats \n";
    }
}

void saveSeats(int seats[6][8], const string& filename) {
    ofstream outFile(filename);
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 8; j++) {
            outFile << seats[i][j] << " ";
        }
        outFile << endl;
    }
    outFile.close();
}

void displaySeats(int seats[6][8]) {
    int num=0;
    cout << "\n============= SCREEN THIS WAY =============\n\n";
    cout << "   ";
    // Display column numbers
    for(int j = 1; j <= 8; j++) {
        cout << "S" << j << " ";
    }
    cout << endl;

    // Display seats
    for(int i = 0; i < 6; i++) {
        cout << "R" << (i + 1) << " ";  // Row number
        for(int j = 0; j < 8; j++) {
            cout << " " << seats[i][j] << " ";
            if(seats[i][j]==1){
                num ++;
            }
        }
        cout << endl;
    }
    cout << "\nNote: 1 = Available, 0 = Booked\n";
    cout<<"available Seats : "<<num<<"\nBooked Seats : "<<(48-num)<<endl;
}

bool bookSeat(int seats[6][8], string& name, string& phone, int& token) {
    // Display current seating arrangement
    displaySeats(seats);

    // Get user information
    cin.ignore();
    cout << "\nEnter your name: ";
    getline(cin, name);
    cout << "\nEnter your phone number: ";
    getline(cin, phone);

    //  seat selection
    int rowChoice, seatNumber;
    cout << "\nEnter row (1-6): ";
    cin >> rowChoice;
    cout << "Enter seat number (1-8): ";
    cin >> seatNumber;

    // Convert user input as array starts from 0
    int rowIndex = rowChoice - 1;
    int seatIndex = seatNumber - 1;

    // check Validity
    if(rowIndex < 0 || rowIndex >= 6 || seatIndex < 0 || seatIndex >= 8) {
        cout << "Invalid seat selection!\n";
        return false;
    }

    // Check if the seat is already booked
    else if(seats[rowIndex][seatIndex] == 0) {
        cout << "Seat already booked!\n";
        return false;
    }
    else {
    // Mark the seat as booked
    seats[rowIndex][seatIndex] = 0;

    // Generate booking token
    srand(time(0));
    token = generateToken();

    // Save booking information to file
    ofstream out("booking.txt", ios::app);
    out << name << "\t" << phone << "\t" << rowChoice << "\t" << seatNumber << "\t" << token << "\t";

    cout << "Seat booked successfully!\n";
    return true;
    }
}

int generateToken() {
    return rand() % 900000 + 100000;
}

void ticket_booking(int seats[6][8], const string& filename) {
    string name;
    string phone;
    int token;

    if(bookSeat(seats, name, phone, token)) {
        cout << "\n=== Booking Confirmation ===" << endl;
        cout << "Name: " << name << endl;
        cout << "Phone: " << phone << endl;
        cout << "Your booking token is: " << token << endl;
        cout << "==========================" << endl;

        // Save the updated seating arrangement
        saveSeats(seats, filename);
    }
}

void readMovieNames(string filename, string& movie1, string& movie2, string& movie3) {
    ifstream file(filename);
    string line;
    int lineCount = 0;


    // Read file line by line
    while (getline(file, line)) {
        lineCount++;

        // Store movie names in respective strings
        if (lineCount == 1) {
            movie1 = line;
        }
        else if (lineCount == 6) {
            movie2 = line;
        }
        else if (lineCount == 11) {
            movie3 = line;
        }

    }


}
