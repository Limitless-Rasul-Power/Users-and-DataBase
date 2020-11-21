#pragma once
#include <string>
class User
{
private:
	std::string name;
	std::string password;
	std::string phone_number;
	std::string email;

public:

	User();

	explicit inline User(const std::string& email);

	User(const std::string& email, const std::string& password);

	User(const std::string& email, const std::string& password, const std::string& phone_number);

	User(const std::string& email, const std::string& password, const std::string& phone_number, const std::string& name);

	void Set_email(const std::string& email);
	std::string Get_email() const;

	void Set_password(const std::string& password);
	std::string Get_password() const;

	void Set_phone_number(const std::string& phone_number);
	std::string Get_phone_number() const;

	void Set_name(const std::string& name);
	std::string Get_name() const;

	friend std::ostream& operator << (std::ostream& out, const User& user);
	friend std::istream& operator >> (std::istream& in, User& user);
};
void Encrypt_password(std::string& password);