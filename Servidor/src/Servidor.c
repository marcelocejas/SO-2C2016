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
	char* ConfigPath = "../SERVER.cfg";
	ServerConfig = malloc(sizeof(t_config_server));
	cargarConfiguracion(ConfigPath, ServerConfig);
	int socketServer = IniciarSocketServidor(ServerConfig->puerto);
	if (socketServer == -1) {
		printf("Error creando socket servidor");
	}
	int socketCliente = AceptarConexionCliente(socketServer);
	if (socketCliente != -1) {
		printf("Cliente %d conetado.", socketCliente);
	}
	else{
		printf("Error aceptanco conexion.");
	}
	t_msjCabecera* msjCabecera = malloc(sizeof(t_msjCabecera));
	char* msj = recibirMsjConEncabezado(socketCliente, msjCabecera);
	if (msj != NULL) {
		if (atenderMsjCliente(msj, msjCabecera->tipoMensaje)) {
			printf("Mensaje atendido Ok.\n");
		}
	} else {
		printf("Error recibiendo mensaje.");
		return EXIT_FAILURE;
	}

	finalizarConfig();
	return EXIT_SUCCESS;
}

int atenderMsjCliente(char* msj, int tipoMsj) {
	switch (tipoMsj) {
	case 1:
		printf("mensaje = 1\n");
		break;
	case 2:
		printf("mensaje = 2\n");
		break;
	default:
		printf("No se reconoce msj\n");
		break;
	}
	return EXIT_SUCCESS;
}
