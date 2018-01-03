#include "stdafx.h"

#include <windows.h>
#include <iostream>
using namespace std;
#include "lift.h"

Lift::Lift(int n, double h, double v, double tdoors) {
	if (n < 5) this->n = 5;
	else if (n > 20) this->n = 20;
	else this->n = n;

	this->h = h;
	this->v = v;
	this->tdoors = tdoors;

	floor = 1;
	curH = getFloorHeight(floor);
	cout << "Floor = " << floor << endl;
}

Lift::~Lift() {
}

void Lift::run() {
	double sec = getSeconds(), old;
	while (true) {
		old = sec;
		sec = getSeconds();
		double dt = sec - old;

		if (ct != ctNone) {
			if (mode == lmStop || mode == lmRun) {
				mode = lmRun;
				if (ct == ctPress) {
					target = ptarget;
					calcSign();
				}
				ct = ctNone;
			}
		}

		if (mode != lmStop) {
			if (floor == target) {
				if (mode == lmRun) {
					mode = lmOpenDoors;
					saveTdoors = sec;
				}
				else if (mode == lmOpenDoors) {
					double t = getSeconds();
					if (t - saveTdoors >= tdoors) {
						cout << "The door is open" << endl;
						mode = lmCloseDoors;
						saveTdoors = sec;
					}
				}
				else if (mode == lmCloseDoors) {
					double t = sec;
					if (t - saveTdoors >= tdoors) {
						cout << "The door is closed" << endl;
						mode = lmStop;
						if (ct == ctPress) {
							target = ptarget;
							calcSign();
							mode = lmRun;
						}
						ct = ctNone;
					}
				}
			}
			else {
				if (mode == lmRun) {
					curH += v * dt * sign;
					if (sign == 1) {
						if (curH > (floor - 1) * h + h) {
							floor++;
							cout << "Floor = " << floor << endl;
						}
					}
					else if (sign == -1) {
						if (curH < (floor - 1) * h - h) {
							floor--;
							cout << "Floor = " << floor << endl;
						}
					}
				}
			}
		}
		//cout << "run" << endl;
		Sleep(1);
		if (mode == lmStop) break;
	}
}

void Lift::call(int target) {
	if (target < 1 || target > n) return;
	if (mode == lmStop && ct == ctNone) {
		doCmd(ctCall, target);
	}
}

void Lift::press(int target) {
	if (target < 1 || target > n) return;
	doCmd(ctPress, target);
}

void Lift::doCmd(CmdType ct, int target) {
	this->ct = ct;
	if (ct == ctPress) ptarget = target;
	else this->target = target;

	calcSign();

	if (mode == lmStop)	
		thr = new thread(&Lift::run, this);
}

double Lift::getFloorHeight(int floor) {
	return (floor - 1) * h;
}

double Lift::getSeconds() {
	int msec = GetTickCount();
	return ((double)msec) / 1000;
}

void Lift::calcSign() {
	if (this->target > floor) sign = 1;
	else if (this->target < floor) sign = -1;
	else sign = 0;
}