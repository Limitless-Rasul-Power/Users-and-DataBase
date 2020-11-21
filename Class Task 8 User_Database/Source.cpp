#include <iostream>
#include "Data_Base.h"
#define ADMIN_PASSWORD "7SOUL7"

using namespace std;

int main()
{
	srand(unsigned short(time(NULL)));
	User* u1 = new User("mike@mail.ru", "mynameisMike", "994932491", "Mike");
	User* u2 = new User("anthonyrobbins@power.life", "Limitless Power", "7777777", "Tony Robbins");
	User* u3 = new User("bot@m.ru", "bot", "111111", "Bot");

	User** all = new User * [3]{ u1, u2, u3 };

	DataBase db(all, 3);

	const unsigned short menu_options = 7;
	string menu[menu_options] = { "Sign In(Email)", "Sign In(Name)", "Sign Up", "Delete User", "Show All Users", "Search User", "Exit" };

	enum Options
	{
		Sign_In_Email, Sign_In_Name, Sign_Up, Delete_User, Show_All_Users, Search_User, EXIT
	};


	COORD c{ 47, 10 };
	unsigned short option = 0;

	CONSOLE_FONT_INFOEX cfi{};
	cfi.cbSize = sizeof(cfi);
	cfi.dwFontSize.X = 0;
	cfi.dwFontSize.Y = 20;
	cfi.FontFamily = FF_DONTCARE;
	cfi.FontWeight = FW_EXTRALIGHT;

	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), FALSE, &cfi);

	CONSOLE_CURSOR_INFO cci{};

	GetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
	cci.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);


	while (true)
	{
		while (true)
		{
			system("CLS");
			c.X -= 6;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), DARK_BLUE);
			cout << "Welcome to BeatifullSouls.com";
			c.Y += 2;
			c.X += 6;
			for (unsigned short i = 0; i < menu_options; i++)
			{
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				if (option == i)
				{
					c.X += 5;
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), AQUA_BLUE);
					cout << menu[i];
					c.X -= 5;
				}
				else
				{
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
					cout << menu[i];
				}
				c.Y++;
			}
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), WHITE);
			c.Y -= 9;

			int choice = _getch();


			switch (choice)
			{
			case 72:
				if (option == 0)
					option = 6;
				else
					--option;
				break;

			case 80:
				if (option == 6)
					option = 0;
				else
					++option;
				break;
			}

			if (choice == 13)
				break;
		}

		system("CLS");

		switch (option)
		{
		case Sign_In_Email:
		{
			string email{};
			string password{};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "Enter Email: ";
			getline(cin, email);

			c.Y++;

			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

			cout << "Enter Password: ";
			getline(cin, password);

			system("CLS");
			bool is_sign_in = db.Sign_in_with_email(email, password);
			c.Y -= 2;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

			if (is_sign_in)
				cout << "Welcome To BeatifullSouls.com HomePage\n";
			else
				cout << "Email or Password is Wrong or Both or Last User don't be deleted!\n";
		}
		break;

		case Sign_In_Name:
		{
			string user_name{};
			string password{};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

			cout << "Enter User Name: ";
			getline(cin, user_name);
			c.Y++;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

			cout << "Enter Password: ";
			getline(cin, password);

			system("CLS");
			c.Y -= 2;
			bool is_sign_in = db.Sign_in_with_name(user_name, password);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

			if (is_sign_in)
				cout << "Welcome To BeatifullSouls.com HomePage\n";
			else
				cout << "User Name or Password is Wrong or Both or Last User don't be deleted!\n";

		}
		break;

		case Sign_Up:
		{
			User* new_user = new User;
			cin >> *new_user;
			system("CLS");
			bool is_sign_up = db.Sign_up(new_user);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

			if (is_sign_up)
				cout << "New User Added Successfully!\n";
			else
				cout << "This Name or Email had been choosen\n";
		}
		break;

		case Delete_User:
		{
			string name;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

			string admin_password{};
			cout << "Enter ADMIN PASSWORD: ";
			getline(cin, admin_password);

			if (admin_password == ADMIN_PASSWORD)
			{
				system("CLS");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "Enter Name which you want to Delete: ";
				getline(cin, name);
				bool is_user_deleted = db.Delete_user(name);

				system("CLS");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				if (is_user_deleted)
					cout << "User " << name << " is Successfully Deleted!\n";
				else
					cout << "User " << name << " Not Found or user " << name << " is last user!\n";
			}
			else
			{
				c.Y++;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
				cout << "Admin Password is Wrong!!!\n";
				c.Y--;
			}
		}
		break;
		case Show_All_Users:
			cout << db;
			break;

		case Search_User:
		{	string user_name{};
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);

			cout << "Enter User Name: ";
			getline(cin, user_name);
			c.Y++;

			User* find = db.Get_user_by_name(user_name);
			system("CLS");

			if (find == nullptr)
				cout << "User Not Found\n";
			else
				cout << *find;

			c.Y--;
		}
			break;
		case EXIT:
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
			cout << "Bye-Bye See You Soon";
			return 0;
		}

		option = 0;
		system("pause");
	}



	system("pause");
	return 0;
}