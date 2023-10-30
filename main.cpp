#include <iostream>
#include <fstream>
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
	while (!ifs.eof())
	{
		char readline[256];
		ifs.getline(readline, 256);
	}
	ifs.close();
	return 0;
}
