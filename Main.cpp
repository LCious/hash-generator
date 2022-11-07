#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <random>

using namespace std;

string string_to_hex(const std::string& input) // simboliu konvertavimas i hex'a
{
	static const char hex_digits[] = "0123456789ABCDEF";

	std::string output;
	output.reserve(input.length() * 2);
	for (unsigned char c : input)
	{
		output.push_back(hex_digits[c >> 4]);
		output.push_back(hex_digits[c & 15]);
	}
	return output;
}

int main(int argc, char const* argv[])
{
	int input;
	cout << "Ivesti ranka (0), is failo (1): ";
	cin >> input;

	int lines = 0;
	string txt;
	stringstream text;
	vector<string> col;
	if (input == 1) // ivestis is failo
	{
		//TO DO
		cout << "Atsiprasome nuskaityti is failo negalima";
	}
	else // ivestis ranka
	{
		cout << "Iveskite teksta: ";
		cin.clear();
		cin.ignore(256, '\n');
		getline(cin, txt);
	}

	cout << "Pradinis tekstas: " << endl << txt << endl;
	string hash = "EE9A17A0F3E783EE983B7EFD23324395FE3A8E0563F860EF72D5420B9414FBEC"; // seed'as
	int tmp = 0;
	auto start = std::chrono::steady_clock::now();
	for (int i = 1; i < 64; i++)										// hash funkcija
	{
		for (int j = 0; j < txt.size(); j++)
		{
			tmp = hash[i];
			tmp = tmp ^ int(txt[j]);
			hash[i] = char(tmp);
			hash[i - 1] += i ^ j;
		}
		hash[i] = int(hash[i]) + int(hash[64 - i]);
	}
	auto end = std::chrono::steady_clock::now();

	hash = string_to_hex(hash);
	hash.resize(64);
	cout << hash << endl;
	cout << "Uztruko: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "mcs" << endl;
}