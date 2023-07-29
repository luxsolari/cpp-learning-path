#include <iostream>
#include <algorithm>
using namespace std;

int multiplicarConSumas (int a, int b);

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
			cout << "Ingresar el primer numero: ";
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

		cout << "El resultado de la multiplicacion es: " << multiplicarConSumas(inputs[0], inputs[1]);

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

int multiplicarConSumas (int a, int b)
{
	int resultado = 0;
	bool resultadoNegativo = false;

	if (a < 0 && b < 0)
	{
		a = (a * -1);
		b = (b * -1);
	}
	else
	{
		if (a < 0)
		{
			resultadoNegativo = true;
			a = (a * -1);
		}
		if (b < 0)
		{
			resultadoNegativo = true;
			b = (b * -1);
		}	
	}

	for (int i = 0; i < b; i ++)
	{
		resultado += a;
	}

	if (resultadoNegativo) return (resultado * -1);
	return resultado;
}

