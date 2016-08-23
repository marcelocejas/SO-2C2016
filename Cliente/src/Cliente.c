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
	char* ConfigPath = "./Cliente.cfg";
	ClienteConfig = malloc(sizeof(t_config_server));
	cargarConfiguracion(ConfigPath, ClienteConfig);

	int socketCliente = conectarConServer(ClienteConfig->serverIp, ClienteConfig->serverPuerto);
	if (socketCliente == -1) {
		printf("No se pudo conectar con el server");
		return EXIT_FAILURE;
	}
	char* msj = "Hola Msj 1";
	t_msjCabecera* cabeceraMsj = malloc(sizeof(t_msjCabecera));
	cabeceraMsj->tipoMensaje = 1;
	cabeceraMsj->logitudMensaje = strlen(msj)+1;
	if (enviarMsjConEncabezado(socketCliente, msj, cabeceraMsj) == -1) {
		printf("Error enviando msj.\n");
		return EXIT_FAILURE;
	}

	finalizarConfig();
	free(msj);
	free(cabeceraMsj);
	return EXIT_SUCCESS;
}
