#include <iostream>
#include <string>

using namespace std;

class Debugger
{
public:
	void set_Debugger(bool b) { debug = b; }			// Used to set toggle debugger
	bool get_Debugger() const { return debug; }			// Used to get toggle debugger

	// Used to print messages onto the console
	void get_Debug(std::string str) const { if (get_Debugger()) {std::cout << str << std::endl; } }

private:
	bool debug = false;		// Used for toggling Debugger
};

