/*-------------------------------
TRUCOS DE MAGIA CON CARTAS:

Autores:
Jaime Sevilla Molina.
Victor Gonzalez del Hierro.

Fecha:
2015/2

Version:
5.0

Features:
Aparte de lo pedido en el enunciado de la practica, hemos implementado:
1. Deteccion y correcciones de errores en la entrada de datos por consola.
2. Un truco de magia addicional.
3. Juego de cartas Blackjack.
4. Soporte para multiples perfiles de usuario.
5. Opciones de manipulacion de las estadisticas: reseteo, borrado, backups,...

Warnings:
En los trucos que requieren cargar mazos determinados hemos implementado una funcion que
los carga automaticamente, sin pedirte el nombre de dicho mazo. Para que la funcion cargue
el mazo deseado debes cambiar el nombre desl archivo que quieres que cargue, la propia funcion
de dicho truco.
---------------------------------*/

//BIBLIOTECAS
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

//VARIABLES GLOBALES
const int CARTASxPALO = 13,
MAX_CARTAS = 52,
APU_MIN = 5,
APU_MAX = 50,
DINERO_INI = 1000;

//TIPOS PROPIOS
//Enumerados

typedef enum tJugador
{
	Jugador,
	Automata
};

typedef enum
{
	picas,
	treboles,
	diamantes,
	corazones
} tPalo;

typedef enum
{
	A = 1, J = 11, Q, K
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
		palo(p),
		num(n)
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
	tMazo() : cuantas(0){}

	//Metodos	
	//Funciones de carga y guardado de mazos
	bool cargar(string &nomb);
	bool cargar_auto(string &nomb);
	bool mazoValido(int cartasNecesarias, string &nomb);
	void cargar_mazo_completo();
	bool agregar();
	bool guardar(string &nomb);

	//Funciones de manipulacion de un mazo individual
	inline void vaciar();
	void barajar();
	void intercambiar(int pos1, int pos2);
	bool desplazar(int numero);
	void cortar(int cuantasCartas);
	bool partir(tMazo &otroMazo, int cuantasCoger);
	bool unir(const tMazo &otroMazo);
	void carta_concreta_dentro();
	void carta_concreta_fuera();
	bool agregar_carta(tCarta carta);
	bool quitar_carta(tCarta carta);

	//Funciones para repartir en varios mazos
	void repartirParImpar(tMazo &mazoPar, tMazo &mazoImpar);
	void repartirFigurasNumeros(tMazo &mazoFiguras, tMazo &mazoNumeros);
	void repartirBajaAlta(tMazo &mazoBajas, tMazo &mazoAltas);
	void repartirNegroRojo(tMazo &mazoNegro, tMazo &mazoRojo);
	void repartir_segun_criterio(tMazo &mazo1, tMazo &mazo2, bool(*criterio)(tCarta));
	void repartirIntercalando(int enCuantos, int queMazo, tMazo &mazoNuevo);
	int repartir_en_n(tMazo mazo[], int n);

	void repartir_n_cartas(tMazo &mazoJugador, int cuantasQuieres);

	int repartir_con_cuenta_atras(tMazo &mazoNuevo, int cuenta);

	//Operadores
	tCarta& operator[](const int index){ return cartas[index]; }
	const tCarta& operator[](const int index) const { return cartas[index]; }
	//Datos
	tCarta cartas[MAX_CARTAS];
	int cuantas;
};

class Blackjack
{
public:
	//Constructor
	Blackjack() :
		dinero(DINERO_INI),
		cont(0)
	{
		mazo.cargar_mazo_completo();
	}

	//Metodos
	// Menus
	int menu_opciones();
	int opciones_de_blackjack();

	//Funciones de archivo
	bool actualizar_stats(tJugador ganador, string usuario);

	//Funciones de datos
	int apuesta();
	void doblarApuesta(char decision, int cuantasVeces, int apu, bool &dudaApuesta);
	void recompensa(int apu, int queHacer, string usuario);
	int valor(const tMazo &mano);

	//Funciones de juego
	void run(string usuario);
	void mano(string usuario);
	bool turno_crupier();
	inline void ganar(int apu);
	inline void perder(int apu);

private:
	//Variables
	int dinero,
		cont;
	tMazo mazo;
	tMazo mazoJugador, mazoBot;
};

//FUNCIONES
string iniciar_sesion();
string usuario_valido();

//Menus
int menu_principal();
int menu_de_carga_y_guardado();
int menu_de_manipulacion_de_mazos();
int menu_de_juegos();
int menu_de_magia();

int digitoEntre(int a, int b);
inline void linea();

inline tCarta elegir_carta();
int elegir_numero();
char elegir_palo();
char paloValido();

//Funciones de output
void mostrar(const tMazo mazo[], int n, int cuantasPorMazo);
void mostrar(const tMazo mazo);
int mostrar(const tCarta carta);
int mostrar(const tNumero n);
int mostrar(const tPalo p);
bool mostrar(string archivo);
void prediccion();
void revelar_carta(int sumaValor);
int valor(tCarta carta);

//Funciones de carga y guardado de mazos
bool abrir(string &nomb, ifstream &archivo);

string traducir(tCarta carta);
tCarta traducir(char p, int n);

//Funciones de manipulacion de un mazo individual
int randint(int max);

//Funciones para repartir en varios mazos
bool pares(tCarta carta);
bool figuras(tCarta carta);
bool bajas(tCarta carta);
bool negro(tCarta carta);

//Funciones de archivo
void registrar_nueva_ejecucion();
void stats(string usuario);
void fcopy(string origen, string destino);
bool restore_from_backup();
string reset(string usuario);
void hard_reset();
void soft_reset(string usuario);
void delete_user(string usuario);

//Trucos de magia
void truco_de_los_tres_montones();
void truco_de_la_posada();
void truco_del_jugador_desconfiado();
void truco_de_cabo_caniaberal();

//Funcion de pausa
inline void pausa();

