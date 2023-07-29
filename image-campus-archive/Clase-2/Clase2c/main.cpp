#include<iostream>
using namespace std;

int main()
{
	cout << "Hello world!" << endl;
	int primerNumero;
	int segundoNumero;

	cout << "Primer numero: ";
	cin >> primerNumero;

	cout << "Segundo numero: ";
	cin >> segundoNumero;

	bool sonIguales = (primerNumero == segundoNumero);
	bool sonDiferentes = (primerNumero != segundoNumero);
	bool esMayor = (primerNumero > segundoNumero);
	bool esMenor = (primerNumero < segundoNumero);
	bool esMayorOIgual = (primerNumero >= segundoNumero);
	bool esMenorOIgual = (primerNumero <= segundoNumero);

	if (sonIguales)
	{
		cout << "Los numeros ingresados son iguales" << endl;
	}
	else if (esMayor)
	{
		cout << "El primer numero es mayor al segundo" << endl;
	}
	else
	{
		cout << "Los numeros ingresados no son iguales" << endl;
	}
}
