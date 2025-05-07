#include <ostream>
using std::ostream;
#include <iostream>
using std::cerr;
using std::endl;
using std::cout;
#include <vector>
#include "Bot.h"

const int MAX_BOTS = 100;
const int BATTERY_CONSUMPTION = 10;
const int BATTERY_THRESHOLD = 20;
const int BATTERY_THRESHOLD_HOME = 10;

//////////////GESTIONE DEI BOT//////////////
int Bot::currentID_ = 0;

Bot::Bot() {}

Bot::Bot(int id, Type type)
	: id_{ id }, type_{ type }, status_{ Status::Active }, batteryLevel_{ 100 }, humidity_{ 0 }, temperature_{ 0 }, plantHealth_{ true } {

}
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

//Aggiunta di membri
void Bot::add_bot(int n, Type type, vector<Bot>& bots) {
	if (currentID_ > MAX_BOTS) {
		cerr << "Error: Maximum number of bots reached." << endl;
	}
	else {
		for (int i = 0; i < n; ++i) {
			bots.emplace_back(currentID_++, type);
			cout << (type == Type::Rover ? "Rover" : "Drone") << " ID " << bots.back().id() << " added." << endl;
		}
		cout << "\n" << endl;
	}
}

//Controllo disponibilità del bot
bool Bot::check_is_available() {
	if (status_ == Status::Active) {
		return true;
	}
	else {
		cerr << "Error: Bot ID " << id_ << " is not available." << endl;
		return false;
	}
}

//Controllo dello stato di tutti i bot
void Bot::check_all_status(vector<Bot>& bots) {
	for (int i = 0; i < bots.size(); i++) {
 		if (bots[i].status() == Status::Error) {
 			cout << "Bot " << bots[i].id() << " is damaged!";
		}
 		else if (bots[i].status() == Status::Active) {
 			cout << "Bot " << bots[i].id() << " is available.";
		}
 		else if (bots[i].status() == Status::Moving) {
 			cout << "Bot " << bots[i].id() << " is moving.";
		}
 		else if (bots[i].status() == Status::Measuring) {
 			cout << "Bot " << bots[i].id() << " is measuring.";
		}
 		else if (bots[i].status() == Status::Homing) {
 			cout << "Bot " << bots[i].id() << " is homing.";
		}
 		else {
 			cout << "Bot " << bots[i].id() << " is in an unknown state.";
		}
 		cout << "\n" << endl;
	}
}

//Gestione dello stato dei bot in base alle attività in corso
void Bot::set_status(vector<Bot>& bots, int id) {

	if (bots[id].status() == Status::Active) {
	}
	else if (bots[id].status() == Status::Error) {
		cerr << "Bot ID " << id << " encountered an error." << endl;
	}
	else if (bots[id].status() == Status::Homing) {
		if (batteryLevel_ < BATTERY_THRESHOLD_HOME) {
			cerr << "Error: Battery level too low to return home." << endl;
			bots[id].set_error();
		}
		batteryLevel_ -= BATTERY_CONSUMPTION; // Simulate battery consumption
	}
    else if (bots[id].status() == Status::Moving) {
		if (batteryLevel_ <= BATTERY_THRESHOLD) {
			cerr << "Error: Battery level too low to move\n" << endl;
			bots[id].set_homing();
		}
		batteryLevel_ -= BATTERY_CONSUMPTION; //Consumo batteria
	}
	else if (bots[id].status() == Status::Measuring) {
		if (batteryLevel_ <= BATTERY_THRESHOLD) {
			cerr << "Error: Battery level too low to measure." << endl;
			bots[id].set_homing();
		}
		batteryLevel_ -= BATTERY_CONSUMPTION; // Simulate battery consumption
	}
}

//Gestione all'accesso delle celle
void Bot::move_to_cell(AgriField& field, std::vector<Bot>& bots) {
	
	set_moving();
	set_status(bots, id_);
	cout << "Insert the coordinates of the position: ";
	int row = 0, col = 0;
	std::cin >> row >> col;
	AgriCell& targetCell = field.get_cell(row, col);

	humidity_ = (type_ == Type::Rover) ? targetCell.hum_Field : targetCell.hum_Air;
	temperature_ = targetCell.tempCell;
	plantHealth_ = (type_ == Type::Rover) ? targetCell.plantHealth_Field : targetCell.plantHealth_Air;

	// Cambia stato a Measuring dopo essere arrivato
	set_measuring();
	cout << "Bot ID " << id_ << " moved to cell (" << row << ", " << col << ").\n" << endl;
}

//Impostazione dello stato dei bot
void Bot::set_moving() {
	status_ = Status::Moving;
}

void Bot::set_measuring() {
	status_ = Status::Measuring;
}

void Bot::set_homing() {
	status_ = Status::Homing;
}

void Bot::set_error() {
	status_ = Status::Error;
}

void Bot::set_active() {
	status_ = Status::Active;
}

void Bot::recharge() {
	batteryLevel_ = 100;
	status_ = Status::Active;
}

//////////////GESTIONE DEI CAMPI//////////////
AgriField::AgriField() {}

AgriCell::AgriCell(int hum_Field, int hum_Air, int tempCell, bool plantHealth_Field, bool plantHealth_Air)
	: hum_Field{ hum_Field }, hum_Air{ hum_Air }, tempCell{ tempCell }, plantHealth_Field{ plantHealth_Field }, plantHealth_Air{ plantHealth_Air } {

}

AgriField::AgriField(int rows, int cols)
	: rows_{ rows }, cols_{ cols }, field_(rows, vector<AgriCell>(cols, AgriCell(50, 50, 20, true, true))) {

}

AgriCell& AgriField::get_cell(int row, int col) {
	if (row < 0 || row >= rows_ || col < 0 || col >= cols_) {
		cerr << "Error: Invalid cell coordinates." << endl;
		return field_[0][0]; // Return a default cell in case of error
	}
	else {
		return field_[row][col];
	}
}

void AgriField::show_field() const {
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

int AgriField::rows() const{
	return rows_;
}

int AgriField::cols() const{
	return cols_;
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