int main()
{
	int opcion, eleccion;
	tMazo mazo;
	string nomb, usuario;

	srand(time(NULL));
	mazo.vaciar();

	usuario = iniciar_sesion();
	registrar_nueva_ejecucion();

	do
	{
		eleccion = menu_principal();
		if (eleccion == 1)
		{
			do
			{
				opcion = menu_de_carga_y_guardado();
				if (opcion == 1)
				{
					linea();
					if (mazo.cargar(nomb))
					{
						cout << "Mazo:" << endl;
						mostrar(mazo);
					}
					else cout << "El archivo no pudo cargarse." << endl;
				}
				else if (opcion == 2)
				{
					linea();
					mazo.cargar_mazo_completo();

					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 3)
				{
					linea();
					if (mazo.guardar(nomb))
						cout << "Guardado exitoso!" << endl;
					else cout << "Fallo al guardar" << endl;
				}
				else if (opcion == 4)
				{
					linea();
					mazo.agregar();
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
			} while (opcion != 0);
		}
		else if (eleccion == 2)
		{
			do
			{
				opcion = menu_de_manipulacion_de_mazos();
				if (opcion == 1)
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
					mazo.cortar(cantidad);
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 3)
				{
					linea();
					int cualQuieres;
					tMazo negro, rojo;
					mazo.repartirNegroRojo(negro, rojo);

					cout << "Negras: " << endl;
					mostrar(negro);

					cout << "Rojas: " << endl;
					mostrar(rojo);

					cout << "Que mazo escoges?" << endl
						<< "1 - Negras" << endl
						<< "2 - Rojas" << endl
						<< "0 - Ultimo mazo cargado" << endl;

					cualQuieres = digitoEntre(0, 2);

					if (cualQuieres == 1)
					{
						mazo.vaciar();
						mazo.unir(negro);
					}
					else if (cualQuieres == 2)
					{
						mazo.vaciar();
						mazo.unir(rojo);
					}
				}
				else if (opcion == 4)
				{
					linea();
					int cualQuieres;
					tMazo alto, bajo;
					mazo.repartirBajaAlta(bajo, alto);

					cout << "Bajas: " << endl;
					mostrar(bajo);

					cout << "Altas: " << endl;
					mostrar(alto);

					cout << "Que mazo escoges?"      << endl
						<< "1 - Bajas"               << endl
						<< "2 - Altas"               << endl
						<< "0 - Ultimo mazo cargado" << endl;

					cualQuieres = digitoEntre(0, 2);

					if (cualQuieres == 1)
					{
						mazo.vaciar();
						mazo.unir(bajo);
					}
					else if (cualQuieres == 2)
					{
						mazo.vaciar();
						mazo.unir(alto);
					}
				}
				else if (opcion == 5)
				{
					linea();
					int cualQuieres;
					tMazo par, impar;
					mazo.repartirParImpar(par, impar);

					cout << "Pares: " << endl;
					mostrar(par);

					cout << "Impares: " << endl;
					mostrar(impar);

					cout << "Que mazo escoges?" << endl
						<< "1 - Pares" << endl
						<< "2 - Impares" << endl
						<< "0 - Ultimo mazo cargado" << endl;

					cualQuieres = digitoEntre(0, 2);

					if (cualQuieres == 1)
					{
						mazo.vaciar();
						mazo.unir(par);
					}
					else if (cualQuieres == 2)
					{
						mazo.vaciar();
						mazo.unir(impar);
					}
				}
				else if (opcion == 6)
				{
					linea();
					int cualQuieres;
					tMazo figura, numero;
					mazo.repartirFigurasNumeros(figura, numero);

					cout << "Figuras:" << endl;
					mostrar(figura);

					cout << "Numeros:" << endl;
					mostrar(numero);

					cout << "Que mazo escoges?"       << endl
						 << "1 - Figuras"             << endl
						 << "2 - Numeros"             << endl
						 << "0 - Ultimo mazo cargado" << endl;

					cualQuieres = digitoEntre(0, 2);

					if (cualQuieres == 1)
					{
						mazo.vaciar();
						mazo.unir(figura);
					}
					else if (cualQuieres == 2)
					{
						mazo.vaciar();
						mazo.unir(numero);
					}
				}
				else if (opcion == 7)
				{
					linea();

					int en_cuantos;
					int cualQuieres;

					cout << "En cuantos mazos quieres separar este mazo?" << endl;
					en_cuantos = digitoEntre(1,4);

					tMazo *mazos = new tMazo[en_cuantos];
					int cuantas = mazo.repartir_en_n(mazos, en_cuantos);

					mostrar(mazos, en_cuantos, cuantas);

					cout << "Que mazo escoges? (0 para ultimo mazo cargado):";

					cualQuieres = digitoEntre(0, en_cuantos);

					if (cualQuieres != 0)
					{
						mazo.vaciar();
						mazo.unir(mazos[cualQuieres-1]);
					}
					delete[] mazos;
				}
				else if (opcion == 8)
				{
					linea();

					int cuantas;
					tMazo mazoExtra;

					cout << "Cuantas cartas quieres?" << endl;
					cin >> cuantas;
					mazo.repartir_n_cartas(mazoExtra, cuantas);
					mazo.vaciar();
					mazo.unir(mazoExtra);

					cout << "Mazo:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 9)
				{
					linea();
					cout << "Mazo:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 10)
				{
					if (mazo.cuantas == MAX_CARTAS)
					{
						cout << "Error, el mazo no puede "
							<< "tener mas de 52 cartas" << endl;
					}
					else
					{
						linea();
						mazo.carta_concreta_dentro();
						cout << "Mazo actual:" << endl;
						mostrar(mazo);
					}
				}
				else if (opcion == 11)
				{
					linea();
					mazo.carta_concreta_fuera();
					cout << "Mazo actual:" << endl;
					mostrar(mazo);
				}
				else if (opcion == 12)
				{
					mazo.vaciar();
				}
			} while (opcion != 0);
		}
		else if (eleccion == 3)
		{
			Blackjack bj; bj.run(usuario);
		}
		else if (eleccion == 4)
		{
			do
			{
				opcion = menu_de_magia();
				if (opcion == 1)
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
				else if (opcion == 4)
				{
					linea();
					truco_de_cabo_caniaberal();
				}
			} while (opcion != 0);
		}
	} while (eleccion != 0);

	return 1;
}

//Devuelve el nombre de usuario, y crea su perfil 
//en las estadisticas si no existe
string iniciar_sesion()
{
	//Conseguimos el nombre de usuario
	string usuario;
	cout << "Bienvenido al programa de la cartomagia!" << endl
		<< "Como te llamas? ";
	usuario = usuario_valido();

	string line;
	ofstream backup;
	//Abrimos el archivo stats
	ifstream stats;
	stats.open("stats.txt");

	//Restauracion desde backup, si es necesaria
	if (!stats.good())
	{
		cout << "\"stats.txt\" no existe. Buscando backup." << endl;
		stats.close();
		restore_from_backup();
		stats.open("stats.txt");
	}
	if (stats.good())
	{
		//Busqueda de la info del usuario
		getline(stats, line);
		while (line != usuario && !stats.eof())
		{
			getline(stats, line);
		}
		//Si el usuario no existe, creamos un nuevo perfil de usuario.
		if (stats.eof())
		{
			cout << "Usuario no encontrado. Se creara un nuevo perfil." << endl;

			backup.open("backup.txt", ios::app);
			backup << usuario << endl
				<< 0 << endl  //Ganadas
				<< 0 << endl  //Perdidas
				<< endl;
			backup.close();
		}
		else
		{
			cout << "Bienvenido de nuevo " << usuario << endl;
		}
	}
	else
		//Si el archivo stats no existe y no hay backup, creamos un nuevo archivo 
		//y agregamos el perfil del nuevo usuario
	{
		cout << "Un nuevo archivo sera creado." << endl;

		backup.open("backup.txt");
		backup << 0 << endl << endl //Ejecuciones
			<< usuario << endl         //Usuario
			<< 0 << endl         //Ganadas
			<< 0 << endl         //Perdidas
			<< endl;
		backup.close();
	}
	stats.close();

	fcopy("backup.txt", "stats.txt");

	return usuario;
}

//Evita que el nombre de usuario empiece por un numero, para evitar 
//errores a la hora de buscar a ese usuario en el archivo stats.txt
string usuario_valido()
{
	string nombre;

	cin >> nombre;
	cin.clear();

	while (isdigit(nombre[0]))
	{
		cout << "Error, el nombre de usuario no puede empezar por un digito" << endl;
		cin >> nombre;
		cin.clear();
	}
	return nombre;
}


//Menu que permite al usuario acceder a otros menus, o bien al juego de blackjack 
int menu_principal()
{
	linea();
	cout << "Menu principal:"                  << endl
		<< "1 - Menu de carga y guardado"      << endl
		<< "2 - Menu de manipulacion de mazos" << endl
		<< "3 - Menu de Blackjack"             << endl
		<< "4 - Menu de magia de cartas"       << endl
		<< "0 - Salir"                         << endl;

	return digitoEntre(0, 4);
}

//Menu que permite al usuario cargar y/o guardar segun que mazos
int menu_de_carga_y_guardado()
{
	linea();
	cout << "Menu de carga y guardado:"   << endl
		<< "1 - Cargar mazo a elegir"     << endl
		<< "2 - Cargar mazo completo"     << endl
		<< "3 - Guardar"                  << endl
		<< "4 - Agregar mazo"             << endl
		<< "0 - Volver al menu principal" << endl;

	return digitoEntre(0, 4);
}

//Menu que permite al usuario manipular de diferentes formas 
//el mazo que haya cargado anteriormente
int menu_de_manipulacion_de_mazos()
{
	linea();
	cout << "Menu de manipulacion de mazos:"   << endl
		<< "1  - Barajar"                      << endl
		<< "2  - Cortar"                       << endl
		<< "3  - Separar en negras y rojas"    << endl
		<< "4  - Separar en altas y bajas"     << endl
		<< "5  - Separar en pares e impares"   << endl
		<< "6  - Separar en figuras y numeros" << endl
		<< "7  - Separar en n montones"        << endl
		<< "8  - Repartir n cartas"            << endl
		<< "9  - Mostrar mazo actual"          << endl
		<< "10 - Aniadir una carta concreta"   << endl
		<< "11 - Eliminar una carta concreta"  << endl
		<< "12 - Vaciar mazo actual"           << endl
		<< "0  - Volver al menu principal"     << endl;

	return digitoEntre(0, 12);
}

//Menu que permite al usuario acceder a los distintos trucos de magia
int menu_de_magia()
{
	linea();
	cout << "Menu de magia de cartas:"         << endl
		<< "1 - Truco de los tres montones"    << endl
		<< "2 - Truco de la posada"            << endl
		<< "3 - Truco del jugador desconfiado" << endl
		<< "4 - Truco de cabo caniaveral "     << endl
		<< "0 - Volver al menu principal"      << endl;

	return digitoEntre(0, 4);
}

//Funcion que impide que el usuario introduzca algo que no sea un digito 
//contenido entre los argumentos de dicha funcion
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

	} while (digito == -1);

	return digito;
}

