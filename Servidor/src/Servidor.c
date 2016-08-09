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
	char* ConfigPath = "SERVER.cfg";
	cargarConfiguracion(ConfigPath, ServerConfig);
	int socketServer = IniciarSocketServidor(ServerConfig->puerto);
	if(socketServer == -1){
		printf("Error creando socket servidor");
	}
	if (AceptarConexionCliente(socketServer) == -1) {
		printf("Error aceptanco conexion.");
	}
	finalizarConfig();
	return EXIT_SUCCESS;
}
