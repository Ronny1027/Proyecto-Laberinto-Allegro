//Victoria.h
#ifndef VICTORIA_H
#define VICTORIA_H

#include <allegro5/allegro_font.h>

//Nuevo tipo de dato tipo DatosPartida
struct DatosPartida {
    int movimientos;
    double tiempo;
    int anchoLaberinto;
    int altoLaberinto;
};


void mostrarPantallaVictoria(ALLEGRO_FONT* fuente, DatosPartida datos);

//Variable entera manejarVictoria
int manejarVictoria(ALLEGRO_EVENT evento);

#endif