//Saca por consola una linea de guion
inline void linea()
{
	cout << setfill('-') << setw(79) << '-' << endl << setfill(' ');
}

//Permite al usuario elegir una carta pidiendole el numero y el palo
//de dicha carta
inline tCarta elegir_carta()
{
	return traducir(elegir_palo(), elegir_numero());
}

//Pide al usuario el numero de la carta que quiere elegir
int elegir_numero()
{
	cout << "Que numero de carta escoges?"
		<< " (debe estar entre 1 y 13) " << endl;

	return digitoEntre(1, 13);
}

//Pide al usuario el char correspondiente al palo de la carta que quiere elegir
char elegir_palo()
{

	cout << "Que palo eliges?"
		<< " (p = picas, d = diamantes, t = treboles, c = corazones)" << endl;

	return paloValido();
}

char paloValido()
{
	char simboloPalo = 'j';

	do
	{
		cin.sync();
		cin >> simboloPalo;

		if (simboloPalo != 'p' || simboloPalo != 'd' || simboloPalo != 't' || simboloPalo != 'c')
		{
			cout << "Error, introduce una de estas cuatro letras (p = picas, d = diamantes, "
				<< "t = treboles, c = corazones)";
			simboloPalo = 'j';
		}
	} while (simboloPalo == 'j');

	return simboloPalo;
}

//Muestra por consola tantos mazos como se le pasen como argumento
void mostrar(const tMazo mazo[], int n, int cuantasPorMazo)
{
	int longitud;

	cout << " ";

	for (int i = 0; i<n; i++)
	{
		cout << "Mazo " << (i + 1) << ":";

		if (i != (n-1))
			cout << right << setw(17);
	}
	cout << endl;

	for (int i = 0; i < cuantasPorMazo; i++)
	{
		cout << " ";

		for (int j = 0; j < n; j++)
		{
			longitud = mostrar(mazo[j][i]);
			if (j == 0 && mazo[j][i].num == 10)
			{
				longitud++;
			}
			if (j != (n - 1))
			{
				cout << right << setw(20 - longitud);
			}
		}
		cout << endl;
	}
}

//Muestra por consola el mazo que le pases como argumento
void mostrar(tMazo mazo)
{
	for (int i = 0; i < mazo.cuantas; i++)
	{
		mostrar(mazo[i]);
		cout << endl;
	}
	cout << endl;
}

//Muestra la carta que le pases como argumento
int mostrar(const tCarta carta)
{
	int longTotal;

	int longNumero = mostrar(carta.num);

	cout << " ";

	int longPalo = mostrar(carta.palo);

	longTotal = longNumero + longPalo + 1;

	return longTotal;
}

//Traduce los numeros de una carta a simbolos (A, J, Q, K)
//y los muestra por consola
int mostrar(const tNumero n)
{
	int longNumero = 1;

	if (n == A)
	{
		cout << "A";
	}
	else if (n == J)
	{
		cout << "J";
	}
	else if (n == Q)
	{
		cout << "Q";
	}
	else if (n == K)
	{
		cout << "K";
	}
	else
	{
		cout << n;
	}
	return longNumero;
}

//Traduce los palos de una carta y los muestra por consola
int mostrar(const tPalo p)
{
	int longPalo;

	if (p == picas)
	{
		cout << "de picas";
		
		longPalo = 8;
	}
	else if (p == treboles)
	{
		cout << "de treboles";

		longPalo = 11;
	}
	else if (p == diamantes)
	{
		cout << "de diamantes";

		longPalo = 12;
	}
	else /*if (c == corazones)*/
	{
		cout << "de corazones";

		longPalo = 12;
	}
	return longPalo;
}

//Muestra el contenido del archivo que le pases como argumento
bool mostrar(string archivo)
{
	bool ok;
	ifstream acerca;
	char c;

	linea();

	acerca.open(archivo);

	if (acerca.is_open())
	{
		acerca.get(c); //Lee el primer caracter

		while (!acerca.fail()) //Mientras la lectura no falle
		{
			cout << c;
			acerca.get(c); //Lee el siguiente caracter
		}
		ok = true;
		acerca.close();
	}
	else
	{
		cout << "Error, no se encontro el archivo" << endl;
		ok = false;
	}
	return ok;
}

//Usada en el truco cabo caniaveral, adivina la carta que saldra al final del truco
void prediccion(tMazo mazo)
{
	cout << "Saldra la carta: ";

	mostrar(mazo[8]);

	cout << endl;
}

//Usada en el truco cabo caniaveral, revela cual es la carta resultante del truco
void revelar_carta(int sumaValor, tMazo &mazo)
{
	cout << "Ahora contamos " << sumaValor << " cartas, y las "
		<< "vamos mostrando:" << endl << endl;

	for (int i = sumaValor; i>0; i--)
	{
		cout << "Carta " << sumaValor - i + 1 << ": " << endl;

		mostrar(mazo[mazo.cuantas - sumaValor + i - 1]);

		cout << endl;
	}

	cout << "La carta final es: ";

	mostrar(mazo[mazo.cuantas - sumaValor]);

	cout << endl;
}

//Usada en el truco cabo caniaveral, determina el valor de la carta que le 
//pases como argumento, teniendo en cuenta que las figuras tambien valen 10
int valor(tCarta carta)
{
	int valor;

	if (carta.num == K || carta.num == Q || carta.num == J)
	{
		valor = 10;
	}
	else
	{
		valor = carta.num;
	}
	return valor;
}

//Carga un mazo de un archivo a elección del usuario.
bool tMazo::cargar(string &nomb)
{
	char p;
	int cont = 0, n;
	ifstream archivo;
	if (abrir(nomb, archivo))
	{
		archivo >> p;
		while (p != 'x' && cont < MAX_CARTAS)
		{
			archivo >> n;
			cartas[cont] = traducir(p, n);
			cont++;
			archivo >> p;
		}
		cuantas = cont;
		archivo.close();
		return true;
	}
	else return false;
}

//Carga automaticamente el archivo que le pases como argumento
bool tMazo::cargar_auto(string &nomb)
{
	char p;
	int cont = 0, n;
	ifstream archivo(nomb);
	if (archivo.is_open())
	{
		archivo >> p;
		while (p != 'x' && cont < MAX_CARTAS)
		{
			archivo >> n;
			cartas[cont] = traducir(p, n);
			cont++;
			archivo >> p;
		}
		cuantas = cont;
		archivo.close();
		return true;
	}
	else return false;
}

//Comprueba que el mazo cargado tenga las cartas necesarias para los trucos
bool tMazo::mazoValido(int cartasNecesarias, string &nomb)
{
	if (cargar_auto(nomb))
	{
		if (cartasNecesarias != cuantas)
		{
			cout << "Error, el mazo cargado no tiene las "
				<< cartasNecesarias << " cartas necesarias." << endl
				<< "Sal del programa, ve al codigo, modifica el nombre "
				<< "del archivo y vuelve a ejecutar el programa y el truco"
				<< endl;

			pausa();
		}
		return true;
	}
	else return false;
}

