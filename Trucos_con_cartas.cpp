#include <fstream>
#include <iostream>
#include <iomanip>
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
//Menus
int menu();
int digitoEntre(int a, int b);

//Funciones de obtencion de datos
int cuantas(const tMazo mazo);

tPalo palo(tCarta carta);
tNumero numero(tCarta carta);

//Funciones de output
void mostrar(tMazo mazo);
void mostrar(tCarta carta);

//Funciones de carga y guardado de mazos
bool cargar(tMazo mazo, string &nomb);
bool cargar_auto(tMazo mazo, string &nomb);
bool abrir(string &nomb, ifstream &archivo);
bool agregar(tMazo mazo);

bool guardar(const tMazo mazo, string &nomb);

string traducir(tCarta carta);
tCarta traducir(char p, int n);

//Funciones de manipulacion de un mazo individual
void vaciar(tMazo mazo);

void barajar(tMazo mazo);
int randint(int max);
void intercambiar (tMazo mazo, int pos1, int pos2);
bool desplazar(tMazo mazo, int numero);

void cortar(tMazo mazo, int cuantasCartas);
bool partir(tMazo mazo, int cuantasCoger, tMazo otroMazo);
bool unir(tMazo mazo, const tMazo otroMazo);

//Funciones para repartir en varios mazos
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);

void repartirIntercalando(const tMazo mazo, int enCuantos, int queMazo, tMazo mazoNuevo);
void repartir_en_tres(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3);
void repartir_en_cuatro(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3, tMazo mazo4);

//Trucos de magia
void truco_de_los_tres_montones();
void truco_de_la_posada();

//System
void pausa();

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
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			if (cargar(mazo, nomb))
				mostrar(mazo);
			else cout << "El archivo no pudo cargarse." << endl;
		}
		else if (opcion == 2) 
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			barajar(mazo);
			cout << "Mazo barajado:" << endl;
			mostrar(mazo);
		}
		else if (opcion == 3) 
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			agregar(mazo);
			cout << "Mazo actual:" << endl;
			mostrar(mazo);
		}
		else if (opcion == 4) 
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ')
		         << "Cuantas?";
			cin >> cantidad;
			cortar(mazo, cantidad);
			cout << "Mazo actual:" << endl;
			mostrar(mazo);
		}
		else if (opcion == 5) 
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			if (guardar(mazo, nomb)) 
				 cout << "Guardado exitoso!" << endl;
			else cout << "Fallo al guardar" << endl;
		}
		else if (opcion == 6) 
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			tMazo negro, rojo;
			repartirNegroRojo(mazo, negro, rojo);
			
			cout << "Negras: " << endl;
			mostrar(negro);
			
			cout << "Rojas: " << endl;
			mostrar(rojo);
		} 
		else if (opcion == 7) 
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			tMazo alto, bajo;
			repartirBajaAlta(mazo,bajo,alto);
			
			cout << "Bajas: " << endl;
			mostrar(bajo);
			
			cout << "Altas: " << endl;
			mostrar(alto);
		} 
		else if (opcion == 8) 
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			tMazo mazo1, mazo2, mazo3;
			repartir_en_tres(mazo, mazo1, mazo2, mazo3);
		}
		else if (opcion == 9) 
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			tMazo mazo1, mazo2, mazo3, mazo4;
			repartir_en_cuatro(mazo, mazo1, mazo2, mazo3, mazo4);
		}
		else if (opcion == 10)
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			truco_de_los_tres_montones();
		}
		else if (opcion == 11)
		{
			cout << setfill('-') << setw(79) <<  '-'  << endl
		         << setfill(' ');
			truco_de_la_posada();
		}
	}while(opcion != 0);

	return 1;
}

