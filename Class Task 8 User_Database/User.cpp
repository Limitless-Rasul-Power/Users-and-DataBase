#include <iostream>
#include <assert.h>
#include <windows.h>
#include "User.h"

User::User() :name(""), password(""), phone_number(""), email("")
{}

inline User::User(const std::string& email)
{
	Set_email(email);
}

User::User(const std::string& email, const std::string& password)
	:User(email)
{
	Set_password(password);
}

User::User(const std::string& email, const std::string& password, const std::string& phone_number)
	:User(email, password)
{
	Set_phone_number(phone_number);
}

User::User(const std::string& email, const std::string& password, const std::string& phone_number, const std::string& name)
	:User(email, password, phone_number)
{
	Set_name(name);
}

void User::Set_email(const std::string& email)
{
	assert(!email.empty() && "Email is Empty!");
	this->email = email;
}

std::string User::Get_email() const
{
	return email;
}

void User::Set_password(const std::string& password)
{
	assert(!password.empty() && "Password is Empty!");
	this->password = password;
	Encrypt_password(this->password);
}

std::string User::Get_password() const
{
	return password;
}

void User::Set_phone_number(const std::string& phone_number)
{
	assert(!phone_number.empty() && "Phone Number is Empty!");
	this->phone_number = phone_number;
}

std::string User::Get_phone_number() const
{
	return phone_number;
}

void User::Set_name(const std::string& name)
{
	assert(!name.empty() && "Name is Empty!");
	this->name = name;
}

std::string User::Get_name() const
{
	return name;
}

std::ostream& operator << (std::ostream& out, const User& user)
{
	out << "User Email: " << user.email << '\n';
	out << "User Password: " << user.password << "\n\n";
	out << "User Name: " << user.name << '\n';
	out << "User Phone Number: " << user.phone_number << "\n\n";
	return out;
}

std::istream& operator >> (std::istream& in, User& user)
{
	std::string name{}, password{}, email{}, phone_number{};

	COORD c{ 47, 10 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	std::cout << "Enter User Name: ";
	getline(in, name);
	user.Set_name(name);

	c.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	std::cout << "Enter Password: ";
	getline(in, password);
	user.Set_password(password);

	c.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	std::cout << "Enter Email: ";
	getline(in, email);
	user.Set_email(email);

	c.Y++;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
	std::cout << "Enter Phone Number: ";
	getline(in, phone_number);
	user.Set_phone_number(phone_number);

	return in;
}

void Encrypt_password(std::string& password)
{
	const char* encrypt = "fk~gwAXcKW!2#fh3Rs$df!?><";
	for (unsigned short j = 0; j < password.size(); j++)
		for (size_t i = 0; i < strlen(encrypt); i++)
			password[j] ^= encrypt[i];

	password += "a@#AsdıƏs6:Ş,/~üЮЯыауй132<>><w";
}