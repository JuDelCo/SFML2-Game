// Copyright (c) 2013 Juan Delgado (JuDelCo)
// License: zlib/libpng License
// zlib/libpng License web page: http://opensource.org/licenses/Zlib

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

#endif // DEFINES_HPP