int menu()
{
	cout << setfill('-') << setw(79) <<  '-'  << endl
		 << setfill(' ')
		 << "1  - Cargar"                     << endl
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
	
	return digitoEntre(0,11);
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
void vaciar(tMazo mazo)
{
	mazo[0] = CENTINELA;
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

int randint(int max)
{
	return rand() % (max);
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

void repartirIntercalando(const tMazo mazo, int enCuantos, int queMazo, tMazo mazoNuevo)
{
	int j=0;
	for (int i = queMazo; i<cuantas(mazo); i+=enCuantos, j++)
	{
		mazoNuevo[j] = mazo[i];
	}
	mazoNuevo[j] = CENTINELA;
}

void repartir_en_tres(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3)
{
	//Repartir alternamente
	repartirIntercalando(mazo, 3, 1, mazo2);
	repartirIntercalando(mazo, 3, 2, mazo3);
	repartirIntercalando(mazo, 3, 0, mazo1);

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
}

void repartir_en_cuatro(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3, tMazo mazo4)
{
	//Repartir alternamente
	repartirIntercalando(mazo, 4, 1, mazo2);
	repartirIntercalando(mazo, 4, 2, mazo3);
	repartirIntercalando(mazo, 4, 3, mazo4);
	repartirIntercalando(mazo, 4, 0, mazo1);
	
	//Mostramos los mazos
	cout << "Mazo 1:" << endl;
	mostrar(mazo1);
	cout << endl;

	cout << "Mazo 2:" << endl;
	mostrar(mazo2);
	cout << endl;

	cout << "Mazo 3:" << endl;
	mostrar(mazo3);
	cout << endl;

	cout << "Mazo 4:" << endl;
	mostrar(mazo4);
	cout << endl;
}

void truco_de_los_tres_montones()
{
	tMazo mazoU, mazo1, mazo2, mazo3;
	string nomb = "3montones.txt";
	int mazo;

	//generamos el mazo de 21 cartas
	if(cargar_auto(mazoU, nomb))
	{
		for (int i=0; i<3; i++)
		{
			//Repartir alternamente
			repartir_en_tres(mazoU, mazo1, mazo2, mazo3);
			vaciar(mazoU);

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
	else
	{
		cout << "Archivo \"3montones.txt\" no encontrado" << endl;
	}
}

void truco_de_la_posada()
{
	tMazo mazo1, mazo2, mazo3, mazo4;
	string nomb = "posada.txt";
	int corte;
	
	if (cargar_auto(mazo1, nomb)){
	
		//Contamos la historia
		cout << "Habia una vez una posada con cuatro habitaciones."   << endl
			 << "Un dia llegaron cuatro caballeros y cada uno se" 
			 << "puso en una habitacion diferente."                   << endl
			 << "Luego llegaron cuatro senioras, y para no dejarlas" 
			 << "sin habitacion, ubicaron a cada una en una de dichas"
			 << "habitaciones, con los caballeros."                   << endl
			 << "Luego llegaron cuatro reyes con sus cuatro peones,"
			 << "y pusieron cada rey y cada peon en alguna de dichas" << endl
			 << "cuatro habitaciones. "                               << endl;
		 	 
		pausa();
		repartir_en_cuatro(mazo1, mazo1, mazo2, mazo3, mazo4);
		
		//Juntamos los mazos
		unir(mazo1, mazo2);
		unir(mazo1, mazo3);
		unir(mazo1, mazo4);
	
		//Cortamos el mazo
		cout << "Por que numero de carta quieres cortar?";
		cin >> corte;
		cortar(mazo1, corte);
	
		cout << "Sin embargo, a la maniana siguiente..." << endl;
	
		pausa();
		repartir_en_cuatro(mazo1, mazo1, mazo2, mazo3, mazo4);
	
		cout << "Los cuatro reyes amanecieron en la misma habitacion, "
			 << "y lo mismo sucedio con los caballeros, las damas y los peones" << endl;
	}
	else
	{
		cout << "Archivo \"posada.txt\" no encontrado." << endl;
	}
}

void pausa()
{
	system("pause");
}
