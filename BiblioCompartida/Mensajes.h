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
#include <sys/socket.h>
#include <stdint.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

typedef struct{
	int unsigned tipoMensaje;
	int unsigned logitudMensaje;
}__attribute__((__packed__)) t_msjCabecera;

char* recibirMsjConEncabezado(int );
int recibirMsjCompleto(int , char* , int );
int enviarMsjConEncabezado(int , char* , t_msjCabecera );
int enviarMsjCompleto(int , char* , int );
char* empaquetarCabecera(t_msjCabecera*, int16_t*);
t_msjCabecera* desempaquetarCabecera(char*);

#endif /* MENSAJES_H_ */
