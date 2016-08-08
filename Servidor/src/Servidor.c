/*
 ============================================================================
 Name        : Servidor.c
 Author      : marcelocejas
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "Servidor.h"

t_config_server ServerConfig;


int main(void) {
cargarConfiguracion("SERVER.cfg",ServerConfig);
return EXIT_SUCCESS;
}
