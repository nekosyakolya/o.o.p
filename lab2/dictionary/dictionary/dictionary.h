#pragma once
#include <boost/algorithm/string.hpp>
#include <boost/optional.hpp>
#include <iostream>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <string> 
#include <Windows.h>
#include "const.h"

/*
������� �� ��� ���������� ������:
* ������� - ������������� ������-������ (����������, ��������, ����������/��������� ��������)
* ���������� - ������� � �������������, ���������� ��������
*/


using  Dictionary = std::map<std::string, std::string>;

Dictionary GetDictionaryFromFile(std::ifstream &dictionary);//b

bool FoundTransfer(Dictionary & myFirstMap, const std::string &key);//b

bool IsValidNumArguments(int argc);//b

void StorageChanges(Dictionary & dictionary, const std::string &nameFile);//b
void ProcessExit(Dictionary & dictionary, const std::string &nameFile);
void ProcessTranslation(const std::string &nameFile, Dictionary &dictionary);
bool FoundWord(Dictionary &dictionary, std::string & key);//b

void AddNewWord(Dictionary &dictionary, const std::string & value, const std::string & key);
