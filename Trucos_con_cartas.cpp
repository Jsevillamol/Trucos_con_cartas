#include <iostream>

using namespace std;

//VARIABLES GLOBALES
const int CARTASxPALO=13,
          MAX_CARTAS=52,
          CENTINELA=52;

//TIPOS PROPIOS
typedef enum tPalo
{
	picas,
	treboles,
	diamantes,
	corazones
};

typedef enum tNumero 
{
	A,2,3,4,5,6,7,8,9,10,J,Q,K
};

typedef int tCarta;
typedef tCarta tMazo[MAX_CARTAS+1];

//FUNCIONES

int main()
{

}