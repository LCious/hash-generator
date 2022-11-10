#include "functions.hpp"
using namespace std;

void generate_salt(int size, int length, string &salt) {
	using hrClock = std::chrono::high_resolution_clock;
	std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
	std::uniform_int_distribution<int> numb(48, 126); //raides ASCII

	stringstream buffer;	//irasymas i atminti

	for (int i = 0; i < size; i++)	//eiluciu kiekis
	{
		for (int j = 0; j < length; j++)	//eilutes ilgis
		{
			buffer << (char)numb(mt);
		}
		if (i < size - 1)					//paskutinis endl ne (1001) o 1000
			buffer << "\n";
	}
	salt= buffer.str();
	buffer.str("");
	buffer.clear();
}

int main(int argc, char const* argv[])
{
    cout << "Pasirinkite testavimo metoda: " << endl
        << "---------------------------" << endl
        << "1. Ivedimas i konsole. " << endl
        << "2. Ivedimas is failo. " << endl
        << "3. Failu generavimas " << endl
        << "4. Salt " << endl
        << "---------------------------" << endl;
    int input;
    cin >> input;
    int lines = 0;
    string txt;
    stringstream text;
    vector<string> col;
    while (input != 1 && input != 2 && input != 3 && input != 4)
    {
        cout << "Ivestis neteisinga, bandykite isnaujo:" << endl;
        cin >> input;
    }
    if (input == 2)
    {
        vector<string> data;
        string filename;
        cout << "Pasirinkite faila: " << endl
            << "---------------" << endl
            << "a" << endl
            << "b" << endl
            << "randomText1" << endl
            << "randomText2" << endl
            << "1500symbols_1" << endl
            << "1500symbols_2" << endl
            << "empty.txt" << endl
            << "100000" << endl
            << "100000_1000" << endl
            << "konstitucija" << endl
            << "----------------" << endl;
        cin >> filename;
        filename = "InputFiles/" + filename + ".txt";
        ifstream input(filename);
        bool result = file(filename, data);
        for (auto& line : data)
        {
            text << line;
            col.push_back(line);
            lines++;
        }
        txt = text.str();
        cout << "---------------------------------------------" << endl
             << "Ar norite atlikti testavimus? (Ne:0,Taip:1): " << endl
             << "---------------------------------------------" << endl;
        int input1;
        cin >> input1;
        while (input1 != 0 && input1 != 1)
        {
            cout << "Neteisinga ivestis! Bandykite isnaujo";
            cin >> input1;
        }
        if (input1 == 0)
        {
            using hrClock = std::chrono::high_resolution_clock;
            std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));
            auto start = std::chrono::high_resolution_clock::now();
            hash_function(txt);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> diff = end - start; // Skirtumas (s)
            cout << "Hash'avimas uztruko: " << diff.count() << " s\n"; 
        }
        else if (input1 == 1)
        {
            hash_function(lines, col);
            collisions(lines, col);
            vector<double> percent;
            for (int i = 0; i < col.size() - 1; i++) {
                percent.push_back(compare(col.at(i), col.at(i + 1)));
                i++;
            }
            sort(percent.begin(), percent.end());
            double sum = 0;
            for (auto& el : percent) {
                sum += el;
            }
            cout << "----------HEXADECIMAL SIMILARITIES-----------" << endl
            << "minimum similarity: " << percent.at(0) << "%" << endl
            << "average similarity: " << sum / percent.size() << "%" << endl
            << "maximum similarity: " << percent.at(percent.size() - 1) << "%" << endl
            << "---------------------------------------------" << endl;

            // panasumas BINARY
            percent.clear();
            for (int i = 0; i < col.size() - 1; i++) {
                percent.push_back(compare(hex_to_binary(col.at(i)), hex_to_binary(col.at(i + 1))));
                i++;
            }
            sort(percent.begin(), percent.end());
            sum = 0;
            for (auto& el : percent) {
                sum += el;
            }
            cout<< "------------BINARY SIMILARITIES-------------" << endl
            << "minimum similarity: " << percent.at(0) << "%" << endl
            << "average similarity: " << sum / percent.size() << "%" << endl
            << "maximum similarity: " << percent.at(percent.size() - 1) << "%" << endl
            << "---------------------------------------------" << endl;
            hex_to_binary(col.at(0));
        }
    }
    else if (input == 1)
    {
        cout << "Iveskite teksta: ";
        cin.clear();
        cin.ignore(256, '\n');
        getline(cin, txt);
        cout << "Pradinis tekstas: " << endl
        << txt << endl;
        hash_function(txt);
    }
    else if (input == 3)
    {
        cout << "Pasirinkite failo generavima: " << endl
        << "-------------------------------------------" << endl
        << "1. 100000 simboliu ir 1000 eiluciu " << endl
        << "2. 100000 simboliu su skirtingu 1 simboliu " << endl
        << "-------------------------------------------" << endl;
        cin >> input;
        while (input != 1 && input != 2)
        {
            cout << "Ivestis neteisinga, bandykite isnaujo:" << endl;
            cin >> input;
        }
        if (input == 1)
        {
            generate(100000, 1000); // random simboliu eilutes
        }
        else if (input == 2)
        {
            generate(100000); // skiriasi vienas simbolis
        }
    }
    else if(input ==4){
        string salt;
        generate_salt(1,10, salt);
        cout << "Iveskite teksta: ";
        cin.clear();
        cin.ignore(256, '\n');
        getline(cin, txt);
        cout << "Pradinis tekstas: " << endl
        << txt << endl;
        hash_function(txt+salt);
        cout<<"Salt: "<<salt<<endl;
    }
}