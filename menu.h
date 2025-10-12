// menu.h
#pragma once
#include <allegro5/allegro_font.h>

//Enumeraci�n: Estados posibles del programa
//Se utiliza para controlar el flujo principal desde main.cpp.
enum EstadoPrograma {
    MENU_PRINCIPAL, //Pantalla de inicio con opciones
    CONFIGURACION_LABERINTO, //Pantalla para elegir ancho y alto del laberinto
    JUEGO, //Estado donde se ejecuta el juego visual
    ESTADISTICAS, //Pantalla que muestra estad�sticas guardadas
    SALIR // Finaliza el programa
};

//Muestra el men� principal en pantalla.
//Recibe la fuente para dibujar el texto.
//La opci�n seleccionada se gestiona internamente en menu.cpp.
void mostrarMenu(ALLEGRO_FONT* fuente);


//Maneja los eventos de teclado para navegar por el men�.
//Devuelve el nuevo estado del programa seg�n la opci�n seleccionada.
//Se llama desde el bucle principal en main.cpp.
EstadoPrograma manejarMenu(ALLEGRO_EVENT& evento);