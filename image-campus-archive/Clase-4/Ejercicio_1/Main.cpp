#include <iostream>
#include <string>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
	// Constantes
	const int LIMITE_SECUENCIA_LARGA = 50;
	// Variables para el loop principal y confirmaciones.
	char input;
	bool continuar = true;

	while (continuar)
	{
		// Inicializar las variables numericas en 0 siempre es buena idea para eliminar cualquier "dato basura" pre-existente
		int n1 = 0;
		int n2 = 0;
		bool n1Correcto = false;
		bool n2Correcto = false;

		do
		{
			cout << "Ingresar el primer numero del intervalo: ";
			cin >> n1;
			if (cin)
			{
				n1Correcto = true;
			}
			else
			{
				// Operaciones sobre el stream de entrada para ignorar los inputs invalidos
				// https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
				cin.clear();
				cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
				cout << "Solo se permite ingresar numeros" << endl;
			}
		} while (!n1Correcto);

		do
		{
			// Ignoramos cualquier cosa q haya quedado por alguna razon en el buffer de entrada y no haya sido descartada.
			// Puede pasar si ingresamos un nro decimal (de punto flotante) en el prompt anterior.
			cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
			cout << "Ingresar el segundo numero del intervalo: ";
			cin >> n2;
			if (cin)
			{
				n2Correcto = true;
			}
			else
			{
				cin.clear();
				cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
				cout << "Solo se permite ingresar numeros" << endl;
			}

		} while (!n2Correcto);
		
		// Ignoramos una vez mas solo para que quede todo limpio.
		cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');

		cout << endl << "Secuencia del intervalo: " << endl;
		if (n1 > n2)
		{
			if ((n1 - n2) >= LIMITE_SECUENCIA_LARGA)
			{
				// La funcion Sleep() está implementada solo para Windows, por lo que buscamos una versión mas "portable".
				// Funciona incluyendo <chrono> y <thread>, necesita C++ 11
				// https://stackoverflow.com/questions/58967466/pause-for-loop-for-1-second-in-c
				cout << "Secuencia larga de numeros, puede tardar un rato..." << endl;
				this_thread::sleep_for(0.5s);
			}

			for (int i = n1; i >= n2; i--)
			{
				cout << i << endl;
				this_thread::sleep_for(0.1s);
			}
		}
		else
		{
			if ((n2 - n1) >= LIMITE_SECUENCIA_LARGA)
			{
				cout << "Secuencia larga de numeros, puede tardar un rato..." << endl;
				this_thread::sleep_for(0.5s);
			}
			for (int i = n1; i <= n2; i++)
			{
				cout << i << endl;
				this_thread::sleep_for(0.1s);
			}
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
