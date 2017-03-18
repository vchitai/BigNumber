#include <iostream>
#include <stdlib.h>
#include "Calculator.h"

void Calculator_Start()
{
	Calculator calculator;
	string command = "";
	int exit = 0;
	calculator.DoiSangHeDec();

	do
	{
		system("cls");
		system("Color FC");
		calculator.xuatLoi();
		calculator.callMenu();
		cout << "Input Command: ";
		cin >> command;
		exit = calculator.handleQIntCommand(command);
	} while (exit == 0);

}