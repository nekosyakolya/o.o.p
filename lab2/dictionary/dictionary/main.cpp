#include "stdafx.h"
#include "dictionary.h"

using namespace std;

// use wstring
int main(int argc, char * argv[])
{
	if (!IsValidNumArguments(argc))
	{
		return EXIT_FAILURE;
	}
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const string nameFile = argv[1];
	ifstream dictionaryFile(nameFile);

	Dictionary dictionary = GetDictionaryFromFile(dictionaryFile);

	ProcessTranslation(nameFile, dictionary);
	
	return EXIT_SUCCESS;
}

