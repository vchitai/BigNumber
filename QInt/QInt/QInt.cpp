#include "QInt.h"

const vector <string> QInt::khoiTaoLuyThua2() {
	vector <string> res;
	res.clear();

	res.push_back("1");
	for (int i = 1; i < MAX_BITS; ++i) {
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

//gan bit tai vi tri pos = value
void QInt::ganBit(int pos, int value)
{
	int i = pos / 8;
	int j = pos % 8;

	data[i] &= ~(1 << j);
	data[i] |= (value << j);
}

QInt::QInt()
{
	for (int i = 0; i < 16; ++i)
		data[i] = 0;
	coSo = DEC;
}

QInt::QInt(int so, string input) {
	string realValue;
	setCoSo(so);

	switch (coSo)
	{
	case BIN: realValue = NormalizeBin(input); break;
	case DEC: realValue = DecToBin(input); break;
	case HEX: realValue = NormalizeBin(HexToBin(input)); break;
	default: break;
	}

	if (realValue.size() != 0) {
		for (int i = 0; i < realValue.size(); i++)
			if (realValue[127 - i] == '1')
				ganBit(i, 1);
			else
				ganBit(i, 0);
	}

}

//Check xem nguoi dung nhap cac he 2, 10 hay 16, luu tru vao coSo
//Sau do dung ham tuong ung de chuyen ve he 2.
//Sau khi chuyen ve he 2, chuyen du lieu bit luu vao data.
//Luu y: cach bieu dien chuoi nhi phan <string> khac voi cach bieu dien nhi phan trong char data[16]
//string luu bit cao nhat (bit 127) tai vi tri 0
//char data[16] luu bit cao nhat (bit 127) o bit thu 7 cua data[15]
QInt::QInt(const QInt & number)
{
	for (int i = 0; i < 16; ++i)
		data[i] = number.data[i];
	coSo = number.coSo;
}

//chuyen tu chuoi nhi phan (2) <bit> sang thap phan (10)
//Luu y: So co dau, bit dau tien luu dau
//Ham cong va tru so nguyen lon yeu cau a va b deu la so nguye duong.
//Nen tinh so mu sau cung.
string QInt::BinToDec(string bin)
{
	string kq = "0";
	for (int i = 127; i >= 0; i--)
		if (bin[i] == '1')
			kq = congDec(kq, luyThua2[127 - i]);
	if (bin[0] == '1')
		kq = truDec(kq, luyThua2[127]);
	return kq;
}

//chuyen tu chuoi nhi phan (2) <bit> sang thap luc phan (16)
//Search ro hon ve chuyen tu nhi phan sang thap luc phan
string QInt::BinToHex(string bin)
{
	string binary[16] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000", "1001", "1010", "1011", "1100", "1101", "1110", "1111" };
	string kq = "";
	string t = "";

	for (int i = 0; i <32; i++)
	{
		t = "";
		for (int k = 0; k < 4; k++)
			t += bin[i * 4 + k];
		int j = 0;
		for (j = 0; j < 16; j++)
			if (t == binary[j])
				break;
		if (j < 10)
			kq += j + '0';
		else kq += j % 10 + 'A';
	}

	return kq;
}

//chuyen tu chuoi thap phan (10) <dec> sang nhi phan (2)
//Luu y dau cua so thap phan, chuyen ve chuoi nhi phan chuan
string QInt::DecToBin(string dec)
{
	string bin = "";
	for (int i = luyThua2.size() - 1; i >= 0; i--) {
		if (cmp(dec, luyThua2[i]) != -1) {
			dec = truDec(dec, luyThua2[i]);
			bin.append("1");
		}
		else {
			bin.append("0");
		}
	}
	return bin;
}

//chuyen tu chuoi thap luc phan (16) <hex> sang nhi phan (2)
string QInt::HexToBin(string hex)
{
	string bin = "";
	for (int i = 0; i < hex.length(); ++i) {
		switch (hex[i]) {
		case '0': bin.append("0000"); break;
		case '1': bin.append("0001"); break;
		case '2': bin.append("0010"); break;
		case '3': bin.append("0011"); break;
		case '4': bin.append("0100"); break;
		case '5': bin.append("0101"); break;
		case '6': bin.append("0110"); break;
		case '7': bin.append("0111"); break;
		case '8': bin.append("1000"); break;
		case '9': bin.append("1001"); break;
		case 'a':
		case 'A': bin.append("1010"); break;
		case 'b':
		case 'B': bin.append("1011"); break;
		case 'c':
		case 'C': bin.append("1100"); break;
		case 'd':
		case 'D': bin.append("1101"); break;
		case 'e':
		case 'E': bin.append("1110"); break;
		case 'f':
		case 'F': bin.append("1111"); break;
		}
	}
	return bin;
}

//chuan hoa BIN
string QInt::NormalizeBin(string bin) {
	string res = "";
	for (int i = 0; i < MAX_BITS; i++)
		res.append("0");
	int resSize = res.size();
	int binSize = bin.size();
	for (int i = 0; i < binSize; i++)
		res[resSize - binSize + i] = bin[i];

	return res;
}

//Lay bit tai vi tri pos
char QInt::getBit(int pos) const
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
	string kq = "";
	for (int i = 0; i < 128; i++)
		kq += (getBit(127 - i) + '0');
	return kq;
}

//ham lay bieu dien cua QInt hien tai thanh chuoi thap phan (10) 
//Luu y: tan dung ham BinToDec(), goi ham getBin() sau do su dung ham BinToDec
string QInt::getDec()
{
	return BinToDec(getBin());
}

//ham lay bieu dien cua QInt hien tai thanh chuoi thap luc phan (16)
//Luu y: tan dung ham BinToHex(), goi ham getBin() sau do su dung ham BinToHex
string QInt::getHex()
{
	return BinToHex(getBin());
}

//lay so bu 2
QInt QInt::layBu2() const
{
	QInt res;
	res.coSo = this->coSo;

	for (int i = 0; i < 16; ++i)
		res.data[i] = ~data[i];

	int p = 0;
	while (p < 16 && res.data[p] == -1) {
		res.data[p] = 0;
		p = p + 1;
	}

	if (p < 16) res.data[p] = res.data[p] + 1;

	return res;
}

//thuc hien phep dich bit qua trai
QInt QInt::shiftLeft() const
{
	QInt res = *this;

	int preBit = 0;
	for (int i = 0; i < 16; ++i) {
		int current_bit = ((res.data[i] >> 7) & 1);
		res.data[i] <<= 1;
		res.data[i] |= preBit;
		preBit = current_bit;
	}
	res.ganBit(127, preBit);

	return res;
}

//thuc hien phep dich bit qua phai
QInt QInt::shiftRight() const
{
	QInt res = *this;

	int preBit = res.getBit(127);
	for (int i = 15; i >= 0; --i) {
		int current_bit = (res.data[i] & 1);
		res.data[i] >>= 1;
		res.data[i] &= ~(1 << 7);
		res.data[i] |= (preBit << 7);
		preBit = current_bit;
	}
	
	return res;
}

QInt QInt::operator+(const QInt & number) const
{
	QInt ketQua;
	ketQua.coSo = number.coSo;

	int carry = 0, pre_carry = 0;
	for (int i = 0; i < 128; ++i) {
		int sum = this->getBit(i) + number.getBit(i) + carry;
		pre_carry = carry;
		carry = (sum / 2);
		ketQua.ganBit(i, sum % 2);
	}

	if (carry != pre_carry)
		ketQua.coSo = -1;

	return ketQua;
}

QInt QInt::operator-(const QInt & number) const
{
	return (*this + number.layBu2());
}

QInt QInt::operator*(const QInt & number) const
{
	QInt a;
	int pre_q = 0;
	QInt m = number;
	QInt q = *this;

	for (int i = 128; i > 0; --i) {
		int q0 = q.getBit(0);
		if (pre_q != q0)
			a = (pre_q == 0 ? a - m : a + m);

		int last_bit = a.getBit(0);
		a = a.shiftRight();
		q = q.shiftRight();
		q.ganBit(127, last_bit);
		pre_q = q0;
	}

	int number_bit_0 = 0;
	for (int i = 0; i < 128; ++i)
		number_bit_0 += (1 - a.getBit(i));

	if (number_bit_0 != 0 && number_bit_0 != 128) {
		q.coSo = -1;
		return q;
	}

	if (number_bit_0 == 0) {
		q = q.layBu2();
		if (q.getBit(127) == 1) {
			q.coSo = -1;
			return q;
		}
		else
			return q.layBu2();
	}

	if (number_bit_0 == 128) {
		if (q.getBit(127) == 0)
			return q;
		else {
			q.coSo = -1;
			return q;
		}
	}

	return q;
}

QInt QInt::operator/(const QInt & number) const
{
	int sign_a = this->getBit(127);
	int sign_b = number.getBit(127);

	QInt q = *this;
	QInt m = number;
	QInt a;

	if (sign_a) 
		q = q.layBu2();
	if (sign_b)
		m = m.layBu2();

	for (int i = 128; i > 0; --i) {
		int mb = q.getBit(127);
		a = a.shiftLeft();
		q = q.shiftLeft();
		a.ganBit(0, mb);

		a = a - m;
		if (a.getBit(127) == 1) {
			a = a + m;
			q.ganBit(0, 0);
		}
		else
			q.ganBit(0, 1);
	}

	if (sign_a != sign_b)
		q = q.layBu2();

	return q;
}

QInt & QInt::operator=(const QInt & number)
{
	for (int i = 0; i < 16; ++i)
		data[i] = number.data[i];
	coSo = number.coSo;
	return *this;
}

void QInt::setCoSo(int so)
{
	coSo = so;
}

int QInt::getCoSo() {
	return coSo;
}

QInt::~QInt()
{
}