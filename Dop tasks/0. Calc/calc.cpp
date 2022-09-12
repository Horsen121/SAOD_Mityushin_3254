#include <iostream>
#include <string>
#include <typeinfo>

int main(int argc, char** argv)
{
	using namespace std;

	try {
		if(argc!=4)
			throw std::logic_error("Invalid count of arguments");

		switch (*argv[2]) {
		case '+':
			 cout << stoi(argv[1]) + stoi(argv[3]) << endl; break; 
		case '-':
				cout << stoi(argv[1]) - stoi(argv[3]) << endl; break;
		case '*':
				cout << stoi(argv[1]) * stoi(argv[3]) << endl; break;
		case '/':
			if (argv[3] == "0")
				throw std::logic_error("Divide by zero");
			cout << stoi(argv[1]) / stoi(argv[3]) << endl; break;
		case '%':
				cout << stoi(argv[1]) % stoi(argv[3]) << endl; break;
		}
	}
	catch (const exception& e) {
		cout << e.what() << endl;
	}
}