// laberinto.h
#pragma once
#include <vector>
#include <utility>
#include "celda.h"

// Este m�dulo gestiona la estructura general del laberinto, incluyendo su matriz de celdas, dimensiones y posiciones clave.

// Matriz 2D del laberinto
extern std::vector<std::vector<Celda>> laberinto;

//Dimensiones del laberinto, son definidas por el usuario en la configuraci�n
extern int anchoLaberinto;
extern int altoLaberinto;

// Posiciones clave
//Posici�n de inicio del jugador (se puede usar para dibujarlo)
extern std::pair<int, int> inicio;
//Posici�n de la meta (donde debe llegar el jugador)
extern std::pair<int, int> fin;
//Posici�n actual del jugador (se actualiza durante el juego)
extern std::pair<int, int> posicionJugador;

//Inicializa la matriz con las dimensiones dadas, todas las celdas comienzan con muros en todas las direcciones.
void inicializarLaberinto(int ancho, int alto);
