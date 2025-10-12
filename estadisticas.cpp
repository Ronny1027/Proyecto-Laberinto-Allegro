// estadisticas.cpp
#include "estadisticas.h"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>


//Guarda los datos de una partida en un archivo de texto
void guardarEstadistica(int ancho, int alto, int movimientos, double tiempoSegundos) {
    std::ofstream archivo("maze_solver_log.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << "Size: " << ancho << "x" << alto //Puse "size" ya que no me deja poner la "ñ" de tamaño por la fuente
            << ", Movimientos: " << movimientos
            << ", Tiempo: " << std::fixed << std::setprecision(2) << tiempoSegundos << "s\n";
        archivo.close();
    }
}

//Muestra las estadísticas guardadas en consola
void mostrarEstadisticasGlobales() {
    std::ifstream archivo("maze_solver_log.txt");
    if (archivo.is_open()) {
        std::string linea;
        std::cout << "\n=== Estadísticas de partidas anteriores ===\n";
        while (std::getline(archivo, linea)) {
            std::cout << linea << "\n";
        }
        std::cout << "===========================================\n\n";
        archivo.close();
    }
    else {
        std::cout << "No se encontraron estadísticas.\n";
    }
}

//Muestra las estadísticas en pantalla
void mostrarEstadisticasEnPantalla(ALLEGRO_FONT* fuente) {
    std::ifstream archivo("maze_solver_log.txt");
    std::vector<std::string> lineas;

    if (archivo.is_open()) {
        std::string linea;
        while (std::getline(archivo, linea)) {
            lineas.push_back(linea);
        }
        archivo.close();
    }
    else {
        lineas.push_back("No se encontraron estadísticas.");
    }

    //Dibuja fondo negro:
    al_clear_to_color(al_map_rgb(0, 0, 0));

    //Título:
    al_draw_text(fuente, al_map_rgb(0, 255, 0), 50, 30, 0, "Estadisticas de partidas anteriores:"); //Igualmente sin tilde por la fuente

    //Dibuja cada línea:
    for (size_t i = 0; i < lineas.size(); ++i) {
        al_draw_text(fuente, al_map_rgb(255, 255, 255), 50, 80 + i * 30, 0, lineas[i].c_str());
    }

    al_flip_display();

    //Espera que el usuario presione una tecla para volver
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_EVENT evento;
    al_register_event_source(queue, al_get_keyboard_event_source());

    bool esperando = true;
    while (esperando) {
        al_wait_for_event(queue, &evento);
        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            esperando = false;
        }
    }

    al_destroy_event_queue(queue);
}
