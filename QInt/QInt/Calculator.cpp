#include "Calculator.h"

//Khoi tao mac dinh ans = 0
Calculator::Calculator()
{
	ans = new QInt();
	initQIntMenu();
	initQFloatMenu();
	DoiSangHeDec();
}

void Calculator::xuLyFloatInput(string input, string &thapPhan, string &mu)
{
	int i = 0;
	thapPhan.clear();
	mu.clear();
	while (i < input.length() && input[i] != 'E' &&input[i] != 'e') {
		thapPhan.push_back(input[i]);
		i++;
	}
	i++;
	while (i < input.length()) {
		mu.push_back(input[i]);
		i++;
	}
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
	DoiSangHeDec();
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
	QfloatMenu.push_back(Command('N', "Chuyen sang he BIN"));
	QfloatMenu.push_back(Command('T', "Chuyen sang he DEC"));
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
	cout << "Current Using: " << (mode == MODE_QINT ? "QINT" : "QFLOAT") << endl;
	switch (mode)
	{
	case MODE_QINT:
		cout << "Current Numeral System: " << (coSo == BIN ? "BIN" : (coSo == DEC ? "DEC" : "HEX")) << endl;
		printMenu(QintMenu);
		break;
	case MODE_QFLOAT:
		cout << "Current Numeral System: " << (coSo == BIN ? "BIN" : "DEC") << endl;
		printMenu(QfloatMenu);
		break;
	default:
		break;
	}
}

//Xu ly lenh
bool Calculator::handleQIntCommand(string input)
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
			TruInt(soHang);
			break;
		}
		case '*': {
			QInt soHang = nhapSoHangInt();
			NhanInt(soHang);
			break;
		}
		case '/': {
			QInt soHang = nhapSoHangInt();
			ChiaInt(soHang);
			break;
		}
		case 'Q':
		case 'q':
			return true;
		default:
			if (isQIntConvertValid(input)) {
				delete ans;
				ans = new QInt(nhapInt(input));
			}
			break;
		}
		return false;
	}
	else
	{
		if (isQIntConvertValid(input)) {
			delete ans;
			ans = new QInt(nhapInt(input));
		}
		return false;
	}
}

bool Calculator::handleQFloatCommand(string input)
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
		case '+': {
			QFloat soHang = nhapSoHangFloat();
			CongFloat(soHang);
			break;
		}
		case '-': {
			QFloat soHang = nhapSoHangFloat();
			TruFloat(soHang);
			break;
		}
		case '*': {
			QFloat soHang = nhapSoHangFloat();
			NhanFloat(soHang);
			break;
		}
		case '/': {
			QFloat soHang = nhapSoHangFloat();
			ChiaFloat(soHang);
			break;
		}
		case 'Q':
		case 'q':
			return true;
		default:
			if (isQFloatConvertValid(input)) {
				delete ans;
				ans = new QFloat(nhapFloat(input));
			}
			break;
		}
		return false;
	}
	else
	{
		if (isQFloatConvertValid(input)) {
			delete ans;
			ans = new QFloat(nhapFloat(input));
		}
		return false;
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
	{
		if (input.length() < MAX_BITS)
		{
			Error.push_back(ERROR_INVALID_INPUT);
			return false;
		}
		for (int i = 0; i < (int)input.size(); i++)
		{
			if (input[i] != '0' && input[i] != '1')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		}
		break;
	}
	case DEC:
	{
		int dot = 0;
		int E = 0;
		int i = 0;
		int size = input.length();
		if (input[i] == '-') i++;
		for (; i < size; i++)
		{
			if (input[i] == '-')
			{
				if (input[i - 1] == 'E' || input[i - 1] == 'e')
				{
					continue;
				}
				else
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
			}
			if (input[i] == '.')
			{
				dot++;
				if (i == 0 || i == size - 1)
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
				if (input[i - 1]<'0' || input[i - 1]>'9' || input[i + 1]<'0' || input[i + 1]>'9')
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
				if (dot > 1)
					break;
				else
					continue;
			}
			if (input[i] == 'E' || input[i] == 'e')
			{
				E++;
				if (i == 0 || i == size - 1)
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
				if ((input[i - 1]<'0' || input[i - 1]>'9' || input[i + 1]<'0' || input[i + 1]>'9') && input[i + 1] != '-')
				{
					Error.push_back(ERROR_INVALID_INPUT);
					return false;
				}
				if (E > 1)
					break;
				else
					continue;
			}
			if (input[i] < '0' || input[i] > '9')
			{
				Error.push_back(ERROR_INVALID_INPUT);
				return false;
			}
		}
		if (E > 1 || dot > 1)
		{
			Error.push_back(ERROR_INVALID_INPUT);
			return false;
		}
		break;
	}
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
	}
	else {
		return QInt();
	}
}

