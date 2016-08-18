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

t_config_server* ServerConfig;

int main(void) {
	char* ConfigPath = "./SERVER.cfg";
	ServerConfig = malloc(sizeof(t_config_server));
	cargarConfiguracion(ConfigPath, ServerConfig);
	int socketServer = IniciarSocketServidor(ServerConfig->puerto);
	if (socketServer == -1) {
		printf("Error creando socket servidor");
	}
	int socketCliente = AceptarConexionCliente(socketServer);
	if (socketCliente == -1) {
		printf("Error aceptanco conexion.");
	}
	t_msjCabecera* msjCabecera = malloc(sizeof(t_msjCabecera));
	if (recibirMsjConEncabezado(socketCliente, msjCabecera) == NULL) {
		printf("Error recibiendo mensaje.");
	}
	finalizarConfig();
	return EXIT_SUCCESS;
}
