#include "QInt.h"

const vector <string> QInt::khoiTaoLuyThua2() {
	vector <string> res;
	res.clear();

	res.push_back("1");
	for (int i = 1; i < 128; ++i) {
		res.push_back(congDec(res[i - 1], res[i - 1]));
	}

	return res;
}

const vector <string> QInt::luyThua2 = QInt::khoiTaoLuyThua2();

//ham so sanh tren he 10, ho tro hai ham cong va tru tren co so 10
int QInt::cmp(string a, string b)
{
	while (a.size() < b.size()) a = '0' + a;
	while (b.size() < a.size()) b = '0' + b;
	return (a == b ? 0 : (a > b ? 1 : -1));
}

//a + b (tinh o he co so 10)
//Luu y: ca a va b deu phai cung la so nguyen duong
string QInt::congDec(string a, string b)
{
	int sum = 0, carry = 0;
	string c = "";
	while (a.size() < b.size()) a = '0' + a;
	while (b.size() < a.size()) b = '0' + b;
	for (int i = a.size() - 1; i >= 0; --i) {
		sum = (a[i] - '0') + (b[i] - '0') + carry;
		carry = sum / 10;
		c = char('0' + sum % 10) + c;
	}
	if (carry > 0) c = '1' + c;
	return c;
}

// a - b (tinh o he co so 10)
//Luu y: ca a va b deu phai cung la so nguyen duong
string QInt::truDec(string a, string b)
{
	int dau = 1;
	if (cmp(a, b) == -1) {
		dau = -1;
		swap(a, b);
	}
	int borrow = 0;
	string c = "";
	while (a.size() < b.size()) a = '0' + a;
	while (b.size() < a.size()) b = '0' + b;
	for (int i = a.size() - 1; i >= 0; --i) {
		int sum = a[i] - b[i] - borrow;
		if (sum < 0) {
			sum = sum + 10;
			borrow = 1;
		}
		else
			borrow = 0;
		c = char(sum + '0') + c;
	}
	
	while (c.size() > 0 && c[0] == '0') {
		c.erase(0, 1);
	}
	if (dau == -1) c = '-' + c;
	return c;
}

QInt::QInt()
{
	for (int i = 0; i < 16; ++i)
		data[i] = 0;
	coSo = 2;
}

QInt::QInt(const QInt & number)
{
	for (int i = 0; i < 16; ++i)
		data[i] = number.data[i];
	coSo = number.coSo;
}

//Check xem nguoi dung nhap cac he 2, 10 hay 16, luu tru vao coSo
//Sau do dung ham tuong ung de chuyen ve he 2.
//Sau khi chuyen ve he 2, chuyen du lieu bit luu vao data.
//Luu y: cach bieu dien chuoi nhi phan <string> khac voi cach bieu dien nhi phan trong char data[16]
//string luu bit cao nhat (bit 127) tai vi tri 0
//char data[16] luu bit cao nhat (bit 127) o bit thu 7 cua data[15]
void QInt::nhap()
{	
}

//Kiem tra so dang o co so nao,
//Xuat ket qua ra man hinh theo co so tuong ung.
//Luu y: dung cac ham getBin(), getHex(), getDec() de xuat ra ket qua tuong ung
void QInt::xuat()
{
}

//chuyen tu chuoi nhi phan (2) <bit> sang thap phan (10)
//Luu y: So co dau, bit dau tien luu dau
//Ham cong va tru so nguyen lon yeu cau a va b deu la so nguye duong.
//Nen tinh so mu sau cung.
string QInt::BinToDec(string bin)
{
	return string();
}

//chuyen tu chuoi nhi phan (2) <bit> sang thap luc phan (16)
//Search ro hon ve chuyen tu nhi phan sang thap luc phan
string QInt::BinToHex(string bin)
{
	return string();
}

//chuyen tu chuoi thap phan (10) <dec> sang nhi phan (2)
//Luu y dau cua so thap phan, chuyen ve chuoi nhi phan chuan
string QInt::DecToBin(string dec)
{
	return string();
}

//chuyen tu chuoi thap luc phan (16) <hex> sang nhi phan (2)
string QInt::HexToBin(string hex)
{
	return string();
}

//Lay bit tai vi tri pos
char QInt::getBit(int pos)
{
	int i = pos / 8;
	int j = pos % 8;
	return ((data[i] >> j) & 1);
}

//ham lay bieu dien cua QInt hien tai thanh chuoi nhi phan (2)
//Luu y: cach bieu dien chuoi nhi phan <string> khac voi cach bieu dien nhi phan trong char data[16]
//string luu bit cao nhat tai vi tri 0
//char data[16] luu bit cao nhat o bit thu 7 cua data[15]
string QInt::getBin()
{
	return string();
}

//ham lay bieu dien cua QInt hien tai thanh chuoi thap phan (10) 
//Luu y: tan dung ham BinToDec(), goi ham getBin() sau do su dung ham BinToDec
string QInt::getDec()
{
	return string();
}

//ham lay bieu dien cua QInt hien tai thanh chuoi thap luc phan (16)
//Luu y: tan dung ham BinToHex(), goi ham getBin() sau do su dung ham BinToHex
string QInt::getHex()
{
	return string();
}

QInt QInt::operator+(const QInt & number) const
{
	return QInt();
}

QInt QInt::operator-(const QInt & number) const
{
	return QInt();
}

QInt QInt::operator*(const QInt & number) const
{
	return QInt();
}

QInt QInt::operator/(const QInt & number) const
{
	return QInt();
}

QInt & QInt::operator=(const QInt & number)
{
	for (int i = 0; i < 16; ++i)
		data[i] = number.data[i];
	coSo = number.coSo;
	return *this;
}

QInt::~QInt()
{
}