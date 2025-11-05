// juego.h
#pragma once
#include <allegro5/allegro_font.h>
#include "victoria.h"

//Función que debe implementar (Persona 3/Cristhofer)
//Se encarga de dibujar el laberinto, mover al jugador y detectar si llega a la meta
DatosPartida ejecutarJuego(ALLEGRO_FONT* fuente, ALLEGRO_DISPLAY* display);