#pragma once
#include "QNumber.h"


class QInt: public QNumber
{
private:
	//mang hang luu tru 2^i
	const static vector<string> luyThua2;
private:
	//ham khoi tao luy thua 2
	static const vector <string> khoiTaoLuyThua2();

public:
	QInt();
	QInt(const QInt &number);

	//Check xem nguoi dung nhap cac he 2, 10 hay 16, luu tru vao coSo
	//Sau do dung ham tuong ung de chuyen ve he 2.
	//Sau khi chuyen ve he 2, chuyen du lieu bit luu vao data.
	//Luu y: cach bieu dien chuoi nhi phan <string> khac voi cach bieu dien nhi phan trong char data[16]
	//string luu bit cao nhat (bit 127) tai vi tri 0
	//char data[16] luu bit cao nhat (bit 127) o bit thu 7 cua data[15]
	QInt(int so, string input);

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

	//chuan hoa BIN
	string chuanHoaBin(string bin);

	//Lay bit tai vi tri pos
	char getBit(int pos) const;

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

	//lay gia tri cua QInt hien tai (bieu dien theo coSo hien tai)
	string getValue();

	//lay so bu 2
	QInt layBu2() const;

	//thuc hien phep dich bit qua trai
	QInt shiftLeft() const;

	//thuc hien phep dich bit qua phai
	QInt shiftRight() const;

	//thuc hien phep dich trai d bit
	QInt shiftLeft(int d) const;

	//thuc hien phep dich phai d bit
	QInt shiftRight(int d) const;

	//ham xoay phai
	QInt ror() const;

	//ham xoay trai
	QInt rol() const;

	//chuyen thap phan sang nhi phan nhu de bai yeu cau
	bool* DecToBin(QInt x);

	//chuyen nhi phan sang thap phan nhu de bai yeu cau
	QInt BinToDec(bool *bit);

	//chuyen nhi phan sang thap luc phan nhu de bai yeu cau
	char* BinToHex(bool *bit);

	//chuyen thap phan sang thap luc phan nhu de bai yeu cau
	char* DecToHex(QInt x);

	//Cac ham phep tinh tren QInt (thuc hien tren co so 2)
	QInt operator + (const QInt& number) const;
	QInt operator - (const QInt& number) const;
	QInt operator * (const QInt& number) const;
	QInt operator / (const QInt& number) const;
	QInt operator ~ () const;

	QInt& operator = (const QInt& number);

	string getOutBin(string bin);
	string getOutHex(string bin);

	~QInt();
};

