#include <ostream>
using std::ostream;
#include <iostream>
using std::cerr;
using std::endl;

using std::cout;
#include <vector>
#include "Bot.h"


//Costruttori di default
Bot::Bot() {}
AgriField::AgriField() {}

//Costruttori con parametri di default
Bot::Bot(int id, Type type)
    : id_{ id }, type_{ type }, status_{ Status::Active }, batteryLevel_{ 100 }, humidity_{ 0 }, temperature_{ 0 }, plantHealth_{ true } {
    
}

AgriCell::AgriCell(int hum_Field, int hum_Air, int tempCell, bool plantHealth_Field, bool plantHealth_Air)
		: hum_Field{ hum_Field }, hum_Air{ hum_Air }, tempCell{ tempCell }, plantHealth_Field{ plantHealth_Field }, plantHealth_Air{ plantHealth_Air } {

}

AgriField::AgriField(int rows, int cols)
		: rows_{ rows }, cols_{ cols }, field_(rows, std::vector<AgriCell>(cols, AgriCell(50, 50, 20, true, true))) {

}

int Bot::currentID_ = 0;

//Estrazione stampa dati
int Bot::id() const {
	return id_;
}

Bot::Type Bot::type() const {
	return type_;
}

Bot::Status Bot::status() const {
	return status_;
}

int Bot::batteryLevel() const {
	return batteryLevel_;
}

int Bot::humidity() const {
    return humidity_;
}

int Bot::temperature() const {
    return temperature_;
}

bool Bot::plantHealth() const {
	return plantHealth_;
}


void AgriField::showField() const {
	for (int i = 0; i < rows_; ++i) {
		for (int j = 0; j < cols_; ++j) {
			cout << "Cell (" << i << ", " << j << "): "
				<< "Humidity Field: " << field_[i][j].hum_Field << "%, "
				<< "Humidity Air: " << field_[i][j].hum_Air << "%, "
				<< "Temperature: " << field_[i][j].tempCell << "*C, "
				<< "Plant Health Field: " << (field_[i][j].plantHealth_Field ? "Healthy" : "Unhealthy") << ", "
				<< "Plant Health Air: " << (field_[i][j].plantHealth_Air ? "Healthy" : "Unhealthy") << "\n";
		}
		cout << endl;
	}

}

//Aggiunta di membri
void Bot::add_bot(int n, Type type, std::vector<Bot>& bots) {
    for (int i = 0; i < n; ++i) {
        bots.emplace_back(currentID_++, type);
        cout << (type == Type::Rover ? "Rover" : "Drone") << " ID " << bots.back().id() << " added." << endl;
    }
    cout << "\n" << endl;
}

//Gestione dello stato dei bot in base alle attività in corso
void Bot::set_status(Status ActualStatus, int index) {

	if (ActualStatus == Status::Active) {
	}
	else if (ActualStatus == Status::Error) {
		cerr << "Bot ID " << index << " encountered an error." << endl;
	}
	else if (ActualStatus == Status::Homing) {
		if (batteryLevel_ < 10) {
			cerr << "Error: Battery level too low to return home." << endl;
			status_ = Status::Error;
			return;
		}
		batteryLevel_ -= 10; // Simulate battery consumption
	}
    else if (ActualStatus == Status::Moving) {
		if (batteryLevel_ <= 20) {
			cerr << "Error: Battery level too low to move\n" << endl;
			status_ = Status::Homing;
			return;
		}
		batteryLevel_ -= 10; //Consumo batteria
	}
	else if (ActualStatus == Status::Measuring) {
		if (batteryLevel_ <= 15) {
			cerr << "Error: Battery level too low to measure." << endl;
			status_ = Status::Homing;
			return;
		}
		batteryLevel_ -= 10; // Simulate battery consumption
	}	
	status_ = ActualStatus;
}

void Bot::move_to() {
	status_ = Status::Moving;
}

//Stampa dei dati
ostream& operator <<(ostream& os, const Bot& bot) {
    return os   << "ID: " << bot.id() << "\n"
                << "Type: " << (bot.type() == Bot::Type::Rover ? "Rover" : "Drone") << "\n"
                << "Status: " << (bot.status() == Bot::Status::Active ? "Active" :
                    (bot.status() == Bot::Status::Moving ? "Moving" :
                    (bot.status() == Bot::Status::Measuring ? "Measuring" :
                    (bot.status() == Bot::Status::Homing ? "Homing" : "Error")))) << "\n"
                << "Battery Level: " << bot.batteryLevel() << "%\n"
                << "Humidity: " << bot.humidity() << "%\n"
                << "Temperature: " << bot.temperature() << "*C\n"
                << "Plant Health: " << (bot.plantHealth() ? "Healthy" : "Unhealthy") << "\n";

}