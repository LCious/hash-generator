#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <random>

using namespace std;

string string_to_hex(const std::string &input)
{ // CONVERT SYMBOL TO HEX
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

bool file(string failas, vector<string> &data)
{ // FILE READ
	ifstream in(failas.c_str());
	if (!in)
	{
		cout << "Tokio failo nera!" << endl;
		return false;
	}
	string line;
	int n;
	cout << "Nuskaityti visa faila (0), tam tikra skaiciu eiluciu (1): ";
	cin >> n;
	while (n != 0 && n != 1)
	{
		cout << "Neteisinga ivestis! Nuskaityti visa faila (0), tam tikra skaiciu eiluciu (1): ";
		cin >> n;
	}
	if (n == 0)
	{
		while (getline(in, line))
		{
			data.push_back(line);
		}
	}
	else
	{
		cout << "Kiek eiluciu nuskaityti?: ";
		cin >> n;
		while (n < 1)
		{
			cout << "Neteisinga ivestis! Eiluciu skaicius 1..n: ";
			cin >> n;
		}
		for (int i = 0; i < n; i++)
		{
			getline(in, line);
			data.push_back(line);
		}
	}

	in.close();
	return true;
}

void hash_function(string txt)
{
	string hash = "EE9A17A0F3E783EE983B7EFD23324395FE3A8E0563F860EF72D5420B9414FBEC"; // seed'as
	int tmp = 0;
	for (int i = 1; i < 64; i++)
	{ // hash function
		for (int j = 0; j < txt.size(); j++)
		{
			tmp = hash[i];
			tmp = tmp ^ int(txt[j]);
			hash[i] = char(tmp);
			hash[i - 1] += i ^ j;
		}
		hash[i] = int(hash[i]) + int(hash[64 - i]);
	}
	hash = string_to_hex(hash);
	hash.resize(64);
	cout << hash << endl;
}

void hash_function_everyline(int lines,vector<string> &col){
	int tmp = 0;
	string hash = "EE9A17A0F3E783EE983B7EFD23324395FE3A8E0563F860EF72D5420B9414FBEC"; // seed'as
	for (int i = 0; i < lines; i++)
	{
		for (int j = 0; j < 64; j++)
		{
			for (int x = 0; x < col[i][col[i].size()]; x++)
			{
				tmp = hash[i];
				tmp = tmp ^ int(col[i][x]);
				hash[i] = char(tmp);
				hash[i - 1] += i ^ j;
			}
			hash[j] = int(hash[j]) + int(hash[64 - j]);
		}
		hash = string_to_hex(hash);
		hash.resize(64);
		col[i] = hash;
		cout << col[i];
	}
	cout <<"Eilutciu: "<< lines;
}

void collisions(int lines, vector<string> col) {
	int collision = 0;
	for (int i = 0; i < lines; i++)
	{
	for (int j = 0; j < lines; j++)
	{
		if (col[i] == col[j] && i != j)
		{
			collision++;
		} 
	}
	}
	cout << endl << "Koliziju skaicius: " << collision << endl;
}

int main(int argc, char const *argv[])
{
    cout << "Pasirinkite testavimo metoda: " << endl
    << "---------------------------" << endl
    << "1. Ivedimas i konsole. " << endl
    << "2. Ivedimas is failo. " << endl
    << "2.1 Koliziju testavimas " << endl
    << "2.2 Skirtingumo testavimas " << endl
	<< "3. Palyginimas " << endl
	<< "---------------------------" << endl;
	int input;
	cin >> input;

	int lines = 0;
	string txt;
	stringstream text;
	vector<string> col;
	if (input == 2)
	{
		vector<string> data;
		string filename;
		cout << "Iveskite failo pavadinima: ";
		cin >> filename;
		filename = filename + ".txt";
		ifstream input(filename);
		bool result = file(filename, data);
		for (auto &line : data)
		{
			text << line;
			col.push_back(line);
			lines++;
		}
		txt = text.str();
		if (txt.size() != 0)
		{
    		cout << "---------------------------------------------" << endl
				 << "Ar norite atlikti testavimus? (Ne:0,Taip:1): " << endl
				 << "---------------------------------------------" << endl;
			int input;
			cin >> input;
			while(input != 0 && input != 1){
				cout << "Neteisinga ivestis! Bandykite isnaujo";
				cin >> input;
			}
			if(input == 0){
				auto start = std::chrono::steady_clock::now();
				hash_function(txt);
				auto end = std::chrono::steady_clock::now();
				cout << "Uztruko: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000. << "s" << endl;
			} else if(input == 1){
				// auto start = std::chrono::steady_clock::now();
				hash_function_everyline(lines, col);
				collisions(lines, col);
				// auto end = std::chrono::steady_clock::now();
				// cout << "Uztruko: " << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000. << "s" << endl;
			}
		}
	}
	else if (input == 1)
	{
		cout << "Iveskite teksta: ";
		cin.clear();
		cin.ignore(256, '\n');
		getline(cin, txt);
		cout << "Pradinis tekstas: " << endl << txt << endl;
		hash_function(txt);
	}
}