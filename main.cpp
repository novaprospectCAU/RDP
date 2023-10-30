#include <iostream>
#include <fstream>
#include <sstream>
#include "utils.hpp"

using namespace std;

int main(int argc, char *argv[])
{
	// 예외: 파일이 입력되지 않은 경우나 두 개 이상의 파일이 들어온 경우
	if (argc != 2)
	{
		cout << "only one file required" << endl;
		return 0;
	}

	const string FILENAME = argv[1];
	ifstream ifs;
	ifs.open(FILENAME);
	if (!ifs.is_open())
	{
		cout << "file not existed" << endl;
		return 0;
	}

	int line_count = 0;
	while (!ifs.eof())
	{
		char line_temp[128];
		ifs.getline(line_temp, 128);
		line_count++;
	}
	string str_split[line_count][64];
	ifs.close();

	ifs.open(FILENAME);
	int line_index = 0;
	while (!ifs.eof())
	{
		int word_index = 0;
		char line_temp[128];
		ifs.getline(line_temp, 128);
		istringstream temp(line_temp);
		string word;
		while (temp >> word)
		{
			str_split[line_index][word_index] = word;
			word_index++;
		}
		line_index++;
	}
	ifs.close();
	return 0;
}
