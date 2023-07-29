#include <iostream>
#include <algorithm>
using namespace std;

bool divisible (int dividendo, int divisor);

int main()
{
	char input; 
	bool continuar = true;
	int inputs[2] = {};


	while (continuar)
	{
		for (int i = 0; i < 2; i++)
		{
			bool nroCorrecto = false;
			do
		{
			cout << "Ingresar el primer numero a comprobar: ";
			cin >> inputs[i];
			if (cin)
			{
				nroCorrecto = true;
			}
			else
			{
				// Operaciones sobre el stream de entrada para ignorar los inputs invalidos
				// https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
				cin.clear();
				cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
				cout << "Solo se permite ingresar numeros" << endl;
			}
			} while (!nroCorrecto);
		}

		if (inputs[1] != 0)
		{
			if (divisible(inputs[0], inputs[1]))
			{
				cout << "El numero " << inputs[0] << " es divisible por " << inputs[1] << "." << endl;
			}
			else
			{
				cout << "El numero " << inputs[0] << " no es divisible por " << inputs[1] << "." << endl;
			}
		}
		else
		{
			cout << "La division por 0 no esta definida!" << endl;
		}
		
		do
		{
			cout << endl;
			cout << "Ingresar nuevamente? (s/n): ";
			cin >> input;
			switch (input)
			{
			case 'S':
			case 's':
				system("cls");
				break;
			case 'N':
			case 'n':
				cout << "Terminado!" << endl;
				continuar = false;
				break;
			default:
				cout << "Ingresar solamente 's' o 'n'" << endl;
				break;
			}
		} while (input != 'S' && input != 's' && input != 'N' && input != 'n');
	}
}

bool divisible (int dividendo, int divisor)
{
	if (dividendo % divisor == 0)
	{
		return true;
	}
	return false;
}