//Carga un mazo de 52 cartas sin necesidad de acceder a ningun archivo
void tMazo::cargar_mazo_completo()
{
	int k = 0;

	for (int j = 0; j<4; j++)
	{
		for (int i = 1; i<14; i++)
		{
			cartas[k] = tCarta((tPalo)j, (tNumero)i);
			k++;
			cuantas = 52;
		}
	}
}

//Abre el archivo que indica el usuario. Si el archivo no existe, se pregunta de nuevo, hasta tres veces.
bool abrir(string &nomb, ifstream &archivo)
{
	cout << "Introduzca el nombre del archivo:" << endl;
	cin >> nomb;
	archivo.open(nomb);

	if (!archivo.is_open())
	{
		for (int i = 0; (i<2) && (!archivo.is_open()); i++)
		{
			cout << "Error, no se ha encontrado el archivo " << nomb << endl;
			cin >> nomb;
			archivo.open(nomb);
		}
	}
	if (archivo.is_open()) return true;

	else return false;
}

//Concatena al mazo actual un mazo cargado de archivo.
bool tMazo::agregar()
{
	tMazo otroMazo;
	string nomb;
	if (!otroMazo.cargar(nomb))
	{
		cout << "No pudo cargarse el archivo" << endl;
		return false;
	}
	else if (!unir(otroMazo))
	{
		cout << "El mazo seleccionado junto al actual superan el limite de cartas por mazo" << endl;
		return false;
	}
	else return true;
}

//Guarda el mazo que tengas cargado, en el archivo que tue elijas 
//(en el archivo) actual por defecto
bool tMazo::guardar(string &nomb)
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
		for (int i = 0; i < cuantas; i++)
		{
			archivo << traducir(cartas[i]) << endl;
		}
		archivo << "x";
		return true;
	}
	else return false;
}

//Traduce el palo de una carta a un char
string traducir(tCarta carta)
{
	string s = "";
	switch (carta.palo)
	{
	case picas:
		s += "p";
		break;
	case treboles:
		s += "t";
		break;
	case diamantes:
		s += "d";
		break;
	case corazones:
		s += "c";
		break;
	}
	s += " ";
	s += to_string(carta.num);
	return s;
}

//Traduce una pareje formada por un char y un int a una carta
tCarta traducir(char p, int n)
{
	tPalo suit;

	if (p == 'c') suit = corazones;
	else if (p == 't') suit = treboles;
	else if (p == 'p') suit = picas;
	else /*if (p == 'd')*/ suit = diamantes;

	tCarta carta(suit, (tNumero)n);

	return carta;
}

//Vacia el mazo actual reiniciando el contador de la funcion cuantas()
inline void tMazo::vaciar()
{
	cuantas = 0;
}

//Baraja el mazo, intercambiando aleatoriemente cartas
void tMazo::barajar()
{
	for (int i = 0; i<3 * cuantas; i++)
	{
		intercambiar(randint(cuantas), randint(cuantas));
	}
}

//Genera un numero aleatorio entre 0 y el numero que se le pase como argumento
int randint(int max)
{
	return rand() % (max);
}

//Intercambia al azahar las posiciones de dos cartas dentro de un mazo
void tMazo::intercambiar(int pos1, int pos2)
{
	tCarta aux;

	aux = cartas[pos1];

	cartas[pos1] = cartas[pos2];

	cartas[pos2] = aux;
}

//Desplaza las cartas del mazo a la derecha, para hacer hueco para nuevas cartas
bool tMazo::desplazar(int numero)
{
	if (cuantas + numero <= MAX_CARTAS)
	{
		for (int i = cuantas - 1; i >= 0; i--)
			cartas[i + numero] = cartas[i];
		cuantas += numero;
		return true;
	}
	else return false;
}

//Corta el mazo actual por la posicion que indique el argumento, 
//y completa el mazo situando ambas partes en el orden contrario 
//a en que se separaron
void tMazo::cortar(int cuantasCartas)
{
	tMazo otroMazo;
	//Corta...
	if (partir(otroMazo, cuantasCartas))
	{
		//...y completa.
		unir(otroMazo);
	}
}

//Corta el mazo actual por la posicion que indique el argumento, 
//y guarda la otra parte de este en una variable tMazo 
bool tMazo::partir(tMazo &otroMazo, int cuantasCoger)
{
	int i;
	if (cuantasCoger > cuantas) return false;
	else
	{
		for (i = 0; cuantasCoger + i < cuantas; i++)
		{
			otroMazo[i] = cartas[cuantasCoger + i];
		}

		cuantas = cuantasCoger;
		otroMazo.cuantas = i;

		return true;
	}
}

//Une el mazo actual con el mazo que le pases de argumento, 
//guardando el mazo resultante en el mazo actual
bool tMazo::unir(const tMazo &otroMazo)
{
	if (desplazar(otroMazo.cuantas))
	{
		for (int i = 0; i < otroMazo.cuantas; i++)
		{
			cartas[i] = otroMazo[i];
		}
		return true;
	}
	else return false;
}

//Añade una carta elegida por el usuario al mazo actual
inline void tMazo::carta_concreta_dentro()
{
	agregar_carta(elegir_carta());
}

//Quita una carta elegida por el usuario del mazo actual
inline void tMazo::carta_concreta_fuera()
{
	quitar_carta(elegir_carta());
}

//Añade la carta que le passes como argumento al mazo actual
bool tMazo::agregar_carta(tCarta carta)
{
	if (cuantas == MAX_CARTAS)
	{
		cout << "Error, el mazo no puede contener mas de 52 cartas" << endl;
		return false;
	}
	else
	{
		cartas[cuantas] = carta;
		cuantas++;
		return true;
	}
}

//Quita la carta que le pases como argumento del mazo actual
bool tMazo::quitar_carta(tCarta carta)
{
	int i;

	//Buscamos la carta objetivo
	for (i = 0; cartas[i] != carta && i < cuantas; i++);

	if (i == cuantas)
	{
		cout << "Error, no se encontro la carta seleccionada" << endl;
		return false;
	}
	else
	{
		//Desplazamos el mazo hacia la izquierda, cubriendo la carta objetivo
		for (; i < cuantas - 1; i++)
			cartas[i] = cartas[i + 1];
		cuantas--;
		return true;
	}
}

//Criterio de si la carta que se pase como argumento es par
bool pares(tCarta carta)
{
	return (!(carta.num % 2));
}

//Separa el mazo en dos segun sean sus cartas pares o impares
void tMazo::repartirParImpar(tMazo &mazoPar, tMazo &mazoImpar)
{
	repartir_segun_criterio(mazoPar, mazoImpar, pares);
}

//Criterio de si la carta que se pase como argumento es figura
bool figuras(tCarta carta)
{
	return (carta.num > 10 || carta.num == A);
}

//Separa el mazo en dos segun sean sus cartas figuras o numero
void tMazo::repartirFigurasNumeros(tMazo &mazoFiguras, tMazo &mazoNumeros)
{
	repartir_segun_criterio(mazoFiguras, mazoNumeros, figuras);
}

//Criterio de si la carta que se pase como argumento es baja
bool bajas(tCarta carta)
{
	return (carta.num < 8);
}

//Separa el mazo en dos segun sean sus cartas bajas o altas
void tMazo::repartirBajaAlta(tMazo &mazoBajas, tMazo &mazoAltas)
{
	repartir_segun_criterio(mazoBajas, mazoAltas, bajas);
}

//Criterio de si la carta que se pase como argumento es negra
bool negro(tCarta carta)
{
	return ((carta.palo == picas) || (carta.palo == treboles));
}

//Separa el mazo en dos segun sean sus cartas negras o rojas
void tMazo::repartirNegroRojo(tMazo &mazoNegro, tMazo &mazoRojo)
{
	repartir_segun_criterio(mazoNegro, mazoRojo, negro);
}

