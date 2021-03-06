/*-------------------------------
TRUCOS DE MAGIA CON CARTAS:

Autores:
Jaime Sevilla Molina.
Victor Gonzalez del Hierro.

Fecha:
2015/2

Version:
4.0
-----------------------------------*/

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
void linea();

//Funciones de obtencion de datos
int cuantas(const tMazo mazo);

tPalo palo(tCarta carta);
tNumero numero(tCarta carta);

//Funciones de output
void mostrar(tMazo mazo);
void mostrar(tCarta carta);
void mostrar(tNumero n);
void mostrar(tPalo p);
void mostrar(tMazo mazo1, tMazo mazo2, tMazo mazo3);
void mostrar(tMazo mazo1, tMazo mazo2, tMazo mazo3, tMazo mazo4);

//Funciones de carga y guardado de mazos
bool cargar(tMazo mazo, string &nomb);
bool abrir(string &nomb, ifstream &archivo);
bool mazoValido(tMazo &mazo, int cartasNecesarias, string &nomb);
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

//Funcion de pausa
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
			linea();
			if (cargar(mazo, nomb))
				mostrar(mazo);
			else cout << "El archivo no pudo cargarse." << endl;
		}
		else if (opcion == 2) 
		{
			linea();
			barajar(mazo);
			cout << "Mazo barajado:" << endl;
			mostrar(mazo);
		}
		else if (opcion == 3) 
		{
			linea();
			agregar(mazo);
			cout << "Mazo actual:" << endl;
			mostrar(mazo);
		}
		else if (opcion == 4) 
		{
			linea();
		    cout << "Cuantas?";
			cin >> cantidad;
			cortar(mazo, cantidad);
			cout << "Mazo actual:" << endl;
			mostrar(mazo);
		}
		else if (opcion == 5) 
		{
			linea();
			if (guardar(mazo, nomb)) 
				 cout << "Guardado exitoso!" << endl;
			else cout << "Fallo al guardar" << endl;
		}
		else if (opcion == 6) 
		{
			linea();
			tMazo negro, rojo;
			repartirNegroRojo(mazo, negro, rojo);
			
			cout << "Negras: " << endl;
			mostrar(negro);
			
			cout << "Rojas: " << endl;
			mostrar(rojo);
		} 
		else if (opcion == 7) 
		{
			linea();
			tMazo alto, bajo;
			repartirBajaAlta(mazo,bajo,alto);
			
			cout << "Bajas: " << endl;
			mostrar(bajo);
			
			cout << "Altas: " << endl;
			mostrar(alto);
		} 
		else if (opcion == 8) 
		{
			linea();
			tMazo mazo1, mazo2, mazo3;
			repartir_en_tres(mazo, mazo1, mazo2, mazo3);
			mostrar(mazo1, mazo2, mazo3);
		}
		else if (opcion == 9) 
		{
			linea();
			tMazo mazo1, mazo2, mazo3, mazo4;
			repartir_en_cuatro(mazo, mazo1, mazo2, mazo3, mazo4);
			mostrar(mazo1, mazo2, mazo3, mazo4);
		}
		else if (opcion == 10)
		{
			linea();
			truco_de_los_tres_montones();
		}
		else if (opcion == 11)
		{
			linea();
			truco_de_la_posada();
		}
	}while(opcion != 0);

	return 1;
}

//Permite al usuario elegir que hacer
int menu()
{
	linea();
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
	
	return digitoEntre(0,11);
}

//Controla que el usuario no introduzca un
//digito que no haga nada
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

//Añade una linea de guion
void linea()
{
	cout << setfill('-') << setw(79) <<  '-'  << endl << setfill(' ');
}

//Determina cuantas cartas contiene un mazo concreto
int cuantas(const tMazo mazo)
{
	int i;
	
	for(i=0; mazo[i] != CENTINELA; i++);
	
	return i;
}

//Determina el palo de una carta concreta
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

//Determina el numero de una carta concreta
tNumero numero(tCarta carta)
{
	int seccionNumero;
	
	seccionNumero = (carta % CARTASxPALO);
	
	return tNumero (seccionNumero+1);
}

//Muestra las cartas de un amzo concreto
void mostrar(tMazo mazo)
{
	for(int i=0; mazo[i] != CENTINELA; i++)
	{
		mostrar(mazo[i]);
	}
	cout << endl;
}

