#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//VARIABLES GLOBALES
const int CARTASxPALO=13,
          MAX_CARTAS=52;

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

struct tCarta
{
	tPalo palo;
	tNumero num;

	//Constructor
	tCarta(tPalo p, tnumero n)
	{
		palo = p;
		num = n;
	}
};

struct tMazo
{
	tCarta cartas[MAX_CARTAS];
	int cuantas;

	//Constructor
	tMazo()
	{
		cuantas = 0;
	}
};

//FUNCIONES
//Menus
int menu();
int digitoEntre(int a, int b);
inline void linea();

//Funciones de output
void mostrar(tMazo mazo[], int n);
void mostrar(tMazo mazo);
void mostrar(tCarta carta);
void mostrar(tNumero n);
void mostrar(tPalo p);

//Funciones de carga y guardado de mazos
bool cargar(tMazo mazo, string &nomb);
bool cargar_auto(tMazo mazo, string &nomb);
bool abrir(string &nomb, ifstream &archivo);
bool agregar(tMazo mazo);

bool guardar(const tMazo mazo, string &nomb);

string traducir(tCarta carta);
tCarta traducir(char p, int n);

//Funciones de manipulacion de un mazo individual
inline void vaciar(tMazo mazo);

void barajar(tMazo mazo);
int randint(int max);
void intercambiar (tMazo mazo, int pos1, int pos2);
bool desplazar(tMazo mazo, int numero);

void cortar(tMazo mazo, int cuantasCartas);
bool partir(tMazo mazo, int cuantasCoger, tMazo otroMazo);
bool unir(tMazo mazo, const tMazo otroMazo);
void carta_concreta(tMazo mazo);
tCarta elegir_carta();
int elegir_numero();
char elegir_palo();
bool agregar_carta(tMazo mazo, tCarta carta, tCarta elegir_carta());

//Funciones para repartir en varios mazos
void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas);
void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo);

void repartirIntercalando(const tMazo mazo, int enCuantos, int queMazo, tMazo mazoNuevo);
void repartir_en_n(tMazo mazoI, tMazo mazo[], int n);

//Trucos de magia
void truco_de_los_tres_montones();
void truco_de_la_posada();

//System
inline void pausa();

