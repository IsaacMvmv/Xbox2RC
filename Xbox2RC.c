#include <stdbool.h> // Para poder crear variables booleanas
#include <SDL2/SDL.h> // Para leer y manejar el mando de Xbox


/*
Asignaciones de SDL2 sobre el mando de XBOX ONE X

Botón 0: A
Botón 1: B
Botón 2: X
Botón 3: Y
Botón 4: TL
Botón 5: TR
Botón 6: Select
Botón 7: Start
Botón 8: Modo (Logo Xbox)
Botón 9: Botón joystick izquierdo
Botón 10: Botón joystick derecho
Botón 11: Compartir

Hat 0: Cruceta (DPAD)
        1: Norte
        2: Este
        3: Noreste
        4: Sur
        6: Sureste
        8: Oeste
        9: Noroeste
        12: Suroeste

 Axis 0: Horizontal joystick izquierdo    (Izquierda=-32768)
 Axis 1: Vertical joystick izquierdo      (Arriba=-32768)
 Axis 2: Trigger izquierdo                (Presionado=32768, Suelto=-32768)
 Axis 3: Horizontal joystick derecho      (Izquierda=-32768)
 Axis 4: Vertical joystick derecho        (Arriba=-32768)
 Axis 5: Trigger derecho                  (Presionado=32768, Suelto=-32768)
*/


// Variables de parámetros para la transmisión de datos
long freq_hz = 49861000;
long freq_samples = 2000000;
int ganancia = 47;

 // Creo varios vectores char de 100 caracteres y 250 caracteres respectivamente, para que almacenen el nombre del archivo y el comando final de la transmisión de señales.
char filename[100];
char transmision[250];

bool transmitiendo = false;

void transmitir() {
    if(transmitiendo) return; // Si ya está transmitiendo, salir e ignorar la siguiente llamada

    transmitiendo = true;
    snprintf(transmision, sizeof(transmision), "hackrf_transfer -x %d -f %ld -s %ld -t \"%s\"", ganancia, freq_hz, freq_samples, filename);
    printf("Command: %s\n", transmision);
    system(transmision);
    transmitiendo = false;
}
// Variables con relación al mando:

int botones=12;
int ejes=6;

// Variables relacionadas con fixgiro
bool fixgiro = true;    // Fixgiro establece una memoria para los dos joysticks para que cuando lea RIGHT o LEFT,
bool JS0down = false;    // tenga memoria del anterior input (DOWN + RIGHT, UP + LEFT, etc...) para así, en términos de
bool JS1down = false;    // coches teledirigidos o similares, pueda mantener el giro y evitar "bugs" de girar repentinamente a la derecha yendo hacia atrás.
                         // JS0down y JS1down son variables booleanas que establecen si el último giro fue dado combinado con el hacia adelante o el hacia atrás.

// Crear variable centinela para el while
bool centinela = true;

// Variable para los for
int i;

// Crear funciones para cada botón
void Boton0() {
    printf("Botón 0\n");
}
void Boton1() {
    printf("Botón 1\n");
}
void Boton2() {
    printf("Botón 2\n");
}
void Boton3() {
    printf("Botón 3\n");
}
void Boton4() {
    printf("Botón 4\n");
}
void Boton5() {
    printf("Botón 5\n");
}
void Boton6() {
    printf("Botón 6\n");
}
void Boton7() {
    printf("Botón 7\n");
}
void Boton8() {
    printf("Botón 8, cerrando\n");
    centinela = false;
}
void Boton9() {
    printf("Botón 9\n");
}
void Boton10() {
    printf("Botón 10\n");
}
void Boton11() {
    printf("Botón 11\n");
}

// Creo un vector puntero que puede apuntar a cada funcion de botón
void (*funcionesboton[])() = {
    Boton0,
    Boton1,
    Boton2,
    Boton3,
    Boton4,
    Boton5,
    Boton6,
    Boton7,
    Boton8,
    Boton9,
    Boton10,
    Boton11
};



// Crear funciones para cada axis
// Axis 0 & 1
void JoystickIzquierdo0() {
    printf("JS0: UP\n");
}
void JoystickIzquierdo1() {
    printf("JS0: UP + RIGHT\n");
}
void JoystickIzquierdo2() {
    printf("JS0: RIGHT\n");
}
void JoystickIzquierdo3() {
    printf("JS0: DOWN + RIGHT\n");
}
void JoystickIzquierdo4() {
    printf("JS0: DOWN\n");
}
void JoystickIzquierdo5() {
    printf("JS0: DOWN + LEFT\n");
}
void JoystickIzquierdo6() {
    printf("JS0: LEFT\n");
}

