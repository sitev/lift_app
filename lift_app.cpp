// lift.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <conio.h>
#include <string>
#include <thread>
using namespace std;

#include "lift.h"

int main(int argc, char* argv[])
{
	if (argc != 5) return -1;
	string sn = argv[1]; // ���-�� ������ � �������� � N(�� 5 �� 20);
	string sh = argv[2]; // ������ ������ �����
	string sv = argv[3]; // �������� ����� ��� �������� � ������ � ������� (���������� ������������, �������, 
						 // ��� ����� ���� ���� � �� ����� ���� � ������������ ���������)
	string st = argv[4]; // ����� ����� ��������� � ��������� ������

	Lift lift(stoi(sn), stod(sh), stod(sv), stod(st));
	//thread thr(&Lift::run, &lift);

	while (true) {
		string cmd;
		cin >> cmd;
		if (cmd[0] == 'p') {
			string sfloor = cmd.substr(1);
			int floor = stoi(sfloor);
			lift.press(floor);
		}
		else if (cmd[0] == 'c') {
			string sfloor = cmd.substr(1);
			int floor = stoi(sfloor);
			lift.call(floor);
		}
	}
	return 0;
}

