#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <iostream>

using namespace std;

inline const void FindTextFiles(const string& _Path)
{
    string newPath = _Path + "\\*.*";

    WIN32_FIND_DATAA Finder = WIN32_FIND_DATAA();

    HANDLE hFind = FindFirstFileA(newPath.c_str(), &Finder);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        FindClose(hFind);
        throw runtime_error("Invalid directory path!");
    }

    do
    {
        if (Finder.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && Finder.cFileName[0] != '.')
            FindTextFiles(_Path + "\\" + Finder.cFileName);
        else if (Finder.cFileName[0] == '.')
            continue;
        else
            cout << _Path << '\\' << Finder.cFileName << endl;

    } while (FindNextFileA(hFind, &Finder));

    FindClose(hFind);
    return;
}

int main(int argc, char** argv)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	if (argc < 3)
	{
		cout << "Directory path or text is not stated!" << endl;
		return -1;
	}

	const string DIRECTORY = argv[1];
	const string TEXT = argv[2];

    try
    {
        FindTextFiles(DIRECTORY);
    }
    catch (const exception& ex)
    {
        cout << "Runtime Error: " << ex.what() << endl;

        return -3;
    }

	return 0;
}