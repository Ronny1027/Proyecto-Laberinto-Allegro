// celda.h
#pragma once

//Representa una celda del laberinto
//Cada celda puede tener muros en sus cuatro lados y un estado de visita.
// Esta estructura es utilizada por el generador de laberintos (Persona 2/Ronny) y por el visualizador/movimiento del jugador (Persona 3/Cristhofer).
struct Celda {
    bool muroNorte = true;   // ¿Tiene muro arriba?
    bool muroSur = true;     // ¿Tiene muro abajo?
    bool muroEste = true;    // ¿Tiene muro a la derecha?
    bool muroOeste = true;   // ¿Tiene muro a la izquierda?
    bool visitada = false;   // ¿Ya fue visitada por el algoritmo?
};
