#pragma once

#include "QFloat.h"
#include <fstream>
#include <iostream>
#include <stdlib.h>

#define DEFAULT_MODE 0
#define DEFAULT_NUMERAL 10

#define MODE_QINT 0
#define MODE_QFLOAT 1

#define ERROR_INVALID_INPUT 101
#define ERROR_DIVIDE_BY_0 102
#define ERROR_BUFFER_OVERFLOW 103
#define ERROR_CANT_OPEN_FILE_INPUT 104
#define ERROR_CANT_OPEN_FILE_OUTPUT 105

#define FILE_IN "INPUT.TXT"
#define FILE_OUT "OUTPUT.TXT"

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
protected:
	//Chuyen che do
	void changeMode();

	//Khoi tao menu
	void initQIntMenu();
	void initQFloatMenu();

	//In menu
	void printMenu(vector<Command> cm);

	//Kiem tra du lieu nhap
	bool isQIntConvertValid(string input);
	bool isQFloatConvertValid(string input);

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

	//In Menu
	void callMenu();

	//Xu ly lenh
	bool handleQIntCommand(string input);
	bool handleQFloatCommand(string input);

	//Xu ly lenh tu file
	void handleFile(ifstream& ifile, ofstream& ofile);
	void handleQIntFile();
	void handleQFloatFile();

	//Bao Loi
	void xuatLoi();

	//Xu ly xuat Ans
	string xuatAns();

	//Tach chuoi lay phan mu va phan thap phan cua QFloat
	void xuLyFloatInput(string input, string &thapPhan, string &mu);
public:
	//Khoi tao mac dinh ans = 0
	Calculator();

	//Khoi tao sao chep va sao chep
	Calculator(const Calculator &calc);
	Calculator& operator = (const Calculator& calc);

	//Khoi dong may tinh
	void start();

	//Huy
	~Calculator();
};