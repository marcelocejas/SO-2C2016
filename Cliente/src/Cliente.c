/*
 ============================================================================
 Name        : Cliente.c
 Author      : marcelocejas
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Cliente.h"

t_config_server* ClienteConfig;

int main(void) {
	char* ConfigPath = "./SERVER.cfg";
	ClienteConfig = malloc(sizeof(t_config_server));
	cargarConfiguracion(ConfigPath, ClienteConfig);



	finalizarConfig();
	return EXIT_SUCCESS;
}
