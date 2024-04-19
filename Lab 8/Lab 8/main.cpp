#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#undef max
#undef min
using namespace std;
int countUsers = 0, idUser = 0, countAttempts = 0;
struct user
{
	string nickname;
	string password;
	string name;
};
struct attempts
{
	string date;
	string time;
	string user;
	string status;
	string attempt;
};
struct user* pListUsers = new struct user[0];
struct attempts* pDataLogin = new struct attempts[0];
// ������ � ��������� �������������//
void recordingInStruct(string nickname, string password, string name, int const countUsers)
{
	pListUsers[countUsers].nickname = nickname;
	pListUsers[countUsers].password = password;
	pListUsers[countUsers].name = name;
}

// ��������� ������������� �� ����� //
void getUsers()
{
	string path = "Users.txt";
	fstream fs;
	fs.open(path, fstream::in | fstream::out | fstream::app);
	if (!fs.is_open())
	{
		cout << "������ ��� �������� �����!" << endl;
	}
	else
	{
		string nickname;
		string password;
		string name;
		int count = 1;
		if (fs.peek() == fstream::traits_type::eof()) // �������� �������� �� ��������� ��� ������ �����
		{
			cout << "������������� ����!";
		}
		else
		{
			while (!fs.eof())
			{
				string str = "";
				fs >> str;
				if (fs.peek() == fstream::traits_type::eof())
				{
					count = 0;
					delete[] pListUsers;
					++countUsers;
					pListUsers = new user[countUsers];
					fs.clear();
					fs.seekg(0);
					break;
				}
				else if (count % 3 == 0)
				{
					++countUsers;
				}
				++count;
			}
			while (!fs.eof())
			{
				if (fs.peek() != fstream::traits_type::eof())
				{
					if (count == 1)
					{
						fs >> password;
					}
					else if (count == 2)
					{
						fs >> name;
						recordingInStruct(nickname, password, name, idUser);
						++idUser;
					}
					else
					{
						count = 0;
						fs >> nickname;
					}
					++count;
				}
			}
		}

	}
	fs.close();
}

