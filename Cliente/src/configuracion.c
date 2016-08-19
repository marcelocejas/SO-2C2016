/*
 * configuracion.c
 *
 *  Created on: 8/8/2016
 *      Author: utnso
 */



#include "configuracion.h"

t_config *tConfig;


int cargarConfiguracion(char* archivoRuta, t_config_server* configCliente ) {
	// Genero tabla de configuracion
	tConfig = config_create(archivoRuta);
	if (tConfig == NULL) {
		printf("ERROR: no se encuentra o falta el archivo de configuracion en la direccion \t%s \n", archivoRuta);

		return 0;
	}
	// Verifico que el archivo de configuracion tenga la cantidad de parametros correcta.
	if (config_keys_amount(tConfig) == CANTIDAD_PARAMETROS_CONFIG) {
		// Verifico que los parametros tengan sus valores OK
		// Verifico parametro PUERTO
		if (config_has_property(tConfig, "PUERTO")) {
			configCliente->serverPuerto = config_get_int_value(tConfig, "PUERTO_SERVER");
		} else {
			printf("ERROR: Falta el parametro: %s. \n", "PUERTO_SERVERPUERTO_SERVER");
			return 1;
		}
		if (config_has_property(tConfig, "PUERTO")) {
			configCliente->serverPuerto = config_get_string_value(tConfig, "IP_SERVER");
		} else {
			printf("ERROR: Falta el parametro: %s. \n", "IP_SERVER");
			return 1;
		}
		printf("Archivo de configuración SERVER leido:\n");
		printf("===================================\n");
		printf("SERVER PUERTO: %d\n SERVER IP: %s\n", configCliente->serverPuerto, configCliente->serverIp);
		return 1;
	} else {
		printf("ERROR: El archivo SERVER.cfg no tiene los %d campos que debería.\n", CANTIDAD_PARAMETROS_CONFIG);
		return 0;
	}
}

void finalizarConfig() {
	config_destroy(tConfig);
}
