#include<iostream>

using namespace std;

int main()
{
	// Constantes
	const int N = 20;

	// Variables
	int nroAMostrar = 0;
	char input;
	bool inputCorrecto = false;
	bool continuar = true;

	while (continuar)
	{
		do
		{
			cout << "Ingrese el numero para mostrar su tabla: ";
			cin >> nroAMostrar;
			if (cin)
			{
				inputCorrecto = true;
			}
			else
			{
				// Operaciones sobre el stream de entrada para ignorar los inputs invalidos
				// https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
				cin.clear();
				cout << "Solo se permite ingresar numeros" << endl;
			}
			cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
		} while (!inputCorrecto);

		for (int i = 0; i < N; i++)
		{
			cout << nroAMostrar << " x " << i << " = " << nroAMostrar * i << endl;
		}

		do
		{
			cout << endl;
			cout << "Comenzar de nuevo? (s/n): ";
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


	return 0;
}