# include <iostream>
# include <fstream>
# include <string>
# include <sstream>		// Standard libraries to be used

using namespace std;


int main() {

	int choice;
	do {
		cout << "WELCOME TO MOVIE TICKET ADMIN INTERFACE" << endl << endl;

		cout << "1. Customer's Details" << endl;  // View customer's details from here by entering token number
		cout << "2. Manage Movies" << endl; // Add and manage movies from here
		cout << "3. View Bookings" << endl; // View all the bookings from here
		cout << "4. View Movies Schedule" << endl; // View movies schedule from here
		cout << "5. Unbook all seats" << endl; // Reset the seats after the movie is finished from here
		cout << "6. Exit" << endl << endl; // Exit the program from here

		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;
		switch (choice) {

		case 1: {
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
			cout << endl;

			ifstream in("booking.txt");	// Opens the file and reads it
			while (getline(in, line)) {		// Reads every line and stores in variable 'line'
				stringstream ss(line);		// Creates an object ss that lets us read what's stored in 'line' word by word

				ss >> name >> phone_number >> row_number >> seat_number >> token >> movie_name;

				// Stores first word in the line in variable 'name'. Second word after space in 'phone_number' and so on

				if (token == InputToken) {
					cout << "BOOKING FOUND!" << endl << endl;
					cout << "Name: " << name << endl;
					cout << "Phone Number: " << phone_number << endl;
					cout << "Row Number: " << row_number << endl;
					cout << "Seat Number: " << seat_number << endl;
					cout << "Token Number: " << token << endl;
					cout << "Movie Name: " << movie_name << endl << endl;
					found = true;
				}
			}

				if (found != true) {	 // If token doesn't matches for any customer after reading file, 'found' remains false
					cout << "No bookings with Token Number " << InputToken << "." << endl << endl;
				}



			break;
		}

		case 2: {
			string movie_name;
			string time;
			string date;
			string price;
			int stop = 1;

			while (stop != 0) {
				cout << "Enter the movie details: " << endl;
				cout << "Press 0 if you want to stop adding, 1 to continue ";
				cin >> stop;  // To add multiple movies by one-time running of the program
				cout << endl;
				if (stop == 0) // Program will stop prompting the user for inputs of more movies when the user types '0'
					break;

				getline(cin, price);
				cout << "Enter the movie's name: ";
				getline(cin, movie_name);
				cout << endl;

				cout << "Enter the time: ";
				getline(cin, time);
				cout << endl;

				cout << "Enter the date: ";
				getline(cin, date);
				cout << endl;

				cout << "Enter the price for " << movie_name << ": ";
				getline(cin, price);
				cout << endl;

				ofstream out("movies.txt", ios::app);  // Opening file and writing in it
				out <<  movie_name << endl;
				out <<  time << endl;
				out <<  date << endl;
				out << price << endl;


			}
			break;
		}

		case 3: {
			string bookings;
			ifstream in("booking.txt"); // Opening file and reading it
			in >> bookings;
			cout << "All the bookings till now: " << endl << endl;

			while (getline(in, bookings)) {  // 'while' is to store all lines in "bookings(1).txt" in 'bookings' variable
				cout << bookings << endl << endl;
			}

			break;
		}

		case 4: {
			string movies;
			ifstream in("movies.txt");
			cout << "The movies schedule is as follows: " << endl << endl;
			while (getline(in, movies)) {	  // Reads the file and stores it in 'movies' variable
				cout << movies << endl;
			}

			break;
		}

		case 5: {

			int seats[6][8];
			ofstream out1("seats_1.txt");
			ofstream out2("seats_2.txt");
			ofstream out3("seats_3.txt");


			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {
					seats[i][j] = 1;

				}

			}




			for (int i = 0; i < 6; i++) {
				for (int j = 0; j < 8; j++) {

					out1 << seats[i][j] << " ";
            		out2 << seats[i][j] << " ";
            		out3 << seats[i][j] << " ";
				}
				out1 << endl;
				out2 << endl;
				out3 << endl;

			}
			cout << "All seats have been un-booked for the next day's schedule" << endl << endl;

			out1.close();
			out2.close();
			out3.close();
			break;
		}

		case 6: {
			cout << "THANKS FOR USING!" << endl;

			break;
		}

		default: {
			cout << "Invalid input, try again." << endl << endl;

			break;
		}

		}

	} while (choice != 6);	// Program ends when user types 6 (exit)

	return 0;
}
