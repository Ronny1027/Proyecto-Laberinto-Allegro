// estadisticas.h
#pragma once
#include <string>
#include <allegro5/allegro_font.h>  

//Guarda una partida en el archivo de estad�sticas
//Se debe llamar al finalizar una partida
void guardarEstadistica(int ancho, int alto, int movimientos, double tiempoSegundos);

//Muestra las estad�sticas en consola
void mostrarEstadisticasGlobales();

//Muestra las estad�sticas en pantalla usando Allegro
void mostrarEstadisticasEnPantalla(ALLEGRO_FONT* fuente);