// �������� ����� ������, ������, ����� //
string checkCorrectInput(string n, string text) //nickname, password, name
{
	string str;
	while (1)
	{
		int count = 0;
		cout << text;
		cin >> str;
		for (int i = 0; i < str.length(); i++)
		{
			if ((str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || str[i] == '?' || str[i] == '!' || str[i] == '@' || str[i] == '_') && n == "nickname")
				count++;
			else if ((str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z' || str[i] >= '0' && str[i] <= '9' || str[i] == '?' || str[i] == '!' || str[i] == '@' || str[i] == '_') && n == "password")
				count++;
			else if ((str[i] >= 'a' && str[i] <= 'z' || str[i] >= 'A' && str[i] <= 'Z') && n == "name")
				count++;
		}
		if (str.length() == count && count >= 4)
		{
			break;
		}
		else
		{
			cout << "�� ����� ������� " << n << endl
				<< "���� ������ ���������� ����������� ������� Exit: ";
			cin >> str;
			if (str == "Exit")
				break;
		}
	}
	return str;
}

// ������ � ���� ������ ������������ //
void registration()
{
	cout << "\t�������� ����� ������� ������\n";
	string nickname, password, checkPassword, name;
	/*cout << "����� �� ������ ��������� � ���� ���������, �������� ����� � �� ������ ����� �� ������ 4 ��������\n" <<
		"�� ����� ��������� � ���� ��������� � ����������� �������(? , !, @, _)\n" << endl;*/

	/*cout << "������� �����: ";*/
	nickname = checkCorrectInput("nickname", "����� �� ������ ��������� � ���� ���������, �������� ����� � �� ������ ����� �� ������ 4 ��������\n�� ����� ��������� � ���� ��������� � ����������� �������(? , !, @, _)\n������� �����: ");
	if (nickname == "Exit")
		return;
	/*cout << "\n\n������ �� ������ ��������� � ���� ���������, ���� �� ������ 4 ��������.\n" <<
		"�� ����� ��������� � ���� ��������� � ����������� �������(? , !, @, _), � ����� �������� �����" << endl;*/
	/*cout << "������� ������: ";*/
	password = checkCorrectInput("password", "\n\n������ �� ������ ��������� � ���� ���������, ���� �� ������ 4 ��������.\n�� ����� ��������� � ���� ��������� � ����������� �������(? , !, @, _), � ����� �������� �����\n������� ������: ");
	cout << "��������� ������: ";
	cin >> checkPassword;
	if (password == "Exit" || checkPassword == "Exit")
		return;
	while (password != checkPassword)
	{
		cout << "\n\n������ �� ���������, ��������� ��� ��� �������� ������\n";
		password = checkCorrectInput("password", "\n\n������ �� ������ ��������� � ���� ���������, ���� �� ������ 4 ��������.\n�� ����� ��������� � ���� ��������� � ����������� �������(? , !, @, _), � ����� �������� �����\n������� ������: ");
		cout << "��������� ������: ";
		cin >> checkPassword;
		if (password == "Exit" || checkPassword == "Exit")
			return;
	}
	/*cout << "\n\n��� ������������ �� ������ ��������� � ���� , �������� �����, ����������� �������, ���� �� ������ 4 ��������\n" <<
		"��� ����� ��������� � ���� ������ ��������� �������" << endl;
	cout << "������� ��� ���: ";*/
	name = checkCorrectInput("name", "\n\n��� ������������ �� ������ ��������� � ����, �������� �����, ����������� �������, ���� �� ������ 4 ��������\n��� ����� ��������� � ���� ������ ��������� �������\n������� ��� ���: ");
	if (name == "Exit")
		return;
	fstream fs;
	fs.open("Users.txt", fstream::in | fstream::app | fstream::out);
	if (!fs.is_open())
	{
		cout << "������ ��� �������� �����!" << endl;
	}
	else
	{
		fs << '\n' << nickname << " " << password << " " << name;
	}
	fs.close();
	getUsers();
}

// ������ � ���� ������� ����� //
void loginAttempts(bool checkLogin)
{
	int countUserAttempts = 0, prevUserAttempt = 0;
	bool mod = false;
	string msg = "";
	SYSTEMTIME st;
	GetLocalTime(&st); // ������ � ���������� �������� ������� ��� ������� �����
	string time; // ���������� ��� ������ ���� ������� �����
	if (to_string(st.wHour).length() != 2)
	{
		time += "0" + to_string(st.wHour) + ":";
	}
	else
	{
		time += to_string(st.wHour) + ":";
	}
	if (to_string(st.wMinute).length() != 2)
	{
		time += "0" + to_string(st.wMinute) + ":";
	}
	else
	{
		time += to_string(st.wMinute) + ":";
	}
	if (to_string(st.wSecond).length() != 2)
	{
		time += "0" + to_string(st.wSecond);
	}
	else
	{
		time += to_string(st.wSecond);
	}
	fstream fs;
	fs.open("Login Attempts.txt", fstream::out | fstream::app | fstream::in);
	if (!fs.is_open())
	{
		cout << "������!" << endl;
	}
	else
	{
		while (!fs.eof())
		{
			if (fs.peek() != fstream::traits_type::eof() && !(mod))
			{
				getline(fs, msg);
				if (msg == "")
				{
					continue;
				}
				++countAttempts;
			}
			else if (fs.peek() != fstream::traits_type::eof() && mod)
			{
				for (int i = 0; i < countAttempts; ++i) // ������ � ��������� ������ � ����� 
				{
					fs >> pDataLogin[i].date;
					fs >> msg;
					fs >> pDataLogin[i].time;
					fs >> msg;
					if (msg == "User:")
					{
						fs >> pDataLogin[i].user;
					}
					fs >> msg;
					if (msg == "Attempt:")
					{
						fs >> pDataLogin[i].attempt;
					}
					fs >> msg;
					if (msg == "Status:")
					{
						fs >> pDataLogin[i].status;
					}
					if (pListUsers[idUser].nickname == pDataLogin[i].user) // ����� ������������ ���������� � ������� � ���������
					{
						if (countUserAttempts != 0 && countUserAttempts != i)
						{
							prevUserAttempt = countUserAttempts;
						}
						countUserAttempts = i;
					}
				}
			}
			else if (countAttempts == 0 || (pListUsers[idUser].nickname != pDataLogin[countUserAttempts].user && mod == true)) // ���� ���� ������� ���� � �������  � ������, �� ��������� ������ ���
			{
				if (countAttempts == 0)
				{
					fs.seekg(0);
					fs.clear();
					fs.seekp(0);
				}
				else
				{
					streampos  currentposition = fs.tellg();
					fs.seekp(currentposition, ios::beg);
				}
				fs << to_string(st.wDay) + "-" + to_string(st.wMonth) + "-" + to_string(st.wYear) + " GMT+3 " << time
					<< " User: " << pListUsers[idUser].nickname << " " << "Attempt: " << "1";
				if (checkLogin)
				{
					fs << " Status: " << "Success\n";
				}
				else
				{
					fs << " Status: " << "Failure\n";
				}
				mod = false;
				break;
			}
			else
			{
				fs.clear();
				fs.seekg(0);
				mod = true;
				++countAttempts;
				delete[] pDataLogin;
				pDataLogin = new attempts[countAttempts];
			}
		}
		fs.clear();
		streampos  currentposition = fs.tellg();
		fs.seekp(currentposition, ios::beg);
		if (checkLogin && pDataLogin[countUserAttempts].status == "Failure")
		{
			fs << to_string(st.wDay) + "-" + to_string(st.wMonth) + "-" + to_string(st.wYear) + " GMT+3 " << time
				<< " User: " << pListUsers[idUser].nickname << " " << "Attempt: " << to_string(stoi(pDataLogin[countUserAttempts].attempt)+1) << " Status: " << "Success\n";
		}
		else if (checkLogin && pDataLogin[countUserAttempts].status == "Success")
		{
			if(pDataLogin[prevUserAttempt].status == "Success")
			fs << to_string(st.wDay) + "-" + to_string(st.wMonth) + "-" + to_string(st.wYear) + " GMT+3 " << time
				<< " User: " << pListUsers[idUser].nickname << " " << "Attempt: " << "1" << " Status: " << "Success\n";
			else
				fs << to_string(st.wDay) + "-" + to_string(st.wMonth) + "-" + to_string(st.wYear) + " GMT+3 " << time
				<< " User: " << pListUsers[idUser].nickname << " " << "Attempt: " << "1" << " Status: " << "Success\n";
		}
		else if (mod)
		{
			if (pDataLogin[prevUserAttempt].status == "Success")
			{
				fs << to_string(st.wDay) + "-" + to_string(st.wMonth) + "-" + to_string(st.wYear) + " GMT+3 " << time
					<< " User: " << pListUsers[idUser].nickname << " " << "Attempt: " << "1" << " Status: " << "Failure\n";
			}
			else
			{
				fs << to_string(st.wDay) + "-" + to_string(st.wMonth) + "-" + to_string(st.wYear) + " GMT+3 " << time
					<< " User: " << pListUsers[idUser].nickname << " " << "Attempt: " << to_string(stoi(pDataLogin[countUserAttempts].attempt)+1) << " Status: " << "Failure\n";
			}
		}
	}
	fs.close();
}

// ���� � ������� //
bool authorization()
{
	getUsers();
	string log, pass;
	int output = 0;
	cout << "������� �����: ";
	cin >> log;
	cout << "������� ������: ";
	cin >> pass;
	for (int i = 0; i < countUsers; ++i)
	{
		if (log == pListUsers[i].nickname && pass == pListUsers[i].password)
		{
			idUser = i;
			loginAttempts(true);
			cout << "�� ��� ������������ " << pListUsers[i].name << "!" << endl;
			return true;
		}
		else if (log != pListUsers[i].nickname && i == countUsers - 1)
		{
			cout << "������ ������������ �� ����������" << endl;
			return false;
		}
		else if (log == pListUsers[i].nickname && pass != pListUsers[i].password)
		{
			idUser = i;
			loginAttempts(false);
			cout << "�� ����� �������� ������" << endl;
			return false;
		}
	}
	return false;
}

// ����� ������ //
bool changePassword()
{
	fstream fs;
	string msg = "", password, checkPassword;
	int countSymbols = 0;
	password = checkCorrectInput("password", "\n\n������ �� ������ ��������� � ���� ���������, ���� �� ������ 4 ��������.\n�� ����� ��������� � ���� ��������� � ����������� �������(? , !, @, _), � ����� �������� �����\n������� ������ : ");
	cout << "��������� ������: ";
	cin >> checkPassword;
	while (password != checkPassword)
	{
		cout << "\n\n������ �� ���������, ��������� ��� ��� �������� ������\n";
		password = checkCorrectInput("password", "\n\n������ �� ������ ��������� � ���� ���������, ���� �� ������ 4 ��������.\n�� ����� ��������� � ���� ��������� � ����������� �������(? , !, @, _), � ����� �������� �����\n������� ������: ");
		cout << "��������� ������: ";
		cin >> checkPassword;
	}
	if (password == "Exit" || checkPassword == "Exit")
	{
		cout << "������ ��� ����� ������!" << endl;
		return false;
	}
	fs.open("Users.txt", fstream::out | fstream::in);
	if (!fs.is_open())
	{
		cout << "������ ��� �������� �����" << endl;
	}
	else
	{
		while (!fs.eof())
		{
			if (fs.peek() != fstream::traits_type::eof())
			{
				fs >> msg;
				if (msg == pListUsers[idUser].nickname)
				{
					streampos  currentposition = fs.tellg();
					fs.seekp(currentposition, ios::beg);
					fs << " " << password << " " << pListUsers[idUser].name;
					for (int i = 0, countSymbols = (pListUsers[idUser].password.length() - password.length()); i < abs(countSymbols); i++)
					{
						fs << '\0';
						if ((i - 1) == abs(countSymbols))
						{
							fs << '\n';
						}
					}
					break;
				}
			}
		}
	}
	fs.close();
	getUsers();
	return true;
}

// ������ �� ������ �� �������� ����� ������ � �������� �������� � �� ��������
int intInput(string text, char sign)
{
	string number;
	while (true)
	{
		cout << text;
		cin >> number;
		int count = 0;
		if (number[0] == '-' && (sign == '0' || sign == '-'))
		{
			count++;
		}
		for (int i = 0; i < number.length(); i++)
		{
			if (number[i] >= '0' && number[i] <= '9')
			{
				count++;
			}
		}
		if (((number[0] == '-' && sign == '-') || (number[0] != '-' && sign == '+') || sign == '0') && number.length() == count)
		{
			break;
		}
		else
		{
			cout << "�� ����� �������, ���������� �����" << endl;
		}
	}
	return stoi(number);
} 

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int numberOperation = 0;
	while (true)
	{
		cout << "1.���� � �������\n2.�����������\n3.���������� ������ ���������\n";
		numberOperation = intInput("������� ����� ��������, ������� ������ ���������: ", '+');
		if (numberOperation == 3)
		{
			break;
		}
		switch (numberOperation)
		{
		case 1:
		{
			bool accountStatus = authorization();
			while (accountStatus)
			{
				string choice;
				cout << "������ ������:\n ����� �� �������� - Exit\n ������� ������ - changepass\n" << pListUsers[idUser].nickname << ": ";
				cin >> choice;
				if (choice == "Exit")
				{
					break;
				}
				else if (choice == "changepass")
				{
					if (changePassword())
						break;
					else
						continue;
				}
				else
				{
					cout << "�� ����� �������������� �������, ��������� �����!" << endl;
				}
			}
			break;
		}
		case 2:
		{
			registration();
			break;
		}
		default:
		{
			cout << "����� �������� �� ����������!\n";
			break;
		}
		}
	}
	delete[] pListUsers;
	delete[] pDataLogin;
	return 0;
}