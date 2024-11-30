#include <SDL2/SDL.h>
#include <stdbool.h> // Para while(true)
#include <math.h> // Para hallar la potencia de los joysticks

// Asignaciones de SDL2 sobre el mando XBOX
//
// Botón 0: A
// Botón 1: B
// Botón 2: X
// Botón 3: Y
// Botón 4: TL
// Botón 5: TR
// Botón 6: Select
// Botón 7: Start
// Botón 8: Modo (Logo Xbox)
// Botón 9: Botón joystick izquierdo
// Botón 10: Botón joystick derecho
// Botón 11: Compartir (Es tan raro el icono que me da pereza sacarle buen nombre)
//
// Hat 0: Cruceta (DPAD)
//        1: Norte
//        2: Este
//        3: Noreste
//        4: Sur
//        6: Sureste
//        8: Oeste
//        9: Noroeste
//        12: Suroeste
//
// Axis 0: Horizontal joystick izquierdo    (Izquierda=-32768)
// Axis 1: Vertical joystick izquierdo      (Arriba=-32768)
// Axis 2: Trigger izquierdo                (Presionado=32768, Suelto=-32768)
// Axis 3: Horizontal joystick derecho      (Izquierda=-32768)
// Axis 4: Vertical joystick derecho        (Arriba=-32768)
// Axis 5: Trigger derecho                  (Presionado=32768, Suelto=-32768)
//


