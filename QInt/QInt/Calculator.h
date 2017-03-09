#pragma once
#include "QInt.h"

class Calculator
{
private:
	//Calculator luu 1 so ans tren man hinh
	QInt ans;
public:
	//Khoi tao mac dinh ans = 0
	Calculator();

	//Goi QInt.Nhap(), trong QInt.Nhap() co chon he so
	void NhapAns();

	//Hien thi so ans theo co so cua no
	void XuatAns();

	//Cac Ham DoiSangHeSo() doi coSo cua ans
	void DoiSangHeBin();
	void DoiSangHeDec();
	void DoiSangHeHex();

	//Cac Ham tinh toan:
	//	nhap vao mot doi so
	//	tinh kq
	//	ans <- kq
	void Cong();
	void Tru();
	void Nhan();
	void Chia();
};

void Calculator_Start();