//Muestra el numero y el palo de una carta
void mostrar(tCarta carta)
{
	mostrar(numero(carta));

	cout << " ";

	mostrar(palo(carta));

	cout << endl;
}

//Muestra el numero de una carta
void mostrar(tNumero n)
{
	if      (n == A) cout << "A";
	else if (n == J) cout << "J";
	else if (n == Q) cout << "Q";
	else if (n == K) cout << "K";
	else             cout <<  n ;
}

//Muestra el palo de una carta
void mostrar(tPalo p)
{
	if      (p == picas)         cout <<     "de picas";
	else if (p == treboles)      cout <<  "de treboles";
	else if (p == diamantes)     cout << "de diamantes";
	else /*if (p == corazones)*/ cout << "de corazones";
}

//Muestra el contenido de tres mazos (necesario para 3montones)
void mostrar(tMazo mazo1, tMazo mazo2, tMazo mazo3)
{
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

//Muestra el contenido de cuatro mazos (necesario para posada)
void mostrar(tMazo mazo1, tMazo mazo2, tMazo mazo3, tMazo mazo4)
{
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

//Comprueba que el mazo cargado tenga las cartas necesarias para los trucos
bool mazoValido(tMazo &mazo, int cartasNecesarias, string &nomb)
{
	if(cargar(mazo, nomb))
	{
		while(cartasNecesarias != cuantas(mazo))
			{
				cout << "Error, el mazo nargado no tiene las "
			             << cartasNecesarias << " cartas necesarias" << endl;
				cargar(mazo, nomb);
			}
		return true;
	}
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

//Guarda el mazo actual en el archivo que elija el usuario 
//(por defecto se guarda en el archivo actual)
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

//Traduce los palos de las cartas a caracteres
string traducir(tCarta carta)
{
	string s="";
	switch (palo(carta))
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
	s += to_string(numero(carta));
	return s;
}

//Traduce los caracteres del archivo del mazo a palos
tCarta traducir(char p, int n)
{
	tPalo suit;

	if        (p == 'c')   suit = corazones;
	else if   (p == 't')   suit =  treboles;
	else if   (p == 'p')   suit =     picas;
	else /*if (p == 'd')*/ suit = diamantes;

	return (n-1 + int (suit) * CARTASxPALO);
}

//Vacia el mazo actual
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

//Genera un numero aleatorio entre 0 y el argumento
int randint(int max)
{
	return rand() % (max);
}

//Intercambia las posiciones de dos cartas dentro de un mazo
void intercambiar(tMazo mazo, int pos1, int pos2)
{
	tCarta aux;
	
	aux = mazo[pos1];
	
	mazo[pos1] = mazo[pos2];
	
	mazo[pos2] = aux;
}


//Desplaza las cartas del mazo a la derecha a fin de 
//dejar hueco para añadir mas cartas
bool desplazar(tMazo mazo, int numero)
{
	int total = cuantas(mazo);
	if (total+numero <= MAX_CARTAS)
	{
		for (int i = total; i >= 0; i--)
			mazo[i+numero] = mazo[i];
		return true;
	}
	else return false;
}

//Corta el mazo por la posicion que elija el usuario
void cortar(tMazo mazo, int cuantasCartas)
{
	tMazo otroMazo;
	//Corta...
	if (partir(mazo,cuantasCartas,otroMazo))
		//...y completa.
		unir(mazo, otroMazo);
}

//Parte el mazo en dos por la posicion que indique el argumento cuantasCoger
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

//Une los dos mazos que se le pasen come argumento, guardando
//el mazo resultante en el primero de dichos argumentos
bool unir(tMazo mazo, const tMazo otroMazo)
{
	if (desplazar(mazo, cuantas(otroMazo)))
	{
		for (int i = 0; otroMazo[i] != CENTINELA; i++)
			mazo[i] = otroMazo[i];

		return true;
	}
	else return false;
}

//Separa un mazo en dos distintos segun sean las cartas de este
//mayores, o menores o iguales que siete
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
		else //if(numero(mazo[i])>7) 
		{
			mazoAltas[k] = mazo[i];
			k++;
		}
	}
	mazoBajas[j] = CENTINELA;
	mazoAltas[k] = CENTINELA;
}

//Separa un mazo en dos segun sean sus cartas negras (picas y treboles), 
//o rojas (diamantes y corazones)
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
		else //if((palo(mazo[i]) == diamantes)||(palo(mazo[i]) == corazones)) 
		{
			mazoRojo[k] = mazo[i];
			k++;
		}
	}
	mazoNegro[j] = CENTINELA;
	mazoRojo [k] = CENTINELA;
}

