/*
 * Servidor.h
 *
 *  Created on: 5/8/2016
 *      Author: utnso
 */

#ifndef SERVIDOR_H_
#define SERVIDOR_H_

#include <stdio.h>
#include <stdlib.h>
#include "configuracion.h"
#include "../BiblioCompartida/Conexiones.h"
#include "../BiblioCompartida/Mensajes.h"

int atenderMsjCliente(char*, int);

#endif /* SERVIDOR_H_ */
