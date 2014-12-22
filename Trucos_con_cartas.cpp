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
int menu();
int digitoEntre(int a, int b);

int cuantas(const tMazo mazo);
tPalo palo(tCarta carta);
tNumero numero(tCarta carta);

bool cargar(tMazo mazo, string &nomb);
bool abrir(string &nomb, ifstream &archivo);
bool agregar(tMazo mazo);
bool guardar(const tMazo mazo, string &nomb);
string traducir(tCarta carta);
tCarta traducir(char p, int n);

void barajar(tMazo mazo);
void intercambiar (tMazo mazo, int posicion1, int posicion2);
int randint(int max);

void cortar(tMazo mazo, int cuantasCartas);
bool partir(tMazo mazo, int cuantasCoger, tMazo otroMazo);
bool unir(tMazo mazo, const tMazo otroMazo);

void mostrar(tMazo mazo);
void mostrar(tCarta carta);
void vaciar(tMazo mazo);

int main()
{
	int opcion, cantidad;
	tMazo mazo;
	string nomb;

	srand(time(NULL));
	vaciar(mazo);

	do
	{
		opcion = menu();
		if (opcion == 1) 
		{
			if (cargar(mazo, nomb))
				mostrar(mazo);
			else cout << "El archivo no pudo cargarse." << endl;
		}
		else if (opcion == 2) 
		{
			barajar(mazo);
			cout << "Mazo barajado:" << endl;
			mostrar(mazo);
		}
		else if (opcion == 3) 
		{
			agregar(mazo);
			cout << "Mazo actual:" << endl;
			mostrar(mazo);
		}
		else if (opcion == 4) 
		{
			cout << "Cuantas?";
			cin >> cantidad;
			cortar(mazo, cantidad);
			cout << "Mazo actual:" << endl;
			mostrar(mazo);
		}
		else if (opcion == 5) 
		{
			if (guardar(mazo, nomb)) 
				 cout << "Guardado exitoso!" << endl;
			else cout << "Fallo al guardar" << endl;
		}
	}while(opcion != 0);

	return 1;
}

int cuantas(const tMazo mazo)
{
	int i;
	
	for(i=0; mazo[i] != CENTINELA; i++);
	
	return i;
}

tPalo palo(tCarta carta)
{
	int seccionPalo;
	
	seccionPalo = (carta / CARTASxPALO);
	
	if(seccionPalo == 0)
		return picas;
	else if(seccionPalo == 1)
		return treboles;
	else if(seccionPalo == 2)
		return diamantes;
	else //if(seccionPalo == 3)
		return corazones;
}

tNumero numero(tCarta carta)
{
	int seccionNumero;
	
	seccionNumero = (carta % CARTASxPALO);
	
	return tNumero (seccionNumero+1);
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
		archivo.close();
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

//Concatena al mazo actual un mazo cargado de archivo.
bool agregar(tMazo mazo)
{
	tMazo otroMazo;
	string nomb;
	if (!cargar(otroMazo, nomb))
	{
		cout << "No pudo cargarse el archivo" << endl;
		return false;
	}
	else if (!unir(mazo, otroMazo))
	{
		cout << "El mazo seleccionado junto al actual superan el limite de cartas por mazo" << endl;
		return false;
	}
	else return true;
}

bool guardar(const tMazo mazo, string &nomb)
{
	string response;
	ofstream archivo;
	
	cout << "En que archivo quieres guardar el mazo? (intro para " << nomb << ")" << endl;
	cin.sync();
	getline(cin, response);

	if (response == "") archivo.open(nomb);
	else 
	{
		archivo.open(response);
		nomb == response;
	}

	if (archivo.is_open())
	{
		for(int i = 0; mazo[i] != CENTINELA; i++)
		{
			archivo << traducir(mazo[i]) << endl;
		}
		archivo << "x";
		return true;
	}
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

	if (p == 'c')      suit = corazones;
	else if (p == 't') suit = treboles;
	else if (p == 'p') suit = picas;
	else if (p == 'd') suit = diamantes;

	return (n-1 + int (suit) * CARTASxPALO);
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
	int total = cuantas(mazo), i;

	if (total + cuantas(otroMazo) > MAX_CARTAS) return false;
	else
	{
		for (i = 0; otroMazo[i] != CENTINELA; i++)
		{
			mazo[total + i] = otroMazo[i];
		}

		mazo[total+i] = CENTINELA;
		
		return true;
	}
}

void mostrar(tMazo mazo)
{
	for(int i=0; mazo[i] != CENTINELA && i<MAX_CARTAS; i++)
	{
		mostrar(mazo[i]);
	}
	cout << endl;
}

void mostrar(tCarta carta)
{
	tPalo p = palo(carta);
	tNumero n = numero(carta);
	
	if      (n == A) cout << "A";
	else if (n == J) cout << "J";
	else if (n == Q) cout << "Q";
	else if (n == K) cout << "K";

	cout << " ";

	if      (p == picas)     cout <<     "de picas";
	else if (p == treboles)  cout <<  "de treboles";
	else if (p == diamantes) cout << "de diamantes";
	else if (p == diamantes) cout << "de corazones";

	cout << " ";
}

void vaciar(tMazo mazo)
{
	mazo[0] = CENTINELA;
}

int menu()
{
	cout << "1 - Cargar"                    << endl
	     << "2 - Barajar"                   << endl
	     << "3 - Agregar otro mazo"         << endl
	     << "4 - Cortar"                    << endl
	     << "5 - Guardar"                   << endl
	     << "0 - Salir"                     << endl;
	
	int seleccionar = digitoEntre(0,6);

	return seleccionar;
}

int digitoEntre(int a, int b)
{
	int digito = -1;

	do
	{
		cin.sync(); //Por si quedan datos basura en el buffer
		cin >> digito;

		if (cin.fail())
		{
			cout << "Error! Introduce un digito" << endl;
			cin.clear();
		}

		else if (digito < a || digito > b)
		{
			cout << "Error! Introduce un digito entre " << a << " y " << b << endl;
			digito = -1;
		}
		
	}
	while (digito == -1);

	return digito;
}
