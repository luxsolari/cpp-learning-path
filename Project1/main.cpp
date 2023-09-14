#include <iostream>

enum Opciones
{
	Piedra,
	Papel,
	Tijera
};

using namespace std;

int main()
{
	// Variables
	int opcionJugador;
	int opcionMaquina;
	int resultado;

	// Inicializar el generador de n�meros aleatorios
	srand(time(NULL));

	// Generar la opci�n de la m�quina
	opcionMaquina = rand() % 3;

	// Mostrar el men�
	cout << "Piedra, papel o tijera" << endl;
	cout << "----------------------" << endl;
	cout << "1. Piedra" << endl;
	cout << "2. Papel" << endl;
	cout << "3. Tijera" << endl;
	cout << "Elige una opci�n: ";
	cin >> opcionJugador;

	// Calcular el resultado
	resultado = (opcionJugador - opcionMaquina + 3) % 3;

	// Mostrar el resultado
	cout << "La m�quina ha elegido: ";
	switch (opcionMaquina)
	{
	case Piedra:
		cout << "Piedra" << endl;
		break;
	case Papel:
		cout << "Papel" << endl;
		break;
	case Tijera:
		cout << "Tijera" << endl;
		break;
	}

	cout << "El resultado es: ";
	switch (resultado)
	{
	case 0:
		cout << "Empate" << endl;
		break;
	case 1:
		cout << "Gana la m�quina" << endl;
		break;
	case 2:
		cout << "Gana el jugador" << endl;
		break;
	}

	system("pause");
	return 0;
}