int main() {

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

    // Crear variable de salida del programa
    bool quit = false;

    // Parámetros
    int margen = 2000;
    int margenTLR = 2 * margen - 32768; // Como los trigger tienen un valor en reposo de -32768, se ha de hacer una conversión lineal del margen global para que sea equivalente

    // Crear variables de los valores de cada botón
    int axis0 = 0;
    int axis1 = 0;
    int axis2 = 0;
    int axis3 = 0;
    int axis4 = 0;
    int axis5 = 0;

    int hat0 = 0;

    int boton0 = 0;
    int boton1 = 0;
    int boton2 = 0;
    int boton3 = 0;
    int boton4 = 0;
    int boton5 = 0;
    int boton6 = 0;
    int boton7 = 0;
    int boton8 = 0;
    int boton9 = 0;
    int boton10 = 0;
    int boton11 = 0;

    // Variables relacionadas con PWR
    bool PWR = true; // Si está activado, se incorporan los valores de potencia al programa
    int PWRJS0 = -1;
    int PWRJS1 = -1;
    int PWRTL = -1;
    int PWRTR = -1;
    char PWRJS0_string[100];
    char PWRJS1_string[100];
    char PWRTR_string[100];
    char PWRTL_string[100];

    // Variables relacionadas con fixgiro
    bool fixgiro = false;    // Fixgiro establece una memoria para los dos joysticks para que cuando lea RIGHT o LEFT,
    bool JS0down = false;    // tenga memoria del anterior input (DOWN + RIGHT, UP + LEFT, etc...) para así, en términos de
    bool JS1down = false;    // coches teledirigidos o similares, pueda mantener el giro y evitar "bugs" de girar repentinamente a la derecha yendo hacia atrás.
                             // JS0down y JS1down son variables booleanas que establecen si el último giro fue dado combinado con el hacia adelante o el hacia atrás.



    // Crear funciones para cada botón
    void Boton0() {
        system("echo 'Botón 0'");
    }
    void Boton1() {
        system("echo 'Botón 1'");
    }
    void Boton2() {
        system("echo 'Botón 2'");
    }
    void Boton3() {
        system("echo 'Botón 3'");
    }
    void Boton4() {
        system("echo 'Botón 4'");
    }
    void Boton5() {
        system("echo 'Botón 5'");
    }
    void Boton6() {
        system("echo 'Botón 6'");
    }
    void Boton7() {
        system("echo 'Botón 7'");
    }
    void Boton8() {
        system("echo 'Botón 8'");
    }
    void Boton9() {
        system("echo 'Botón 9'");
    }
    void Boton10() {
        system("echo 'Botón 10'");
    }
    void Boton11() {
        system("echo 'Botón 11'");
    }


    // Crear funciones para cada axis
    // Axis 0 & 1
    void JoystickIzquierdoNorte() {
        sprintf(PWRJS0_string, "echo 'JS0: UP   PWR:' %d", PWRJS0);
        system(PWRJS0_string);
    }
    void JoystickIzquierdoSur() {
        sprintf(PWRJS0_string, "echo 'JS0: DOWN   PWR:' %d", PWRJS0);
        system(PWRJS0_string);
    }
    void JoystickIzquierdoEste() {
        sprintf(PWRJS0_string, "echo 'JS0: RIGHT PWR:' %d", PWRJS0);
        system(PWRJS0_string);
    }
    void JoystickIzquierdoOeste() {
        sprintf(PWRJS0_string, "echo 'JS0: LEFT  PWR:' %d", PWRJS0);
        system(PWRJS0_string);
    }
    void JoystickIzquierdoNoreste() {
        sprintf(PWRJS0_string, "echo 'JS0: UP + RIGHT  PWR:' %d", PWRJS0);
        system(PWRJS0_string);
    }
    void JoystickIzquierdoNoroeste() {
        sprintf(PWRJS0_string, "echo 'JS0: UP + LEFT  PWR:' %d", PWRJS0);
        system(PWRJS0_string);
    }
    void JoystickIzquierdoSureste() {
        sprintf(PWRJS0_string, "echo 'JS0: DOWN + RIGHT  PWR:' %d", PWRJS0);
        system(PWRJS0_string);
    }
    void JoystickIzquierdoSuroeste() {
        sprintf(PWRJS0_string, "echo 'JS0: DOWN + LEFT  PWR:' %d", PWRJS0);
        system(PWRJS0_string);
    }

    // Axis 3 & 4
    void JoystickDerechoNorte() {
        sprintf(PWRJS1_string, "echo 'JS1: UP   PWR:' %d", PWRJS1);
        system(PWRJS1_string);
    }
    void JoystickDerechoSur() {
        sprintf(PWRJS1_string, "echo 'JS1: DOWN   PWR:' %d", PWRJS1);
        system(PWRJS1_string);
    }
    void JoystickDerechoEste() {
        sprintf(PWRJS1_string, "echo 'JS1: RIGHT PWR:' %d", PWRJS1);
        system(PWRJS1_string);
    }
    void JoystickDerechoOeste() {
        sprintf(PWRJS1_string, "echo 'JS1: LEFT  PWR:' %d", PWRJS1);
        system(PWRJS1_string);
    }
    void JoystickDerechoNoreste() {
        sprintf(PWRJS1_string, "echo 'JS1: UP + RIGHT  PWR:' %d", PWRJS1);
        system(PWRJS1_string);
    }
    void JoystickDerechoNoroeste() {
        sprintf(PWRJS1_string, "echo 'JS1: UP + LEFT  PWR:' %d", PWRJS1);
        system(PWRJS1_string);
    }
    void JoystickDerechoSureste() {
        sprintf(PWRJS1_string, "echo 'JS1: DOWN + RIGHT  PWR:' %d", PWRJS1);
        system(PWRJS1_string);
    }
    void JoystickDerechoSuroeste() {
        sprintf(PWRJS1_string, "echo 'JS1: DOWN + LEFT  PWR:' %d", PWRJS1);
        system(PWRJS1_string);
    }

    // Axis 2 & 5
    void TriggerIzquierdoPresionado() {
        sprintf(PWRTL_string, "echo 'TL: HELD  PWR:' %d", PWRTL);
        system(PWRTL_string);
    }

    void TriggerDerechoPresionado() {
        sprintf(PWRTR_string, "echo 'TR: HELD  PWR:' %d", PWRTR);
        system(PWRTR_string);
    }

    // Hat 0
    void DpadNorte() {
        system("echo 'Hat 0: UP'");
    }
    void DpadSur() {
        system("echo 'Hat 0: DOWN'");
    }
    void DpadEste() {
        system("echo 'Hat 0: RIGHT'");
    }
    void DpadOeste() {
        system("echo 'Hat 0: LEFT'");
    }
    void DpadNoreste() {
        system("echo 'Hat 0: UP + RIGHT'");
    }
    void DpadNoroeste() {
        system("echo 'Hat 0: UP + LEFT'");
    }
    void DpadSureste() {
        system("echo 'Hat 0: DOWN + RIGHT'");
    }
    void DpadSuroeste() {
        system("echo 'Hat 0: DOWN + LEFT'");
    }


    //Empezar bucle
    while (!quit) {

        // Se desactiva el bucle si hay Ctrl+C
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Actualizar el estado del joystick
        SDL_JoystickUpdate();

        // Asignar variable a cada joystick, hat y botón
        axis0 = SDL_JoystickGetAxis(joystick, 0);
        axis1 = SDL_JoystickGetAxis(joystick, 1);
        axis2 = SDL_JoystickGetAxis(joystick, 2);
        axis3 = SDL_JoystickGetAxis(joystick, 3);
        axis4 = SDL_JoystickGetAxis(joystick, 4);
        axis5 = SDL_JoystickGetAxis(joystick, 5);

        hat0 = SDL_JoystickGetHat(joystick, 0);

        boton0 = SDL_JoystickGetButton(joystick, 0);
        boton1 = SDL_JoystickGetButton(joystick, 1);
        boton2 = SDL_JoystickGetButton(joystick, 2);
        boton3 = SDL_JoystickGetButton(joystick, 3);
        boton4 = SDL_JoystickGetButton(joystick, 4);
        boton5 = SDL_JoystickGetButton(joystick, 5);
        boton6 = SDL_JoystickGetButton(joystick, 6);
        boton7 = SDL_JoystickGetButton(joystick, 7);
        boton8 = SDL_JoystickGetButton(joystick, 8);
        boton9 = SDL_JoystickGetButton(joystick, 9);
        boton10 = SDL_JoystickGetButton(joystick, 10);
        boton11 = SDL_JoystickGetButton(joystick, 11);

        if (PWR) {
            PWRJS0 = 100 * sqrt(axis0 * axis0 + axis1 * axis1) / 32768;
            PWRJS1 = 100 * sqrt(axis3 * axis3 + axis4 * axis4) / 32768;
            PWRTL = 25 * axis2 / 16384 + 50;
            PWRTR = 25 * axis5 / 16384 + 50;
            if (PWRJS0 > 100) {
                PWRJS0 = 100;
            }
            if (PWRJS1 > 100) {
                PWRJS1 = 100;
            }
        }

        // Axis 1 & 2 | JS0
        if (axis0 > margen && axis1 < -margen) {
            JoystickIzquierdoNoreste();
            if (fixgiro) {
                JS0down = false;
            }
        }
        if (axis0 > margen && axis1 > margen) {
            JoystickIzquierdoSureste();
            if (fixgiro) {
                JS0down = true;
            }
        }
        if (axis0 < -margen && axis1 < -margen) {
            JoystickIzquierdoNoroeste();
            if (fixgiro) {
                JS0down = false;
            }
        }
        if (axis0 < -margen && axis1 > margen) {
            JoystickIzquierdoSuroeste();
            if (fixgiro) {
                JS0down = true;
            }
        }
        if (axis0 > -margen && axis0 < margen && axis1 < -margen) {
            JoystickIzquierdoNorte();}
        if (axis0 > -margen && axis0 < margen && axis1 > margen) {
            JoystickIzquierdoSur();}
        if (axis1 > -margen && axis1 < margen && axis0 > margen) {
            if (fixgiro) {
                if (JS0down) { // Si previamente se ha ido para atrás se va en dirección hacia atrás. Por defecto va a ir hacia adelante
                    JoystickIzquierdoSureste();
                } else {
                    JoystickIzquierdoNoreste();
                }
            } else {
                JoystickIzquierdoEste();}
        }
        if (axis1 > -margen && axis1 < margen && axis0 < -margen) {
            if (fixgiro) {
                if (JS0down) { // Si previamente se ha ido para atrás se va en dirección hacia atrás. Por defecto va a ir hacia adelante
                    JoystickIzquierdoSuroeste();
                } else {
                    JoystickIzquierdoNoroeste();
                }
            } else {
                JoystickIzquierdoOeste();}
        }

        // Axis 3 & 4 | JS1
        if (axis3 > margen && axis4 < -margen) {
            JoystickDerechoNoreste();
            if (fixgiro) {
                JS1down = false;
            }
        }
        if (axis3 > margen && axis4 > margen) {
            JoystickDerechoSureste();
            if (fixgiro) {
                JS1down = true;
            }
        }
        if (axis3 < -margen && axis4 < -margen) {
            JoystickDerechoNoroeste();
            if (fixgiro) {
                JS1down = false;
            }
        }
        if (axis3 < -margen && axis4 > margen) {
            JoystickDerechoSuroeste();
            if (fixgiro) {
                JS1down = true;
            }
        }

        if (axis3 > -margen && axis3 < margen && axis4 < -margen) {
            JoystickDerechoNorte();}
        if (axis3 > -margen && axis3 < margen && axis4 > margen) {
            JoystickDerechoSur();}
        if (axis4 > -margen && axis4 < margen && axis3 > margen) {
            if (fixgiro) {
                if (JS1down) { // Si previamente se ha ido para atrás se va en dirección hacia atrás. Por defecto va a ir hacia adelante
                    JoystickDerechoSureste();
                } else {
                    JoystickDerechoNoreste();
                }
            } else {
                JoystickDerechoEste();}
        }
        if (axis4 > -margen && axis4 < margen && axis3 < -margen) {
            if (fixgiro) {
                if (JS1down) { // Si previamente se ha ido para atrás se va en dirección hacia atrás. Por defecto va a ir hacia adelante
                    JoystickDerechoSuroeste();
                } else {
                    JoystickDerechoNoroeste();
                }
            } else {
                JoystickDerechoOeste();}
        }

        // Axis 2 & 5
        if (axis2 > margenTLR) {
            TriggerIzquierdoPresionado();}
        if (axis5 > margenTLR) {
            TriggerDerechoPresionado();}


        // Hat 0
        if (hat0 == 1) {
            DpadNorte();}
        if (hat0 == 2) {
            DpadEste();}
        if (hat0 == 3) {
            DpadNoreste();}
        if (hat0 == 4) {
            DpadSur();}
        if (hat0 == 6) {
            DpadSureste();}
        if (hat0 == 8) {
            DpadOeste();}
        if (hat0 == 9) {
            DpadNoroeste();}
        if (hat0 == 12) {
            DpadSuroeste();}


        // Botones
        if (boton0) {
            Boton0();}
        if (boton1) {
            Boton1();}
        if (boton2) {
            Boton2();}
        if (boton3) {
            Boton3();}
        if (boton4) {
            Boton4();}
        if (boton5) {
            Boton5();}
        if (boton6) {
            Boton6();}
        if (boton7) {
            Boton7();}
        if (boton8) {
            Boton8();}
        if (boton9) {
            Boton9();}
        if (boton10) {
            Boton10();}
        if (boton11) {
            Boton11();}
    }

    // Cerrar el joystick y SDL
    SDL_JoystickClose(joystick);
    SDL_Quit();

    return 0;
}
