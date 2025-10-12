// configuracion.h
#pragma once
#include <allegro5/allegro_font.h>
#include "laberinto.h"

//Muestra la pantalla de configuración del laberinto
//Permite al usuario ver el ancho y alto actuales
void mostrarConfiguracion(ALLEGRO_FONT* fuente, int ancho, int alto);

//Maneja los eventos de teclado para modificar ancho y alto.
//Flechas izquierda/derecha modifican ancho, arriba/abajo modifican alto.
//ENTER confirma la configuración y devuelve true.
bool manejarConfiguracion(ALLEGRO_EVENT& evento, int& ancho, int& alto); 
