#include <iostream>
#include <chrono>
#include <thread>

using namespace std;

int main()
{
	char input;
	bool continuar = true;

	while (continuar)
	{
		int contadorTurno = 1;
		bool enBatalla = true;

		float vidaMaxJugador = 0.0f;
		float vidaActualJugador = 0.0f;
		float ataqueJugador = 0.0f;

		float vidaMaxEnemigo = 0.0f;
		float vidaActualEnemigo = 0.0f;
		float ataqueEnemigo = 0.0f;

		cout << "TPBS - Totally *Predictable* Battle Simulator" << endl;
		cout << "---------------------------------------------" << endl;

		cout << "Cuantos puntos de vida maxima tiene el jugador? : ";
		cin >> vidaMaxJugador;
		vidaActualJugador = vidaMaxJugador;

		cout << "Cuantos puntos de ataque tiene el jugador? : ";
		cin >> ataqueJugador;


		cout << "Cuantos puntos de vida maxima tiene el enemigo? : ";
		cin >> vidaMaxEnemigo;
		vidaActualEnemigo = vidaMaxEnemigo;

		cout << "Cuantos puntos de ataque tiene el enemigo? : ";
		cin >> ataqueEnemigo;
		cout << endl;
		cout << "---------------------------------------------" << endl;
		cout << "BATTLE START!" << endl;
		cout << "El jugador tiene " << vidaActualJugador << " / " << vidaMaxJugador << " PV y " << ataqueJugador << " de ATK." << endl;
		cout << "El enemigo tiene " << vidaActualEnemigo << " / " << vidaMaxEnemigo << " PV y " << ataqueEnemigo << " de ATK." << endl;
		cout << "---------------------------------------------" << endl;
		cout << endl;
		this_thread::sleep_for(2.5s);

		while (enBatalla)
		{
			cout << "---------------------------------------------" << endl;
			cout << "TURNO " << contadorTurno << ": " << endl;
			this_thread::sleep_for(1s);

			if (vidaActualEnemigo <= ataqueJugador)
			{
				vidaActualEnemigo = 0.0f;
				cout << "El jugador ataca! El enemigo recibe " << ataqueJugador << " de DMG, dejandolo en " << vidaActualEnemigo << " / " << vidaMaxEnemigo << " PV." << endl;
				// El jugador es victorioso, por lo que detenemos la batalla en este punto.
				cout << "El jugador ha ganado la batalla!" << endl;
				enBatalla = false;
			}
			else
			{
				vidaActualEnemigo -= ataqueJugador;
				cout << "El jugador ataca! El enemigo recibe " << ataqueJugador << " de DMG, dejandolo en " << vidaActualEnemigo << " / " << vidaMaxEnemigo << " PV." << endl;

				if (vidaActualJugador <= ataqueEnemigo)
				{
					vidaActualJugador = 0.0f;
					cout << "El enemigo ataca! El jugador recibe " << ataqueEnemigo << " de DMG, dejandolo en " << vidaActualJugador << " / " << vidaMaxJugador << " PV." << endl;
					// El enemigo es victorioso, por lo que detenemos la batalla en este punto.
					cout << "El enemigo ha ganado la batalla!" << endl;
					enBatalla = false;
				}
				else
				{
					vidaActualJugador -= ataqueEnemigo;
					cout << "El enemigo ataca! El jugador recibe " << ataqueEnemigo << " de DMG, dejandolo en " << vidaActualJugador << " / " << vidaMaxJugador << " PV." << endl;
				}
			}
			// Ninguno de los dos participantes tiene 0 PV, por lo que aumentamos el contador de turnos y seguimos.	
			contadorTurno++;
			cout << endl;
			this_thread::sleep_for(2.5s);
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
