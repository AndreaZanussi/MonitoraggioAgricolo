#ifndef BOT_H
#define BOT_H
using std::ostream;
using std::string;
using std::vector;

#include <iostream>

struct AgriCell {
	int hum_Field;
	int hum_Air;
	int tempCell;
	bool plantHealth_Field;
	bool plantHealth_Air;

	AgriCell(int hum_Field, int hum_Air, int tempCell, bool plantHealth_Field, bool plantHealth_Air);
	AgriCell() : hum_Field{ 0 }, hum_Air{ 0 }, tempCell{ 0 }, plantHealth_Field{ true }, plantHealth_Air{ true } { }
};

class AgriField {
public:

	AgriField();
	AgriField(int rows, int cols);

	AgriCell& get_cell(int row, int col);
	void show_field() const;

	int rows() const;
	int cols() const;

private:
	int rows_;
	int cols_;
	vector<vector<AgriCell>> field_;

};

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

	static void add_bot(int n, Type type, vector<Bot>& bots);
	void set_status(vector<Bot>& bots, int id);
	void move_to_cell(AgriField& field, vector<Bot>& bots);
	bool check_is_available();
	void check_all_status(vector<Bot>& bots);

	void set_moving();
	void set_measuring();
	void set_homing();
	void set_error();
	void set_active();

	void recharge();

	int id()			const;
	Type type()			const;
	Status status()		const;
	int batteryLevel()	const;
	int humidity()		const;
	int temperature()   const;
	bool plantHealth()  const;

private:
	int		id_;
	Type	type_;
	Status	status_;
	int		batteryLevel_;
	int		humidity_;		//Rover: hum suolo; Drone: hum aria
	int		temperature_;
	bool	plantHealth_;	//Rover: stato pianta fusto; Drone: stato pianta foglie

	static int currentID_;

};

//Operatori
ostream& operator<<(ostream& os, const Bot& bot);

#endif