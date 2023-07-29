#pragma once
#include "tematicas.h"

enum class Orientacion
{
    HORIZONTAL = 0,
    VERTICAL   = 1,
    DIAGONAL   = 2,
    ///////////////
    COUNT      = 3
};

enum class DimensionGrilla
{
    CHICO   = 16,
    MEDIANO = 24,
    GRANDE  = 32,
    /////////////
    COUNT   = 3
};

enum class CantidadPalabras
{
	POQUITAS    = 4,
    POCAS       = 8,
    MAS_O_MENOS = 16,
    MUCHAS      = 24,
    UN_MONTON   = 32
};

enum class Estado
{
	NO_ENCONTRADO = 0,
    ENCONTRADO    = 1,
    REPETIDO      = 2,
    //////////////////
    COUNT         = 3
};

struct Vector2
{
	int x;
	int y;
};

enum class Color
{
	Black, Blue, Green,
	Cyan, Red, Magenta,
	Brown, White, Gray,
	LightBlue, LightGreen, LightCyan,
	LightRed, LightMagenta, Yellow
};

struct Coordenada
{
    int coordX;
    int coordY;

    Coordenada()
    {
        this->coordX = 0;
        this->coordY = 0;
    }

    Coordenada (int coordX, int coordY)
    {
        this->coordX = coordX;
        this->coordY = coordY;
    }
};

struct Casillero
{
    string contenido;
    Coordenada posicion;

    bool esAutogenerado = false;
    bool esCompartido = false;
	Color colorTexto = Color::White;
    Color colorFondo = Color::Black;

    Casillero() = default;
    Casillero (char contenido, Coordenada posicion, bool esAutogenerado)
    {
        this->contenido = contenido;
        this->posicion  = posicion;
        this->esAutogenerado = esAutogenerado;
    }

    Casillero (const string &contenido, Coordenada posicion, bool esAutogenerado)
    {
        this->contenido = contenido;
        this->posicion  = posicion;
        this->esAutogenerado = esAutogenerado;
    }
};

struct Palabra
{
    string palabra;
    int longitud;
    Orientacion orientacion;
    Coordenada posicionInicio;
    int intentosDeInsercion = 0;
    bool encontrada = false;
    bool marcada = false;

    Palabra (const string &palabra, Orientacion orientacion)
    {
        this->palabra = palabra;
        this->longitud = static_cast<int>(palabra.length());
        this->orientacion = orientacion;
        this->posicionInicio = Coordenada(0, 0);
    }
};
