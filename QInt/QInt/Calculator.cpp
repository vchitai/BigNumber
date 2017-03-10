#include "Calculator.h"

//Khoi tao mac dinh ans = 0
Calculator::Calculator()
{
	ans = QInt();
	initQIntMenu();
}

//Khoi tao menu
void Calculator::initMainMenu() {
	if (mainMenu.size() > 0)
		return;
	mainMenu.push_back(Command('1', "QInt"));
	mainMenu.push_back(Command('2', "QFloat"));
}

void Calculator::initQIntMenu() {
	if (QintMenu.size() > 0)
		return;
	QintMenu.push_back(Command('B', "Chuyen sang he BIN"));
	QintMenu.push_back(Command('H', "Chuyen sang he HEX"));
	QintMenu.push_back(Command('D', "Chuyen sang he DEC"));
	QintMenu.push_back(Command('+', "Cong"));
	QintMenu.push_back(Command('-', "Tru"));
	QintMenu.push_back(Command('*', "Nhan"));
	QintMenu.push_back(Command('/', "Chia"));
	QintMenu.push_back(Command('E', "Thoat"));
}

void Calculator::initQFloatMenu() {
	if (QfloatMenu.size() > 0)
		return;
}

//In Menu
void Calculator::printMenu(vector<Command> cm) {
	for (int i = 0; i < cm.size(); i++)
		cout << "\t" << cm[i].commandId << ". " << cm[i].description << endl;
}

void Calculator::callMenu(int n) {
	switch (n)
	{
	case MAIN_MENU:
		printMenu(mainMenu);
		break;
	case QINT_MENU: 
		printMenu(QintMenu);
		break;
	case QFLOAT_MENU:
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
		case 'D':
		case 'd':
			DoiSangHeDec();
			break;
		case 'B':
		case 'b':
			DoiSangHeBin();
			break;
		case 'H':
		case 'h':
			DoiSangHeHex();
			break;
		case '+': {
			QInt soHang = nhapSoHang2();
			Cong(soHang);
			break;
		}
		case '-': {
			QInt soHang = nhapSoHang2();
			Tru(soHang);
			break;
		}
		case '*': {
			QInt soHang = nhapSoHang2();
			Nhan(soHang);
			break;
		}
		case '/': {
			QInt soHang = nhapSoHang2();
			Chia(soHang);
			break;
		}
		case 'E':
		case 'e':
			return -1;
		default:
			break;
		}
		return 0;
	}
	else
	{
		if (isNhapOk(input))
			ans = nhapInt(input);
		return 0;
	}
}

bool Calculator::isNhapOk(string input) {
	switch (coSo)
	{
	case BIN:
		for (int i = 0; i < input.size(); i++)
			if (input[i] != '0' && input[i] != '1')
				return false;
		break;
	case DEC:
		for (int i = 0; i < input.size(); i++)
			if (input[i] < '0' || input[i] > '9')
				return false;
		break;
	case HEX:
		for (int i = 0; i < input.size(); i++)
			if ((input[i] < '0' || input[i] > '9') && (input[i] < 'A' || input[i] > 'F') && (input[i] < 'a' || input[i] > 'f'))
				return false;
		break;
	default:
		return false;
		break;
	}
	return true;
}

QInt Calculator::nhapSoHang2() {
	string input2;
	cout << "Input term: ";
	cin >> input2;

	if (isNhapOk(input2)) {
		return QInt(coSo, input2);
	} else {
		Error.push_back(ERROR_1);
		return QInt();
	}
}

void Calculator::xuatLoi() {
	if (!Error.empty()) {
		for (int i = 0; i<Error.size(); i++)
			switch (Error[i])
			{
			case ERROR_1:
				cout << "Invalid Number Input" << endl;
				break;
			default:
				break;
			}
	}
	Error.clear();
}

string Calculator::xuatAns() {
	switch (mode)
	{
	case 1: 
		return xuatInt(); 
		break;
	case 2: 
		return xuatFloat(); 
		break;
	default:
		break;
	}
}

//Goi QInt.Nhap(), trong QInt.Nhap() co chon he so
QInt Calculator::nhapInt(string input)
{
	return QInt(coSo, input);
}

//Kiem tra so dang o co so nao,
//Xuat ket qua ra man hinh theo co so tuong ung.
//Luu y: dung cac ham getBin(), getHex(), getDec() de xuat ra ket qua tuong ung
string Calculator::xuatInt()
{
	switch (ans.getCoSo())
	{
	case BIN: return ans.getBin(); break;
	case DEC: return ans.getDec(); break;
	case HEX: return ans.getHex(); break;
	}
}

void Calculator::nhapFloat() {

}

string Calculator::xuatFloat() {
	return string();
}

//Cac Ham DoiSangHeSo() doi coSo trong QInt
void Calculator::DoiSangHeBin()
{
	coSo = BIN;
	ans.setCoSo(coSo);
}


void Calculator::DoiSangHeDec()
{
	coSo = DEC;
	ans.setCoSo(coSo);
}


void Calculator::DoiSangHeHex()
{
	coSo = HEX;
	ans.setCoSo(coSo);
}


//Cac Ham tinh toan yeu cau:
//	nhap vao mot doi so
//	tinh kq
//	ans <- kq
void Calculator::Cong(QInt soHang)
{
	if (Error.empty())
		ans = ans + soHang;
}


void Calculator::Tru(QInt soHang)
{
	if (Error.empty())
		ans = ans - soHang;
}


void Calculator::Nhan(QInt soHang)
{
	if (Error.empty())
		ans = ans * soHang;
}


void Calculator::Chia(QInt soHang)
{
	if (Error.empty())
		ans = ans / soHang;
}

int Calculator::getCoSo()
{
	return coSo;
}
