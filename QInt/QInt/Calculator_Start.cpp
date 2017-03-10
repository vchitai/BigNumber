#include <iostream>
#include <stdlib.h>
#include "Calculator.h"

void Calculator_Start()
{
	Calculator cal;
	cal.DoiSangHeDec();
	string command = "";
	int exit = 0;

	do
	{
		system("cls");
		cal.xuatLoi();
		cout << "Calculator\n";
		cout << "\t" << cal.xuatAns() << endl;
		int coSo = cal.getCoSo();
		cout << "Current Numeral System: " << (coSo == BIN? "BIN" : (coSo == DEC? "DEC" : "HEX")) << endl;
		cal.callMenu(QINT_MENU);
		cout << "Input Command: ";
		cin >> command;
		exit = cal.handleQIntCommand(command);
	} while (exit == 0);

}