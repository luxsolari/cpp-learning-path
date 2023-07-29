#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

enum class Elemento
{
	PIEDRA = 1,
	PAPEL = 2,
	TIJERA = 3
};

enum class Resultado
{
	EMPATE = 0,
	GANADOR_JUGADOR_A = 1,
	GANADOR_JUGADOR_B = 2
};

void mostrarElecciones(string& nombreJugadorA, string& nombreJugadorB, Elemento eleccionJugador1, Elemento eleccionJugador2);
Resultado calcularResultado(Elemento eleccionJugadorA, Elemento eleccionJugadorB);

int main()
{
	constexpr int CANTIDAD_JUGADORES = 4;
	string nombresJugadores[CANTIDAD_JUGADORES] = {};
	Elemento eleccionesJugadores[CANTIDAD_JUGADORES] = {};
	float puntajesJugadores[CANTIDAD_JUGADORES] = {};

	char input; 
	bool continuar = true;
	int nroRonda = 1;

	cout << "MULTI-PLAYER ROCK PAPER SCISSORS!" << endl;
	cout << "Esta version del juego permite hasta una cantidad arbitraria de jugadores! (por default son 4)." << endl;
	cout << "Los jugadores se enfrentan en una ronda de todos contra todos, sin partidos de vuelta." << endl;
	cout << "Las victorias dan 1 punto." << endl;
	cout << "Los empates dan 0.5 puntos." << endl;
	cout << "El ganador al final de todos los juegos sera el jugador con mas puntos acumulados." << endl;
	cout << "-----------------------------------------------------------------------------------------------" << endl;
	cout << "Presionar cualquier tecla para comenzar!" << endl;
	cin.get();

	while (continuar)
	{
		for (int i = 0; i < CANTIDAD_JUGADORES; i++)
		{
			string nombre = "Jugador ";
			nombre += std::to_string(i + 1);
			nombresJugadores[i] = nombre;
			eleccionesJugadores[i] = static_cast<Elemento>((rand() % 3) + 1);

			cout << nombresJugadores[i] << " eligio opcion: " << static_cast<int>(eleccionesJugadores[i]) << endl;
		}

		//for (int i = 0; i < CANTIDAD_JUGADORES; i++)
		//{
		//	string nombreJugador;

		//	cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
		//	getline(cin, nombreJugador);
		//	nombresJugadores[i] = nombreJugador;

		//	int inputJugador;
		//	do
		//	{
		//		cout << nombresJugadores[i] << ", elija su opcion (1 - PIEDRA, 2- PAPEL, 3 - TIJERA): ";
		//		cin >> inputJugador;

		//		if (!cin.good() || (inputJugador < 1 || inputJugador > 3))
		//		{
		//			// Operaciones sobre el stream de entrada para ignorar los inputs invalidos
		//			// https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
		//			cin.clear();
		//			cout << "Solo se permite ingresar numeros entre 1 y 3." << endl;
		//		}
		//		cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
		//	} while (inputJugador < 1 || inputJugador > 3);

		//	switch (inputJugador)
		//	{
		//		case 1:
		//			eleccionesJugadores[i] = Elemento::PIEDRA;
		//			break;
		//		case 2:
		//			eleccionesJugadores[i] = Elemento::PAPEL;
		//			break;
		//		case 3:
		//			eleccionesJugadores[i] = Elemento::TIJERA;
		//			break;
		//	}
		//}

		// Lo que sigue es esencialmente una combinatioria de N elementos tomados de a dos, jugador A y jugador B, sin considerar repeticiones.
		// En este caso, quiero calcular un juego de todos contra todos, pero a diferencia de un "round-robin" con "ida y vuelta",
		// yo solo quiero considerar los casos de "ida".
		// Por ejemplo, si tengo tres jugadores;
		// A debe jugar contra B
		// A debe jugar contra C
		// B   no juega contra A (esto seria el partido de "vuelta", pero no lo quiero considerar)
		// B debe jugar contra C
		// C   no juega contra A (otro caso de "vuelta")
		// C   no juega contra B (otro caso de "vuelta")
		// Eso nos deja solamente con 3 juegos en lugar de los 6 que normalmente tendriamos en un "round-robin".
		//
		// Link a una calculadora para ver la teoria detras del asunto:
		// https://www.hackmath.net/en/calculator/combinations-and-permutations?n=3&k=2&order=1&repeat=0
		int nroJuego = 1;
		cout << endl;
		cout << "-----------------------------------------------------------------------------------------------" << endl;
		for (int jugadorA = 0; jugadorA < CANTIDAD_JUGADORES; jugadorA++)
		{
			for (int jugadorB = jugadorA + 1; jugadorB < CANTIDAD_JUGADORES; jugadorB++)
			{
				if (jugadorA != jugadorB)
				{
					cout << "Juego nro. " << nroJuego << ": ";
					mostrarElecciones(nombresJugadores[jugadorA],
						nombresJugadores[jugadorB],
						eleccionesJugadores[jugadorA],
						eleccionesJugadores[jugadorB]);
					switch (calcularResultado(eleccionesJugadores[jugadorA],
						eleccionesJugadores[jugadorB]))
					{
					case Resultado::GANADOR_JUGADOR_A:
						puntajesJugadores[jugadorA] += 1;
						cout << " " << nombresJugadores[jugadorA] << " ha ganado! + 1 punto" << endl;  
						break;
					case Resultado::GANADOR_JUGADOR_B:
						puntajesJugadores[jugadorB] += 1;
						cout << " " << nombresJugadores[jugadorB] << " ha ganado! + 1 punto" << endl;
						break;
					case Resultado::EMPATE:
						puntajesJugadores[jugadorA] += 0.5f;
						puntajesJugadores[jugadorB] += 0.5f;
						cout << " Es un empate! 0.5 puntos para " << nombresJugadores[jugadorA] << " y " << nombresJugadores[jugadorB] << "." << endl;
					default: break;
					}

					nroJuego++;
				}
			}
		}
		
		cout << endl;
		cout << "RESULTADOS DESPUES DE LA RONDA " << nroRonda << endl;
		for (int i = 0; i < CANTIDAD_JUGADORES; i++)
		{
			cout << "Jugador: " << nombresJugadores[i] << " Puntos: " << puntajesJugadores[i] << endl;
		}

		do
		{
			cout << endl;
			cout << "Siguiente ronda? (s/n): ";
			cin >> input;
			switch (input)
			{
			case 'S':
			case 's':
				nroRonda ++;
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

void mostrarElecciones(string& nombreJugadorA, string& nombreJugadorB, Elemento eleccionJugador1, Elemento eleccionJugador2)
{
	string eleccionJugador1String;
	string eleccionJugador2String;

	switch (eleccionJugador1)
	{
	case Elemento::PIEDRA:
		eleccionJugador1String = "Piedra";
		break;
	case Elemento::PAPEL:
		eleccionJugador1String = "Papel";
		break;
	case Elemento::TIJERA:
		eleccionJugador1String = "Tijera";
		break;
	}

	switch (eleccionJugador2)
	{
	case Elemento::PIEDRA:
		eleccionJugador2String = "Piedra";
		break;
	case Elemento::PAPEL:
		eleccionJugador2String = "Papel";
		break;
	case Elemento::TIJERA:
		eleccionJugador2String = "Tijera";
		break;
	}

	cout << nombreJugadorA << " [" << eleccionJugador1String << "] vs. " << nombreJugadorB << " [" << eleccionJugador2String << "]";
}

Resultado calcularResultado(Elemento eleccionJugadorA, Elemento eleccionJugadorB)
{
	switch (eleccionJugadorA)
	{
	case Elemento::PIEDRA:
		if (eleccionJugadorB == Elemento::PAPEL) return Resultado::GANADOR_JUGADOR_B;
		if (eleccionJugadorB == Elemento::TIJERA) return Resultado::GANADOR_JUGADOR_A;
		break;
	case Elemento::PAPEL:
		if (eleccionJugadorB == Elemento::TIJERA) return Resultado::GANADOR_JUGADOR_B;
		if (eleccionJugadorB == Elemento::PIEDRA) return Resultado::GANADOR_JUGADOR_A;
		break;
	case Elemento::TIJERA:
		if (eleccionJugadorB == Elemento::PIEDRA) return Resultado::GANADOR_JUGADOR_B;
		if (eleccionJugadorB == Elemento::PAPEL) return Resultado::GANADOR_JUGADOR_A;
		break;
	}
	return Resultado::EMPATE;
}
