#include "Calculator.h"

//Khoi tao mac dinh ans = 0
Calculator::Calculator()
{
	ans = new QInt();
	initQIntMenu();
	initQFloatMenu();
}

//Chuyen che do
void Calculator::changeMode() {
	mode = 1 - mode;
	if (ans != NULL)
		delete ans;
	if (mode)
		ans = new QFloat();
	else
		ans = new QInt();
}

//Khoi tao menu
void Calculator::initQIntMenu() {
	if (QintMenu.size() > 0)
		return;
	QintMenu.push_back(Command('S', "Chuyen sang QFloat"));
	QintMenu.push_back(Command('N', "Chuyen sang he BIN"));
	QintMenu.push_back(Command('H', "Chuyen sang he HEX"));
	QintMenu.push_back(Command('T', "Chuyen sang he DEC"));
	QintMenu.push_back(Command('+', "Cong"));
	QintMenu.push_back(Command('-', "Tru"));
	QintMenu.push_back(Command('*', "Nhan"));
	QintMenu.push_back(Command('/', "Chia"));
	QintMenu.push_back(Command('Q', "Thoat"));
}

void Calculator::initQFloatMenu() {
	if (QfloatMenu.size() > 0)
		return;
	QfloatMenu.push_back(Command('S', "Chuyen sang QInt"));
	QfloatMenu.push_back(Command('+', "Cong"));
	QfloatMenu.push_back(Command('-', "Tru"));
	QfloatMenu.push_back(Command('*', "Nhan"));
	QfloatMenu.push_back(Command('/', "Chia"));
	QfloatMenu.push_back(Command('Q', "Thoat"));
}

//In Menu
void Calculator::printMenu(vector<Command> cm) {
	for (int i = 0; i < (int)cm.size(); i++)
		cout << "\t" << cm[i].commandId << ". " << cm[i].description << endl;
}

void Calculator::callMenu() {
	cout << "\t" << xuatAns() << endl;
	switch (mode)
	{
	case MODE_QINT:
		cout << "Current Numeral System: " << (coSo == BIN ? "BIN" : (coSo == DEC ? "DEC" : "HEX")) << endl;
		printMenu(QintMenu);
		break;
	case MODE_QFLOAT:
		printMenu(QfloatMenu);
		break;
	default:
		break;
	}
}

//Xu ly lenh
int Calculator::handleQIntCommand(string input) 
{
	if (input.size() == 1)
	{
		switch (input[0])
		{
		case 'S':
		case 's':
			changeMode();
			break;
		case 'T':
		case 't':
			DoiSangHeDec();
			break;
		case 'N':
		case 'n':
			DoiSangHeBin();
			break;
		case 'H':
		case 'h':
			DoiSangHeHex();
			break;
		case '+': {
			QInt soHang = nhapSoHangInt();
			CongInt(soHang);
			break;
		}
		case '-': {
			QInt soHang = nhapSoHangInt();
			CongInt(soHang);
			break;
		}
		case '*': {
			QInt soHang = nhapSoHangInt();
			CongInt(soHang);
			break;
		}
		case '/': {
			QInt soHang = nhapSoHangInt();
			CongInt(soHang);
			break;
		}
		case 'Q':
		case 'q':
			return -1;
		default:
			if (isQIntConvertValid(input)) {
				delete ans;
				ans = new QInt(nhapInt(input));
			}
			break;
		}
		return 0;
	}
	else
	{
		if (isQIntConvertValid(input)) {
			delete ans;
			ans = new QInt(nhapInt(input));
		}
		return 0;
	}
}

int Calculator::handleQFloatCommand(string input)
{
	if (input.size() == 1)
	{
		switch (input[0])
		{
		case 'S':
		case 's':
			changeMode();
			break;
		case '+': {
			QFloat soHang = nhapSoHangFloat();
			CongFloat(soHang);
			break;
		}
		case '-': {
			QFloat soHang = nhapSoHangFloat();
			CongFloat(soHang);
			break;
		}
		case '*': {
			QFloat soHang = nhapSoHangFloat();
			CongFloat(soHang);
			break;
		}
		case '/': {
			QFloat soHang = nhapSoHangFloat();
			CongFloat(soHang);
			break;
		}
		case 'Q':
		case 'q':
			return -1;
		default:
			if (isQFloatConvertValid(input))
				delete ans;
				ans = new QFloat(nhapFloat(input));
			break;
		}
		return 0;
	}
	else
	{
		if (isQFloatConvertValid(input))
			delete ans;
			ans = new QFloat(nhapFloat(input));
		return 0;
	}
}

