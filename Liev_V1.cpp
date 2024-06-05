#include <iostream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

string generatePassword(int length, bool useDigits, bool useSpecial, bool useUpper, bool useLower) {
	const string digits = "0123456789";
	const string special = "!@#$%^&*()-_=+[]{}|;:'\",.<>?/\\";
	const string upper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	const string lower = "abcdefghijklmnopqrstuvwxyz";

	string characterPool;

	if (useDigits) characterPool += digits;
	if (useSpecial) characterPool += special;
	if (useUpper) characterPool += upper;
	if (useLower) characterPool += lower;

	if (characterPool.empty()) {
		throw invalid_argument("Необходимо выбрать хотя бы один тип символов для генерации пароля.");
	}

	string password;
	mt19937 generator(static_cast<unsigned>(time(nullptr)));
	uniform_int_distribution<> distribution(0, characterPool.size() - 1);

	for (int i = 0; i < length; ++i) {
		password += characterPool[distribution(generator)];
	}

	return password;
}

int main() {
	setlocale(LC_ALL, "Rus");
	system("chcp 1251");

	int length;
	string input;

	cout << "Введите длину пароля: ";
	cin >> length;

	cout << "Использовать цифры? (да/нет): ";
	cin >> input;
	bool useDigits = (input == "да");

	cout << "Использовать специальные символы? (да/нет): ";
	cin >> input;
	bool useSpecial = (input == "да");

	cout << "Использовать заглавные буквы? (да/нет): ";
	cin >> input;
	bool useUpper = (input == "да");

	cout << "Использовать строчные буквы? (да/нет): ";
	cin >> input;
	bool useLower = (input == "да");

	try {
		string password = generatePassword(length, useDigits, useSpecial, useUpper, useLower);
		cout << "Сгенерированный пароль: " << password << endl;
	}
	catch (const invalid_argument & e) {
		cerr << e.what() << endl;
	}

	return 0;
}
