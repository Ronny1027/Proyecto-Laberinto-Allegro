// laberinto.cpp
#include "laberinto.h"

//Variables globales del laberinto

//Matriz 2D que representa el laberinto completo.
//Cada celda contiene informaci�n sobre sus muros y si ha sido visitada
std::vector<std::vector<Celda>> laberinto;


//Dimensiones actuales del laberinto (las que puso el usuario)
int anchoLaberinto = 0;
int altoLaberinto = 0;

//Posici�n de inicio del jugador (por defecto en la esquina superior izquierda)
std::pair<int, int> inicio = { 0, 0 }; 

//Posici�n de la meta (se define como la esquina inferior derecha)
std::pair<int, int> fin;           

//Posici�n actual del jugador (se actualiza durante el juego)
std::pair<int, int> posicionJugador; 

//Crea la matriz del laberinto con las dimensiones dadas
//Cada celda comienza con todos sus muros activos y sin haber sido visitada.
//Tambi�n se definen las posiciones de inicio, fin y jugador.
void inicializarLaberinto(int ancho, int alto) {
    anchoLaberinto = ancho;
    altoLaberinto = alto;

    //Limpia la matriz anterior (si existe) y redimensiona la nueva
    laberinto.clear();
    laberinto.resize(alto, std::vector<Celda>(ancho));

    //Define la posici�n final como la esquina inferior derecha
    fin = { ancho - 1, alto - 1 };

    //Posici�n inicial del jugador (esquina superior izquierda)
    posicionJugador = inicio;
}