bool Calculator::isQIntConvertValid(string input) {
	switch (coSo)
	{
	case BIN:
		for (int i = 0; i < (int)input.size(); i++)
			if (input[i] != '0' && input[i] != '1')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		break;
	case DEC:
	{
		int i = 0;
		if (input[i] == '-')
			i++;
		for (; i < (int)input.size(); i++)
			if (input[i] < '0' || input[i] > '9')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		break;
	}
	case HEX:
		for (int i = 0; i < (int)input.size(); i++)
			if ((input[i] < '0' || input[i] > '9') && (input[i] < 'A' || input[i] > 'F') && (input[i] < 'a' || input[i] > 'f'))
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		break;
	default:
		Error.push_back(ERROR_INVALID_INPUT);
		return false;
		break;
	}
	return true;
}

bool Calculator::isQFloatConvertValid(string input) {
	switch (coSo)
	{
	case BIN:
		for (int i = 0; i < (int)input.size(); i++)
			if (input[i] != '0' && input[i] != '1')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		break;
	case DEC:
	{
		int i = 0;
		if (input[i] == '-')
			i++;
		for (; i < (int)input.size(); i++)
			if (input[i] < '0' || input[i] > '9')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		break;
	}
	case HEX:
		for (int i = 0; i < (int)input.size(); i++)
			if ((input[i] < '0' || input[i] > '9') && (input[i] < 'A' || input[i] > 'F') && (input[i] < 'a' || input[i] > 'f'))
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		break;
	default:
		Error.push_back(ERROR_INVALID_INPUT);
		return false;
		break;
	}
	return true;
}

QInt Calculator::nhapSoHangInt() {
	string input2;
	cout << "Input term: ";
	cin >> input2;

	if (isQIntConvertValid(input2)) {
		return QInt(coSo, input2);
	} else {
		return QInt();
	}
}

QFloat Calculator::nhapSoHangFloat() {
	string input2;
	cout << "Input term: ";
	cin >> input2;

	if (isQFloatConvertValid(input2)) {
		return QFloat();
	}
	else {
		return QFloat();
	}
}

void Calculator::xuatLoi() {
	if (!Error.empty()) {
		for (int i = 0; i<(int)Error.size(); i++)
			switch (Error[i])
			{
			case ERROR_INVALID_INPUT:
				cout << "Invalid Input" << endl;
				break;
			case ERROR_DIVIDE_BY_0:
				cout << "Division by 0" << endl;
				break;
			case ERROR_BUFFER_OVERFLOW:
				cout << "Buffer Overflow" << endl;
				break;
			default:
				break;
			}
	}
	Error.clear();
}

string Calculator::xuatAns() {
	return ans->getValue();
}

//Goi QInt.Nhap(), trong QInt.Nhap() co chon he so
QInt Calculator::nhapInt(string input)
{
	return QInt(coSo, input);
}

QFloat Calculator::nhapFloat(string input) {
	return QFloat();
}

//Cac Ham DoiSangHeSo() doi coSo trong QInt
void Calculator::DoiSangHeBin()
{
	coSo = BIN;
	ans->setCoSo(coSo);
}


void Calculator::DoiSangHeDec()
{
	coSo = DEC;
	ans->setCoSo(coSo);
}


void Calculator::DoiSangHeHex()
{
	coSo = HEX;
	ans->setCoSo(coSo);
}


//Cac Ham tinh toan yeu cau:
//	nhap vao mot doi so
//	tinh kq
//	ans <- kq
void Calculator::CongInt(QInt soHang)
{
	QInt tmp = *(dynamic_cast<QInt*>(ans));
	if (Error.empty())
		tmp = tmp + soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QInt();
	}
	else {
		delete ans;
		ans = new QInt(tmp);
	}
}


void Calculator::TruInt(QInt soHang)
{
	QInt tmp = *(dynamic_cast<QInt*>(ans));
	if (Error.empty())
		tmp = tmp - soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QInt();
	}
	else {
		delete ans;
		ans = new QInt(tmp);
	}
}


void Calculator::NhanInt(QInt soHang)
{
	QInt tmp = *(dynamic_cast<QInt*>(ans));
	if (Error.empty())
		tmp = tmp * soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QInt();
	}
	else {
		delete ans;
		ans = new QInt(tmp);
	}
}


void Calculator::ChiaInt(QInt soHang)
{
	QInt tmp = *(dynamic_cast<QInt*>(ans));
	if (Error.empty())
		tmp = tmp / soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QInt();
	}
	else {
		delete ans;
		ans = new QInt(tmp);
	}
}

void Calculator::CongFloat(QFloat soHang) {

}
void Calculator::TruFloat(QFloat soHang) {

}
void Calculator::NhanFloat(QFloat soHang) {

}
void Calculator::ChiaFloat(QFloat soHang) {

}

int Calculator::getCoSo()
{
	return coSo;
}
