#include "functions.hpp"
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
		exit(0);
	}
	string line;
	int n;
	cout << "----------------------------------------------------------" << endl
		<< "Nuskaityti visa faila (0), tam tikra skaiciu eiluciu (1)? " << endl
		<< "----------------------------------------------------------" << endl;
	cin >> n;
	while (n != 0 && n != 1)
	{
		cout << "Neteisinga ivestis!";
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

void generate(int size, int length) {
	using hrClock = std::chrono::high_resolution_clock;
	std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int> numb(48, 126); //raides ASCII

	stringstream buffer;	//irasymas i atminti

	string fileName = to_string(size);
	fileName += "_" + to_string(length) + ".txt";
	std::ofstream rf("InputFiles/"+fileName);

	auto start = std::chrono::high_resolution_clock::now();
	for (int i = 0; i < size; i++)	//eiluciu kiekis
	{
		for (int j = 0; j < length; j++)	//eilutes ilgis
		{
			buffer << (char)numb(mt);
		}
		if (i < size - 1)					//paskutinis endl ne (1001) o 1000
			buffer << "\n";
	}

	rf << buffer.str();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Skirtumas (s)
	cout << size << " row size generation time " << diff.count() << " s\n";

	buffer.str("");
	buffer.clear();
	rf.close();
}

void generate(int size) {
	using hrClock = std::chrono::high_resolution_clock;
	std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int> numb(48, 126);
	std::uniform_int_distribution<int> rnd(100, 100);

	stringstream buffer;

	string fileName = to_string(size);
	fileName += ".txt";
	std::ofstream rf("InputFiles/" + fileName);

	auto start = std::chrono::high_resolution_clock::now();
	int length;
	string smth;
	for (int i = 0; i < size; i++)
	{
		length = rnd(mt);
		smth.clear();
		for (int j = 0; j < length; j++)
		{
			smth += (char)numb(mt);
		}
		buffer << smth;
		if (i < size - 1)
			buffer << "\n";
		std::uniform_int_distribution<int> change(0, length - 1);
		smth.at(change(mt)) = '/';
		buffer << smth;
		i++;
		if (i < size - 1)
			buffer << "\n";
	}

	rf << buffer.str();

	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start; // Skirtumas (s)
	cout << size << " row size generation time " << diff.count() << " s\n";

	buffer.str("");
	buffer.clear();
	rf.close();
}

void hash_function(string txt)
{
	string hash = "DB1C5DAB6DAFFE28BC1C5D6BC8F912995A2C2AA62E60FEEA036931F9F85EC770"; // SEED
	int tmp = 0;
	for (int i = 1; i < 64; i++)					// hash function
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
	hash = string_to_hex(hash);
	hash.resize(64);
	cout << "---------------------------HASH----------------------------------" << endl;
	cout << hash << endl;
}

void hash_function(int lines,vector<string> &col){
	int tmp = 0;
	string hash = "DB1C5DAB6DAFFE28BC1C5D6BC8F912995A2C2AA62E60FEEA036931F9F85EC770"; // SEED
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
	}
	cout << "Eilutciu skaicius: " << lines << endl;
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
	cout << "Koliziju skaicius: " << collision << endl;
}

double compare(string first, string second)
{
	double percent;
	int same = 0;
	for (int i = 0; i < first.size(); i++)
	{
		if (first.at(i) == second.at(i))
			same++;
	}
	percent = ((double)same / first.size()) * 100;
	return percent;
}

string hex_to_binary(string hexdec)
{
	long int i = 0;
	string binary;
	while (hexdec[i]) {

		switch (hexdec[i]) {
		case '0':
			binary += "0000";
			break;
		case '1':
			binary += "0001";
			break;
		case '2':
			binary += "0010";
			break;
		case '3':
			binary += "0011";
			break;
		case '4':
			binary += "0100";
			break;
		case '5':
			binary += "0101";
			break;
		case '6':
			binary += "0110";
			break;
		case '7':
			binary += "0111";
			break;
		case '8':
			binary += "1000";
			break;
		case '9':
			binary += "1001";
			break;
		case 'A':
		case 'a':
			binary += "1010";
			break;
		case 'B':
		case 'b':
			binary += "1011";
			break;
		case 'C':
		case 'c':
			binary += "1100";
			break;
		case 'D':
		case 'd':
			binary += "1101";
			break;
		case 'E':
		case 'e':
			binary += "1110";
			break;
		case 'F':
		case 'f':
			binary += "1111";
			break;
		}
		i++;
	}
	return binary;
}
