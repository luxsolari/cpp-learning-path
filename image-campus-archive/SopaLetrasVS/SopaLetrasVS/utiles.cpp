#include "utiles.h"

int getRandomNumInclusive (const int min, const int max)
{
    return rand() % (max + 1 - min) + min; 
}

int getRandomNumExclusive (const int min, const int max)
{
    return rand() % (max + min) - min;
}

//function for converting string to upper
string stringToUpper(string oString)
{
   for(int i = 0; i < static_cast<int>(oString.length()); i++){  
       oString[i] = toupper(oString[i]);
    }
    return oString;
}

char getRandomChar ()
{
	// Casting de tipo de dato (convertir de un tipo de dato a otro).
	constexpr int min = static_cast<int>('A');
	constexpr int max = static_cast<int>('Z');

	return static_cast<char>(getRandomNumInclusive(min, max));
}

bool estaOcupado (const Casillero& casillero)
{
	if (casillero.esAutogenerado)
        return false;
	return true;
}

bool insertarEnGrilla(Casillero** grilla, const int dimensionGrilla, Palabra& palabra, const bool alAzar)
{
	int cantidadOcupadas;
	int intentos = 1;
	bool insertable = true;
	Coordenada posicionInicio;
	bool insertado;

	switch (palabra.orientacion)  
	{
	case Orientacion::HORIZONTAL:
		// Intentar encontrar lugar para insertar la palabra
		do
		{
			if (alAzar)
			{
				// Elegir una posicion al azar
				posicionInicio = Coordenada(getRandomNumExclusive(0, dimensionGrilla - palabra.longitud), 
					getRandomNumExclusive(0, dimensionGrilla));
				palabra.posicionInicio = posicionInicio;
			}
			else
			{
				// Insertar en la posicion indicada
				posicionInicio = palabra.posicionInicio;
			}

			// Buscar espacios ocupados y señalarlos
			cantidadOcupadas = 0;
			for (int i = 0; i < palabra.longitud; i++)
			{
				if (estaOcupado(grilla[posicionInicio.coordY][posicionInicio.coordX + i]) && 
				grilla[posicionInicio.coordY][posicionInicio.coordX + i].contenido[0] != palabra.palabra[i])
				{
					cantidadOcupadas ++;
				}
			}

			if (cantidadOcupadas > 0)
				intentos ++;
			if (intentos == INTENTOS_MAX)
			{
				insertable = false;
				palabra.intentosDeInsercion = INTENTOS_MAX;
			}
		}
		while (cantidadOcupadas != 0 && intentos <= INTENTOS_MAX);

		// Insertar la palabra
		if (insertable)
		{
			for (int i = 0; i < palabra.longitud; i++)
			{
				Casillero casilleroAInsertar = Casillero(palabra.palabra[i], 
					Coordenada(posicionInicio.coordY, posicionInicio.coordX + i), 
					false);

				if(grilla[posicionInicio.coordY][posicionInicio.coordX + i].contenido[0] == casilleroAInsertar.contenido[0]
					&& !grilla[posicionInicio.coordY][posicionInicio.coordX + i].esAutogenerado)
				{
					casilleroAInsertar.esCompartido = true;
				}

				grilla[posicionInicio.coordY][posicionInicio.coordX + i] = casilleroAInsertar;

			}
			return insertado = true;
		}
		palabra.intentosDeInsercion = intentos;
		break;
	case Orientacion::VERTICAL:
		do
		{
			if (alAzar)
			{
				posicionInicio = Coordenada(getRandomNumExclusive(0, dimensionGrilla), 
					getRandomNumExclusive(0, dimensionGrilla - palabra.longitud));
				palabra.posicionInicio = posicionInicio;
			}
			else
			{
				posicionInicio = palabra.posicionInicio;
			}

			cantidadOcupadas = 0;
			for (int i = 0; i < palabra.longitud; i++)
			{
				if (estaOcupado(grilla[posicionInicio.coordY + i][posicionInicio.coordX]) && 
				grilla[posicionInicio.coordY + i][posicionInicio.coordX].contenido[0] != palabra.palabra[i])
				{
					cantidadOcupadas ++;
				}
			}

			if (cantidadOcupadas > 0)
				intentos ++;
			if (intentos == INTENTOS_MAX)
			{
				insertable = false;
				palabra.intentosDeInsercion = INTENTOS_MAX;
			}
		}
		while (cantidadOcupadas != 0 && intentos <= INTENTOS_MAX);

		if (insertable)
		{
			for (int i = 0; i < palabra.longitud; i++)
			{
				Casillero casilleroAInsertar = Casillero(palabra.palabra[i], 
					Coordenada(posicionInicio.coordY + i, posicionInicio.coordX), 
					false);

				if(grilla[posicionInicio.coordY + i][posicionInicio.coordX].contenido[0] == casilleroAInsertar.contenido[0]
					&& !grilla[posicionInicio.coordY + i][posicionInicio.coordX].esAutogenerado)
				{
					casilleroAInsertar.esCompartido = true;
				}

				grilla[posicionInicio.coordY + i][posicionInicio.coordX] = casilleroAInsertar;
			}
			palabra.intentosDeInsercion = intentos;
			return insertado = true;
		}
		break;
	case Orientacion::DIAGONAL:
		do
		{
			if (alAzar)
			{
				posicionInicio = Coordenada(getRandomNumExclusive(0, dimensionGrilla - palabra.longitud), 
					getRandomNumExclusive(0, dimensionGrilla - palabra.longitud));
				palabra.posicionInicio = posicionInicio;
			}
			else
			{
				posicionInicio = palabra.posicionInicio;
			}

			cantidadOcupadas = 0;
			for (int i = 0; i < palabra.longitud; i++)
			{
				if (estaOcupado(grilla[posicionInicio.coordY + i][posicionInicio.coordX + i]) && 
				grilla[posicionInicio.coordY + i][posicionInicio.coordX + i].contenido[0] != palabra.palabra[i])
				{
					cantidadOcupadas ++;
				}
			}

			if (cantidadOcupadas > 0)
				intentos ++;
			if (intentos == INTENTOS_MAX)
			{
				insertable = false;
				palabra.intentosDeInsercion = INTENTOS_MAX;
			}
		}
		while (cantidadOcupadas != 0 && intentos <= INTENTOS_MAX);

		if (insertable)
		{
			for (int i = 0; i < palabra.longitud; i++)
			{
				Casillero casilleroAInsertar = Casillero(palabra.palabra[i], 
					Coordenada(posicionInicio.coordY + i, posicionInicio.coordX + i), 
					false);

				if(grilla[posicionInicio.coordY + i][posicionInicio.coordX + i].contenido[0] == casilleroAInsertar.contenido[0]
					&& !grilla[posicionInicio.coordY + i][posicionInicio.coordX + i].esAutogenerado)
				{
					casilleroAInsertar.esCompartido = true;
				}

				grilla[posicionInicio.coordY + i][posicionInicio.coordX + i] = casilleroAInsertar;
			}
			palabra.intentosDeInsercion = intentos;
			return insertado = true;
		}
		break;
	default:
		break;
	}
	return insertado = false;
}

