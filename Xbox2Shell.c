#include <SDL2/SDL.h>
#include <stdbool.h> //Para while(true)

// Nota
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
//
// Axis 0: Horizontal joystick izquierdo    (Izquierda=-32767)
// Axis 1: Vertical joystick izquierdo      (Arriba=-32767)
// Axis 2: Trigger izquierdo                (Presionado=32767, Suelto=-32767)
// Axis 3: Horizontal joystick derecho      (Izquierda=-32767)
// Axis 4: Vertical joystick derecho        (Arriba=-32767)
// Axis 5: Trigger derecho                  (Presionado=32767, Suelto=-32767)


int main() {
    
    // Inicializar SDL para mando y teclado
    SDL_Init(SDL_INIT_JOYSTICK | SDL_INIT_EVENTS);

    // Abrir joystick
    SDL_Joystick* joystick = SDL_JoystickOpen(0);

    // Crear algunas variables
    bool quit = false;
    // Variables relacionadas con fixgiro
    bool fixgiro = false;    // Fixgiro establece una memoria para los dos joysticks para que cuando lea RIGHT o LEFT,
    bool JS0down = false;    // tenga memoria del anterior input (DOWN + RIGHT, UP + LEFT, etc...) para así, en términos de
    bool JS1down = false;    // coches teledirigidos o similares, pueda mantener el giro y evitar "bugs" de girar repentinamente a la derecha yendo hacia atrás.
                             // JS0down y JS1down son variables booleanas que establecen si el último giro fue dado combinado con el hacia adelante o el hacia atrás.

    // Parámetros
    int margen = 16378;

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
        system("echo 'JS0: UP'");
    }
    void JoystickIzquierdoSur() {
        system("echo 'JS0: DOWN'");
    }
    void JoystickIzquierdoEste() {
        system("echo 'JS0: RIGHT'");
    }
    void JoystickIzquierdoOeste() {
        system("echo 'JS0: LEFT'");
    }
    void JoystickIzquierdoNoreste() {
        system("echo 'JS0: UP + RIGHT'");
    }
    void JoystickIzquierdoNoroeste() {
        system("echo 'JS0: UP + LEFT'");
    }
    void JoystickIzquierdoSureste() {
        system("echo 'JS0: DOWN + RIGHT'");
    }
    void JoystickIzquierdoSuroeste() {
        system("echo 'JS0: DOWN + LEFT'");
    }

    // Axis 3 & 4
    void JoystickDerechoNorte() {
        system("echo 'JS1: UP'");
    }
    void JoystickDerechoSur() {
        system("echo 'JS1: DOWN'");
    }
    void JoystickDerechoEste() {
        system("echo 'JS1: RIGHT'");
    }
    void JoystickDerechoOeste() {
        system("echo 'JS1: LEFT'");
    }
    void JoystickDerechoNoreste() {
        system("echo 'JS1: UP + RIGHT'");
    }
    void JoystickDerechoNoroeste() {
        system("echo 'JS1: UP + LEFT'");
    }
    void JoystickDerechoSureste() {
        system("echo 'JS1: DOWN + RIGHT'");
    }
    void JoystickDerechoSuroeste() {
        system("echo 'JS1: DOWN + LEFT'");
    }

    // Axis 2 & 5
    void TriggerIzquierdoPresionado() {
        system("echo 'TL: HELD'");
    }

    void TriggerDerechoPresionado() {
        system("echo 'TR: HELD'");
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
        int axis0 = SDL_JoystickGetAxis(joystick, 0);
        int axis1 = SDL_JoystickGetAxis(joystick, 1);
        int axis2 = SDL_JoystickGetAxis(joystick, 2);
        int axis3 = SDL_JoystickGetAxis(joystick, 3);
        int axis4 = SDL_JoystickGetAxis(joystick, 4);
        int axis5 = SDL_JoystickGetAxis(joystick, 5);

        int hat0 = SDL_JoystickGetHat(joystick, 0);

        int boton0 = SDL_JoystickGetButton(joystick, 0);
        int boton1 = SDL_JoystickGetButton(joystick, 1);
        int boton2 = SDL_JoystickGetButton(joystick, 2);
        int boton3 = SDL_JoystickGetButton(joystick, 3);
        int boton4 = SDL_JoystickGetButton(joystick, 4);
        int boton5 = SDL_JoystickGetButton(joystick, 5);
        int boton6 = SDL_JoystickGetButton(joystick, 6);
        int boton7 = SDL_JoystickGetButton(joystick, 7);
        int boton8 = SDL_JoystickGetButton(joystick, 8);
        int boton9 = SDL_JoystickGetButton(joystick, 9);
        int boton10 = SDL_JoystickGetButton(joystick, 10);
        int boton11 = SDL_JoystickGetButton(joystick, 11);

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
        if (axis2 > margen) {
            TriggerIzquierdoPresionado();}
        if (axis5 > margen) {
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

    // Close the joystick and quit SDL
    SDL_JoystickClose(joystick);
    SDL_Quit();

    return 0;
}
