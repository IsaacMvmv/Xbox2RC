# Xbox2RC
Proyecto que consiste en lograr controlar un dispositivo RC con un mando de xbox one series X/S

## Programas/Herramientas que usaré
### Programación:
  - Sublime text 4
  - GNU CC
  - SDL2

### Radiofrecuencia / Espectros / Ondas
  - [QSpectrumAnalyzer](https://github.com/xmikos/qspectrumanalyzer)
  - [CubicSDR](https://github.com/cjcliffe/CubicSDR)
  - [GQRX](https://github.com/gqrx-sdr/gqrx)
  - [Universal Radio Hacker (URH)](https://github.com/jopohl/urh)
  - [Audacity](https://github.com/audacity/audacity)


## Recursos web:
  - https://www.ivanglinkin.com/hackrf-as-the-best-sdr-friend-for-hackers/


## Descripciones
### Xbox2Shell.c
Xbox2Shell.c es un script inicialmente pensado exclusivmente para uso en linux y con un mando de XBOX one series X/S. Necesitará modificaciones si se quiere hacer funcionar en otro entorno y con otros mandos.
Elegí el lenguaje C ante python por el rendimiento. Al controlar un dispositivo radio control, entre ellos coches teledirigidos, es de crucial importancia mantener un delay lo más bajo posible entre el input y la reacción del coche.
Además, elegí la biblioteca SDL2 porque es más cómoda que linux/joystick.h a la hora de leer varios inputs al mismo tiempo, lo cual es algo a lo que le doy importancia.

Mi comando de compilación suele ser
```
gcc -o Xbox2Shell Xbox2Shell.c -lSDL2 -O3
```
