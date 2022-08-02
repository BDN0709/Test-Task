#include <Windows.h>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <iostream>

using namespace std;

inline const bool IsTextFile(const WIN32_FIND_DATAA& _File)
{
    const string FullFileName = _File.cFileName;

    return (FullFileName.find(".txt", FullFileName.size() - 5) != string::npos);
}

inline const bool ContainsSpecifedText(const string& _FullPath, const string& _Text)
{
    ifstream fin(_FullPath.c_str());
    string str = "";

    while (getline(fin, str))
        if (str.find(_Text) != string::npos)
        {
            fin.close();
            return true;
        }

    return false;
}

inline const void FindTextFiles(const string& _Path)
{
    string newPath = _Path + "\\*.*";

    WIN32_FIND_DATAA FindedFile = WIN32_FIND_DATAA();

    HANDLE hFind = FindFirstFileA(newPath.c_str(), &FindedFile);

    if (hFind == INVALID_HANDLE_VALUE)
    {
        FindClose(hFind);
        throw runtime_error("Invalid directory path!");
    }

    do
    {
        if (FindedFile.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY && FindedFile.cFileName[0] != '.')
            FindTextFiles(_Path + "\\" + FindedFile.cFileName);
        else if (FindedFile.cFileName[0] == '.')
            continue;
        else
        {
            if (IsTextFile(FindedFile))
                cout << _Path << '\\' << FindedFile.cFileName << endl;
        }

    } while (FindNextFileA(hFind, &FindedFile));

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