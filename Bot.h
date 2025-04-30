#ifndef BOT_H
#define BOT_H
using std::ostream;
using std::string;

#include <iostream>

class Bot{
public:
	enum class Status {
		Active, Moving, Measuring, Homing, Error
	};

	enum class Type {
		Rover, Drone
	};

	Bot();
	Bot(int id, Type type);

	static void add_rover(int n, std::vector<Bot>& bots);
	static void add_drone(int n, std::vector<Bot>& bots);

	int id()			const;
/*	Type type()			const;
	Status status()		const;
	int batteryLevel()	const;
	int humidity()		const;
	int temperature()   const;
	bool plantHealth()  const;*/



private:
	int id_;
	Type type_;
	Status status_;
	bool active_;
	bool moving_;
	bool measuring_;
	bool homing_;
	bool error_;

	int batteryLevel_;
	int humidity_;		//Rover: hum suolo; Drone: hum aria
	int temperature_;
	bool plantHealth_;	//Rover: stato pianta fusto; Drone: stato pianta foglie

	static int currentID_;


};

//operators
ostream& operator<<(ostream& os, const Bot& bot);


#endif