QFloat Calculator::nhapSoHangFloat() {
	string input2;
	cout << "Input term: ";
	cin >> input2;

	if (isQFloatConvertValid(input2)) {
		string thapPhan;
		string mu;
		if (coSo == DEC) {
			xuLyFloatInput(input2, thapPhan, mu);
		}
		else if (coSo == BIN) {
			thapPhan = input2;
			mu = "";
		}
		return QFloat(coSo, thapPhan, mu);
	}
	else {
		return QFloat();
	}
}

void Calculator::xuatLoi() {
	if (!Error.empty()) {
		for (int i = 0; i < (int)Error.size(); i++)
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
	string thapPhan;
	string mu;
	if (coSo == DEC) {
		xuLyFloatInput(input, thapPhan, mu);
	}
	else if (coSo == BIN) {
		thapPhan = input;
		mu = "";
	}
	return QFloat(coSo, thapPhan, mu);
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
	if (tmp.getCoSo() == -2) {
		Error.push_back(ERROR_DIVIDE_BY_0);
		delete ans;
		ans = new QInt();
	} else if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QInt();
	} else {
		delete ans;
		ans = new QInt(tmp);
	}
}

void Calculator::CongFloat(QFloat soHang) {
	QFloat tmp = *(dynamic_cast<QFloat*>(ans));
	if (Error.empty())
		tmp = tmp + soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QFloat();
	}
	else {
		delete ans;
		ans = new QFloat(tmp);
	}
}

void Calculator::TruFloat(QFloat soHang) {
	QFloat tmp = *(dynamic_cast<QFloat*>(ans));
	if (Error.empty())
		tmp = tmp - soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QFloat();
	}
	else {
		delete ans;
		ans = new QFloat(tmp);
	}
}

void Calculator::NhanFloat(QFloat soHang) {
	QFloat tmp = *(dynamic_cast<QFloat*>(ans));
	if (Error.empty())
		tmp = tmp * soHang;
	if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QFloat();
	}
	else {
		delete ans;
		ans = new QFloat(tmp);
	}
}

void Calculator::ChiaFloat(QFloat soHang) {
	QFloat tmp = *(dynamic_cast<QFloat*>(ans));
	if (Error.empty())
		tmp = tmp / soHang;
	if (tmp.getCoSo() == -3) {
		Error.push_back(ERROR_DIVIDE_BY_0);
		delete ans;
		ans = new QInt();
	} else if (tmp.getCoSo() == -1) {
		Error.push_back(ERROR_BUFFER_OVERFLOW);
		delete ans;
		ans = new QFloat();
	} else {
		delete ans;
		ans = new QFloat(tmp);
	}
}

//Khoi dong may tinh
void Calculator::start()
{
	string command;
	bool exit = false;
	do
	{
		system("cls");
		system("Color FC");
		xuatLoi();
		callMenu();
		cout << "Input Command: ";
		cin >> command;
		if (mode == MODE_QINT)
			exit = handleQIntCommand(command);
		else
			exit = handleQFloatCommand(command);
	} while (!exit);
}

Calculator::Calculator(const Calculator &calc)
{
	coSo = calc.coSo;
	mode = calc.mode;
	QintMenu = calc.QintMenu;
	QfloatMenu = calc.QfloatMenu;
	Error = calc.Error;
	if (mode == MODE_QINT) {
		if (ans != NULL)
			delete ans;
		ans = new QInt(*((QInt*)(calc.ans)));
	}
	else {
		if (ans != NULL)
			delete ans;
		ans = new QFloat(*((QFloat*)(calc.ans)));
	}
}

Calculator& Calculator::operator = (const Calculator& calc)
{
	coSo = calc.coSo;
	mode = calc.mode;
	QintMenu = calc.QintMenu;
	QfloatMenu = calc.QfloatMenu;
	Error = calc.Error;
	if (mode == MODE_QINT) {
		if (ans != NULL)
			delete ans;
		ans = new QInt(*((QInt*)(calc.ans)));
	}
	else {
		if (ans != NULL)
			delete ans;
		ans = new QFloat(*((QFloat*)(calc.ans)));
	}

	return (*this);
}

Calculator::~Calculator()
{
	if (ans != NULL)
		delete ans;
}