#include <iostream>
using namespace std;

int main () 
{
	int myAwesomeInteger = 5;
	float myAwesomeFloat = 34.65f;
	bool myAwesomeBoolean = (bool) 10;

	if (myAwesomeInteger - myAwesomeInteger)
	{
		cout << "Dentro del if" << endl;
	}
	else {
		cout << "Fuera del if" << endl;
	}

	return 0;
}