//Generalizar es mejor. Para que tener cuatro funciones practicamente iguales?
void tMazo::repartir_segun_criterio(tMazo &mazo1, tMazo &mazo2, bool(*criterio)(tCarta))
{
	int j = 0, k = 0;

	for (int i = 0; i < cuantas; i++)
	{
		if (criterio(cartas[i]))
		{
			mazo1[j] = cartas[i];
			j++;
		}
		else
		{
			mazo2[k] = cartas[i];
			k++;
		}
	}
	mazo1.cuantas = j;
	mazo2.cuantas = k;
}

//Reparte una de cada enCuantos cartas del mazo actual a mazoNuevo, 
//comenzando por la carta queMaoz del mazo actual
void tMazo::repartirIntercalando(int enCuantos, int queMazo, tMazo &mazoNuevo)
{
	int j = 0;
	for (int i = queMazo; i < cuantas; i += enCuantos, j++)
	{
		mazoNuevo[j] = cartas[i];
	}
	mazoNuevo.cuantas = j;
}

//Reparte el mazo actual en tantos mazos como le pases como argumento
int tMazo::repartir_en_n(tMazo mazo[], int n)
{
	//Repartir alternamente
	for (int i = 0; i<n; i++)
		repartirIntercalando(n, i, mazo[i]);

	return ((*this).cuantas / n);
}

//Reparte consecutivamente las cartas que pases como argumento desde el
//mazo actual a mazoJugador
void tMazo::repartir_n_cartas(tMazo &mazoJugador, int cuantasQuieres)
//cont evita que siempre repartamos las mismas cartas.
{
	if (cuantasQuieres >(*this).cuantas)
	{
		cout << "Error, no puedes coger mas cartas de las que tiene el mazo" << endl;
	}
	else if (cuantasQuieres + mazoJugador.cuantas > MAX_CARTAS)
	{
		cout << "Error, el mazo no puede contener mas de 52 cartas" << endl;
	}
	else
	{
		for (int i = 0; i < cuantasQuieres; i++)
			mazoJugador[mazoJugador.cuantas++] = (*this)[--(*this).cuantas];
	}
}

//Usada en el truco de cabo caniaveral, reparte las cartas que le pases como argumento
//del mazo principal a mazoNuevo y las va mostrando, haciendo una cuenta atras desde cuenta.
//Si el numero de la carta coincide con cuenta, el reparto se detiene, en cambio si la cuenta 
//llega a 0 la cuenta tambien se detiene, pero no se muestra la ultima carta.
int tMazo::repartir_con_cuenta_atras(tMazo &mazoNuevo, int cuenta)
{
	int i = cuenta + 1;

	do
	{
		i--;
		(*this).repartir_n_cartas(mazoNuevo, 1);

		if (i == 0)
		{
			cout << "Carta " << i << ": "
				<< "Valor = 0";
		}
		else
		{
			cout << "Carta " << i << ": ";
			mostrar(mazoNuevo[cuenta - i]);
		}

		pausa();
	} while (i>0 && valor(mazoNuevo[cuenta - i]) != i);

	return i;
}

//Actualiza el numero de ejecuciones guardado en el archivo stats.
void registrar_nueva_ejecucion()
{
	int ejecuciones; char c;

	ifstream stats("stats.txt", ios::in);
	ofstream backup("backup.txt", ios::out);
	//Las comprobaciones de backup ya se han hecho en iniciar_sesion()

	stats >> ejecuciones;
	backup << ejecuciones + 1;

	stats.get(c);
	while (!stats.eof())
	{
		backup.put(c);
		stats.get(c);
	}

	stats.close();
	backup.close();

	fcopy("backup.txt", "stats.txt");
}

//Actualiza las estadisticas
bool Blackjack::actualizar_stats(tJugador ganador, string usuario)
{
	bool ok;
	int ganadas, perdidas;
	string linea;
	ifstream stats;
	ofstream actualizar;

	stats.open("stats.txt");

	//Restauracion con el backup, si es necesaria
	if (!stats.good())
	{
		cout << "Error! stats.txt no existe. Buscando backup..." << endl;
		stats.close();

		restore_from_backup();

		stats.open("stats.txt");
	}

	actualizar.open("backup.txt");

	if (stats.good())
	{
		//Copia de stats a backup, hasta la info del usuario
		do
		{
			getline(stats, linea);
			actualizar << linea << endl;
		} while (linea != usuario);

		//Actualizacion de datos
		stats >> ganadas;
		stats >> perdidas;

		if (ganador == Jugador)   ganadas += 1;
		else if (ganador == Automata) perdidas += 1;

		actualizar << ganadas << endl;
		actualizar << perdidas << endl;

		char c;
		stats.get(c);
		while (!stats.eof())
		{
			actualizar.put(c);
			stats.get(c);
		}

		ok = true;
	}
	else
	{
		ganadas = (ganador == Jugador) ? 1 : 0;
		perdidas = (ganador == Automata) ? 1 : 0;

		actualizar << 1 << endl << endl //Ejecuciones
			<< usuario << endl
			<< ganadas << endl
			<< perdidas << endl
			<< endl;

		cout << "El archivo 'stats.txt' no se encontro, se ha creado un nuevo archivo" << endl;

		ok = false;
	}
	stats.close();
	actualizar.close();

	//Ahora copiamos la informacion actualizada en el archivo original
	fcopy("backup.txt", "stats.txt");

	return ok;
}

//Muestra las estadisticas del jugador actual.
void stats(string usuario)
{
	ifstream stats;
	string line;
	int ganadas, perdidas, ejecuciones;

	stats.open("stats.txt");

	stats >> ejecuciones;

	getline(stats, line);

	while (line != usuario)
	{
		getline(stats, line);
	}

	stats >> ganadas;
	stats >> perdidas;

	cout << setfill('-') << setw(79) << '-' << endl;
	cout << "Numero de ejecuciones del programa: " << ejecuciones << endl;
	cout << endl;
	cout << "Partidas de " << usuario << ": " << (ganadas + perdidas) << endl;
	cout << right
		<< setfill(' ') << setw(22) << "ganadas: " << ganadas << endl
		<< setfill(' ') << setw(22) << "perdidas: " << perdidas << endl
		<< endl;

	stats.close();
}

//Copia el contenido de un archivo en otro 
//por si fuera necesario restaurar un archivo
void fcopy(string origen, string destino)
{
	ifstream paso1;
	ofstream paso2;
	char 	  word;

	paso1.open(origen);
	paso2.open(destino);

	paso1.get(word);

	while (!paso1.eof())
	{
		paso2.put(word);
		paso1.get(word);
	}

	paso1.close();
	paso2.close();
}

//Copia backup.txt en stats.txt. Si backup no existe devuelve false
bool restore_from_backup()
{
	ifstream backup; bool ok;

	backup.open("backup.txt");
	if (backup.good())
	{
		backup.close();
		fcopy("backup.txt", "stats.txt");
		ok = true;
	}
	else
	{
		backup.close();
		cout << "El backup no ha sido encontrado" << endl;
		ok = false;
	}
	return ok;
}

//Menu con opciones de reseteo de estadisticas.
string reset(string usuario)
{
	cout << setfill('-') << setw(79) << '-' << endl
		<< "1 - Borrar estadisticas del jugador actual" << endl
		<< "2 - Borrar perfil del jugador actual" << endl
		<< "3 - Borrar todas las estadisticas" << endl
		<< "0 - Volver al menu" << endl;
	cout << setfill(' ');

	int opcion = digitoEntre(0, 3);

	if (opcion == 1)
		soft_reset(usuario);
	else if (opcion == 2)
	{
		delete_user(usuario);
		usuario = iniciar_sesion();
	}
	else if (opcion == 3)
	{
		hard_reset();
		usuario = iniciar_sesion();
	}
	return usuario;
}

//Borra todas las estadisticas.
void hard_reset()
{
	remove("backup.txt");
	remove("stats.txt");
}

