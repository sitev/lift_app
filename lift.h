#pragma once

#include <thread>

enum LiftMode {lmStop, lmOpenDoors, lmCloseDoors, lmRun};
enum CmdType {ctNone, ctCall, ctPress};

class Lift {
public:
	Lift(int n, double h, double v, double tdoors);
	~Lift();

	void run();
	void call(int target);
	void press(int target);
protected:
	int n;
	double h, v, tdoors;
	double curH, saveTdoors;
	int floor = 1;
	int target, sign, ptarget;
	LiftMode mode = lmStop;
	CmdType ct = ctNone;
	thread *thr;
	void doCmd(CmdType ct, int target);
	double getFloorHeight(int floor);
	double getSeconds();
	void calcSign();
};

