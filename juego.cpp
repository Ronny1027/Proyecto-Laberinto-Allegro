// juego.cpp
#include "juego.h"
#include "laberinto.h"
#include "estadisticas.h"
#include <iostream>


//Esta funci�n ser� reemplazada por (Persona 3/Cristhofer)
//En este momento, puse temporalmente que simule una partida para probar el sistema de estad�sticas
void ejecutarJuego(ALLEGRO_FONT* fuente) {
    std::cout << "Juego iniciado con laberinto de " << anchoLaberinto << "x" << altoLaberinto << "\n";

    // Simulaci�n de partida terminada
    int movimientos = 50;
    double tiempoSegundos = 20.5;

    guardarEstadistica(anchoLaberinto, altoLaberinto, movimientos, tiempoSegundos);
}