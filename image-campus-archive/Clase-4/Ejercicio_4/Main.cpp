#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

enum Elemento 
{
	NINGUNO = 0,
	PIEDRA  = 1,
	PAPEL   = 2,
	TIJERA  = 3
};

enum Resultado
{
	INDEFINIDO = -1,
	EMPATE = 0,
	GANADOR_JUGADOR_1 = 1,
	GANADOR_JUGADOR_2 = 2,

};

int main()
{
	char input;
	bool continuar = true;

	cout << "LOS CREADORES DE:" << endl;
	this_thread::sleep_for(0.5s);
	cout << "TPBS - Totally *Predictable* Battle Simulator" << endl;
	this_thread::sleep_for(0.5s);
	cout << "Presentan..." << endl;
	this_thread::sleep_for(3s);

	while (continuar)
	{
		Elemento elementoJugador1 = NINGUNO;
		Elemento elementoJugador2 = NINGUNO;
		Resultado resultado = INDEFINIDO;

		cout << "--------------------------------------------------" << endl;
		cout << "TP RPS - Totally *Predictable* Rock-Paper-Scissors" << endl;
		cout << "--------------------------------------------------" << endl;

		int inputJugador1;
		do
		{
			cout << "Jugador 1, elija su opcion (1 - PIEDRA, 2- PAPEL, 3 - TIJERA): ";
			cin >> inputJugador1;

			if (!cin.good() || (inputJugador1 < 1 || inputJugador1 > 3))
			{
				// Operaciones sobre el stream de entrada para ignorar los inputs invalidos
				// https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
				cin.clear();
				cout << "Solo se permite ingresar numeros entre 1 y 3." << endl;
			}
			cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
		} while (inputJugador1 < 1 || inputJugador1 > 3);

		// "Casteamos" el tipo int a nuestro enum.
		// https://anteru.net/blog/2007/c-background-static-reinterpret-and-c-style-casts/
		elementoJugador1 = static_cast<Elemento>(inputJugador1);

		system("cls");

		int inputJugador2;
		do
		{
			cout << "Jugador 2, elija su opcion (1 - PIEDRA, 2- PAPEL, 3 - TIJERA): ";
			cin >> inputJugador2;

			if (!cin.good() || (inputJugador2 < 1 || inputJugador2 > 3))
			{
				// Operaciones sobre el stream de entrada para ignorar los inputs invalidos
				// https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
				cin.clear();
				cout << "Solo se permite ingresar numeros entre 1 y 3." << endl;
			}
			cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
		} while (inputJugador2 < 1 || inputJugador2 > 3);

		// "Casteamos" el tipo int a nuestro enum.
		// https://anteru.net/blog/2007/c-background-static-reinterpret-and-c-style-casts/
		elementoJugador2 = static_cast<Elemento>(inputJugador2);

		system("cls");

		switch (elementoJugador1)	
		{
		case PIEDRA:
			cout << "El jugador 1 eligio: PIEDRA" << endl;
			if (elementoJugador2 == PAPEL)
			{
				cout << "El jugador 2 eligio: PAPEL" << endl;
				resultado = GANADOR_JUGADOR_2;
			}
			else if (elementoJugador2 == PIEDRA)
			{
				cout << "El jugador 2 eligio: PIEDRA" << endl;
				resultado = EMPATE;
			}
			else 
			{
				cout << "El jugador 2 eligio: TIJERA" << endl;
				resultado = GANADOR_JUGADOR_1;
			}
			break;
		case PAPEL:
			cout << "El jugador 1 eligio: PAPEL" << endl;
			if (elementoJugador2 == PAPEL)
			{
				cout << "El jugador 2 eligio: PAPEL" << endl;
				resultado = EMPATE;
			}
			else if (elementoJugador2 == PIEDRA)
			{
				cout << "El jugador 2 eligio: PIEDRA" << endl;
				resultado = GANADOR_JUGADOR_1;
			}
			else
			{
				cout << "El jugador 2 eligio: TIJERA" << endl;
				resultado = GANADOR_JUGADOR_2;
			}
			break;
		case TIJERA:
			cout << "El jugador 1 eligio: TIJERA" << endl;
			if (elementoJugador2 == PAPEL)
			{
				cout << "El jugador 2 eligio: PAPEL" << endl;
				resultado = GANADOR_JUGADOR_1;
			}
			else if (elementoJugador2 == PIEDRA)
			{
				cout << "El jugador 2 eligio: PIEDRA" << endl;
				resultado = GANADOR_JUGADOR_2;
			}
			else
			{
				cout << "El jugador 2 eligio: TIJERA" << endl;
				resultado = EMPATE;
			}
			break;
		}

		switch (resultado)
		{
		case EMPATE:
			cout << "El resultado es un empate!" << endl;
			break;
		case GANADOR_JUGADOR_1:
			cout << "El jugador 1 gana!" << endl;
			break;
		case GANADOR_JUGADOR_2:
			cout << "El jugador 2 gana!" << endl;
			break;
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
