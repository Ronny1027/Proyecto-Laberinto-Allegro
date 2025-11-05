// menu.cpp
#include "menu.h"
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>

//Variable global para saber qué opción está seleccionada
//Se actualiza con las flechas arriba/abajo.
int opcionSeleccionada = 0;

//Dibuja el menú principal en pantalla.
//Recibe la fuente para mostrar el texto.
//Resalta la opción seleccionada en amarillo.
void mostrarMenu(ALLEGRO_FONT* fuente) {
    //Limpia la pantalla y la pinta de negro (Por el momento es una interfaz muy sencilla)
    al_clear_to_color(al_map_rgb(0, 0, 0));

    // Lista de opciones del menú
    const char* opciones[] = {
        "1. Generar laberinto y jugar",
        "2. Estadisticas globales", //Lo escribí sin tilde, ya que la fuente actual no la soporta
        "3. Ver resumen global",
        "4. Salir"
    };

    //Dibuja el título del menú en verde
    al_draw_text(fuente, al_map_rgb(0, 255, 0), 100, 40, 0, "Menu Principal");

    //Recorre las opciones y las dibuja en pantalla
    for (int i = 0; i < 4; i++) {
        //Si la opción está seleccionada, se dibuja en amarillo. Si no, la dibuja en blanco
        ALLEGRO_COLOR color = (i == opcionSeleccionada) ? al_map_rgb(255, 255, 0) : al_map_rgb(255, 255, 255);
        //Dibuja la opción en la posición correspondiente
        al_draw_text(fuente, color, 100, 100 + i * 40, 0, opciones[i]);
    }
    //Actualiza la pantalla para mostrar los cambios
    al_flip_display();
}

//Maneja los eventos de teclado para navegar por el menú.
//Flechas arriba/abajo cambian la opción seleccionada.
//ENTER confirma la selección y devuelve el estado correspondiente.
//Si no se presiona ENTER, se mantiene en MENU_PRINCIPAL.
EstadoPrograma manejarMenu(ALLEGRO_EVENT& evento) {
    if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (evento.keyboard.keycode) {
        case ALLEGRO_KEY_UP:
            opcionSeleccionada = (opcionSeleccionada - 1 + 4) % 4; // Subir opción correctamente
            break;
        case ALLEGRO_KEY_DOWN:
            opcionSeleccionada = (opcionSeleccionada + 1) % 4; // Bajar opción
            break;
        case ALLEGRO_KEY_ENTER:
            switch (opcionSeleccionada) {
            case 0: return CONFIGURACION_LABERINTO;
            case 1: return ESTADISTICAS;
            case 2: return RESUMEN_GLOBAL;
            case 3: return SALIR;
            }
        }
    }
    return MENU_PRINCIPAL; //Si no se presiona ENTER, se mantiene en el menú principal
}