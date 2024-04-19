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
// Запись в структуру пользователей//
void recordingInStruct(string nickname, string password, string name, int const countUsers)
{
	pListUsers[countUsers].nickname = nickname;
	pListUsers[countUsers].password = password;
	pListUsers[countUsers].name = name;
}

// Получение пользователей из файла //
void getUsers()
{
	string path = "Users.txt";
	fstream fs;
	fs.open(path, fstream::in | fstream::out | fstream::app);
	if (!fs.is_open())
	{
		cout << "Ошибка при открытии файла!" << endl;
	}
	else
	{
		string nickname;
		string password;
		string name;
		int count = 1;
		if (fs.peek() == fstream::traits_type::eof()) // проверка является ли следующий шаг концом файла
		{
			cout << "Пользователей нету!";
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

// Проверка ввода логина, пароля, имени //
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
			cout << "Вы ввели неверно " << n << endl
				<< "Если хотите прекратить регистрацию введите Exit: ";
			cin >> str;
			if (str == "Exit")
				break;
		}
	}
	return str;
}

// Запись в файл нового пользователя //
void registration()
{
	cout << "\tСоздание новой учётной записи\n";
	string nickname, password, checkPassword, name;
	/*cout << "Логин не должен содержать в себе кириллицу, арабские цифры и он должен иметь не меньше 4 символов\n" <<
		"Он может содержать в себе латинские и специальные символы(? , !, @, _)\n" << endl;*/

	/*cout << "Введите логин: ";*/
	nickname = checkCorrectInput("nickname", "Логин не должен содержать в себе кириллицу, арабские цифры и он должен иметь не меньше 4 символов\nОн может содержать в себе латинские и специальные символы(? , !, @, _)\nВведите логин: ");
	if (nickname == "Exit")
		return;
	/*cout << "\n\nПароль не должен содержать в себе кириллицу, быть не меньше 4 символов.\n" <<
		"Он может содержать в себе латинские и специальные символы(? , !, @, _), а также арабские цифры" << endl;*/
	/*cout << "Введите пароль: ";*/
	password = checkCorrectInput("password", "\n\nПароль не должен содержать в себе кириллицу, быть не меньше 4 символов.\nОн может содержать в себе латинские и специальные символы(? , !, @, _), а также арабские цифры\nВведите пароль: ");
	cout << "Повторите пароль: ";
	cin >> checkPassword;
	if (password == "Exit" || checkPassword == "Exit")
		return;
	while (password != checkPassword)
	{
		cout << "\n\nПароли не одинаковы, повторите еще раз создание пароля\n";
		password = checkCorrectInput("password", "\n\nПароль не должен содержать в себе кириллицу, быть не меньше 4 символов.\nОн может содержать в себе латинские и специальные символы(? , !, @, _), а также арабские цифры\nВведите пароль: ");
		cout << "Повторите пароль: ";
		cin >> checkPassword;
		if (password == "Exit" || checkPassword == "Exit")
			return;
	}
	/*cout << "\n\nИмя пользователя не должно содержать в себе , арабские цифры, специальные символы, быть не меньше 4 символов\n" <<
		"Оно может содержать в себе только латинские символы" << endl;
	cout << "Введите своё имя: ";*/
	name = checkCorrectInput("name", "\n\nИмя пользователя не должно содержать в себе, арабские цифры, специальные символы, быть не меньше 4 символов\nОно может содержать в себе только латинские символы\nВведите своё имя: ");
	if (name == "Exit")
		return;
	fstream fs;
	fs.open("Users.txt", fstream::in | fstream::app | fstream::out);
	if (!fs.is_open())
	{
		cout << "Ошибка при открытии файла!" << endl;
	}
	else
	{
		fs << '\n' << nickname << " " << password << " " << name;
	}
	fs.close();
	getUsers();
}

// Запись в файл попытки входа //
void loginAttempts(bool checkLogin)
{
	int countUserAttempts = 0, prevUserAttempt = 0;
	bool mod = false;
	string msg = "";
	SYSTEMTIME st;
	GetLocalTime(&st); // запись в переменную текущего времени для попытки входа
	string time; // переменная для вывода даты попытки входа
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
		cout << "Ошибка!" << endl;
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
				for (int i = 0; i < countAttempts; ++i) // запись в структуру данных с файла 
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
					if (pListUsers[idUser].nickname == pDataLogin[i].user) // Поиск пользователя заходящего в профиль в структуре
					{
						if (countUserAttempts != 0 && countUserAttempts != i)
						{
							prevUserAttempt = countUserAttempts;
						}
						countUserAttempts = i;
					}
				}
			}
			else if (countAttempts == 0 || (pListUsers[idUser].nickname != pDataLogin[countUserAttempts].user && mod == true)) // Если нету попыток вход в аккаунт  в списке, то выполняет данные код
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

// Вход в аккаунт //
bool authorization()
{
	getUsers();
	string log, pass;
	int output = 0;
	cout << "Введите логин: ";
	cin >> log;
	cout << "Введите пароль: ";
	cin >> pass;
	for (int i = 0; i < countUsers; ++i)
	{
		if (log == pListUsers[i].nickname && pass == pListUsers[i].password)
		{
			idUser = i;
			loginAttempts(true);
			cout << "Мы вас приветствуем " << pListUsers[i].name << "!" << endl;
			return true;
		}
		else if (log != pListUsers[i].nickname && i == countUsers - 1)
		{
			cout << "Такого пользователя не существует" << endl;
			return false;
		}
		else if (log == pListUsers[i].nickname && pass != pListUsers[i].password)
		{
			idUser = i;
			loginAttempts(false);
			cout << "Вы ввели неверный пароль" << endl;
			return false;
		}
	}
	return false;
}

// Смена пароля //
bool changePassword()
{
	fstream fs;
	string msg = "", password, checkPassword;
	int countSymbols = 0;
	password = checkCorrectInput("password", "\n\nПароль не должен содержать в себе кириллицу, быть не меньше 4 символов.\nОн может содержать в себе латинские и специальные символы(? , !, @, _), а также арабские цифры\nВведите пароль : ");
	cout << "Повторите пароль: ";
	cin >> checkPassword;
	while (password != checkPassword)
	{
		cout << "\n\nПароли не одинаковы, повторите еще раз создание пароля\n";
		password = checkCorrectInput("password", "\n\nПароль не должен содержать в себе кириллицу, быть не меньше 4 символов.\nОн может содержать в себе латинские и специальные символы(? , !, @, _), а также арабские цифры\nВведите пароль: ");
		cout << "Повторите пароль: ";
		cin >> checkPassword;
	}
	if (password == "Exit" || checkPassword == "Exit")
	{
		cout << "Ошибка при смене пароля!" << endl;
		return false;
	}
	fs.open("Users.txt", fstream::out | fstream::in);
	if (!fs.is_open())
	{
		cout << "Ошибка при открытии файла" << endl;
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

// Защита от дурака на принципе ввода строки и проверки символов и их подсчёта
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
			cout << "Вы ввели неверно, попробуйте снова" << endl;
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
		cout << "1.Вход в аккаунт\n2.Регистрация\n3.Завершение работы программы\n";
		numberOperation = intInput("Введите номер операции, которую хотите совершить: ", '+');
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
				cout << "Список команд:\n Выйти из аккаунта - Exit\n Сменить пароль - changepass\n" << pListUsers[idUser].nickname << ": ";
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
					cout << "Вы ввели несуществующую команду, повторите снова!" << endl;
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
			cout << "Такой операции не существует!\n";
			break;
		}
		}
	}
	delete[] pListUsers;
	delete[] pDataLogin;
	return 0;
}