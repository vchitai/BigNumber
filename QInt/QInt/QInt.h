#pragma once
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <math.h>
#include <string.h>
#include <string>
#include <vector>
using namespace std;

class QInt
{
private:
	//Mang luu 128 bit trong so lon
	//bit 0: la bit 0 cua data[0]
	//bit 1: la bit 1 cua data[0]
	//bit 7: la bit 7 cua data[0]
	//bit 8: la bit 0 cua data[1]
	//...
	char data[16];

	//mang hang luu tru 2^i
	const static vector<string> luyThua2;

	//coSo luu tru co so dang luu tru
	//2 : co so 2
	//10: co so 10
	//16: co so 16
	int coSo;

private:
	//ham khoi tao luy thua 2
	static const vector <string> khoiTaoLuyThua2();

	//ham so sanh tren he 10, ho tro hai ham cong va tru tren co so 10
	static int cmp(string a, string b);

	//a + b (tinh o he co so 10)
	//Luu y: ca a va b deu phai cung la so nguyen duong
	static string congDec(string a, string b);

	// a - b (tinh o he co so 10)
	//Luu y: ca a va b deu phai cung la so nguyen duong
	static string truDec(string a, string b);

public:
	QInt();
	QInt(const QInt &number);

	//Check xem nguoi dung nhap cac he 2, 10 hay 16, luu tru vao coSo
	//Sau do dung ham tuong ung de chuyen ve he 2.
	//Sau khi chuyen ve he 2, chuyen du lieu bit luu vao data.
	//Luu y: cach bieu dien chuoi nhi phan <string> khac voi cach bieu dien nhi phan trong char data[16]
	//string luu bit cao nhat (bit 127) tai vi tri 0
	//char data[16] luu bit cao nhat (bit 127) o bit thu 7 cua data[15]
	void nhap();

	//Kiem tra so dang o co so nao,
	//Xuat ket qua ra man hinh theo co so tuong ung.
	//Luu y: dung cac ham getBin(), getHex(), getDec() de xuat ra ket qua tuong ung
	void xuat();

	//chuyen tu chuoi nhi phan (2) <bit> sang thap phan (10)
	//Luu y: So co dau, bit dau tien luu dau
	//Ham cong va tru so nguyen lon yeu cau a va b deu la so nguye duong.
	//Nen tinh so mu sau cung.
	string BinToDec(string bin);

	//chuyen tu chuoi nhi phan (2) <bit> sang thap luc phan (16)
	//Search ro hon ve chuyen tu nhi phan sang thap luc phan
	string BinToHex(string bin);

	//chuyen tu chuoi thap phan (10) <dec> sang nhi phan (2)
	//Luu y dau cua so thap phan, chuyen ve chuoi nhi phan chuan
	string DecToBin(string dec);

	//chuyen tu chuoi thap luc phan (16) <hex> sang nhi phan (2)
	string HexToBin(string hex);

	//Lay bit tai vi tri pos
	char getBit(int pos);

	//ham lay bieu dien cua QInt hien tai thanh chuoi nhi phan (2)
	//Luu y: cach bieu dien chuoi nhi phan <string> khac voi cach bieu dien nhi phan trong char data[16]
	//string luu bit cao nhat tai vi tri 0
	//char data[16] luu bit cao nhat o bit thu 7 cua data[15]
	string getBin();

	//ham lay bieu dien cua QInt hien tai thanh chuoi thap phan (10) 
	//Luu y: tan dung ham BinToDec(), goi ham getBin() sau do su dung ham BinToDec
	string getDec();

	//ham lay bieu dien cua QInt hien tai thanh chuoi thap luc phan (16)
	//Luu y: tan dung ham BinToHex(), goi ham getBin() sau do su dung ham BinToHex
	string getHex();

	//Cac ham phep tinh tren QInt (thuc hien tren co so 2)
	QInt operator + (const QInt& number) const;
	QInt operator - (const QInt& number) const;
	QInt operator * (const QInt& number) const;
	QInt operator / (const QInt& number) const;

	QInt& operator = (const QInt& number);

	~QInt();
};