//Inicializa a 0 las estadisticas de un usuario.
void soft_reset(string usuario)
{
	int i;
	string linea;
	ifstream stats;
	ofstream actualizar;

	stats.open("stats.txt");

	//Restauracion con el backup, si es necesaria
	if (!stats.good())
	{
		cout << "Error! stats.txt no existe. Buscando backup..." << endl;
		stats.close();

		restore_from_backup();

		stats.open("stats.txt");
	}

	actualizar.open("backup.txt");

	if (stats.good())
	{
		//Copia de stats a backup, hasta la info del usuario
		do
		{
			getline(stats, linea);
			actualizar << linea << endl;
		} while (linea != usuario);

		//Ignoramos los datos anteriores...
		stats >> i;
		stats >> i;
		//...y los sutituimos por 0
		actualizar << 0 << endl; //Ganadas
		actualizar << 0;         //Perdidas

		char c;
		stats.get(c);
		while (!stats.eof())
		{
			actualizar.put(c);
			stats.get(c);
		}
	}
	else
	{

		actualizar << 1 << endl << endl //Ejecuciones
			<< usuario << endl
			<< 0 << endl
			<< 0 << endl
			<< endl;

		cout << "El archivo 'stats.txt' no se encontro, se ha creado un nuevo archivo" << endl;
	}

	stats.close();
	actualizar.close();

	//Ahora copiamos la informacion actualizada en el archivo original
	fcopy("backup.txt", "stats.txt");
}

//Elimina un perfil de usuario en las estadisticas.
void delete_user(string usuario)
{
	string linea;
	ifstream stats;
	ofstream actualizar;

	stats.open("stats.txt");

	//Restauracion con el backup, si es necesaria
	if (!stats.good())
	{
		cout << "Error! stats.txt no existe. Buscando backup..." << endl;
		stats.close();

		restore_from_backup();

		stats.open("stats.txt");
	}

	actualizar.open("backup.txt");

	if (stats.good())
	{
		//Copia de stats a backup, hasta la info del usuario
		getline(stats, linea);
		while (linea != usuario)
		{
			actualizar << linea << endl;
			getline(stats, linea);
		}

		//Ignoramos los datos anteriores
		for (int i = 0; i<4; i++)
			stats.ignore(1000, '\n');

		//Copiamos el resto del archivo
		char c;
		stats.get(c);
		while (!stats.eof())
		{
			actualizar.put(c);
			stats.get(c);
		}
	}
	else
	{

		actualizar << 1 << endl << endl //Ejecuciones
			<< endl;

		cout << "El archivo 'stats.txt' no se encontro, se ha creado un nuevo archivo" << endl;
	}

	stats.close();
	actualizar.close();

	//Ahora copiamos la informacion actualizada en el archivo original
	fcopy("backup.txt", "stats.txt");
}

//Truco de la parte obligatoria
void truco_de_los_tres_montones()
{
	tMazo mazoU, mazo[3];
	string nomb = "3montones.txt.";
	int n;

	cout << "Se trata de un truco de adivinacion en el que un mazo de 21 cartas se reparte "
		<< "alternamente en tres montones, y se le pide al usuario que escoja una carta y "
		<< "la memorice, y despues los mazos se vuelven a juntar. El proceso se repite tres "
		<< "veces, y al final, la consola adivinara la carta elegida por el usuario" << endl;

	//generamos el mazo de 21 cartas
	if (mazoU.mazoValido(21, nomb))
	{
		for (int i = 0; i<3; i++)
		{
			if (i == 0)
			{
				cout << "Empezamos dividimos el mazo en tres repartiendo cartas alternamente "
					 << "desde el mazo inicial a otros tres mazos." << endl;

				pausa();

				cout << "Ahora fijate en una de las cartas de cualquiera de los tres mazos, "
					<< "y memorizala" << endl;

				pausa();
			}
			else if (i == 1)
			{
				cout << "Repetimos el proceso otra vez" << endl;

				pausa();

				cout << "Localiza la carta que has meorizado antes" << endl;

				pausa();
			}
			else if (i == 2)
			{
				cout << "Y volvemos a repetirlo una ultima vez" << endl;

				pausa();

				cout << "Presta atencion y encuentra tu carta" << endl;

				pausa();
			}
			//Repartir alternamente
			int cuantas = mazoU.repartir_en_n(mazo, 3);
			mazoU.vaciar();
			mostrar(mazo, 3, cuantas);

			//El usuario elije mazo
			cout << "En que mazo esta tu carta?" << endl;
			n = digitoEntre(1, 3);

			//Juntamos los mazos
			if (n == 1)
			{
				mazoU.unir(mazo[2]);
				mazoU.unir(mazo[0]);
				mazoU.unir(mazo[1]);
			}
			else if (n == 2)
			{
				mazoU.unir(mazo[2]);
				mazoU.unir(mazo[1]);
				mazoU.unir(mazo[0]);
			}
			else //if (n == 3)
			{
				mazoU.unir(mazo[1]);
				mazoU.unir(mazo[2]);
				mazoU.unir(mazo[0]);
			}
		}

		//Adivinamos la carta
		cout << "Tu carta era el..." << endl;
		mostrar(mazoU[10]);
		cout << endl;
	}
	else
	{
		cout << "Archivo " << nomb << " no encontrado" << endl
			 << "Sal del programa, ve al codigo, modifica el nombre "
			 << "del archivo y vuelve a ejecutar el programa y el truco"
			 << endl;
	}
}

//Truco de la parte obligatoria
void truco_de_la_posada()
{
	tMazo mazo[4], mazoU;
	string nomb = "posada.txt";
	int corte;

	if (mazoU.mazoValido(16, nomb))
	{
		//Contamos la historia
		cout << "Habia una vez una posada con cuatro habitaciones." << endl
			 << "Un dia llegaron cuatro caballeros y cada uno se"
			 << "puso en una habitacion diferente." << endl
			 << "Luego llegaron cuatro senioras, y para no dejarlas"
			 << "sin habitacion, ubicaron a cada una en una de dichas"
			 << "habitaciones, con los caballeros." << endl
			 << "Luego llegaron cuatro reyes con sus cuatro peones,"
			 << "y pusieron cada rey y cada peon en alguna de dichas" << endl
			 << "cuatro habitaciones. " << endl;

		pausa();
		int cuantas = mazoU.repartir_en_n(mazo, 4);
		mazoU.vaciar();

		mostrar(mazo, 4, cuantas);

		//Juntamos los mazos
		for (int i = 0; i<4; i++)
			mazoU.unir(mazo[i]);

		//Cortamos el mazo
		cout << "Por que numero de carta quieres cortar?";
		cin  >> corte;
		mazoU.cortar(corte);

		cout << "Sin embargo, a la maniana siguiente..." << endl;

		pausa();
		mazoU.repartir_en_n(mazo, 4);

		mostrar(mazo, 4, cuantas);

		cout << "Los cuatro reyes amanecieron en la misma habitacion, "
			 << "y lo mismo sucedio con los caballeros, las damas y los peones" << endl;
	}
	else
	{
		cout << "Archivo " << nomb << " no encontrado" << endl
			 << "Sal del programa, ve al codigo, modifica el nombre "
			 << "del archivo y vuelve a ejecutar el programa y el truco"
			 << endl;
	}
}

