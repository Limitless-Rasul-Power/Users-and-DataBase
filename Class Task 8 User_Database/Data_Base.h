#pragma once
#include "User.h"
#include <time.h>
#include <conio.h>
#include <windows.h>
#define AQUA_BLUE 3
#define DARK_BLUE 9
#define WHITE 7

class DataBase
{

private:
	User** users;
	unsigned short number_of_users;

public:

	DataBase();

	explicit inline DataBase(const short& number_of_users);

	DataBase(User** const& users, const short& number_of_users);

	void Set_number_of_users(const short& number_of_users);
	unsigned short Get_number_of_users() const;

	void Set_users(User** const& users);

	bool Sign_in_with_name(const std::string& name, std::string& password);

	bool Sign_in_with_email(const std::string& email, std::string& password);

	void Add_new_user(User* const& new_user);

	bool Delete_user(const std::string& name);

	bool Sign_up(User* const& new_user);

	User* Get_user_by_name(const std::string& name);

	User* Get_user_by_email(const std::string& email);

	inline ~DataBase();

	friend std::ostream& operator << (std::ostream& out, const DataBase& data_base);

};
