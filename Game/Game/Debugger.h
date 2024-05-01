#include <iostream>
#include <string>

using namespace std;

class Debugger
{
public:
	void set_Debugger(bool b) { debug = b; }
	bool get_Debugger() const { return debug; }
	void get_Debug(std::string str) const { if (get_Debugger()) {std::cout << str << std::endl; } }

private:
	bool debug = false;
};

