#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <random>

using namespace std;

string string_to_hex(const std::string& input){			//CONVERT SYMBOL TO HEX
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

bool file(string failas, vector<string>& data){			//FILE READ
	ifstream in(failas.c_str());
	if (!in){
		cout << "Tokio failo nera!" << endl;
		return false;
	}
	string line;
	int n;
	cout << "Nuskaityti visa faila (0), tam tikra skaiciu eiluciu (1): ";
	cin >> n;
	while (n != 0 && n != 1){
		cout << "Neteisinga ivestis! Nuskaityti visa faila (0), tam tikra skaiciu eiluciu (1): ";
		cin >> n;
	}
	if (n == 0){
		while (getline(in, line)){
			data.push_back(line);
		}
	}else{
		cout << "Kiek eiluciu nuskaityti?: ";
		cin >> n;
		while (n < 1){
			cout << "Neteisinga ivestis! Eiluciu skaicius 1..n: ";
			cin >> n;
		}
		for (int i = 0; i < n; i++){
			getline(in, line);
			data.push_back(line);
		}
	}

	in.close();
	return true;
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
	if (input == 1){
		vector<string> data;
		string filename;
		cout << "Iveskite failo pavadinima: ";
		cin >> filename;
		filename = filename + ".txt";
		ifstream input(filename);
		bool result = file(filename, data);
		for (auto& line : data){
			text << line;
			col.push_back(line);
			lines++;
		}
		txt = text.str();
	}else if(input ==0){
		cout << "Iveskite teksta: ";
		cin.clear();
		cin.ignore(256, '\n');
		getline(cin, txt);
	}

	cout << "Pradinis tekstas: " << endl << txt << endl;
	string hash = "EE9A17A0F3E783EE983B7EFD23324395FE3A8E0563F860EF72D5420B9414FBEC"; // seed'as
	int tmp = 0;
	auto start = std::chrono::steady_clock::now();

		for (int i = 1; i < 64; i++){				//hash function
			for (int j = 0; j < txt.size(); j++){
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