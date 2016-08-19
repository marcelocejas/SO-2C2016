/*
 * configuracion.h
 *
 *  Created on: 8/8/2016
 *      Author: utnso
 */

#ifndef CONFIGURACION_H_
#define CONFIGURACION_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commons/config.h"

#define CANTIDAD_PARAMETROS_CONFIG  2

typedef struct configInfo {
	int serverPuerto;
	char* serverIp;
} t_config_server;


int cargarConfiguracion(char*, t_config_server*);
void finalizarConfig(void);

#endif /* CONFIGURACION_H_ */
