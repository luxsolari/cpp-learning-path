#include <iostream>

using namespace std;

int main()
{
	int numero1 = 0;
	int numero2 = 0;
	int intermedios = 0;

	cout << "Ingrese el primer nunero: " << endl;
	cin >> numero1;

	cout << "Ingrese el segundo numero: " << endl;
	cin >> numero2;

	cout << numero1 << endl;

	do
	{
		intermedios == numero1;

		cout << intermedios++ << endl;

	} while (intermedios < numero2);

	cout << numero2 << endl;

}
