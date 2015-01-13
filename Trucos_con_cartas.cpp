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
//Enumerados
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

//Clases
class tCarta 
{
public:
	//Constructores
	tCarta() :
		palo(picas),
		num(A)
	{}

	tCarta(tPalo p, tNumero n) :
		palo (p),
		num (n)
	{}

	friend bool operator != (tCarta a, tCarta b)
	{
		return ((a.palo != b.palo) || (a.num != b.num));
	}

	tPalo palo;
	tNumero num;
};

class tMazo
{
public:
	//Constructor
	tMazo(): cuantas(0){}

	//Metodos
	void barajar();
	void intercambiar (int pos1, int pos2);

	//Datos
	tCarta cartas[MAX_CARTAS];
	int cuantas;
};

//FUNCIONES
//Menus
int menu_principal();
int menu_de_carga_y_guardado();
int menu_de_manipulacion_de_mazos();
int menu_de_juegos_de_cartas();
int menu_de_magia();

int digitoEntre(int a, int b);
inline void linea();

int digitoEntre(int a, int b);

inline tCarta elegir_carta();
int elegir_numero();
char elegir_palo();

//Funciones de output
void mostrar(const tMazo mazo[], int n);
void mostrar(const tMazo &mazo);
void mostrar(const tCarta carta);
void mostrar(const tNumero n);
void mostrar(const tPalo p);

//Funciones de carga y guardado de mazos
bool cargar(tMazo &mazo, string &nomb);
bool cargar_auto(tMazo &mazo, string &nomb);
void cargar_mazo_completo(tMazo &mazo);
bool abrir(string &nomb, ifstream &archivo);
bool agregar(tMazo &mazo);

bool guardar(const tMazo &mazo, string &nomb);

string traducir(tCarta carta);
tCarta traducir(char p, int n);

//Funciones de manipulacion de un mazo individual
inline void vaciar(tMazo &mazo);

int randint(int max);

bool desplazar(tMazo &mazo, int numero);

void cortar(tMazo &mazo, int cuantasCartas);
bool partir(tMazo &mazo, tMazo &otroMazo, int cuantasCoger);
bool unir(tMazo &mazo, const tMazo &otroMazo);

void carta_concreta_dentro(tMazo &mazo);
void carta_concreta_fuera(tMazo &mazo);

bool agregar_carta(tMazo &mazo, tCarta carta);
bool quitar_carta(tMazo &mazo, tCarta carta);

//Funciones para repartir en varios mazos
bool pares(tCarta carta);
void repartirParImpar(const tMazo &mazo, tMazo &mazoPar, tMazo &mazoImpar);
bool figuras(tCarta carta);
void repartirFigurasNumeros(const tMazo &mazo, tMazo &mazoFiguras, tMazo &mazoNumeros);
bool bajas(tCarta carta);
void repartirBajaAlta(const tMazo &mazo, tMazo &mazoBajas, tMazo &mazoAltas);
bool negro(tCarta carta);
void repartirNegroRojo(const tMazo &mazo, tMazo &mazoNegro, tMazo &mazoRojo);

void repartir_segun_criterio(const tMazo &mazo, tMazo &mazo1, tMazo &mazo2, bool (*criterio)(tCarta));

void repartirIntercalando(const tMazo &mazo, int enCuantos, int queMazo, tMazo &mazoNuevo);
void repartir_en_n(tMazo &mazoI, tMazo mazo[], int n);

//Trucos de magia
void truco_de_los_tres_montones();
void truco_de_la_posada();
void truco_del_jugador_desconfiado();

//System
inline void pausa();

