#pragma once
#include "QInt.h"

class Calculator
{
private:
	QInt ans;
public:
	//Khoi tao mac dinh ans = 0
	Calculator();

	//Goi QInt.Nhap(), trong QInt.Nhap() co chon he so
	void NhapAns();

	void XuatAns();

	//Cac Ham DoiSangHeSo() doi coSo trong QInt
	void DoiSangHeBin();
	void DoiSangHeDec();
	void DoiSangHeHex();

	//Cac Ham tinh toan yeu cau:
	//	nhap vao mot doi so
	//	tinh kq
	//	ans <- kq
	void Cong();
	void Tru();
	void Nhan();
	void Chia();

	void Start();
};

void Calculator_main();