#include <iostream>
#include <string>
using namespace std;

void inicializarArreglos(int cantidadDeArreglos, int** listaDeArreglos);
int buscarEnArreglo(int nroBuscado, int longitudArreglo, int* arreglo);

int main()
{
	int cantidadDeArreglos = 0;
	cout << "Ingrese la cantidad de arreglos a inicializar:";
	cin >> cantidadDeArreglos;

	// Creamos un array bidimensional (lista de listas)
	int** listaDeArreglos = new int* [cantidadDeArreglos];
	inicializarArreglos(cantidadDeArreglos, listaDeArreglos);

	int nroBuscado;
	bool nroBuscadoCorrecto = false;
	do
	{
		cout << "Ingresar un numero a buscar dentro de la lista de arreglos:" << endl;
		cin >> nroBuscado;
		if (cin.good())
		{
			nroBuscadoCorrecto = true;
			for (int i = 0; i < cantidadDeArreglos; i++)
			{
				int coincidencias = buscarEnArreglo(nroBuscado, listaDeArreglos[i][0], listaDeArreglos[i]);
				if (coincidencias > 0)
					cout << "El nro " << nroBuscado << " se encontro " << coincidencias << " veces en el arreglo nro. " << i << "." << endl;
				else
					cout << "El nro " << nroBuscado << " no se encontro en el arreglo nro. " << i << "." << endl;
			}
		}
		else
		{
			// Operaciones sobre el stream de entrada para ignorar los inputs invalidos
			// https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
			cin.clear();
			cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
			cout << "Solo se permite ingresar numeros" << endl;
		}
	} while (!nroBuscadoCorrecto);
	// Borramos recursos usados que fueron creados con new
	delete[] listaDeArreglos;
	return 0;
}

void inicializarArreglos(int cantidadDeArreglos, int** listaDeArreglos)
{
	for (int i = 0; i < cantidadDeArreglos; i++)
	{
		int longitud;
		bool longitudCorrecta = false;

		do
		{
			cout << "Incializando el array " << i + 1 << endl;
			cout << "Que longitud tiene este array?: ";
			cin >> longitud;

			if (cin.good())
			{
				longitudCorrecta = true;
				// Asignamos un elemento mas que los necesarios al array, para el truco explicado en el comentario abajo.
				listaDeArreglos[i] = new int[longitud + 1];

				for (int j = 0; j < longitud + 1; j++)
				{
					if (j == 0)
					{
						// Con este "truco", guardo la longitud del array dinamico en el elemento 0,
						// para poder conocer su tamaño mas adelante sin tener que
						// recurrir bucles complicados de conteo de elementos.
						// https://stackoverflow.com/questions/492384/how-to-find-the-sizeof-a-pointer-pointing-to-an-array
						listaDeArreglos[i][j] = longitud;
					}
					else
					{
						int valorElemento;
						bool valorCorrecto = false;
						do
						{
							cout << "Cual es el valor del elemento " << j << "?: ";
							cin >> valorElemento;
							if (cin.good())
							{
								valorCorrecto = true;
								listaDeArreglos[i][j] = valorElemento;
							}
							else
							{
								// Operaciones sobre el stream de entrada para ignorar los inputs invalidos
								// https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
								cin.clear();
								cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
								cout << "Solo se permite ingresar numeros" << endl;
							}
						} while (!valorCorrecto);
					}

				}
			}
			else
			{
				// Operaciones sobre el stream de entrada para ignorar los inputs invalidos
				// https://stackoverflow.com/questions/5655142/how-to-check-if-input-is-numeric-in-c
				cin.clear();
				cin.ignore((std::numeric_limits<std::streamsize>::max()), '\n');
				cout << "Solo se permite ingresar numeros" << endl;
			}
		} while (!longitudCorrecta);
	}
}
int buscarEnArreglo(int nroBuscado, int longitudArreglo, int* arreglo)
{
	int coincidencias = 0;
	// Comenzamos a contar desde 1, porque los arreglos dinámicos tienen su longitud guardada en la primer posición.
	for (int i = 1; i <= longitudArreglo; i++)
	{
		if (nroBuscado == arreglo[i])
			coincidencias++;
	}
	return coincidencias;
}
