#include <iostream>
#include <Windows.h>
using namespace std;

// Constantes globales
const int TIEMPO_DELAY_SEGUNDOS = 0.2;
const float CURACION_DE_POCION = 25.0f;
char respuesta;

int main()
{
	int vidaMaxima = 100.0f;
    int vidaActual = vidaMaxima;

	while (vidaActual > 1.0f)
	{
		cout << "Vida del jugador: " << vidaActual << endl;
		if (vidaActual <= (vidaMaxima * 0.25))
		{
			cout << "Quiere utilizar una pocion? (s/n): ";
			cin >> respuesta;
			if (respuesta == 's')
			{
				vidaActual += CURACION_DE_POCION;
			}
		}
		vidaActual--;
		Sleep(TIEMPO_DELAY_SEGUNDOS * 1000);
		system("cls");
	}
    return 0;
}