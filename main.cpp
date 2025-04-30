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

void clearIN() {
	cin.clear();
	cin.ignore(1000, '\n');
};

int valid_n() {
	int n = 0;
	cout << "How many bots do you want to add? ";
	cin >> n;
	if ( (n <= 0) || (n > 100) ){
		cerr << "Error: invalid number" << endl;
		clearIN();
		return 0;
	}
	return n;
};

void adding_rover(std::vector<Bot>& bots) {
	int n_bot = valid_n();
	Bot::add_rover(n_bot, bots);
};

void adding_drone(std::vector<Bot>& bots) {
	int n_bot = valid_n();
	Bot::add_drone(n_bot, bots);
};

void show_bots(std::vector<Bot>& bots) {

	cout << "Actually there are " << bots.size() << " bots in the system.\n" << endl;

};

void menu(std::vector<Bot>& bots) {

	cout << "Do you want to add:\n";
	cout << "1 - Rover\n";
	cout << "2 - Drone\n";
	cout << "3 - Show how many bots are presents\n";
	cout << "4 - Show specific bot\n";
	cout << "5 - Exit\n";

	int choice = 0;
	cin >> choice;

	switch (choice) {
	case 1:
		adding_rover(bots);
		menu(bots);
		break;
	case 2:
		adding_drone(bots);
		menu(bots);
		break;
	case 3:
		show_bots(bots);
		menu(bots);
		break;
	case 4:
		int id;
		cout << "Insert the ID of the bot you want to show: ";
		cin >> id;
		
		if (bots.empty()) {
			cerr << "Error: no bots in the system!" << endl;
			clearIN();
			menu(bots);
		}
		else if (id < 0 || id >= bots.size()) {
			cerr << "Error: invalid ID! Please enter a valid option (0-" << bots.size() << ")" << endl;
			clearIN();
			menu(bots);
		}
		else {
			cout << bots[id] << endl;
			menu(bots);
		}
		break;
	case 5:
		cout << "Ending..." << endl;
		break;
	default:
		clearIN();
		cerr << "Error: invalid choise! Please enter a valid option (1-5).\n" << endl;
		menu(bots);
		break;
	}
}

int main()
{
	cout << "//////////////////////////////////////////////\n"
		 << "Welcome to the Agricultural Monitoring System!\n"
		 << "//////////////////////////////////////////////\n"
		 << endl;

	std::vector<Bot> bots;				//vettore di memoria delle unità  
	menu(bots);							//interfaccia gestione bots
    cout << "END OF PROGRAM" << endl;
    //cin.ignore();
    return 0;
}

