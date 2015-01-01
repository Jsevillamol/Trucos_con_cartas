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

void vaciar(tMazo mazo);

int cuantas(const tMazo mazo);
tPalo palo(tCarta carta);
tNumero numero(tCarta carta);

bool cargar(tMazo mazo, string &nomb);
bool cargar_auto(tMazo mazo, string &nomb);
bool abrir(string &nomb, ifstream &archivo);
bool agregar(tMazo mazo);
bool guardar(const tMazo mazo, string &nomb);
string traducir(tCarta carta);
tCarta traducir(char p, int n);

void barajar(tMazo mazo);
void intercambiar (tMazo mazo, int pos1, int pos2);
bool desplazar(tMazo mazo, int numero);
int randint(int max);

void cortar(tMazo mazo, int cuantasCartas);
bool partir(tMazo mazo, int cuantasCoger, tMazo otroMazo);
bool unir(tMazo mazo, const tMazo otroMazo);

void mostrar(tMazo mazo);
void mostrar(tCarta carta);

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);
void repartirIntercalando(const tMazo mazo, int enCuantos, int queMazo, tMazo mazoNuevo);

void truco_de_los_tres_montones();

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
		else if (opcion == 6) 
		{
			tMazo negro, rojo;
			repartirNegroRojo(mazo, negro, rojo);
			
			cout << "Negras: " << endl;
			mostrar(negro);
			
			cout << "Rojas: " << endl;
			mostrar(rojo);
		} 
		else if (opcion == 7) 
		{
			tMazo alto, bajo;
			repartirBajaAlta(mazo,bajo,alto);
			
			cout << "Bajas: " << endl;
			mostrar(bajo);
			
			cout << "Altas: " << endl;
			mostrar(alto);
		} 
		else if (opcion == 10)
		{
			truco_de_los_tres_montones();
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
		while (p != 'x' && cont < MAX_CARTAS)
		{
			archivo >> n;
			mazo[cont] = traducir(p,n);
			cont++;
			archivo >> p;
		}
		mazo[cont] = CENTINELA;
		archivo.close();
		return true;
	}
	else return false;
}

bool cargar_auto(tMazo mazo, string &nomb)
{
	char p;
	int cont=0, n;
	ifstream archivo(nomb);
	if (archivo.is_open())
	{
		archivo >> p;
		while (p != 'x' && cont < MAX_CARTAS)
		{
			archivo >> n;
			mazo[cont] = traducir(p,n);
			cont++;
			archivo >> p;
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
	tCarta aux;
	
	aux = mazo[pos1];
	
	mazo[pos1] = mazo[pos2];
	
	mazo[pos2] = aux;
}

bool desplazar(tMazo mazo, int numero)
{
	int total = cuantas(mazo);
	if (total+numero < MAX_CARTAS)
	{
		for (int i = total; i >= 0; i--)
			mazo[i+numero] = mazo[i];
		return true;
	}
	else return false;
}

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas)
{	
	int j=0, k=0;

	for(int i=0; mazo[i] != CENTINELA; i++)
	{
		if     (numero(mazo[i])<8) 
		{
			mazoBajas[j] = mazo[i];
			j++;
		}
		else if(numero(mazo[i])>7) 
		{
			mazoAltas[k] = mazo[i];
			k++;
		}
	}
	mazoBajas[j] = CENTINELA;
	mazoAltas[k] = CENTINELA;
}

void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo)
{
	int j=0, k=0;

	for(int i=0; mazo[i] != CENTINELA; i++)
	{
		if     ((palo(mazo[i]) == picas)||(palo(mazo[i]) == treboles)) 
		{
			mazoNegro[j] = mazo[i];
			j++;
		}
		else if((palo(mazo[i]) == diamantes)||(palo(mazo[i]) == corazones)) 
		{
			mazoRojo[k] = mazo[i];
			k++;
		}
	}
	mazoNegro[j] = CENTINELA;
	mazoRojo [k] = CENTINELA;
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
	int total = cuantas(mazo);
	int otroTotal = cuantas(otroMazo);

	if (desplazar(mazo, otroTotal))
	{
		for (int i = 0; otroMazo[i] != CENTINELA; i++)
		{
			mazo[i] = otroMazo[i];
		}

		return true;
	}
	else return false;
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
	else             cout << n;

	cout << " ";

	if      (p == picas)     cout <<     "de picas";
	else if (p == treboles)  cout <<  "de treboles";
	else if (p == diamantes) cout << "de diamantes";
	else if (p == corazones) cout << "de corazones";

	cout << endl;
}

void vaciar(tMazo mazo)
{
	mazo[0] = CENTINELA;
}

int menu()
{
	cout << "1  - Cargar"                     << endl
	     << "2  - Barajar"                    << endl
	     << "3  - Agregar otro mazo"          << endl
	     << "4  - Cortar"                     << endl
	     << "5  - Guardar"                    << endl
	     << "6  - Separar en negras y rojas"  << endl
	     << "7  - Separar en altas y bajas"   << endl
	     << "8  - Separar en tres montones"   << endl
	     << "9  - Separar en cuatro montones" << endl
	     << "10 - Truco de los tres montones" << endl
	     << "11 - Truco de la Posada"         << endl
	     << "0  - Salir"                      << endl;
	
	int seleccionar = digitoEntre(0,11);

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

void repartirIntercalando(const tMazo mazo, int enCuantos, int queMazo, tMazo mazoNuevo)
{
	int j=0;
	for (int i = queMazo; i<cuantas(mazo); i+=enCuantos, j++)
	{
		mazoNuevo[j] = mazo[i];
	}
	mazoNuevo[j] = CENTINELA;
}

void truco_de_los_tres_montones()
{
	tMazo mazoU, mazo1, mazo2, mazo3;
	string nomb = "3montones.txt";
	int mazo;

	//generamos el mazo de 21 cartas
	cargar_auto(mazoU, nomb);

	for (int i=0; i<3; i++)
	{
		//Repartir alternamente
		repartirIntercalando(mazoU, 3, 1, mazo2);
		repartirIntercalando(mazoU, 3, 2, mazo3);
		repartirIntercalando(mazoU, 3, 0, mazo1);
		vaciar(mazoU);
		//Mostrar
		cout << "Mazo 1:" << endl;
		mostrar(mazo1);
		cout << endl;

		cout << "Mazo 2:" << endl;
		mostrar(mazo2);
		cout << endl;

		cout << "Mazo 3:" << endl;
		mostrar(mazo3);
		cout << endl;

		//El usuario elije mazo
		cout << "En que mazo esta tu carta?" << endl;
		mazo = digitoEntre(1,3);

		//Juntamos los mazos
		if (mazo == 1)
		{
			unir(mazoU, mazo3);
			unir(mazoU, mazo1);
			unir(mazoU, mazo2);
		}
		else if (mazo == 2)
		{
			unir(mazoU, mazo3);
			unir(mazoU, mazo2);
			unir(mazoU, mazo1);
		}
		else //if (mazo == 3)
		{
			unir(mazoU, mazo2);
			unir(mazoU, mazo3);
			unir(mazoU, mazo1);
		}
	}

	//Adivinamos la carta
	cout << "Tu carta era el..." << endl;
	mostrar(mazoU[10]);
}
