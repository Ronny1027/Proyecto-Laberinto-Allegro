// juego.cpp
#include "juego.h"
#include "laberinto.h"
#include "estadisticas.h"
#include <iostream>
#include "generador.h"
#include <allegro5/allegro_image.h>  // Para imágenes
#include <allegro5/allegro_primitives.h>  
//Esta función será reemplazada por (Persona 3/Cristhofer)-Apunte de Daniel
//Se deben agregar las partes del juego: mover jugador, detectar meta y un par de cosas más.
/* El renderizado es solo modificar un poco lo que ya se tiene en la función ejecutarJuego.
Y agregar aspectos simples de formato.*/
//En este momento, puse temporalmente que simule una partida para probar el sistema de estadísticas
void ejecutarJuego(ALLEGRO_FONT* fuente) {
    std::cout << "Juego iniciado con laberinto de " << anchoLaberinto << "x" << altoLaberinto << "\n";

	//Se guarda el laberinto en una matriz de celdas.
    std::vector<std::vector<Celda>> laberinto(altoLaberinto, std::vector<Celda>(anchoLaberinto));
	generarLaberinto(laberinto);//Se llama al generador para crear el laberinto.

    //Desde este punto.
    ALLEGRO_BITMAP* pared = al_create_bitmap(32, 32);
    ALLEGRO_BITMAP* camino = al_create_bitmap(32, 32);

    // Llenar pared (rojo)
    al_set_target_bitmap(pared);
    al_clear_to_color(al_map_rgb(255, 0, 0));

    // Llenar camino (verde)
    al_set_target_bitmap(camino);
    al_clear_to_color(al_map_rgb(0, 255, 0));

    // Volver al backbuffer
    al_set_target_backbuffer(al_get_current_display());
	//Hasta aqui, se debe cambiar por las imagenes, el ejemplo usado fue para probar el dibujo, el como se estaba generando.
    
    //Se configura las celdas
	int tamCelda = 32; // Se define un tamaño fijo para cada celda de 32x32 píxeles.
	int ventanaAncho = anchoLaberinto * tamCelda;// Ancho total de la ventana según el tamaño del laberinto
	int ventanaAlto = altoLaberinto * tamCelda;// Alto total de la ventana según el tamaño del laberinto

	
    ALLEGRO_DISPLAY* display = al_get_current_display();

	//Cola de eventos y bucle principal
   
	// Bucle principal del juego
    bool redibujar = true;
    ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
    al_register_event_source(colaEventos, al_get_display_event_source(display));
    al_register_event_source(colaEventos, al_get_keyboard_event_source()); // ← AGREGAR ESTA

    while (redibujar) {//Ciclo para generar.
        ALLEGRO_EVENT evento;
        al_wait_for_event(colaEventos, &evento);//

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            redibujar = false;
        }

        // Dibujar el laberinto CON MARGEN
        al_clear_to_color(al_map_rgb(0, 0, 0));

        int margenX = 100;
        int margenY = 50;

        al_clear_to_color(al_map_rgb(40, 40, 40)); // Fondo gris oscuro

        //Se recorre primero el alto
        for (int y = 0; y < altoLaberinto; y++) {
            //Se recorre ahora el ancho
            for (int x = 0; x < anchoLaberinto; x++) {
                int margenX = 100;
                int margenY = 50;
                int posX = x * tamCelda + margenX;
                int posY = y * tamCelda + margenY;

                const Celda& celda = laberinto[y][x];

                //Fondo de la celda
                al_draw_filled_rectangle(posX, posY, posX + tamCelda, posY + tamCelda, al_map_rgb(210, 180, 140));

                //Se verifica si hay muros
                if (celda.muroNorte)
                    al_draw_filled_rectangle(posX, posY, posX + tamCelda, posY + 4, al_map_rgb(139, 69, 19));

                if (celda.muroSur)
                    al_draw_filled_rectangle(posX, posY + tamCelda - 4, posX + tamCelda, posY + tamCelda, al_map_rgb(139, 69, 19));

                if (celda.muroEste)
                    al_draw_filled_rectangle(posX + tamCelda - 4, posY, posX + tamCelda, posY + tamCelda, al_map_rgb(139, 69, 19));

                if (celda.muroOeste)
                    al_draw_filled_rectangle(posX, posY, posX + 4, posY + tamCelda, al_map_rgb(139, 69, 19));
            }
        }

        al_draw_text(fuente, al_map_rgb(255, 255, 255), 10, 10, 0,
            "Laberinto Generado - Presiona ESC para salir");//Texto de guia
        al_flip_display();

        //Evento del ESC para salir de la ventana
        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                redibujar = false;
            }
        }
    }

	//Se destruyen los bitmaps y la cola de eventos.
    al_destroy_bitmap(pared);
    al_destroy_bitmap(camino);
    al_destroy_event_queue(colaEventos);

	//Estadísticas de ejemplo
    int movimientos = 50;
    double tiempoSegundos = 20.5;
    guardarEstadistica(anchoLaberinto, altoLaberinto, movimientos, tiempoSegundos);
}