void marcarPalabra (Casillero** grilla, const Palabra& palabra, Color color)
{
	switch (palabra.orientacion) 
	{
	case Orientacion::HORIZONTAL:
		for (int i = 0; i < palabra.longitud; i++)
		{
			grilla[palabra.posicionInicio.coordY][palabra.posicionInicio.coordX + i].colorTexto = color;
			if (grilla[palabra.posicionInicio.coordY][palabra.posicionInicio.coordX + i].esCompartido)
			{
				grilla[palabra.posicionInicio.coordY][palabra.posicionInicio.coordX + i].colorFondo = Color::Yellow;
				grilla[palabra.posicionInicio.coordY][palabra.posicionInicio.coordX + i].colorTexto = Color::Black;
			}
		}
		break;
	case Orientacion::VERTICAL:
		for (int i = 0; i < palabra.longitud; i++)
		{
			grilla[palabra.posicionInicio.coordY + i][palabra.posicionInicio.coordX].colorTexto = color;
			if (grilla[palabra.posicionInicio.coordY + i][palabra.posicionInicio.coordX].esCompartido)
			{
				grilla[palabra.posicionInicio.coordY + i][palabra.posicionInicio.coordX].colorFondo = Color::Yellow;
				grilla[palabra.posicionInicio.coordY + i][palabra.posicionInicio.coordX].colorTexto = Color::Black;
			}
		}
		break;
	case Orientacion::DIAGONAL:
		for (int i = 0; i < palabra.longitud; i++)
		{
			grilla[palabra.posicionInicio.coordY + i][palabra.posicionInicio.coordX + i].colorTexto = color;
			if (grilla[palabra.posicionInicio.coordY + i][palabra.posicionInicio.coordX + i].esCompartido)
			{
				grilla[palabra.posicionInicio.coordY + i][palabra.posicionInicio.coordX + i].colorFondo = Color::Yellow;
				grilla[palabra.posicionInicio.coordY + i][palabra.posicionInicio.coordX + i].colorTexto = Color::Black;
			}
		}
		break;
	}
}

