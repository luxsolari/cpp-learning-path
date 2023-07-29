#include <iostream>
#include <string>
#include <Windows.h>

using namespace std;

enum CharacterState
{
	Normal   = -1,
	Burning  = 1,
	Frozen   = 2,
	Blinded  = 3,
	Stunned	 = 4,
	Poisoned = 5
};

int main()
{
	CharacterState estadoPersonaje = Burning;


	switch (estadoPersonaje)
	{
		case Burning:
			cout << "quemado" << endl;
			break;
		case Frozen:
			cout << "congelado" << endl;
			break;
		case Blinded:
			cout << "cegado" << endl;
			break;
		case Stunned:
			cout << "paralizado" << endl;
			break;
		case Poisoned:
			cout << "envenenado" << endl;
			break;
		default:
			cout << "otro estado" << endl;
			break;
	}

	return 0;
}
