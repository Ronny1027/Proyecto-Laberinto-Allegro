//ProyectoLaberintoAllegro
/*Integrantes:
-Daniel Alejandro Arrieta Víquez
-Ronny Espinoza Cordero
-Cristhofer Herrera
*/


//main.cpp

//1. Bibliotecas de Allegro y encabezados del proyecto
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <cstdio> //Para imprimir errores
#include "menu.h"           //Menú principal
#include "laberinto.h"      //Estructura del laberinto
#include "configuracion.h"  //Pantalla de configuración
#include "estadisticas.h" //Pantalla de estadísticas
#include "generador.h" //Vincular con función que reciba la matriz laberinto (Persona 2/Ronny)
#include "juego.h" //Vincular con juego (Persona 3/Cristopher)


int main() {
    //2. Inicialización de Allegro y sus componentes
    if (!al_init()) {
        fprintf(stderr, "Error al inicializar Allegro.\n"); //En caso de que de error
        return -1;
    }

    al_install_keyboard();       //Para capturar teclas
    al_init_font_addon();        //Para usar fuentes
    al_init_ttf_addon();         //Para fuentes TTF
    al_init_primitives_addon();  //Para dibujar líneas y formas

    //3. Crear ventana, cola de eventos y fuente
    ALLEGRO_DISPLAY* display = al_create_display(800, 600); // Tamaño ventana
    if (!display) {
        fprintf(stderr, "Error al crear la ventana.\n");
        return -1;
    }

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    al_register_event_source(queue, al_get_keyboard_event_source());

    //Fuente integrada (Se usa temporalmente una por dedecto, sin tildes ni caracteres especiales)
    ALLEGRO_FONT* fuente = al_create_builtin_font();

    //4. Estado inicial del programa
    EstadoPrograma estado = MENU_PRINCIPAL;

    //5. Mostrar el menú al iniciar
    mostrarMenu(fuente);

    //6. Bucle principal del programa
    while (estado != SALIR) {
        ALLEGRO_EVENT evento;
        al_wait_for_event(queue, &evento); //Espera una tecla

        switch (estado) {
        case MENU_PRINCIPAL:
            //Muestra el menú principal con las opciones disponibles
            estado = manejarMenu(evento); //Cambia estado según tecla
            if (estado == MENU_PRINCIPAL) {
                mostrarMenu(fuente); //Redibuja si se sigue en el menú
            }
            break;

        case CONFIGURACION_LABERINTO: {
            //Pantalla interactiva para elegir tamaño del laberinto
            int ancho = 10;
            int alto = 10;
            mostrarConfiguracion(fuente, ancho, alto);

            bool confirmado = false;
            while (!confirmado) {
                //Espera eventos de teclado para modificar ancho y alto
                ALLEGRO_EVENT eventoConfig;
                al_wait_for_event(queue, &eventoConfig);

                confirmado = manejarConfiguracion(eventoConfig, ancho, alto);
                mostrarConfiguracion(fuente, ancho, alto);
            }
            
            //Inicializa la matriz del laberinto con celdas vacías
            inicializarLaberinto(ancho, alto);

            generarLaberinto(laberinto); //Llamar al generador de laberintos (Persona 2/Ronny)

            //Cambia al estado de juego, se encarga de la visualización y movimiento (Persona 3/Cristhofer)
            estado = JUEGO;
            break;
        }

        case ESTADISTICAS:
            mostrarEstadisticasEnPantalla(fuente); //Se muestran las estadísticas
            estado = MENU_PRINCIPAL;
            break;

        case JUEGO:
            //Llama al módulo de juego (Persona 3/Cristhofer))
            ejecutarJuego(fuente);

            estado = MENU_PRINCIPAL;
            break;
    

        default:
            break;
        }
    }

    //7. Liberar recursos
    al_destroy_display(display);
    al_destroy_event_queue(queue);
    al_destroy_font(fuente);

    return 0;
}