//Truco obligatorio de la parte opcional
void truco_del_jugador_desconfiado()
{
	tMazo mazoD, mazo[4], mazoNegro, mazoRojo, mazoBajas, mazoAltas;
	tMazo mazoPar, mazoImpar, mazoFiguras, mazoNumeros;
	string nomb = "desconfiado.txt";

	if (mazoD.mazoValido(20, nomb))
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

		int cuantas = mazoD.repartir_en_n(mazo, 4);
		mostrar(mazo, 4, cuantas);
		pausa();

		cout << "El jugador dice que no se fia del que ha repartido, asi que propone "
			 << "seguir unos pasos para asegurarse de que el reparto ha sido aleatorio "
			 << "y justo:" << endl;
		pausa();

		for (int i = 0; i<2; i++)
		{
			if (i == 0)
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
			mazo[0].repartirNegroRojo(mazoNegro, mazoRojo);
			mazo[1].repartirBajaAlta(mazoBajas, mazoAltas);
			mazo[2].repartirParImpar(mazoPar, mazoImpar);
			mazo[3].repartirFigurasNumeros(mazoFiguras, mazoNumeros);

			mazoNumeros.unir(mazoBajas);
			mazoRojo.unir(mazoPar);
			mazoAltas.unir(mazoFiguras);
			mazoImpar.unir(mazoNegro);

			mazo[0] = mazoNumeros;
			mazo[1] = mazoRojo;
			mazo[2] = mazoAltas;
			mazo[3] = mazoImpar;


			mostrar(mazo, 4, cuantas);
			pausa();
		}

		cout << "Y otra mas, con la excepcion de que ahora cada jugador se quedara con su mazo "
			 << "derecho, y pasan su izquierdo al jugador de su izquierda, despues los vuelven "
			 << "a juntar." << endl;
		pausa();

		mazo[0].repartirNegroRojo(mazoNegro, mazoRojo);
		mazo[1].repartirBajaAlta(mazoBajas, mazoAltas);
		mazo[2].repartirParImpar(mazoPar, mazoImpar);
		mazo[3].repartirFigurasNumeros(mazoFiguras, mazoNumeros);

		mazoRojo.unir(mazoBajas);
		mazoAltas.unir(mazoPar);
		mazoImpar.unir(mazoFiguras);
		mazoNumeros.unir(mazoNegro);

		mazo[0] = mazoRojo;
		mazo[1] = mazoAltas;
		mazo[2] = mazoImpar;
		mazo[3] = mazoNumeros;

		cout << "Entonces los jugadores miran sus mazos, y descubren que..." << endl;
		pausa();
		mostrar(mazo, 4, cuantas);

		cout << "El jugador desconfiado tiene escalera de color. El de su izquierda full. El siguiente, "
			 << "poker. Y el ultimo, color" << endl;
	}
	else
	{
		cout << "Archivo " << nomb << " no encontrado" << endl
			 << "Sal del programa, ve al codigo, modifica el nombre "
			 << "del archivo y vuelve a ejecutar el programa y el truco"
			 << endl;
	}
}

//Truco addicional de parte de la casa
void truco_de_cabo_caniaberal()
{
	tMazo mazoI, mazo[4];
	int valorMazo1, valorMazo2, valorMazo3, valorMazo4, valorTotal = 0;

	cout << "El truco consiste en la adivinacion por parte de la consola "
		 << "de la carta que saldra tras tras repartir un mazo en cuatro "
		 << "de una determinada manera." << endl << endl;

	mazoI.cargar_mazo_completo();

	mazoI.barajar();

	pausa();

	cout << "Mazo completo barajado: " << endl;
	mostrar(mazoI);

	cout << endl;

	prediccion(mazoI);

	pausa();

	cout << endl
	     << "Una vez que la consola ha hecho la prediccion, nos disponemos "
	     << "nos disponemos a repartir 10 cartas del mazo barajado a otro mazo, "
	     << "haciendo una cuenta atras desde 10. si el numero de la carta que salga "
	     << "coincide con el numero por el que vayamos en la cuenta atras, se dejara "
	     << "esa carta boca arriba en el primer mazo y se pasara a repartir a otro; "
	     << "sin embargo, si la cuenta llega hasta 0 si que cioncida ningun numero de "
		 << "carta con el de la cuenta, la ultima carta se dejara boca abajo en el mazo "
		 << "al que estemos repartiendo, y se procedera a repartir a otro mazo." << endl
		 << "Este proceso se realizara un total de 4 veces, o sea, se repartiran cartas "
		 << "a 4 mazos desde el mazo principal." << endl;

	pausa();

	cout << "Primer mazo: " << endl;
	valorMazo1 = mazoI.repartir_con_cuenta_atras(mazo[0], 10);
	cout << endl;
	pausa();
	cout << "Segundo mazo: " << endl;
	valorMazo2 = mazoI.repartir_con_cuenta_atras(mazo[1], 10);
	cout << endl;
	pausa();
	cout << "Tercer mazo: " << endl;
	valorMazo3 = mazoI.repartir_con_cuenta_atras(mazo[2], 10);
	cout << endl;
	pausa();
	cout << "Cuarto mazo: " << endl;
	valorMazo4 = mazoI.repartir_con_cuenta_atras(mazo[3], 10);

	pausa();

	cout << "A continuacion se suman los numeros de las cartas que se "
		<< "que se quedaran boca arriba (las que esten boca abajo suman 0), "
		<< "y del primer mazo se sacan tantas cartas como indique la suma "
		<< "obtenida anteriormente." << endl << endl;

	valorTotal = valorMazo1 + valorMazo2 + valorMazo3 + valorMazo4;

	revelar_carta(valorTotal, mazoI);
}

//Menu de opciones del juego de blackjack
int Blackjack::menu_opciones()
{
	linea();

	cout << "Menu de Blackjack:" << endl
		<< "1 - Jugar" << endl
		<< "2 - Reglas" << endl
		<< "3 - Estadisticas" << endl
		<< "4 - Cambiar usuario" << endl
		<< "5 - Resetear estadisticas" << endl
		<< "0 - Salir" << endl;

	return digitoEntre(0, 5);
}

//Opciones que tienes durante tu turno en el juego de blackjack
int Blackjack::opciones_de_blackjack()
{
	cout << "Que decides hacer?:" << endl
		<< "1 - Pedir" << endl
		<< "2 - Plantarse" << endl
		<< "3 - Doblar apuesta" << endl
		<< "0 - Abandonar" << endl;

	return digitoEntre(0, 3);
}

//Te pregunta cuanto quieres apostar en una partida de blackjack
int Blackjack::apuesta()
{
	int pastaJugada;
	cout << "Cuanto quieres apostar?" << endl;

	pastaJugada = digitoEntre(APU_MIN, APU_MAX);

	if (pastaJugada == dinero)
	{
		cout << "Con que apuestas todo el dinero que te queda, eh?." << endl
			<< "Buena suerte... " << endl;

		pausa();

		cout << "Buena suerte... Te hara falta" << endl;
	}
	else
	{
		while (pastaJugada > dinero)
		{
			cout << "Error, no puedes apostar mas dinero del que tienes" << endl;

			pastaJugada = digitoEntre(APU_MIN, APU_MAX);
		}
	}
	return pastaJugada;
}

//Funcion que controla si puedes o no dolar la apuesta 
//mediante recursividad
void Blackjack::doblarApuesta(char decision, int cuantasVeces, int apu, bool &dudaApuesta)
{
	while ((decision != 's') && (decision != 'n') && (cuantasVeces < 3))
	{
		if (cuantasVeces == 0)
		{
			cout << "Eso no es ni si, ni no, se ve que te lo estas pensando, "
				<< "haces bien, es una decision muy importante, pero tranquilo, "
				<< "tu sobre todo no te pongas nervioso..." << endl;

			pausa();

			cout << "Que haces entonces, doblas la apuesta o no? (s(si)/n(no))";
			cin.clear();
			cin >> decision;

			cuantasVeces += 1;
		}
		else if (cuantasVeces == 1)
		{
			cout << "Parece que te lo estas pensando mucho. Te estas poniendo "
				<< "nervioso? Relmente la decision no es tan importante" << endl;

			pausa();

			cout << "Que haces entonces, doblas la apuesta o no? (s(si)/n(no))";
			cin.clear();
			cin >> decision;

			cuantasVeces += 1;
		}
		else if (cuantasVeces == 2)
		{
			cout << "Lo siento, pero si dudas tanto debe ser que en ralidad no ves "
				<< "clara esa decision, continua la partida sin doblar la apuesta"
				<< endl;

			cuantasVeces += 1;

			dudaApuesta = false;
		}
	}

	if (decision == 'n')
	{
		cout << "Cobarde... Bueno, ahora si ganas tus ganancias seran "
			<< "menores, pero tu lo has querido..." << endl;

		dudaApuesta = false;
	}
	else if (decision == 's')
	{
		cout << "Has tomado tu decision, ya no hay vuelta atras..."
			<< endl;

		dinero -= apu;
		apu *= 2;

		cout << "Ahora juegas la partida por " << apu << " dolares" << endl;

		dudaApuesta = false;
	}
}

