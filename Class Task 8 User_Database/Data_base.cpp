#include <iostream>
#include <assert.h>
#include "Data_base.h"

DataBase::DataBase() :users(nullptr), number_of_users(0)
{}

inline DataBase::DataBase(const short& number_of_users)
{
	Set_number_of_users(number_of_users);
}

DataBase::DataBase(User** const& users, const short& number_of_users)
	:DataBase(number_of_users)
{
	Set_users(users);
}

void DataBase::Set_number_of_users(const short& number_of_users)
{
	assert(number_of_users > 0 && "Numbwe Of Users is 0!");
	this->number_of_users = number_of_users;
}

unsigned short DataBase::Get_number_of_users() const
{
	return number_of_users;
}

void DataBase::Set_users(User** const& users)
{
	this->users = new User * [Get_number_of_users()];

	for (unsigned short i = 0; i < Get_number_of_users(); i++)
	{
		this->users[i] = new User;
		this->users[i] = users[i];
	}

}

bool DataBase::Sign_in_with_name(const std::string& name, std::string& password)
{
	auto current_user = Get_user_by_name(name);
	Encrypt_password(password);

	if (current_user != nullptr)
		if (current_user->Get_password() == password)
			return true;

	return false;
}

bool DataBase::Sign_in_with_email(const std::string& email, std::string& password)
{
	auto current_user = Get_user_by_email(email);
	Encrypt_password(password);

	if (current_user != nullptr)
		if (current_user->Get_password() == password)
			return true;

	return false;
}

void DataBase::Add_new_user(User* const& new_user)
{
	auto temp_data = new User * [Get_number_of_users() + 1];

	for (unsigned short i = 0; i < Get_number_of_users(); i++)
	{
		temp_data[i] = new User;
		temp_data[i] = this->users[i];
	}

	temp_data[Get_number_of_users()] = new_user;

	delete[] this->users;
	this->users = temp_data;
	temp_data = nullptr;
	Set_number_of_users(++this->number_of_users);
}

bool DataBase::Delete_user(const std::string& name)
{
	auto temp = Get_user_by_name(name);
	if (temp == nullptr || Get_number_of_users() == 1)
		return false;
	else
	{
		auto temp_data_base = new User * [Get_number_of_users() - 1];
		unsigned short go_next = 0;

		for (unsigned short i = 0; i + go_next < Get_number_of_users(); i++)
		{
			if (this->users[i]->Get_name() == name)
				++go_next;

			if (i + go_next < Get_number_of_users())
			{
				temp_data_base[i] = new User;
				temp_data_base[i] = this->users[i + go_next];
			}

		}

		delete[] this->users;
		this->users = temp_data_base;
		temp_data_base = nullptr;
		Set_number_of_users(--this->number_of_users);
	}
	return true;
}

bool DataBase::Sign_up(User* const& new_user)
{
	for (unsigned short i = 0; i < Get_number_of_users(); i++)
		if (new_user->Get_name() == this->users[i]->Get_name() || new_user->Get_email() == this->users[i]->Get_email())
			return false;

	Add_new_user(new_user);
	return true;
}

User* DataBase::Get_user_by_name(const std::string& name)
{
	for (unsigned short i = 0; i < Get_number_of_users(); i++)
		if (this->users[i]->Get_name() == name)
			return this->users[i];

	return nullptr;
}

User* DataBase::Get_user_by_email(const std::string& email)
{
	for (unsigned short i = 0; i < Get_number_of_users(); i++)
		if (this->users[i]->Get_email() == email)
			return this->users[i];

	return nullptr;
}

inline DataBase::~DataBase()
{
	for (unsigned short i = 0; i < Get_number_of_users(); i++)
		delete this->users[i];

	delete[] this->users;
}

std::ostream& operator << (std::ostream& out, const DataBase& data_base)
{
	for (unsigned short i = 0; i < data_base.Get_number_of_users(); i++)
	{
		out << *(data_base.users[i]);
		out << "========================\n\n";
	}
	return out;
}