#include "QNumber.h"

QNumber::QNumber()
{
}

//ham so sanh tren he 10, ho tro hai ham cong va tru tren co so 10
int QNumber::cmp(string a, string b)
{
	if (a[0] == '-' && b[0] == '-') {
		a.erase(0, 1);
		b.erase(0, 1);
		return -cmp(a, b);
	}

	if (a[0] == '-') {
		return -1;
	}

	if (b[0] == '-') {
		return 1;
	}

	while (a.size() < b.size()) a = '0' + a;
	while (b.size() < a.size()) b = '0' + b;
	return (a == b ? 0 : (a > b ? 1 : -1));
}

//a + b (tinh o he co so 10)
//Luu y: ca a va b deu phai cung la so nguyen duong
string QNumber::congDec(string a, string b)
{
	if (a[0] == '-' && b[0] == '-') {
		a.erase(0, 1);
		b.erase(0, 1);
		return truDec("0", congDec(a, b));
	}

	if (a[0] == '-') {
		a.erase(0, 1);
		return truDec(b, a);
	}

	if (b[0] == '-') {
		b.erase(0, 1);
		return truDec(a, b);
	}

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
string QNumber::truDec(string a, string b)
{
	if (a[0] == '-' && b[0] == '-') {
		a.erase(0, 1);
		b.erase(0, 1);
		return truDec(b, a);
	}

	if (a[0] == '-') {
		a.erase(0, 1);
		return truDec("0", congDec(a, b));
	}

	if (b[0] == '-') {
		b.erase(0, 1);
		return congDec(a, b);
	}

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

//gan bit tai vi tri pos = value
void QNumber::ganBit(int pos, int value)
{
	int i = pos / 8;
	int j = pos % 8;

	data[i] &= ~(1 << j);
	data[i] |= (value << j);
}

void QNumber::setCoSo(int so) {
	coSo = so;
}

int QNumber::getCoSo() {
	return coSo;
}

QNumber::~QNumber()
{
}

string toString(int dec) {
	string res;
	bool dau = false;
	if (dec < 0) {
		dec = -dec;
		dau = true;
	}

	while (dec > 0) {
		res.push_back('0' + dec % 10);
		dec = dec / 10;
	}

	string res2;
	for (int i = res.length() - 1; i >= 0; i--)
		res2.push_back(res[i]);

	if (dau) {
		res2 = "-" + res2;
	}

	return res2;
}

int valueOf(string s) {
	int res = 0;
	for (int i = 0; i < s.length(); i++) {
		if (s[i] < '0' || s[i] > '9')
			return -1;
		else {
			res *= 10;
			res += s[i] - '0';
		}
	}
	return res;
}