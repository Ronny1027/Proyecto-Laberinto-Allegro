// estadisticas.h
#pragma once
#include <string>
#include <allegro5/allegro_font.h>  

//Guarda una partida en el archivo de estadísticas
//Se debe llamar al finalizar una partida
void guardarEstadistica(int ancho, int alto, int movimientos, double tiempoSegundos);

//Muestra las estadísticas en consola
void mostrarEstadisticasGlobales();

//Muestra las estadísticas en pantalla usando Allegro
void mostrarEstadisticasEnPantalla(ALLEGRO_FONT* fuente);