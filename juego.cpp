// juego.cpp
#include "juego.h"
#include "laberinto.h"
#include "estadisticas.h"
#include <iostream>
#include "generador.h"
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
//Esta funcion será reemplazada por (Persona 3/Cristhofer)-Apunte de Daniel
//Se deben agregar las partes del juego: mover jugador, detectar meta y un par de cosas más.
/* El renderizado es solo modificar un poco lo que ya se tiene en la funcion ejecutarJuego.
Y agregar aspectos simples de formato.*/
//En este momento, puse temporalmente que simule una partida para probar el sistema de estadisticas
DatosPartida ejecutarJuego(ALLEGRO_FONT* fuente, ALLEGRO_DISPLAY* displayPrincipal) {
    std::cout << "Juego iniciado con laberinto de " << anchoLaberinto << "x" << altoLaberinto << "\n";

    std::vector<std::vector<Celda>> laberinto(altoLaberinto, std::vector<Celda>(anchoLaberinto));
    generarLaberinto(laberinto);
    
    //Se configura las celdas
	int tamCelda = 32; // Se define un tamaño fijo para cada celda de 32x32 pixeles.
	int ventanaAncho = anchoLaberinto * tamCelda;// Ancho total de la ventana segun el tamaño del laberinto
	int ventanaAlto = altoLaberinto * tamCelda;// Alto total de la ventana segun el tamaño del laberinto

    // Margenes
    int margenX = 100;
    int margenY = 50;

    //Se representa el jugador como un punto y la posicion inicial en el centro de la primera celda
    float jugadorX = 100 + tamCelda / 2.0f;  // centro de la primera celda + margen
    float jugadorY = 50 + tamCelda / 2.0f;
    float radioJugador = 5.0f;
    float velocidad = 6.0f;

    //Se define la posicion de la meta en la ultima celda
    int metaX = anchoLaberinto - 1;
    int metaY = altoLaberinto - 1;
    float metaPosX = margenX + metaX * tamCelda + tamCelda / 2.0f;
    float metaPosY = margenY + metaY * tamCelda + tamCelda / 2.0f;
    float tamMeta = tamCelda / 2.0f;  // Tamaño del cuadrado de meta

    bool juegoGanado = false;
    bool teclas[ALLEGRO_KEY_MAX] = { false };
    ALLEGRO_DISPLAY* display = al_get_current_display();
    ALLEGRO_DISPLAY* displayJuego = displayPrincipal;

    //Contadores para obtener estadisticas
    int movimientos = 0;
    double tiempoInicio = al_get_time();
    double tiempoSegundos = 0.0;

    // Sonido de victoria
     ALLEGRO_SAMPLE* sonidoVictoria = NULL;
     bool sonidoReproducido = false;

     // Inicializar audio (agregar esto antes de cargar sonidos)
     if (!al_install_audio()) {
         std::cout << "Error inicializando audio\n";
     }
     if (!al_init_acodec_addon()) {
         std::cout << "Error inicializando codecs de audio\n";
     }
     if (!al_reserve_samples(1)) {
         std::cout << "Error reservando samples de audio\n";
     }

     // Cargar sonido de victoria
     sonidoVictoria = al_load_sample("sonidos/victoria.wav");
     if (!sonidoVictoria) {
         std::cout << "No se pudo cargar el sonido de victoria\n";
     }

	//Cola de eventos y bucle principal
   
	// Bucle principal del juego
    bool redibujar = true;
    bool salirPorVictoria = false;

    ALLEGRO_EVENT_QUEUE* colaEventos = al_create_event_queue();
    al_register_event_source(colaEventos, al_get_display_event_source(display));
    al_register_event_source(colaEventos, al_get_keyboard_event_source()); // ← AGREGAR ESTA

    while (redibujar) {//Ciclo para generar.
        ALLEGRO_EVENT evento;
        al_wait_for_event(colaEventos, &evento);//

        if (!juegoGanado) {
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
                teclas[evento.keyboard.keycode] = true;
            else if (evento.type == ALLEGRO_EVENT_KEY_UP)
                teclas[evento.keyboard.keycode] = false;
        }

        if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
            redibujar = false;
        }

        if (!juegoGanado) {
            // Calcular posición futura del jugador
            float nuevaX = jugadorX;
            float nuevaY = jugadorY;

            bool seMovio = false;

            if (teclas[ALLEGRO_KEY_UP]) {
                nuevaY -= velocidad;
                seMovio = true;
            }
            if (teclas[ALLEGRO_KEY_DOWN]) {
                nuevaY += velocidad;
                seMovio = true;
            }
            if (teclas[ALLEGRO_KEY_LEFT]) {
                nuevaX -= velocidad;
                seMovio = true;
            }
            if (teclas[ALLEGRO_KEY_RIGHT]) {
                nuevaX += velocidad;
                seMovio = true;
            }

            // Contar movimientos solo si realmente se movió
            if (seMovio) {
                movimientos++;
            }

            // Detección de colisiones más precisa
            bool colision = false;

            // Convertir coordenadas a celdas
            int celdaCentroX = (nuevaX - margenX) / tamCelda;
            int celdaCentroY = (nuevaY - margenY) / tamCelda;

            // Verificar que las celdas estén dentro del laberinto
            if (celdaCentroX >= 0 && celdaCentroX < anchoLaberinto &&
                celdaCentroY >= 0 && celdaCentroY < altoLaberinto) {

                Celda& celdaActual = laberinto[celdaCentroY][celdaCentroX];

                // Verificar colisiones con los muros considerando el radio del jugador
                float offset = radioJugador + 2.0f;

                // Norte
                if (nuevaY - radioJugador < margenY + celdaCentroY * tamCelda + 4 && celdaActual.muroNorte) {
                    if (teclas[ALLEGRO_KEY_UP]) colision = true;
                }

                // Sur
                if (nuevaY + radioJugador > margenY + (celdaCentroY + 1) * tamCelda - 4 && celdaActual.muroSur) {
                    if (teclas[ALLEGRO_KEY_DOWN]) colision = true;
                }

                // Oeste
                if (nuevaX - radioJugador < margenX + celdaCentroX * tamCelda + 4 && celdaActual.muroOeste) {
                    if (teclas[ALLEGRO_KEY_LEFT]) colision = true;
                }

                // Este
                if (nuevaX + radioJugador > margenX + (celdaCentroX + 1) * tamCelda - 4 && celdaActual.muroEste) {
                    if (teclas[ALLEGRO_KEY_RIGHT]) colision = true;
                }

                // Verificar celdas adyacentes para casos en el borde entre celdas
                if (nuevaX - radioJugador < margenX + celdaCentroX * tamCelda && celdaCentroX > 0) {
                    Celda& celdaOeste = laberinto[celdaCentroY][celdaCentroX - 1];
                    if (celdaOeste.muroEste && teclas[ALLEGRO_KEY_LEFT]) colision = true;
                }

                if (nuevaX + radioJugador > margenX + (celdaCentroX + 1) * tamCelda && celdaCentroX < anchoLaberinto - 1) {
                    Celda& celdaEste = laberinto[celdaCentroY][celdaCentroX + 1];
                    if (celdaEste.muroOeste && teclas[ALLEGRO_KEY_RIGHT]) colision = true;
                }

                if (nuevaY - radioJugador < margenY + celdaCentroY * tamCelda && celdaCentroY > 0) {
                    Celda& celdaNorte = laberinto[celdaCentroY - 1][celdaCentroX];
                    if (celdaNorte.muroSur && teclas[ALLEGRO_KEY_UP]) colision = true;
                }

                if (nuevaY + radioJugador > margenY + (celdaCentroY + 1) * tamCelda && celdaCentroY < altoLaberinto - 1) {
                    Celda& celdaSur = laberinto[celdaCentroY + 1][celdaCentroX];
                    if (celdaSur.muroNorte && teclas[ALLEGRO_KEY_DOWN]) colision = true;
                }
            }

            // Actualizar posición solo si no hay colisión
            if (!colision) {
                jugadorX = nuevaX;
                jugadorY = nuevaY;
            }

            // Mantener al jugador dentro de los límites del laberinto
            if (jugadorX - radioJugador < margenX) jugadorX = margenX + radioJugador;
            if (jugadorX + radioJugador > margenX + anchoLaberinto * tamCelda) jugadorX = margenX + anchoLaberinto * tamCelda - radioJugador;
            if (jugadorY - radioJugador < margenY) jugadorY = margenY + radioJugador;
            if (jugadorY + radioJugador > margenY + altoLaberinto * tamCelda) jugadorY = margenY + altoLaberinto * tamCelda - radioJugador;

            // Verificar si llegó a la meta (centro del cuadrado rojo)
            bool enMetaX = (jugadorX >= metaPosX - tamMeta / 2 && jugadorX <= metaPosX + tamMeta / 2);
            bool enMetaY = (jugadorY >= metaPosY - tamMeta / 2 && jugadorY <= metaPosY + tamMeta / 2);
            if (enMetaX && enMetaY) {
                juegoGanado = true;
                tiempoSegundos = al_get_time() - tiempoInicio;
                salirPorVictoria = true; // Cambia la variable a verdadero

                // Reproducir sonido de victoria
                if (sonidoVictoria && !sonidoReproducido) {
                    al_play_sample(sonidoVictoria, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                    sonidoReproducido = true;
                    al_rest(0.3); //Pausa para que el sonido se reproduzca
                }

                //Salir inmediatamente al ganar
                redibujar = false;
                break; // Salir del bucle del juego inmediatamente
            }
        }

        // Dibujar
        al_clear_to_color(al_map_rgb(40, 40, 40));

        // Dibujar laberinto
        for (int y = 0; y < altoLaberinto; y++) {
            for (int x = 0; x < anchoLaberinto; x++) {
                int posX = x * tamCelda + margenX;
                int posY = y * tamCelda + margenY;

                const Celda& celda = laberinto[y][x];

                // Fondo de la celda
                al_draw_filled_rectangle(posX, posY, posX + tamCelda, posY + tamCelda, al_map_rgb(210, 180, 140));

                // Dibujar muros
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

        // Dibujar meta (cuadrado rojo en la celda final)
        al_draw_filled_rectangle(metaPosX - tamMeta / 2, metaPosY - tamMeta / 2,
            metaPosX + tamMeta / 2, metaPosY + tamMeta / 2,
            al_map_rgb(255, 0, 0));
        al_draw_rectangle(metaPosX - tamMeta / 2, metaPosY - tamMeta / 2,
            metaPosX + tamMeta / 2, metaPosY + tamMeta / 2,
            al_map_rgb(200, 0, 0), 2);

        // Dibujar jugador
        al_draw_filled_circle(jugadorX, jugadorY, radioJugador, al_map_rgb(255, 0, 0));

        // Mostrar mensajes
        if (juegoGanado) {
            al_draw_text(fuente, al_map_rgb(0, 255, 0), ventanaAncho / 2, 20, ALLEGRO_ALIGN_CENTER,
                "¡FELICIDADES! ¡GANASTE EL JUEGO!");
            al_draw_textf(fuente, al_map_rgb(255, 255, 255), ventanaAncho / 2, 50, ALLEGRO_ALIGN_CENTER,
                "Movimientos: %d - Tiempo: %.1f segundos", movimientos, tiempoSegundos);
            al_draw_text(fuente, al_map_rgb(255, 255, 255), ventanaAncho / 2, 80, ALLEGRO_ALIGN_CENTER,
                "Presiona ESC para salir");
        }
        else {
            al_draw_text(fuente, al_map_rgb(255, 255, 255), 10, 10, 0,
                "Laberinto Generado - Llega al cuadrado rojo - Presiona ESC para salir");
            al_draw_textf(fuente, al_map_rgb(255, 255, 255), 10, 30, 0,
                "Movimientos: %d", movimientos);
            al_draw_textf(fuente, al_map_rgb(255, 255, 255), 10, 50, 0,
                "Tiempo: %.1f segundos", al_get_time() - tiempoInicio);
        }

        al_flip_display();


        if (evento.type == ALLEGRO_EVENT_KEY_DOWN) {
            if (evento.keyboard.keycode == ALLEGRO_KEY_ESCAPE) {
                redibujar = false;
            }
        }
    }

    al_destroy_event_queue(colaEventos);
    
    //if (sonidoVictoria) al_destroy_sample(sonidoVictoria);
    //al_uninstall_audio();

    // Guardar estadísticas reales
    if (juegoGanado) {
        guardarEstadistica(anchoLaberinto, altoLaberinto, movimientos, tiempoSegundos);
        std::cout << "Juego completado! Movimientos: " << movimientos << ", Tiempo: " << tiempoSegundos << " segundos\n";
    }
    else {
        tiempoSegundos = al_get_time() - tiempoInicio;
        std::cout << "Juego abandonado. Movimientos: " << movimientos << ", Tiempo: " << tiempoSegundos << " segundos\n";
    }

    //Guardar datos de partida
    DatosPartida datos;
    datos.movimientos = movimientos;
    datos.tiempo = tiempoSegundos;
    datos.anchoLaberinto = anchoLaberinto;
    datos.altoLaberinto = altoLaberinto;

    return datos; //Retorno de datos
}