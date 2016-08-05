/*
 * Mensajes.h
 *
 *  Created on: 5/8/2016
 *      Author: utnso
 */

#ifndef MENSAJES_H_
#define MENSAJES_H_

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdint.h>

typedef struct{
	int unsigned tipoMensaje;
	int unsigned logitudMensaje;
}__attribute__((__packed__)) mensaje_t;


char* mensaje_serializer(mensaje_t*, int16_t*);
mensaje_t* mensaje_deserializer(char*);

#endif /* MENSAJES_H_ */
