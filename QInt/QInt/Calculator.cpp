#include "Calculator.h"

//Khoi tao mac dinh ans = 0
Calculator::Calculator()
{
	ans = QInt();
}


//Goi QInt.Nhap(), trong QInt.Nhap() co chon he so
void Calculator::NhapAns()
{
	ans.nhap();
}


void Calculator::XuatAns()
{
	ans.xuat();
}


//Cac Ham DoiSangHeSo() doi coSo trong QInt
void Calculator::DoiSangHeBin()
{
	ans.SetCoSo(2);
}


void Calculator::DoiSangHeDec()
{
	ans.SetCoSo(10);
}


void Calculator::DoiSangHeHex()
{
	ans.SetCoSo(16);
}


//Cac Ham tinh toan yeu cau:
//	nhap vao mot doi so
//	tinh kq
//	ans <- kq
void Calculator::Cong()
{
	QInt p;
	p.nhap();
	ans = ans + p;
}


void Calculator::Tru()
{
	QInt p;
	p.nhap();
	ans = ans + p;
}


void Calculator::Nhan()
{
	QInt p;
	p.nhap();
	ans = ans * p;
}


void Calculator::Chia()
{
	QInt p;
	p.nhap();
	ans = ans / p;
}

