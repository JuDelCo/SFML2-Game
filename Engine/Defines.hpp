#pragma once
#ifndef DEFINES_HPP
#define DEFINES_HPP


#define LOG_ALL             (0)
#define LOG_FILE            (1)
#define LOG_CONSOLE         (2)


#define ERROR_NONE          (0)  // Ningun Error
#define ERROR_INIT          (1)  // Error al iniciar
#define ERROR_TEXTURE       (2)  // Error al cargar una textura
#define ERROR_SOUND         (3)  // Error de sonido
#define ERROR_FILELOAD      (4)  // Error al cargar un fichero
#define ERROR_TILELOAD      (5)  // Error al cargar un tileset
#define ERROR_LAYERLOAD     (6)  // Error al cargar una capa
#define ERROR_SPRITELOAD    (7)  // Error al cargar un sprite
#define ERROR_ANIMATION     (8)  // Error de animación
#define ERROR_TEXT          (9)  // Error de texto


#define EVENT_KEYFOCUS      (0)  // On Key Focus
#define EVENT_KEYBLUR       (1)  // On Key Blur
#define EVENT_KEYDOWN       (2)  // On Key Down
#define EVENT_KEYUP         (3)  // On Key Up
#define EVENT_MOUSEFOCUS    (4)  // On Mouse Focus
#define EVENT_MOUSEBLUR     (5)  // On Mouse BLur
#define EVENT_MOUSEMOTION   (6)  // On Mouse Motion
#define EVENT_MOUSEDOWN     (7)  // On Mouse Down
#define EVENT_MOUSEUP       (8)  // On Mouse Up
#define EVENT_MOUSEWHEEL    (9)  // On Mouse Wheel
#define EVENT_TEXTENTERED   (10) // On Text Entered
#define EVENT_VIDEORESIZE   (11) // On Video Resize
#define EVENT_QUIT          (12) // On Quit


#endif // DEFINES_HPP
