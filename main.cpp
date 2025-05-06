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

void clear_in() {
	cin.clear();
	cin.ignore(1000, '\n');
};

int valid_n() {
	int n = 0;
	cout << "How many bots do you want to add? ";
	cin >> n;
	if ( (n <= 0) || (n > 50) ){
		cerr << "Error: invalid number or number too high" << endl;
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

void checking_all_status(std::vector<Bot>& bots) {
	for (int i = 0; i < bots.size(); i++) {
		if (bots[i].status() == Bot::Status::Error) {
			cout << "Bot " << bots[i].id() << " is damaged!\n" << endl;
		}
		else if (bots[i].status() == Bot::Status::Active) {
			cout << "Bot " << bots[i].id() << " is active.\n" << endl;
		}
		else if (bots[i].status() == Bot::Status::Moving) {
			cout << "Bot " << bots[i].id() << " is moving.\n" << endl;
		}
		else if (bots[i].status() == Bot::Status::Measuring) {
			cout << "Bot " << bots[i].id() << " is measuring.\n" << endl;
		}
		else if (bots[i].status() == Bot::Status::Homing) {
			cout << "Bot " << bots[i].id() << " is homing.\n" << endl;
		}
	}
};

bool check_status(int id, std::vector<Bot>& bots) {

	if (bots[id].status() != Bot::Status::Active) {
		return false;
	}
	else {
		return true;
	}
};

void adding_rover(std::vector<Bot>& bots) {
	int n_bot = valid_n();
	Bot::add_bot(n_bot, Bot::Type::Rover, bots);
};

void adding_drone(std::vector<Bot>& bots) {
	int n_bot = valid_n();
	Bot::add_bot(n_bot, Bot::Type::Drone, bots);
};

void show_bots(std::vector<Bot>& bots) {

	cout << "Actually there are " << bots.size() << " bots in the system.\n" << endl;

};

void menu(std::vector<Bot>& bots) {

	int choice = 0;
	int id;

	do {
		cout << "Please select an option:\n";
		cout << "1 - Exit\n";
		cout << "2 - Add Rover(s)\n";
		cout << "3 - Add Drone(s)\n";
		cout << "4 - Show how many bots are presents\n";
		cout << "5 - Show all bots status\n";
		cout << "6 - Show a specific bot legend\n";
		cout << "7 - Send a bot to a specific position\n";
		cout << "Insert your choice: ";

		cin >> choice;

		if (cin.fail()) {
			clear_in();
			cerr << "Error: invalid choise! Please enter a valid option (1-5).\n" << endl;
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
			show_bots(bots);
			break;
		case 5:
			if (bots.size() == 0) {
				cerr << "Error: no bots in the system!\n" << endl;
				break;
			}
			else {
				checking_all_status(bots);
				break;
			}
			break;
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
				bool available = check_status(id, bots);
				if (available == true) {
					cout << "Insert the coordinates of the position: ";
					int r = 0, c = 0;
					cin >> r >> c;
					if (cin.fail()) {
						cerr << "Error: invalid coordinates!\n" << endl;
						clear_in();
						continue;
					}
					else {
						bots[id].move_to();
						bots[id].set_status(Bot::Status::Moving, id);
						cout << "Bot " << bots[id].id() << " is moving to position (" << r << ", " << c << ").\n" << endl;
					}
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

	std::vector<Bot> bots;				//Vettore di memoria delle unità 
	menu(bots);							//Interfaccia gestione bots
    cout << "END OF PROGRAM" << endl;
	cin.ignore();
	cin.get();
    return 0;
}

