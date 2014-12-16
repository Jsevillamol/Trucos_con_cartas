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
int cuantas(tMazo mazo);

bool cargar(tMazo mazo, string &nomb);
bool abrir(string &nomb, ifstream &archivo);
string traducir(tCarta carta);
tCarta traducir(string carta);

void barajar(tMazo mazo);
void intercambiar (tMazo mazo, int posicion1, int posicion2);
int randint(int max);

void cortar(tMazo mazo, int cuantasCartas);
bool partir(tMazo mazo, int cuantasCoger, tMazo otroMazo);
bool unir(tMazo mazo, const tMazo otroMazo);

int main()
{
	return 1;
}

int cuantas(tMazo mazo)
{
	return 1; //Placeholder
}

//Carga un mazo de un archivo a elección del usuario.
bool cargar(tMazo mazo, string &nomb)
{
	string linea;
	int cont=0;
	ifstream archivo;
	if (abrir(nomb, archivo))
	{
		getline(archivo,linea);
		while (linea != "x" && cont < MAX_CARTAS)
		{
			mazo[cont] = traducir(linea);
			getline(archivo,linea);
			cont++;
		}
		mazo[cont] = CENTINELA;
		return true;
	}
	else return false;
}

//Abre el archivo que indica el usuario. Si el archivo no existe, se pregunta de nuevo, hasta tres veces.
bool abrir(string &nomb, ifstream &archivo)
{
	return false; //PLACEHOLDER
}

string traducir(tCarta carta)
{
	return ""; //PLACEHOLDER
}

tCarta traducir(string carta)
{
	return 1; //PLACEHOLDER
}


//Baraja el mazo, intercambiando aleatoriemente cartas
void barajar(tMazo mazo)
{
	int nCartas = cuantas(mazo), pos1, pos2;
	for (int i=0; i<3*nCartas; i++)
	{
		pos1 = randint(nCartas);
		pos2 = randint(nCartas);
		intercambiar(mazo, pos1, pos2);
	}
}

void intercambiar(tMazo mazo, int pos1, int pos2)
{

}

int randint(int max)
{
	return 1; //PLACEHOLDER
}

void cortar(tMazo mazo, int cuantasCartas)
{
	tMazo otroMazo;
	//Corta...
	if (partir(mazo,cuantasCartas,otroMazo))
		//...y completa.
		unir(mazo, otroMazo);
}

bool partir(tMazo mazo, int cuantasCoger, tMazo otroMazo)
{
	return true; //PLACEHOLDER
}

bool unir(tMazo mazo, const tMazo otroMazo)
{
	return true; //PLACEHOLDER
}