//Reparte cartas de un mazo a otro intercaladamente
void repartirIntercalando(const tMazo mazo, int enCuantos, int queMazo, tMazo mazoNuevo)
{
	int j=0;
	for (int i = queMazo; i<cuantas(mazo); i+=enCuantos, j++)
	{
		mazoNuevo[j] = mazo[i];
	}
	mazoNuevo[j] = CENTINELA;
}

//Reparte cartas de un mazo a otros tres mazos intercaladamente
void repartir_en_tres(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3)
{
	//Repartir alternamente
	repartirIntercalando(mazo, 3, 1, mazo2);
	repartirIntercalando(mazo, 3, 2, mazo3);
	repartirIntercalando(mazo, 3, 0, mazo1);
}

//Reparte cartas de un mazo a otros cuatro mazos intercaladamente
void repartir_en_cuatro(tMazo mazo, tMazo mazo1, tMazo mazo2, tMazo mazo3, tMazo mazo4)
{
	//Repartir alternamente
	repartirIntercalando(mazo, 4, 1, mazo2);
	repartirIntercalando(mazo, 4, 2, mazo3);
	repartirIntercalando(mazo, 4, 3, mazo4);
	repartirIntercalando(mazo, 4, 0, mazo1);
}

void truco_de_los_tres_montones()
{
	tMazo mazoU, mazo1, mazo2, mazo3;
	string nomb;
	int mazo;
	
	cout << "El truco consiste en:" << endl
	     << "En primer lugar mostramos un mazo de 21 cartas" << endl;
	
	//generamos el mazo de 21 cartas
	if (mazoValido(mazoU, 21, nomb))
	{
		for (int i=0; i<3; i++)
		{
			if(i == 0)
			{
				cout << "Ahora dividimos el mazo en tres repartiendo cartas alternamente "
				     << "desde el mazo inicial a otros tres mazos." << endl;
				     
				pausa();
				
				cout << "Ahora fijate en una de las cartas de cualquiera de los tres mazos, "
				     << "y memorizala" << endl;
				     
				pausa();
			}
			else if(i == 1)
			{
				cout << "Repetimos el proceso otra vez" << endl;
				
				pausa();
				
				cout << "Localiza la carta que has meorizado antes" << endl;
				
				pausa();
			}
			else if(i == 2)
			{
				cout << "Y volvemos a repetirlo una ultima vez" << endl;
				
				pausa();
				
				cout << "Presta atencion y encuentra tu carta" << endl;
				
				pausa();
			}
			//Repartir alternamente
			repartir_en_tres(mazoU, mazo1, mazo2, mazo3);
			vaciar(mazoU);
			mostrar(mazo1, mazo2, mazo3);

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
	string nomb = "posada.txt";
	tMazo mazoU, mazo1, mazo2, mazo3, mazo4;
	int corte;
	
	if (mazoValido(mazoU, 16, nomb))
	{
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
		repartir_en_cuatro(mazoU, mazo1, mazo2, mazo3, mazo4);
		mostrar(mazo1, mazo2, mazo3, mazo4);
		
		//Juntamos los mazos
		unir(mazoU, mazo1);
		unir(mazoU, mazo2);
		unir(mazoU, mazo3);
		unir(mazoU, mazo4);
	
		//Cortamos el mazo
		cout << "Por que numero de carta quieres cortar?";
		cin >> corte;
		cortar(mazoU, corte);
	
		cout << "Sin embargo, a la maniana siguiente..." << endl;
	
		pausa();
		repartir_en_cuatro(mazoU, mazo1, mazo2, mazo3, mazo4);
		mostrar(mazo1, mazo2, mazo3, mazo4);
	
		cout << "Los cuatro reyes amanecieron en la misma habitacion, "
		     << "y lo mismo sucedio con los caballeros, las damas y los peones" << endl;
	}
	else
	{
		cout << "Error. Archivo \"posada.txt\" no encontrado." << endl;
	}
}

void pausa()
{
	cin.sync();
	cin.get();
}
