// MonitoraggioAgricolo.cpp : Questo file contiene la funzione 'main', in cui inizia e termina l'esecuzione del programma.
//Ipotesi: un bot se viene danneggiato (error), può essere sostituito con un altro bot cambiando la scheda ID.
//		   Non si può quindi eliminare un ID. Al limite rimarrà inutilizzato.
//
#include <iostream>
#include <vector>
#include <string>
#include "Bot.h"

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::pair;

const int MAX_ROWS = 10;
const int MAX_COLS = 10;

void clear_in() {
	cin.clear();
	cin.ignore(1000, '\n');
};

pair<int, int> valid_field() {
	int rows = 0, cols = 0;
	cout << "Set the field measure LxW [m^2]:" << endl;

	while (true) {
		cin >> rows >> cols;
		if ((cin.fail()) || (rows <= 0) || (cols <= 0) || (rows > MAX_ROWS) || (cols > MAX_COLS)) {
			cerr << "Error: invalid field size or too big!\n" << endl;
			clear_in();
		}
		else {
			return {rows, cols};
			break;
		}
	}
};

int valid_n() {
	int n = 0;
	cout << "How many bots do you want to add? ";
	cin >> n;
	if ( (n <= 0) || (n > 50) ){
		cerr << "Error: invalid number or too high" << endl;
		clear_in();
		return 0;
	}
	return n;
};

int valid_id(int size) {
	int id = 0;
	if (size == 0) {
		cerr << "Error: no bots in the system!\n" << endl;
		clear_in();
		return -1;
	}
	else {
		cout << "Insert the ID of the bot: ";
		cin >> id;
		if (cin.fail()) {
			cerr << "Error: invalid ID! Please enter a valid option (0-" << size - 1 << ")\n" << endl;
			clear_in();
			return -1;
		}
		//Per evitare di accedere ad elementi fuori al vettore con un conseguente errore del programma
		else if (id < 0 || id >(size - 1)) {
			cerr << "Error: invalid ID number! Please enter a valid option (0-" << size - 1 << ")\n" << endl;
			clear_in();
			return -1;
		}
		else {
			return id;
		}
	}
};

void adding_rover(vector<Bot>& bots) {
	int n_bot = valid_n();
	Bot::add_bot(n_bot, Bot::Type::Rover, bots);
};

void adding_drone(vector<Bot>& bots) {
	int n_bot = valid_n();
	Bot::add_bot(n_bot, Bot::Type::Drone, bots);
};

void menu(vector<Bot>& bots, AgriField& field) {

	int choice = 0;
	int id;

	do {
		cout << "Please select an option:\n"
			<< "1 - Exit\n"
			<< "2 - Add Rover(s)\n"
			<< "3 - Add Drone(s)\n"
			<< "4 - Show how many bots are presents\n"
			<< "5 - Show all bots status\n"
			<< "6 - Show a specific bot legend\n"
			<< "7 - Send a bot to a specific position\n"
			<< "Insert your choice: " << endl;

		cin >> choice;

		if (cin.fail()) {
			clear_in();
			cerr << "Error: invalid choise! Please enter a valid option (1-7).\n" << endl;
			continue;
		}

		switch (choice) {
		case 1:
			break;
		case 2:
			adding_rover(bots);
			break;
		case 3:
			adding_drone(bots);
			break;
		case 4:
			cout << "Actually there are " << bots.size() << " bots in the system.\n" << endl;
			break;
		case 5:
			if (bots.size() == 0) {
				cerr << "Error: no bots in the system!\n" << endl;
				break;
			}
			else {
				bots[0].check_all_status(bots);
				break;
			}
		case 6:
			id = valid_id(static_cast<int>(bots.size()));
			if (id == -1) {
				break;
			}
			else {
				cout << bots[id] << endl;
				break;
			}
		case 7:
			id = valid_id(static_cast<int>(bots.size()));
			if (id == -1) {
				break;
			}
			else {
				bool available = bots[id].check_is_available();
				if (available == true) {
					bots[id].move_to_cell(field, bots);
				}
				else {
					cerr << "Error: bot is not available!\n" << endl;
				}
			}
			break;
		default:
			clear_in();
			cerr << "Error: invalid choise! Please enter a valid option (1-5).\n" << endl;
			break;
		}
	}
	while (choice != 1);
	cout << "Ending..." << endl;
}

int main()
{
	cout << "//////////////////////////////////////////////\n"
		 << "WELCOME TO THE AGRICULTURAL MONITORING SYSTEM!\n"
		 << "//////////////////////////////////////////////\n"
		 << endl;

	//Creazione del campo di lavoro
	pair<int, int> dimensions = valid_field();
 	AgriField field(dimensions.first, dimensions.second);
	vector<Bot> bots;							//Vettore di memoria delle unità 

	menu(bots, field);							//Interfaccia gestione bots
    cout << "END OF PROGRAM" << endl;
	cin.ignore();
	cin.get();
    return 0;
}