int main()
{
	int opcion, eleccion;
	tMazo mazo;
	string nomb;

	srand(time(NULL));
	vaciar(mazo);

	do
	{
		eleccion = menu_principal();
		if (eleccion == 1) 
		{
			do
			{
				opcion = menu_de_carga_y_guardado();
				if      (opcion == 1)
				{
					linea();
					if (cargar(mazo, nomb))
						{
						cout << "Mazo:" << endl;
						mostrar(mazo);
						}
					else cout << "El archivo no pudo cargarse." << endl;
				}
				else if (opcion == 2)
				{
					linea();
					cargar_mazo_completo(mazo);
					
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 3)
				{
					linea();
					if (guardar(mazo, nomb)) 
						cout << "Guardado exitoso!" << endl;
					else cout << "Fallo al guardar" << endl;
				}
				else if (opcion == 4)
				{
					linea();
					agregar(mazo);
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
			}while (opcion != 0);
		}
		else if (eleccion == 2) 
		{
			do
			{
				opcion = menu_de_manipulacion_de_mazos();
				if      (opcion == 1)
				{
					linea();
					mazo.barajar();
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
					tMazo par, impar;
					repartirParImpar(mazo, par, impar);
					
					cout << "Pares: " << endl;
					mostrar(par);
					
					cout << "Impares: " << endl;
					mostrar(impar);
				}
				else if (opcion == 6)
				{
					linea();
					tMazo figura, numero;
					repartirFigurasNumeros(mazo, figura, numero);
					
					cout << "Figuras:" << endl;
					mostrar(figura);
					
					cout << "Numeros:" << endl;
					mostrar(numero);
				}
				else if (opcion == 7)
				{
					linea();

					int en_cuantos;
					cout << "En cuantos mazos quieres separar este mazo?" << endl;
					cin >> en_cuantos;

					tMazo *mazos = new tMazo[en_cuantos];
					repartir_en_n(mazo, mazos, en_cuantos);

					mostrar(mazos, en_cuantos);

					delete[] mazos;
				}
				else if (opcion == 8)
				{
					linea();
					cout << "Mazo:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 9)
				{
					if (mazo.cuantas == MAX_CARTAS)
					{
						cout << "Error, el mazo no puede "
						     << "tener mas de 52 cartas" << endl;
					}
					else
					{
						linea();
						carta_concreta_dentro(mazo);
						cout << "Mazo actual:" << endl;
						mostrar(mazo);
					}
				}
				else if (opcion == 10)
				{
					linea();
					carta_concreta_fuera(mazo);
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
				/*else if (opcion == 11)
				{
					linea();
					//agregar_mazo();
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}*/
				else if (opcion == 12)
				{
					vaciar(mazo);
				}
			}while (opcion != 0);
		}
		/*else if (eleccion == 3) 
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
		}*/
		else if (eleccion == 4) 
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
				else if (opcion == 3)
				{
					linea();
					truco_del_jugador_desconfiado();
				}
			}while (opcion != 0);
		}
	}while(eleccion != 0);

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
	cout << "Menu de carga y guardado:"    << endl
	     << "1 - Cargar mazo a elegir"     << endl
	     << "2 - Cargar mazo completo"     << endl
	     << "3 - Guardar"                  << endl
	     << "4 - Agregar mazo"             << endl
	     << "0 - Volver al menu principal" << endl;

	return digitoEntre(0,4);
}

int menu_de_manipulacion_de_mazos()
{
	linea();
 	cout << "Menu de manipulacion de mazos:"    << endl
 	     << "1  - Barajar"                      << endl
	     << "2  - Cortar"                       << endl
 	     << "3  - Separar en negras y rojas"    << endl
	     << "4  - Separar en altas y bajas"     << endl
	     << "5  - Separar en pares e impares"   << endl
	     << "6  - Separar en figuras y numeros" << endl
	     << "7  - Separar en n montones"        << endl
	     << "8  - Mostrar mazo actual"          << endl
 	     << "9  - Aniadir una carta concreta"   << endl
 	     << "10 - Eliminar una carta concreta"  << endl
 	     << "11 - Vaciar mazo actual"           << endl
 	     << "0  - Volver al menu principal"     << endl;
	
	return digitoEntre(0,11);
}

int menu_de_juegos()
{
	linea();
	cout << "Menu de juegos de cartas:"    << endl
	     << "1 - Blackjack"                << endl
	     << "2 - Poker Texas Hold'em"      << endl
	     << "3 - Canasta"                  << endl
	     << "0 - Volver al menu principal" << endl;
		 
	return digitoEntre(0,3);
}

int menu_de_magia()
{
	linea();
	cout << "Menu de magia de cartas:"         << endl
	     << "1 - Truco de los tres montones"   << endl
	     << "2 - Truco de la posada"           << endl
	     << "3 - Truco del jugador despistado" << endl
	     << "0 - Volver al menu principal"     << endl;
		 
	return digitoEntre(0,3);
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

inline tCarta elegir_carta()
{
	return traducir(elegir_palo(), elegir_numero());
}

int elegir_numero()
{
	int number;
	
	cout << "Que numero de carta escoges?"
	     << " (debe estar entre 1 y 13) " << endl;
	
	return digitoEntre(1,13);
}

char elegir_palo()
{
	char simboloPalo;
	
	cout << "Que palo eliges?"
	     << " (p = picas, d = diamantes, t = treboles, c = corazones)" << endl;
	cin >> simboloPalo;
	
	return simboloPalo;
}

void mostrar(const tMazo mazo[], int n)
{
	for(int i=0; i<n; i++)
	{
		cout << "Mazo " << (i+1) << ":" << endl;
		mostrar(mazo[i]);
	}
}

void mostrar(const tMazo &mazo)
{
	for(int i=0; i < mazo.cuantas; i++)
	{
		mostrar(mazo.cartas[i]);
	}
	cout << endl;
}

void mostrar(const tCarta carta)
{
	mostrar(carta.num);

	cout << " ";

	mostrar(carta.palo);

	cout << endl;
}

void mostrar(const tNumero n)
{
	if      (n == A) cout << "A";
	else if (n == J) cout << "J";
	else if (n == Q) cout << "Q";
	else if (n == K) cout << "K";
	else             cout <<  n ;
}

void mostrar(const tPalo p)
{
	if      (p == picas)     cout <<     "de picas";
	else if (p == treboles)  cout <<  "de treboles";
	else if (p == diamantes) cout << "de diamantes";
	else /*if (p == corazones)*/ cout << "de corazones";
}

//Carga un mazo de un archivo a elección del usuario.
bool cargar(tMazo &mazo, string &nomb)
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

bool cargar_auto(tMazo &mazo, string &nomb)
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

void cargar_mazo_completo(tMazo &mazo)
{
	int k=0;
	
	for (int j=0; j<4; j++)
	{
		for (int i=1; i<14; i++)
		{
			mazo.cartas[k] = tCarta((tPalo) j, (tNumero) i);
			k++;
			mazo.cuantas = 52;
		}
	}	
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
bool agregar(tMazo &mazo)
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

bool guardar(const tMazo &mazo, string &nomb)
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

	tCarta carta(suit, (tNumero) n);

	return carta;
}

inline void vaciar(tMazo &mazo)
{
	mazo.cuantas = 0;
}

//Baraja el mazo, intercambiando aleatoriemente cartas
void tMazo::barajar()
{
	for (int i=0; i<3*cuantas; i++)
	{
		intercambiar(randint(cuantas), randint(cuantas));
	}
}

int randint(int max)
{
	return rand() % (max);
}

void tMazo::intercambiar(int pos1, int pos2)
{
	tCarta aux;
	
	aux = cartas[pos1];
	
	cartas[pos1] = cartas[pos2];
	
	cartas[pos2] = aux;
}

//Desplaza las cartas del mazo a la derecha, para hacer hueco para nuevas cartas
bool desplazar(tMazo &mazo, int numero)
{
	if (mazo.cuantas + numero <= MAX_CARTAS)
	{
		for (int i = mazo.cuantas-1; i >= 0; i--)
			mazo.cartas[i+numero] = mazo.cartas[i];
		mazo.cuantas += numero;
		return true;
	}
	else return false;
}

void cortar(tMazo &mazo, int cuantasCartas)
{
	tMazo otroMazo;
	//Corta...
	if (partir(mazo,otroMazo, cuantasCartas))
	{
		//...y completa.
		unir(mazo, otroMazo);
	}
}

bool partir(tMazo &mazo, tMazo &otroMazo, int cuantasCoger)
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

bool unir(tMazo &mazo, const tMazo &otroMazo)
{
	if (desplazar(mazo, otroMazo.cuantas))
	{
		for (int i = 0; i < otroMazo.cuantas; i++)
		{
			mazo.cartas[i] = otroMazo.cartas[i];
		}

		return true;
	}
	else return false;
}

inline void carta_concreta_dentro(tMazo &mazo)
{
	agregar_carta(mazo, elegir_carta());
}

inline void carta_concreta_fuera(tMazo &mazo)
{
	quitar_carta(mazo, elegir_carta());
}

bool agregar_carta(tMazo &mazo, tCarta carta)
{
	if (mazo.cuantas == MAX_CARTAS)
	{
		cout << "Error, el mazo no puede contener mas de 52 cartas" << endl;
		return false;
	}
	else
	{
		mazo.cartas[mazo.cuantas] = carta;
		mazo.cuantas++;
		return true;
	}
}

bool quitar_carta(tMazo &mazo, tCarta carta)
{
	int i;
	
	//Buscamos la carta objetivo
	for(i=0; mazo.cartas[i] != carta && i < mazo.cuantas; i++);
	
	if (i == mazo.cuantas)
	{
		cout << "Error, no se encontro la carta seleccionada" << endl;
		return false;
	}
	else
	{
		//Desplazamos el mazo hacia la izquierda, cubriendo la carta objetivo
		for(; i < mazo.cuantas-1; i++)
			mazo.cartas[i] = mazo.cartas[i+1];
		mazo.cuantas--;
		return true;
	}
}

bool pares(tCarta carta)
{
	return (!(carta.num % 2));
}

void repartirParImpar(const tMazo &mazo, tMazo &mazoPar, tMazo &mazoImpar)
{
	repartir_segun_criterio(mazo, mazoPar, mazoImpar, pares);
}

bool figuras(tCarta carta)
{
	return (carta.num > 10 || carta.num == A);
}

void repartirFigurasNumeros(const tMazo &mazo, tMazo &mazoFiguras, tMazo &mazoNumeros)
{
	repartir_segun_criterio(mazo, mazoFiguras, mazoNumeros, figuras);
}

bool bajas(tCarta carta)
{
	return (carta.num < 8);
}

void repartirBajaAlta(const tMazo &mazo, tMazo &mazoBajas, tMazo &mazoAltas)
{
	repartir_segun_criterio(mazo, mazoBajas, mazoAltas, bajas);
}

bool negro(tCarta carta)
{
	return ((carta.palo == picas)||(carta.palo == treboles));
}

void repartirNegroRojo(const tMazo &mazo, tMazo &mazoNegro, tMazo &mazoRojo)
{
	repartir_segun_criterio(mazo, mazoNegro, mazoRojo, negro);
}

//Generalizar es mejor. Para que tener cuatro funciones practicamente iguales?
void repartir_segun_criterio(const tMazo &mazo, tMazo &mazo1, tMazo &mazo2, bool (*criterio)(tCarta))
{
	int j=0, k=0;

	for(int i=0; i < mazo.cuantas; i++)
	{
		if     (criterio(mazo.cartas[i]))
		{
			mazo1.cartas[j] = mazo.cartas[i];
			j++;
		}
		else
		{
			mazo2.cartas[k] = mazo.cartas[i];
			k++;
		}
	}
	mazo1.cuantas = j;
	mazo2.cuantas = k;
}

void repartirIntercalando(const tMazo &mazo, int enCuantos, int queMazo, tMazo &mazoNuevo)
{
	int j=0;
	for (int i = queMazo; i < mazo.cuantas; i+=enCuantos, j++)
	{
		mazoNuevo.cartas[j] = mazo.cartas[i];
	}
	mazoNuevo.cuantas = j;
}

void repartir_en_n(tMazo &mazoI, tMazo mazo[], int n)
{
	//Repartir alternamente
	for(int i=0; i<n; i++)
		repartirIntercalando(mazoI, n, i, mazo[i]);
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
			mostrar(mazo, 3);

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
		mostrar(mazoU.cartas[10]);
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

void truco_del_jugador_desconfiado()
{
	tMazo mazoD, mazo[4], mazoNegro, mazoRojo, mazoBajas, mazoAltas; 
	tMazo mazoPar, mazoImpar, mazoFiguras, mazoNumeros;
	string nomb = "desconfiado.txt";
	

	
	if (cargar_auto(mazoD, nomb))
	{
		cout << "En una partida de poker de mesa redonda, con cuatro jugadores sentados "
		     << "en ella, un jugador dice que desconfia de que los jugadores sentados en "
		     << "la mesa le hagan trampas. Por ello propone que las 20 cartas que se van "
		     << "a repartir sean visibles para todos antes de repartirse." << endl;
	     	     pausa();
	     	     
		cout << "Mazo:" << endl;
		mostrar(mazoD);
		pausa();
		
		cout << "El mazo se baraja y se reparte entre los cuatro jugadores." << endl;
		pausa();
		
		repartir_en_n(mazoD, mazo, 4);
		mostrar(mazo, 4);
		pausa();
		
		cout << "El jugador dice que no se fia del que ha repartido, asi que propone "
		     << "seguir unos pasos para asegurarse de que el reparto ha sido aleatorio "
		     << "y justo:" << endl;
		pausa();
		
		for (int i=0; i<2; i++) 
		{
			if      (i == 0)
			{
				cout << "Cada jugador debe dividir su mazo en dos, pero cada jugador "
				     << "con un criterio distinto: El jugador que desconfia "
				     << "(jugador 1) debe separar su mazo por colores (negro a la izquierda, "
				     << "rojo a la derecha). El jugador situado a su derecha debera separar el "
				     << "suyo segun sea el numero de su carta inferior (izquierda) o superior "
				     << "(derecha) a 7. El siguiente jugador separara su mazo en cartas pares "
				     << "(izquierda) e impares (derecha). Y el ultimo jugador habra de separar "
				     << "su mazo en figuras (izquierda) y numeros (derecha)." << endl
				     << "A continuacion cada jugador pasara su mazo izquierdo al jugador de su "
				     << "izquierda, y su mazo derecho al jugador de su derecha. Ahora los jugadores "
				     << "tendran un solo mazo formado por los dos que les pasaron sus companieros." << endl;
				pausa();
			}
			else if (i == 1)
			{
				cout << "El proceso se repetira una vez mas" << endl;
				pausa();
			}
			repartirNegroRojo(mazo[0], mazoNegro, mazoRojo);
			repartirBajaAlta(mazo[1], mazoBajas, mazoAltas);
			repartirParImpar(mazo[2], mazoPar, mazoImpar);
			repartirFigurasNumeros(mazo[3], mazoFiguras, mazoNumeros);
			
			unir(mazoNumeros, mazoBajas);
			unir(mazoRojo, mazoPar);
			unir(mazoAltas, mazoFiguras);
			unir(mazoImpar, mazoNegro);
			
			mazo[0] = mazoNumeros;
			mazo[1] = mazoRojo;
			mazo[2] = mazoAltas;
			mazo[3] = mazoImpar;
			
			
			mostrar(mazo, 4);
			pausa();
		}
		
		cout << "Y otra mas, con la excepcion de que ahora cada jugador se quedara con su mazo "
		     << "derecho, y pasan su izquierdo al jugador de su izquierda, despues los vuelven "
		     << "a juntar." << endl;
		pausa();
		
		repartirNegroRojo(mazo[0], mazoNegro, mazoRojo);
		repartirBajaAlta(mazo[1], mazoBajas, mazoAltas);
		repartirParImpar(mazo[2], mazoPar, mazoImpar);
		repartirFigurasNumeros(mazo[3], mazoFiguras, mazoNumeros);
		
		unir(mazoRojo, mazoBajas);
		unir(mazoAltas, mazoPar);
		unir(mazoImpar, mazoFiguras);
		unir(mazoNumeros, mazoNegro);
		
		mazo[0] = mazoRojo;
		mazo[1] = mazoAltas;
		mazo[2] = mazoImpar;
		mazo[3] = mazoNumeros;
		
		cout << "Entonces los jugadores miran sus mazos, y descubren que..." << endl;
		pausa();
		mostrar(mazo, 4);
		
		cout << "El jugador desconfiado tiene escalera de color. El de su izquierda full. El siguiente, "
		     << "poker. Y el ultimo, color" << endl;
	}
	else
	{
		cout << "Error, archivo \"desconfiado.txt\" no encontrado";
	}
}

inline void pausa()
{
	system("pause");
}
