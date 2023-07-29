// Directiva de pre-procesamiento
#include <iostream> // biblioteca estandar de C++
using std::cout;
using std::cin;
using std::endl;

// Funcion principal de C++
int main() // this is a comment line
{
	cout << "Hello world!" << endl;
	int primerNumero;
	int segundoNumero;

	cout << "Primer numero: ";
	cin >> primerNumero;

	cout << "Segundo numero: ";
	cin >> segundoNumero;

	int suma = primerNumero + segundoNumero;
	cout << "La suma es igual a: " << suma << endl;

	cin.get();
	return 0;
}
