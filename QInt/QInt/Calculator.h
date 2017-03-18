#pragma once
#include "QFloat.h"

#define DEFAULT_MODE 0
#define DEFAULT_NUMERAL 10

#define MODE_QINT 0
#define MODE_QFLOAT 1

#define ERROR_INVALID_INPUT 101
#define ERROR_DIVIDE_BY_0 102
#define ERROR_BUFFER_OVERFLOW 103

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
	QNumber *ans;
	//Mode : 0 - QInt, 1 - QFloat, Default = 0
	int mode = DEFAULT_MODE;
	//CoSo : 2 - BIN, 10 - DEC, 16 - HEX, DEFAULT = 10
	int coSo = DEFAULT_NUMERAL;
	//Menu
	vector<Command> QintMenu;
	vector<Command> QfloatMenu;
	//Bao loi
	vector<int> Error;
public:
	//Khoi tao mac dinh ans = 0
	Calculator();

	//Chuyen che do
	void changeMode();

	//Khoi tao menu
	void initQIntMenu();
	void initQFloatMenu();

	//In Menu
	void printMenu(vector<Command> cm);
	void callMenu();

	//Xu ly lenh
	int handleQIntCommand(string input);
	int handleQFloatCommand(string input);

	//Kiem tra du lieu nhap
	bool isQIntConvertValid(string input);
	bool isQFloatConvertValid(string input);

	//Bao Loi
	void xuatLoi();

	//Xu ly xuat Ans
	string xuatAns();
	//Xu ly nhap so hang
	QInt nhapSoHangInt();
	QFloat nhapSoHangFloat();

	//Nhap QInt
	QInt nhapInt(string input);

	//Nhap QFloat
	QFloat nhapFloat(string input);

	//Cac Ham DoiSangHeSo() doi coSo cua ans
	void DoiSangHeBin();
	void DoiSangHeDec();
	void DoiSangHeHex();

	//Cac Ham tinh toan:
	//	nhap vao mot doi so
	//	tinh kq
	//	ans <- kq
	void CongInt(QInt soHang);
	void TruInt(QInt soHang);
	void NhanInt(QInt soHang);
	void ChiaInt(QInt soHang);
	void CongFloat(QFloat soHang);
	void TruFloat(QFloat soHang);
	void NhanFloat(QFloat soHang);
	void ChiaFloat(QFloat soHang);

	//Lay Co So
	int getCoSo();
};

void Calculator_Start();