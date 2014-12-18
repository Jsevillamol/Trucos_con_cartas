#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

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
	A=1, J=11, Q, K
} tNumero;

typedef int tCarta;
typedef tCarta tMazo[MAX_CARTAS+1];

//FUNCIONES
int cuantas(tMazo mazo);
tPalo palo(tCarta carta);
tNumero numero(tCarta carta);

bool cargar(tMazo mazo, string &nomb);
bool abrir(string &nomb, ifstream &archivo);
string traducir(tCarta carta);
tCarta traducir(char p, int n);

void barajar(tMazo mazo);
void intercambiar (tMazo mazo, int posicion1, int posicion2);
int randint(int max);

void cortar(tMazo mazo, int cuantasCartas);
bool partir(tMazo mazo, int cuantasCoger, tMazo otroMazo);
bool unir(tMazo mazo, const tMazo otroMazo);

void mostrar(tMazo mazo);
void vaciar(tMazo mazo);

int main()
{
	srand(time(NULL));
	return 1;
}

int cuantas(tMazo mazo)
{
	int i;
	
	for(i=0; mazo[i] != CENTINELA; i++);
	
	return i;
}

tPalo palo(tCarta carta)
{
	return picas;
}

tNumero numero(tCarta carta)
{
	return A;
}

//Carga un mazo de un archivo a elección del usuario.
bool cargar(tMazo mazo, string &nomb)
{
	char p;
	int cont=0, n;
	ifstream archivo;
	if (abrir(nomb, archivo))
	{
		archivo >> p;
		archivo >> n;
		while (p != 'x' && cont < MAX_CARTAS)
		{
			mazo[cont] = traducir(p,n);
			archivo >> p;
			archivo >> n;
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
	cout << "Introduzca el nombre del archivo:" << endl;
	cin >> nomb;
	archivo.open(nomb);	
	
	if(!archivo.is_open())
	{
		for(int i=0; (i<2) && (!archivo.is_open()); i++)
		{
			cout << "Error, no se ha encontrado el archivo " << nomb << endl;
			cin  >> nomb;
			archivo.open(nomb);
		}
	}
	if(archivo.is_open()) return true;
	
	else return false;
}

string traducir(tCarta carta)
{
	string s="";
	switch (palo(carta))
	{
		case 0: 
			s+="p";
			break;
		case 1:
			s+="t";
			break;
		case 2:
			s+="d";
			break;
		case 3:
			s+="c";
			break;
	}
	s += " ";
	s += to_string(numero(carta));
	return s;
}

tCarta traducir(char p, int n)
{
	tPalo suit;

	if (p == 'c')     suit = corazones;
	else if (p == 't') suit = treboles;
	else if (p == 'p') suit = picas;
	else if (p == 'd') suit = diamantes;

	return n + int (suit) * CARTASxPALO;
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
	return rand() % (max + 1);
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
	int i;
	if (cuantasCoger > cuantas(mazo)) return false;
	else
	{
		for (i = 0; mazo[cuantasCoger + i] != CENTINELA; i++)
		{
			otroMazo[i] = mazo[cuantasCoger + i];
		}

		mazo[cuantasCoger] = CENTINELA;
		otroMazo[i] = CENTINELA;

		return true;
	}
}

bool unir(tMazo mazo, const tMazo otroMazo)
{
	return true; //PLACEHOLDER
}

void mostrar(tMazo mazo)
{
	for(int i=0; mazo[i] != CENTINELA && i<MAX_CARTAS; i++)
	{
		cout << traducir(mazo[i]) << " ";
	}
	cout << endl;
}

void vaciar(tMazo mazo)
{
	mazo[0] = CENTINELA;
}