void JoystickIzquierdo7() {
    printf("JS0: UP + LEFT\n");
}

// Axis 3 & 4
void JoystickDerecho0() {
    printf("JS1: UP\n");

    snprintf(filename, sizeof(filename), "/home/isaac/clones/XboxRC/RTL-SDR-adelante-49_861MHz-2MSps-2MHz.complex16s");
    transmitir();
}
void JoystickDerecho1() {
    printf("JS1: UP + RIGHT\n");

    snprintf(filename, sizeof(filename), "/home/isaac/clones/XboxRC/RTL-SDR-alantederecha-49_861MHz-2MSps-2MHz.complex16s");
    transmitir();
}
void JoystickDerecho2() {
    printf("JS1: RIGHT\n");
}
void JoystickDerecho3() {
    printf("JS1: DOWN + RIGHT\n");

    snprintf(filename, sizeof(filename), "/home/isaac/clones/XboxRC/RTL-SDR-atrasderecha-49_861MHz-2MSps-2MHz.complex16s");
    transmitir();
}
void JoystickDerecho4() {
    printf("JS1: DOWN\n");

    snprintf(filename, sizeof(filename), "/home/isaac/clones/XboxRC/RTL-SDR-atras-49_861MHz-2MSps-2MHz.complex16s");
    transmitir();
}
void JoystickDerecho5() {
    printf("JS1: DOWN + LEFT\n");

    snprintf(filename, sizeof(filename), "/home/isaac/clones/XboxRC/RTL-SDR-atrasizquierda-49_861MHz-2MSps-2MHz.complex16s");
    transmitir();
}
void JoystickDerecho6() {
    printf("JS1: LEFT\n");
}

void JoystickDerecho7() {
    printf("JS1: UP + LEFT\n");

    snprintf(filename, sizeof(filename), "/home/isaac/clones/XboxRC/RTL-SDR-alanteizquierda-49_861MHz-2MSps-2MHz.complex16s");
    transmitir();
}

// Axis 2 & 5
void TriggerIzquierdoPresionado() {
    printf("TL: HELD\n");
}

void TriggerDerechoPresionado() {
    printf("TR: HELD\n");
}

// Hat 0
void Dpad0() {
    printf("Hat 0: UP\n");
}
void Dpad1() {
    printf("Hat 0: UP + RIGHT\n");
}
void Dpad2() {
    printf("Hat 0: RIGHT\n");
}
void Dpad3() {
    printf("Hat 0: DOWN + RIGHT\n");
}
void Dpad4() {
    printf("Hat 0: DOWN\n");
}
void Dpad5() {
    printf("Hat 0: DOWN + LEFT\n");
}
void Dpad6() {
    printf("Hat 0: LEFT\n");
}
void Dpad7() {
    printf("Hat 0: UP + LEFT\n");
}



// Comienzo de la función main