void revelarRespuestas (Casillero** grilla, const int dimensionGrilla)
{
	for (int i = 0; i < dimensionGrilla; ++i) 
	{
        for (int j = 0; j < dimensionGrilla; j++)
        {
            if (grilla[i][j].esAutogenerado) grilla[i][j].contenido = ' ';
			else if (grilla[i][j].esCompartido)
			{
				grilla[i][j].colorTexto = Color::Black;
				grilla[i][j].colorFondo = Color::Yellow;
			}
			else if (grilla[i][j].colorTexto != Color::LightGreen)
			{
				grilla[i][j].colorTexto = Color::LightRed;
				grilla[i][j].colorFondo = Color::Black;
			}
        }
    }
}

void randomizarGrilla (Casillero** grilla, const int dimensionGrilla){
	for (int i = 0; i < dimensionGrilla; ++i) 
	{
        grilla[i] = new Casillero[dimensionGrilla];
        for (int j = 0; j < dimensionGrilla; j++)
        {
            grilla[i][j] = Casillero(getRandomChar(), Coordenada(i, j), true);
        }
    }
}

void mostrarGrilla (Casillero** grilla, const int dimensionGrilla)
{
	for (int i = 0; i < dimensionGrilla; i++)
	{
		for (int j = 0; j < dimensionGrilla; j++)
		{
			setBackgroundColor(grilla[i][j].colorFondo);
			setForegroundColor(grilla[i][j].colorTexto);
			cout << grilla[i][j].contenido;
			setBackgroundColor(Color::Black);
			setForegroundColor(Color::White);
			cout << " ";

		}
		cout << endl;
	}
}

void inicializarPalabrasABuscar(vector<Palabra>& palabrasAEncontrar, const string palabrasTematicas[], int palabrasTotales, int dimensionGrilla)
{
	while (static_cast<int>(palabrasAEncontrar.size()) < palabrasTotales)
	{
		const int indiceAInsertar = getRandomNumExclusive(0, MAX_ARRAY_SIZE);
		// agregar palabras que no excedan el tamaño de la grilla
		if (palabrasTematicas[indiceAInsertar].length() < static_cast<unsigned>(dimensionGrilla))
		{
			bool insertable = true;
			// verificar si la palabra se agregó antes
			int instancias = 0;
			for (int j = 0; j < static_cast<int>(palabrasAEncontrar.size()); j++)
			{
				if (palabrasAEncontrar.at(j).palabra == palabrasTematicas[indiceAInsertar])
				{
					instancias++ ;
				}
			}
			// solo permitimos una cierta cantidad de repetidos.
			if (instancias > REPETIDOS_MAXIMOS)
				insertable = false;

			if (insertable)
			{
				Orientacion orientacion;
				if (dimensionGrilla == static_cast<int>(DimensionGrilla::CHICO))
					orientacion = static_cast<Orientacion>(getRandomNumExclusive(0, static_cast<int>(Orientacion::COUNT) - 1));
				else
					orientacion = static_cast<Orientacion>(getRandomNumExclusive(0, static_cast<int>(Orientacion::COUNT)));
				Palabra palabra = Palabra(
					palabrasTematicas[indiceAInsertar],
					orientacion);

				palabrasAEncontrar.push_back(palabra);
			}	
		}
	}
}

