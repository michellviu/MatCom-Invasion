# MatCom-Invasion
## Objetivo:
Desarrollar un juego de estilo arcade en C, similar al clásico "Alien Invaders", donde el jugador
controla una nave espacial para defender la Tierra de una invasión alienígena. Este proyecto tiene
como objetivo principal poner en práctica conceptos fundamentales de la asignatura Sistema
Operativo, como la programación orientada a eventos, la concurrencia, la gestión de la memoria y
el diseño de estrategias de planificación.
## Ejecucion:
Para ejecutar el programa es necesario tener instalado la biblioteca SDL2, el codigo para compilar los archivos necesarios en la termina de linux dentro del directorio del programa es: gcc -o MatCom_Invaders main.c Game.c Render.c Player.c Bullet.c Alien.c -lSDL2 -lSDL2_ttf
Luego se ejecuta usando el comando: ./MatComInvaders