int main() {
    // Crear variables de los valores de cada botón
    int axis[ejes];
    int hat0 = 0; // El mando tiene un solo hat (cruceta)
    int boton[botones];

    // Parámetros
    int margen = 10000;
    int margenTLR = 2 * margen - 32768; // Como los trigger tienen un valor en reposo de -32768, se ha de hacer una conversión lineal del margen global para que sea equivalente


    // Inicializar SDL para mando y teclado
    if (SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_EVENTS) != 0) {
        printf("Error inicializando SDL: %s\n", SDL_GetError());
        return 1; // Salir si SDL no se inicializa

    }
    // Abrir joystick
    SDL_Joystick* joystick = SDL_JoystickOpen(0);

    if (joystick == NULL) {
        printf("Error abriendo joystick: %s\n", SDL_GetError());
        SDL_Quit();
        return 1; // Salir si SDL no lee el mando
    }

    // Empezar bucle
    while (centinela) {

        // Actualizar el estado del joystick
        SDL_JoystickUpdate();

        // Asignar variable a cada joystick, hat y botón
        for(i=0;i<ejes;i++){
            axis[i] = SDL_JoystickGetAxis(joystick, i);
        }

        hat0 = SDL_JoystickGetHat(joystick, 0);

        for(i=0;i<botones;i++){
            boton[i] = SDL_JoystickGetButton(joystick, i);
        }

        // Axis 1 & 2 | JS0
        if (axis[0] > margen && axis[1] < -margen) {
            JoystickIzquierdo1();
            if (fixgiro) {
                JS0down = false;
            }
        }
        if (axis[0] > margen && axis[1] > margen) {
            JoystickIzquierdo3();
            if (fixgiro) {
                JS0down = true;
            }
        }
        if (axis[0] < -margen && axis[1] < -margen) {
            JoystickIzquierdo7();
            if (fixgiro) {
                JS0down = false;
            }
        }
        if (axis[0] < -margen && axis[1] > margen) {
            JoystickIzquierdo5();
            if (fixgiro) {
                JS0down = true;
            }
        }
        if (axis[0] > -margen && axis[0] < margen && axis[1] < -margen) {
            JoystickIzquierdo0();}
        if (axis[0] > -margen && axis[0] < margen && axis[1] > margen) {
            JoystickIzquierdo4();}
        if (axis[1] > -margen && axis[1] < margen && axis[0] > margen) {
            if (fixgiro) {
                if (JS0down) { // Si previamente se ha ido para atrás se va en dirección hacia atrás. Por defecto va a ir hacia adelante
                    JoystickIzquierdo3();
                } else {
                    JoystickIzquierdo1();
                }
            } else {
                JoystickIzquierdo2();}
        }
        if (axis[1] > -margen && axis[1] < margen && axis[0] < -margen) {
            if (fixgiro) {
                if (JS0down) { // Si previamente se ha ido para atrás se va en dirección hacia atrás. Por defecto va a ir hacia adelante
                    JoystickIzquierdo5();
                } else {
                    JoystickIzquierdo7();
                }
            } else {
                JoystickIzquierdo6();}
        }

        // Axis 3 & 4 | JS1
        if (axis[3] > margen && axis[4] < -margen) {
            JoystickDerecho1();
            if (fixgiro) {
                JS1down = false;
            }
        }
        if (axis[3] > margen && axis[4] > margen) {
            JoystickDerecho3();
            if (fixgiro) {
                JS1down = true;
            }
        }
        if (axis[3] < -margen && axis[4] < -margen) {
            JoystickDerecho7();
            if (fixgiro) {
                JS1down = false;
            }
        }
        if (axis[3] < -margen && axis[4] > margen) {
            JoystickDerecho5();
            if (fixgiro) {
                JS1down = true;
            }
        }

        if (axis[3] > -margen && axis[3] < margen && axis[4] < -margen) {
            JoystickDerecho0();}
        if (axis[3] > -margen && axis[3] < margen && axis[4] > margen) {
            JoystickDerecho4();}
        if (axis[4] > -margen && axis[4] < margen && axis[3] > margen) {
            if (fixgiro) {
                if (JS1down) { // Si previamente se ha ido para atrás se va en dirección hacia atrás. Por defecto va a ir hacia adelante
                    JoystickDerecho3();
                } else {
                    JoystickDerecho1();
                }
            } else {
                JoystickDerecho2();}
        }
        if (axis[4] > -margen && axis[4] < margen && axis[3] < -margen) {
            if (fixgiro) {
                if (JS1down) { // Si previamente se ha ido para atrás se va en dirección hacia atrás. Por defecto va a ir hacia adelante
                    JoystickDerecho5();
                } else {
                    JoystickDerecho7();
                }
            } else {
                JoystickDerecho6();}
        }

        // Axis 2 & 5
        if (axis[2] > margenTLR) {
            TriggerIzquierdoPresionado();}
        if (axis[5] > margenTLR) {
            TriggerDerechoPresionado();}
        

        // Hat 0
        if (hat0 == 1) {
            Dpad0();}
        if (hat0 == 2) {
            Dpad2();}
        if (hat0 == 3) {
            Dpad1();}
        if (hat0 == 4) {
            Dpad4();}
        if (hat0 == 6) {
            Dpad3();}
        if (hat0 == 8) {
            Dpad6();}
        if (hat0 == 9) {
            Dpad7();}
        if (hat0 == 12) {
            Dpad5();}


        // Botones
        for (i=0; i<botones; i++) {
            if (boton[i]) {
                funcionesboton[i]();
            }
        }  
    }

    // Cerrar el joystick, SDL y vaciar el puntero
    SDL_JoystickClose(joystick);
    SDL_Quit();
    return 0;
}