int main()
{
	int opcion;
	tMazo mazo;
	string nomb;

	srand(time(NULL));
	vaciar(mazo);

	do
	{
		opcion = menu_principal();
		if (opcion == 1) 
		{
			do
			{
				opcion = menu_de_carga_y_guardado();
				if      (opcion == 1)
				{
					linea();
					if (cargar(mazo, nomb))
						mostrar(mazo);
					else cout << "El archivo no pudo cargarse." << endl;
				}
				else if (opcion == 2)
				{
					linea();
					if (guardar(mazo, nomb)) 
						cout << "Guardado exitoso!" << endl;
					else cout << "Fallo al guardar" << endl;
				}
				else if (opcion == 3)
				{
					linea();
					agregar(mazo);
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
			}while (opcion != 0);
			opcion = menu_principal();
		}
		else if (opcion == 2) 
		{
			do
			{
				opcion = menu_de_manipulacion_de_mazos();
				if      (opcion == 1)
				{
					linea();
					barajar(mazo);
					cout << "Mazo barajado:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 2)
				{
					int cantidad;
					
					linea();
					cout << "Cuantas?";
					cin >> cantidad;
					cortar(mazo, cantidad);
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 3)
				{
					linea();
					tMazo negro, rojo;
					repartirNegroRojo(mazo, negro, rojo);
			
					cout << "Negras: " << endl;
					mostrar(negro);
			
					cout << "Rojas: " << endl;
					mostrar(rojo);
				}
				else if (opcion == 4)
				{
					linea();
					tMazo alto, bajo;
					repartirBajaAlta(mazo,bajo,alto);
			
					cout << "Bajas: " << endl;
					mostrar(bajo);
			
					cout << "Altas: " << endl;
					mostrar(alto);	
				}
				else if (opcion == 5)
				{
					linea();

					int en_cuantos;
					cout << "En cuantos mazos quieres separar este mazo?" << endl;
					cin >> en_cuantos;

					tMazo *mazos;
					mazos = new tMazo[en_cuantos];
					repartir_en_n(mazo, mazos, en_cuantos);

					mostrar(mazos, en_cuantos);

					delete mazos;
				}
				else if (opcion == 6)
				{
					linea();
					cout << "Mazo:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 7)
				{
					linea();
					carta_concreta(mazo);
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
				/*else if (opcion == 8)
				{
					linea();
					//agregar_mazo();
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}*/
				else if (opcion == 9)
				{
					vaciar(mazo);
				}
			}while (opcion != 0);
			opcion = menu_principal();
		}
		/*else if (opcion == 3) 
		{
			do
			{
				opcion = menu_de_juegos();
				if      (opcion == 1)
				{
					//blackjack();
				}
				else if (opcion == 2)
				{
					//poker();
				}
				else if (opcion == 3)
				{
					//canasta();
				}
			}while (opcion != 0) 
			opcion = menu_principal();
		}*/
		else if (opcion == 4) 
		{
			do
			{
				opcion = menu_de_magia();
				if      (opcion == 1)
				{
					linea();
					truco_de_los_tres_montones();
				}
				else if (opcion == 2)
				{
					linea();
					truco_de_la_posada();
				}
			}while (opcion != 0);
			opcion = menu_principal();
		}
	}while(opcion != 0);

	return 1;
}

int menu_principal()
{
	linea();
        cout << "Menu principal:"                   << endl
             << "1 - Menu de carga y guardado"      << endl
             << "2 - Menu de manipulacion de mazos" << endl
             << "3 - Menu de juegos de cartas"      << endl
             << "4 - Menu de magia de cartas"       << endl
             << "0 - Salir"                         << endl;
	
	return digitoEntre(0,4);
}

int menu_de_carga_y_guardado()
{
	linea();
	cout << "Menu de carga y guardado:"      << endl
	     << "1 - Cargar"                     << endl
	     << "2 - Guardar"                    << endl
	     << "3 - Agregar mazo"               << endl
	     << "0 - Volver al menu principal"   << endl;

	return digitoEntre(0,2);
}

int menu_de_manipulacion_de_mazos()
{
	linea();
 	cout << "Menu de manipulacion de mazos:"  << endl
 	     << "1  - Barajar"                    << endl
	     << "2  - Cortar"                     << endl
 	     << "3  - Separar en negras y rojas"  << endl
	     << "4  - Separar en altas y bajas"   << endl
	     << "5  - Separar en n montones"      << endl
	     << "6  - Mostrar mazo actual"        << endl
 	     << "7  - Aniadir una carta concreta" << endl
 	     << "8  - Aniadir mazo ordenado"      << endl
 	     << "9  - Vaciar mazo actual"         << endl
 	     << "0  - Volver al menu principal"   << endl;
	
	return digitoEntre(0,10);
}

int menu_de_juegos()
{
	linea();
	cout << "Menu de juegos de cartas:"       << endl
	     << "1 - Blackjack"                   << endl
	     << "2 - Poker Texas Hold'em"         << endl
	     << "3 - Canasta"                     << endl
	     << "0 - Volver al menu principal"    << endl;
		 
	return digitoEntre(0,3);
}

int menu_de_magia()
{
	linea();
	cout << "Menu de magia de cartas:"       << endl
	     << "1 - Truco de los tres montones" << endl
	     << "2 - Truco de la posada"         << endl
	     << "0 - Volver al menu principal"   << endl;
		 
	return digitoEntre(0,2);
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

inline void linea()
{
	cout << setfill('-') << setw(79) <<  '-'  << endl << setfill(' ');
}

void mostrar(tMazo mazo[], int n)
{
	for(int i=0; i<n; i++)
	{
		cout << "Mazo " << i << ":" << endl;
		mostrar(mazo[i]);
	}
}

void mostrar(tMazo mazo)
{
	for(int i=0; i < mazo.cuantas; i++)
	{
		mostrar(mazo.cartas[i]);
	}
	cout << endl;
}

void mostrar(tCarta carta)
{
	mostrar(carta.num);

	cout << " ";

	mostrar(carta.palo);

	cout << endl;
}

void mostrar(tNumero n)
{
	if      (n == A) cout << "A";
	else if (n == J) cout << "J";
	else if (n == Q) cout << "Q";
	else if (n == K) cout << "K";
	else             cout <<  n ;
}

void mostrar(tPalo p)
{
	if      (p == picas)     cout <<     "de picas";
	else if (p == treboles)  cout <<  "de treboles";
	else if (p == diamantes) cout << "de diamantes";
	else /*if (p == corazones)*/ cout << "de corazones";
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
			mazo.cartas[cont] = traducir(p,n);
			cont++;
			archivo >> p;
		}
		mazo.cuantas = cont;
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
			mazo.cartas[cont] = traducir(p,n);
			cont++;
			archivo >> p;
		}
		mazo.cuantas = cont;
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
		for(int i = 0; i < mazo.cuantas; i++)
		{
			archivo << traducir(mazo.cartas[i]) << endl;
		}
		archivo << "x";
		return true;
	}
	else return false;
}

string traducir(tCarta carta)
{
	string s="";
	switch (carta.palo)
	{
		case picas: 
			s+="p";
			break;
		case treboles:
			s+="t";
			break;
		case diamantes:
			s+="d";
			break;
		case corazones:
			s+="c";
			break;
	}
	s += " ";
	s += to_string(carta.num);
	return s;
}

tCarta traducir(char p, int n)
{
	tPalo suit;

	if      (p == 'c') suit = corazones;
	else if (p == 't') suit = treboles;
	else if (p == 'p') suit = picas;
	else /*if (p == 'd')*/ suit = diamantes;

	tCarta carta(suit, num);

	return carta;
}

inline void vaciar(tMazo mazo)
{
	mazo.cuantas = 0;
}

//Baraja el mazo, intercambiando aleatoriemente cartas
void barajar(tMazo mazo)
{
	int pos1, pos2;
	for (int i=0; i<3*mazo.cuantas; i++)
	{
		pos1 = randint(mazo.cuantas);
		pos2 = randint(mazo.cuantas);
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
	
	aux = mazo.cartas[pos1];
	
	mazo.cartas[pos1] = mazo.cartas[pos2];
	
	mazo.cartas[pos2] = aux;
}

bool desplazar(tMazo mazo, int numero)
{
	if (mazo.cuantas + numero < MAX_CARTAS)
	{
		for (int i = mazo.cuantas; i >= 0; i--)
			mazo.cartas[i+numero] = mazo.cartas[i];
		mazo.cuantas += numero;
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
	if (cuantasCoger > mazo.cuantas) return false;
	else
	{
		for (i = 0; cuantasCoger + i < mazo.cuantas; i++)
		{
			otroMazo.cartas[i] = mazo.cartas[cuantasCoger + i];
		}

		mazo.cuantas = cuantasCoger;
		otroMazo.cuantas = i;

		return true;
	}
}

bool unir(tMazo mazo, const tMazo otroMazo)
{
	if (desplazar(mazo, otroMazo.cuantas))
	{
		for (int i = 0; i < otroMazo.cuantas; i++)
		{
			mazo.cartas[i] = otroMazo.cartas[i];
		}
		mazo.cuantas += otroMazo.cuantas;
		return true;
	}
	else return false;
}

inline void carta_concreta(tMazo mazo)
{
	agregar_carta(mazo, elegir_carta());
}

inline tCarta elegir_carta()
{
	return traducir(elegir_palo(), elegir_numero());
}

tNumero elegir_numero()
{
	cout << "Que numero de carta te gustaria aniadir?"
	     << " (debe estar entre 1 y 13) " << endl;
	
	return digitoEntre(1,13);
}

char elegir_palo()
{
	char simboloPalo;
	
	cout << "De que palo te gustaria que fuese?"
	     << " (p = picas, d = diamantes, t = treboles, c = corazones)" << endl;
	cin >> simboloPalo;
	
	return simboloPalo;
}

bool agregar_carta(tMazo mazo, tCarta carta, tCarta elegir_carta())
{
	if (mazo.cuantas == MAX_CARTAS)
	{
		cout << "Error, el mazo no puede contener mas de 52 cartas" << endl;
		return false;
	}
	else
	{
		mazo.cartas[i] = carta;
		mazo.cuantas++;
		return true;
	}
}

void repartirBajaAlta(const tMazo mazo, tMazo mazoBajas, tMazo mazoAltas)
{	
	int j=0, k=0;

	for(int i=0; i < mazo.cuantas; i++)
	{
		if     (mazo.cartas[i].numero < 8) 
		{
			mazoBajas.cartas[j] = mazo.cartas[i];
			j++;
		}
		else //(mazo.cartas[i].numero > 7) 
		{
			mazoAltas.cartas[k] = mazo.cartas[i];
			k++;
		}
	}
	mazoBajas.cuantas = j;
	mazoAltas.cuantas = k;
}

void repartirNegroRojo(const tMazo mazo, tMazo mazoNegro, tMazo mazoRojo)
{
	int j=0, k=0;

	for(int i=0; i < mazo.cuantas; i++)
	{
		if     (mazo.cartas[i].palo == picas)||mazo.cartas[i].palo == treboles)) 
		{
			mazoNegro.cartas[j] = mazo.cartas[i];
			j++;
		}
		else //if(mazo.cartas[i].palo== diamantes)||(mazo.cartas[i].palo == corazones)) 
		{
			mazoRojo.cartas[k] = mazo.cartas[i];
			k++;
		}
	}
	mazoNegro.cuantas = j;
	mazoRojo.cuantas = k;
}

void repartirIntercalando(const tMazo mazo, int enCuantos, int queMazo, tMazo mazoNuevo)
{
	int j=0;
	for (int i = queMazo; i < mazo.cuantas; i+=enCuantos, j++)
	{
		mazoNuevo.cartas[j] = mazo.cartas[i];
	}
	mazoNuevo.cuantas = j;
}

void repartir_en_n(tMazo mazoI, tMazo mazo[], int n)
{
	//Repartir alternamente
	for(int i=0; i<n; i++)
		repartirIntercalando(mazoI, n, 0, mazo[i]);
}

void truco_de_los_tres_montones()
{
	tMazo mazoU, mazo[3];
	string nomb = "3montones.txt";
	int n;

	//generamos el mazo de 21 cartas
	if(cargar_auto(mazoU, nomb))
	{
		for (int i=0; i<3; i++)
		{
			//Repartir alternamente
			repartir_en_n(mazoU, mazo, 3);
			vaciar(mazoU);

			//El usuario elije mazo
			cout << "En que mazo esta tu carta?" << endl;
			n = digitoEntre(1,3);

			//Juntamos los mazos
			if      (n == 1)
			{
				unir(mazoU, mazo[2]);
				unir(mazoU, mazo[0]);
				unir(mazoU, mazo[1]);
			}
			else if (n == 2)
			{
				unir(mazoU, mazo[2]);
				unir(mazoU, mazo[1]);
				unir(mazoU, mazo[0]);
			}
			else //if (n == 3)
			{
				unir(mazoU, mazo[1]);
				unir(mazoU, mazo[2]);
				unir(mazoU, mazo[0]);
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
	tMazo mazo[4], mazoU;
	string nomb = "posada.txt";
	int corte;
	
	if (cargar_auto(mazoU, nomb)){
	
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
		repartir_en_n(mazoU, mazo, 4);
		vaciar(mazoU);

		mostrar(mazo, 4);

		//Juntamos los mazos
		for(int i=0; i<4; i++)
			unir(mazoU, mazo[i]);
	
		//Cortamos el mazo
		cout << "Por que numero de carta quieres cortar?";
		cin >> corte;
		cortar(mazoU, corte);
	
		cout << "Sin embargo, a la maniana siguiente..." << endl;
	
		pausa();
		repartir_en_n(mazoU, mazo, 4);
		
		mostrar(mazo, 4);

		cout << "Los cuatro reyes amanecieron en la misma habitacion, "
			 << "y lo mismo sucedio con los caballeros, las damas y los peones" << endl;
	}
	else
	{
		cout << "Archivo \"posada.txt\" no encontrado." << endl;
	}
}

inline void pausa()
{
	system("pause");
}
