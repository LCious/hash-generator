#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <cmath>
#include <chrono>
#include <random>

#include <iomanip>
#include <algorithm>
#include <time.h>

using namespace std;

string string_to_hex(const std::string&);

bool file(string, vector<string>&);

void hash_function(string);

void generate(int, int);

void generate(int); 

void hash_function(int,vector<string>&);

void collisions(int, vector<string>);

double compare(string, string);

string hex_to_binary(string);

void comparison();

#endif