//Define y proporciona la recompensa tras una partida de blackjack
//basandose en los posibles finales de esta
void Blackjack::recompensa(int apu, int queHacer, string usuario)
{
	int manoCrup = valor(mazoBot);
	int manoJug = valor(mazoJugador);
	tJugador ganador;

	cout << "Mazo actual: " << endl;
	mostrar(mazoJugador);
	cout << endl;

	cout << "Mazo del crupier: " << endl;
	mostrar(mazoBot);
	cout << endl;

	if (queHacer == 0)
	{
		cout << "Has abandonado la partida" << endl;

		perder(apu);

		ganador = Automata;
	}
	else if (queHacer == 2)
	{
		if ((manoJug <= 21) && (manoCrup <= 21))
		{

			if (manoJug <= manoCrup)
			{
				if (manoJug == manoCrup)
				{
					cout << "El crupier y tu teneis la misma mano, "
						<< "gana el Crupier" << endl;
				}
				else
				{
					cout << "El crupier tiene una mano mejor que la tuya" << endl;
				}

				perder(apu);

				ganador = Automata;
			}
			else
			{
				apu += apu;

				cout << "Tu mano es mejor que la del crupier" << endl;

				ganar(apu);

				ganador = Jugador;
			}
		}
		else if (manoJug > 21)
		{
			cout << "Tu mano supera el valor de 21" << endl;

			perder(apu);

			ganador = Automata;
		}
		else if ((manoJug <= 21) && (manoCrup > 21))
		{
			apu += apu;

			cout << "La mano del crupier supera el valor de 21" << endl;

			ganar(apu);

			ganador = Jugador;
		}
		else if ((manoJug == 21) && (mazoJugador.cuantas == 2))
		{
			apu += apu / 2;

			cout << "Has conseguido blackjack con tus dos primeras cartas" << endl;

			ganar(apu);

			ganador = Jugador;
		}
	}
	else
	{
		if (manoJug > 21)
		{
			cout << "Tu mano supera el valor de 21" << endl;

			perder(apu);

			ganador = Automata;
		}
		else if (manoCrup == 21)
		{
			cout << "El crupier y tu teneis la misma mano, "
				<< "gana el Crupier" << endl;

			perder(apu);

			ganador = Automata;
		}
		else
		{
			apu += apu;

			cout << "Tu mano es mejor que la del crupier" << endl;

			ganar(apu);

			ganador = Jugador;
		}
	}
	actualizar_stats(ganador, usuario);
}

//Define el valor de una mano de blackjack
int Blackjack::valor(const tMazo &mano)
{
	int total = 0;
	bool hay_un_as = false;
	for (int i = 0; i < mano.cuantas; i++)
	{
		if (mano[i].num == A) hay_un_as = true;
		if ((mano[i].num == K) || (mano[i].num == J) || (mano[i].num == Q))
		{
			total += 10;
		}
		else total += (int)mano[i].num;
	}
	if (hay_un_as && total <= 11) return total + 10; //El as puede valer 1 o 11, según nos convenga.
	else return total;
}

//Controla el menu de blackjack
void Blackjack::run(string usuario)
{

	int opcion;
	string archivo = "reglas_bj.txt";

	cout << "Saldo actual: " << dinero << endl;

	do
	{
		opcion = menu_opciones();
		if (opcion == 1)
		{
			if (dinero == 0)
			{
				cout << "No puedes volver a jugar, te has quedado sin dinero,"
					<< " reinicia el programa para volver a jugar";
			}
			else
			{
				mano(usuario);
			}
		}
		else if (opcion == 2)
		{
			mostrar(archivo);
		}
		else if (opcion == 3)
		{
			stats(usuario);
		}
		else if (opcion == 4)
		{
			cout << "Hasta la proxima, " << usuario << endl;
			usuario = iniciar_sesion();
		}
		else if (opcion == 5)
		{
			usuario = reset(usuario);
		}
	} while (opcion != 0);
}

//Controla una partida de blackjack
void Blackjack::mano(string usuario)
{
	int queHacer, apu;
	bool dudaApuesta = true;

	cout << "Bienvenido al juego de Blackjack" << endl;

	mazo.barajar();

	mazo.repartir_n_cartas(mazoJugador, 2);
	mazo.repartir_n_cartas(mazoBot, 2);

	cout << "Mano actual:" << endl;
	mostrar(mazoJugador);
	cout << endl;

	cout << "Carta del crupier:" << endl;
	mostrar(mazoBot[0]);
	cout << endl;

	apu = apuesta();
	dinero -= apu;

	//Antes de comenzar a jugar hay que comprobar que ni el crupier ni el jugador tengan 21 o más
	do
	{
		//Siempre empieza el jugador

		queHacer = opciones_de_blackjack();

		if (queHacer == 1)
		{
			cout << "Has pedido otra carta" << endl << endl;

			mazo.repartir_n_cartas(mazoJugador, 1);

			cout << "Mano actual:" << endl;
			mostrar(mazoJugador);
			cout << endl;

			cout << "Carta del crupier:" << endl;
			mostrar(mazoBot[0]);
			cout << endl;
		}
		else if (queHacer == 2)
		{
			cout << "Has decidido plantarte" << endl;
		}
		else if (queHacer == 3)
		{
			if (mazoJugador.cuantas > 2)
			{
				cout << "Error, no puedes doblar la apuesta si ya has pedido otra carta" << endl;
			}
			else
			{
				if (dudaApuesta == true)
				{
					if (apu > dinero / 2)
					{
						cout << "Lo siento, pero con tu saldo restante (" << dinero << ") no "
							<< "puedes permitirte doblar la apuesta" << endl;
					}
					else
					{
						int cuantasVeces = 0;

						if (apu == dinero / 2)
						{
							cout << "Doblar la apuesta ahora, supone apostar la totalidad "
								<< "de tu saldo restante, estas seguro de que quieres "
								<< "hacerlo? (s(si)/n(no))";
						}
						else if (apu < dinero / 2)
						{
							cout << "Estas seguro de que quieres doblar la apuesta? (s(si)/n(no))";
						}

						char decision;

						cin.clear();
						cin >> decision;

						doblarApuesta(decision, cuantasVeces, apu, dudaApuesta);
					}
				}
				else if (dudaApuesta == false)
				{
					cout << "Lo siento, pero no puedes doblar la apuesta si ya "
						<< "antes has decidido hacerlo o no hacerlo" << endl;
				}
			}
		}
	} while ((valor(mazoJugador) < 21) && (queHacer != 2) && (queHacer != 0));

	turno_crupier();

	recompensa(apu, queHacer, usuario);

	mazoBot.vaciar();
	mazoJugador.vaciar();
}


bool Blackjack::turno_crupier()
{
	bool pasa_crup = true;
	while (valor(mazoJugador) <= 21 && valor(mazoBot) < valor(mazoJugador))
	{
		cout << "El crupier ha pedido una carta" << endl;
		mazo.repartir_n_cartas(mazoBot, 1);
		pasa_crup = false;
	}

	cout << "El crupier ahora tiene " << mazoBot.cuantas << " cartas." << endl
		<< "Su carta visible es: "; mostrar(mazoBot[0]); cout << endl;

	return pasa_crup;
}

//Muestra por consola que el usuario ha ganado, añade lo que
//ganara de la apuesta a su dinero actual, y se lo muestra
inline void Blackjack::ganar(int apu)
{
	dinero += apu;

	cout << "Enhorabuena, has ganado " << apu << " dolares" << endl
		<< "Saldo actual: " << dinero << " dolares" << endl;
}

//Determina que el jugador ha perdido y le muestra el saldo actual
inline void Blackjack::perder(int apu)
{
	cout << "Lo siento, has perdido los " << apu << " dolares que apostabas" << endl
		<< "Saldo actual: " << dinero << " dolares" << endl;
}

//Pausa el programa, para continuar pulsa cualquier boton
inline void pausa()
{
	cin.sync(); //Para eliminar los datos basura del buffer
	cin.get();
}
