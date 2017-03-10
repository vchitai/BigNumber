#pragma once
#include "QInt.h"

#define MAIN_MENU 1
#define QINT_MENU 3
#define QFLOAT_MENU 5

#define ERROR_1 101

struct Command {
	char commandId;
	string description;
	
	Command(char id, string desc) {
		commandId = id;
		description = desc;
	}
};

class Calculator
{
private:
	//Calculator luu 1 ket qua thuc hien truoc, default = 0
	QInt ans;
	//Mode : 1 - QInt, 2 - QFloat, default = 1
	int mode = 1;
	//CoSo : 2 - BIN, 10 - DEC, 16 - HEX
	int coSo = DEC;
	//Menu
	vector<Command> mainMenu;
	vector<Command> QintMenu;
	vector<Command> QfloatMenu;
	//Bao loi
	vector<int> Error;
public:
	//Khoi tao mac dinh ans = 0
	Calculator();

	//Khoi tao menu
	void initMainMenu();
	void initQIntMenu();
	void initQFloatMenu();

	//In Menu
	void printMenu(vector<Command>);
	void callMenu(int);

	//Xu ly lenh
	int handleQIntCommand(string input);

	//Kiem tra du lieu nhap
	bool isNhapOk(string input);

	//Bao Loi
	void xuatLoi();

	//Xu ly xuat Ans
	string xuatAns();
	//Xu ly nhap so hang 2
	QInt nhapSoHang2();

	//Nhap QInt
	QInt nhapInt(string input);
	//Xuat QInt
	string xuatInt();

	//Nhap QFloat
	void nhapFloat();
	//Xuat QFloat
	string xuatFloat();

	//Cac Ham DoiSangHeSo() doi coSo cua ans
	void DoiSangHeBin();
	void DoiSangHeDec();
	void DoiSangHeHex();

	//Cac Ham tinh toan:
	//	nhap vao mot doi so
	//	tinh kq
	//	ans <- kq
	void Cong(QInt soHang);
	void Tru(QInt soHang);
	void Nhan(QInt soHang);
	void Chia(QInt soHang);

	//Lay Co So
	int getCoSo();
};

void Calculator_Start();