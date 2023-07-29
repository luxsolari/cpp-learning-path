// Directiva de pre-procesamiento
#include <iostream> // biblioteca estandar de C++
using std::cout;
using std::cin;
using std::endl;

// Funcion principal de C++
int main () // this is a comment line
{
	// tipo de variable - nombre de variable ;
	int numero; // declaracion de una variable
	numero = 42; // inicializacion de una variable;

	float miNumeroDecimal = 42.5f; // numero decimal
	double miOtroNumeroDecimal = 42.6; // numero decimal de precision doble
	char letra = 'A'; // variable con un solo caracter de texto
	bool variableBooleana = true;

	cout << "Hello world!" << endl;
	
	int suma = numero + miNumeroDecimal;
	cout << suma << endl;
	
	cin.get();
	return 0;
}
