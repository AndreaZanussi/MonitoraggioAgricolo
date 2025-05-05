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
		cerr << "Error: invalid number" << endl;
		clear_in();
		return 0;
	}
	return n;
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

	do {
		cout << "Please select an option:\n";
		cout << "1 - Add Rover(s)\n";
		cout << "2 - Add Drone(s)\n";
		cout << "3 - Show how many bots are presents\n";
		cout << "4 - Show specific bot\n";
		cout << "5 - Exit\n";

		cin >> choice;

		if (cin.fail()) {
			clear_in();
			cerr << "Error: invalid choise! Please enter a valid option (1-5).\n" << endl;
			continue;
		}


		switch (choice) {
		case 1:
			adding_rover(bots);
			break;
		case 2:
			adding_drone(bots);
			break;
		case 3:
			show_bots(bots);
			break;
		case 4:
			int id;
			if (bots.empty()) {
				cerr << "Error: no bots in the system!\n" << endl;
				clear_in();
				continue;
			}
			else {
				cout << "Insert the ID of the bot you want to show: ";
				cin >> id;			
			}
			if (cin.fail()) {
				cerr << "Error: invalid ID! Please enter a valid option (0-" << bots.size() - 1 << ")\n" << endl;
				clear_in();
				continue;
			}
			//Per evitare di accedere ad elementi fuori al vettore con un conseguente errore del programma
			else if (id < 0 || id > (bots.size() - 1)) {
				cerr << "Error: invalid ID! Please enter a valid option (0-" << bots.size() - 1 << ")\n" << endl;
				clear_in();
				continue;
			}
			else {
				cout << bots[id] << endl;
			}
			break;
		case 5:
			break;
		default:
			clear_in();
			cerr << "Error: invalid choise! Please enter a valid option (1-5).\n" << endl;
			break;
		}
	}
	while (choice != 5);
	cout << "Ending..." << endl;
}

int main()
{
	cout << "//////////////////////////////////////////////\n"
		 << "Welcome to the Agricultural Monitoring System!\n"
		 << "//////////////////////////////////////////////\n"
		 << endl;

	std::vector<Bot> bots;				//Vettore di memoria delle unità 
	menu(bots);							//Interfaccia gestione bots
    cout << "END OF PROGRAM" << endl;
	cin.ignore();
	cin.get();
    return 0;
}

