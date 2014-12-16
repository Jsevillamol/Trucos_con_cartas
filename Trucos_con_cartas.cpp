#include <fstream>
#include <iostream>
#include <string>

using namespace std;

//VARIABLES GLOBALES
const int CARTASxPALO=13,
          MAX_CARTAS=52,
          CENTINELA=52;

//TIPOS PROPIOS
typedef enum
{
	picas,
	treboles,
	diamantes,
	corazones
} tPalo;

typedef enum  
{
	A, J=11, Q, K
} tNumero;

typedef int tCarta;
typedef tCarta tMazo[MAX_CARTAS+1];

//FUNCIONES

bool cargar(tMazo mazo, string &nomb);
bool abrir(string &nomb, ifstream &archivo);
string traducir(tCarta carta);
tCarta traducir(string carta);

int main()
{

}

//Carga un mazo de un archivo a elección del usuario.
bool cargar(tMazo mazo, string &nomb)
{
	string linea;
	int cont=0;
	ifstream archivo;
	if (abrir(nomb, archivo))
	{
		getline(linea, archivo);
		while (linea != "x" && cont < MAX_CARTAS)
		{
			mazo[cont] = traducir(linea);
			getline(linea, archivo);
			cont++;
		}
		mazo[cont] = CENTINELA;
		return true;
	}
	else return false;
}

//Abre el archivo que indica el usuario. Si el archivo no existe, se pregunta de nuevo, hasta tres veces.
bool abrir(string &nomb, ifstream &archivo);

string traducir(tCarta carta);
tCarta traducir(string carta);