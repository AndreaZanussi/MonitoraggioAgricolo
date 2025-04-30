#include <ostream>
using std::ostream;
#include <iostream>
using std::cerr;
using std::endl;

using std::cout;
#include <vector>
#include "Bot.h"



//Costruttore di default
Bot::Bot() {}

//Costruttore con parametri di default
Bot::Bot(int id, Type type)
    : id_{ id }, type_{ type }, status_{ Status::Active }, active_{ true }, moving_{ false }, measuring_{ false },
    homing_{ false }, error_{ false }, batteryLevel_{ 100 }, humidity_{ 0 }, temperature_{ 0 }, plantHealth_{ true } {
    
}

int Bot::currentID_ = 0;

//estrazione stampa dati
int Bot::id() const {
	return id_;
}
/*
Bot::Type Bot::type() const {
	return type_;
}

Bot::Status Bot::status() {
	return status_;
}

int Bot::batteryLevel() {
	return batteryLevel_;
}

int Bot::humidity() {
    return humidity_;
}

int Bot::temperature() {
    return temperature_;
}

bool Bot::plantHealth() {
	return plantHealth_;
}*/

void Bot::add_rover(int n, std::vector<Bot>& bots) {
    for (int i = 0; i < n; ++i) {
        bots.emplace_back(i, Type::Rover);
        cout << "Rover ID " << bots.size() << " added." << endl;
    }
    cout << "\n" << endl;
}

void Bot::add_drone(int n, std::vector<Bot>& bots) {
    for (int i = 0; i < n; ++i) {
        bots.emplace_back(i, Type::Drone);
        cout << "Drone ID " << bots.size() << " added." << endl;
    }
    cout << "\n" << endl;
}


ostream& operator <<(ostream& os, const Bot& bot) {
    return os << "ID: " << bot.id() << "\n";
 //               << "Type: " << (bot.type() == Bot::Type::Rover ? "Rover" : "Drone") << "\n"
 //               << "Status: " << (bot.status() == Bot::Status::Active ? "Active" : (bot.status() == Bot::Status::Moving ? "Moving" : (bot.status() == Bot::Status::Measuring ? "Measuring" : (bot.status() == Bot::Status::Homing ? "Homing" : "Error")))) << "\n"
 //               << "Battery Level: " << bot.batteryLevel() << "%\n"
 //               << "Humidity: " << bot.humidity() << "%\n"
 //               << "Temperature: " << bot.temperature() << "°C\n"
 //               << "Plant Health: " << (bot.plantHealth() ? "Healthy" : "Unhealthy") << "\n";

}