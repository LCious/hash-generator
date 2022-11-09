#include "functions.hpp"
using namespace std;

int main(int argc, char const* argv[])
{
    cout << "Pasirinkite testavimo metoda: " << endl
        << "---------------------------" << endl
        << "1. Ivedimas i konsole. " << endl
        << "2. Ivedimas is failo. " << endl
        << "3. Palyginimas " << endl
        << "4. Failu generavimas " << endl
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
            hash_function(txt);
        }
        else if (input1 == 1)
        {
            hash_function_everyline(lines, col,input1);
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
        "To do comparison";
    }
    else if (input == 4)
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
}