Estado estaEnLista(vector<Palabra>& palabrasAEncontrar, const string& palabraBuscada)
{
	vector<Palabra> coincidencias = {};

	for (Palabra& element : palabrasAEncontrar)
	{
		if (element.palabra == palabraBuscada)
			coincidencias.push_back(element);
	}

	if (!coincidencias.empty())
	{
		int noEncontradas = 0;
		for (const Palabra& coincidencia : coincidencias)
		{
			if (!coincidencia.encontrada) noEncontradas ++;
		}

		if (noEncontradas == 0) return Estado::REPETIDO;

		// Magia negra para borrar elementos que cumplan un criterio especifico de una lista
		// https://stackoverflow.com/a/32062165
		palabrasAEncontrar.erase(
			remove_if(palabrasAEncontrar.begin(), palabrasAEncontrar.end(), [&](Palabra const &p)
			{
				return (p.palabra == palabraBuscada);
			}), palabrasAEncontrar.end());

		for (Palabra& coincidencia : coincidencias)
		{
			if (!coincidencia.encontrada)
			{
				coincidencia.encontrada = true;
				palabrasAEncontrar.push_back(coincidencia);
				break;
			}
		}
		for (Palabra& coincidencia : coincidencias)
		{
			if (!coincidencia.encontrada || coincidencia.marcada)
				palabrasAEncontrar.push_back(coincidencia);
		}
		return Estado::ENCONTRADO;
	}
	return Estado::NO_ENCONTRADO;
}

Palabra buscarPalabra (vector<Palabra>& palabrasAEncontrar, const string& palabraBuscada)
{
	for (Palabra& palabra : palabrasAEncontrar)
	{
		if (palabra.palabra == palabraBuscada && palabra.encontrada && !palabra.marcada)
		{
			palabra.marcada = true;
			return palabra;
		}
	}
	return {"", Orientacion::HORIZONTAL};
}

Vector2 getConsoleDimensions ()
{
	Vector2 dimensions;

	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(handle, &csbi);

	dimensions.x = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	dimensions.y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return dimensions;
}

void setCursorPosition (Vector2 position)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos = {(short) position.x, (short) position.y };

	SetConsoleCursorPosition(hConsole, pos);
}

void setBackgroundColor (Color color)
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttrib = 0;
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

	GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);
	wAttrib = screenBufferInfo.wAttributes;

	wAttrib &= ~(BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED | BACKGROUND_INTENSITY);

	int c = (int)color;

	if (c & (int)Color::Blue)
		wAttrib |= BACKGROUND_BLUE;
	if (c & (int)Color::Green)
		wAttrib |= BACKGROUND_GREEN;
	if (c & (int)Color::Red)
		wAttrib |= BACKGROUND_RED;
	if (c & (int)Color::Gray)
		wAttrib |= BACKGROUND_INTENSITY;

	SetConsoleTextAttribute(outputHandle, wAttrib);
}

void setForegroundColor (Color color)
{
	HANDLE outputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	WORD wAttrib = 0;
	CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;

	GetConsoleScreenBufferInfo(outputHandle, &screenBufferInfo);
	wAttrib = screenBufferInfo.wAttributes;

	wAttrib &= ~(FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);

	int c = (int)color;

	if (c & (int)Color::Blue)
		wAttrib |= FOREGROUND_BLUE;
	if (c & (int)Color::Green)
		wAttrib |= FOREGROUND_GREEN;
	if (c & (int)Color::Red)
		wAttrib |= FOREGROUND_RED;
	if (c & (int)Color::Gray)
		wAttrib |= FOREGROUND_INTENSITY;

	SetConsoleTextAttribute(outputHandle, wAttrib);
}
