/*
 ============================================================================
 Name        : ClienteServidor.c
 Author      : marcelocejas
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include "ClienteServidor.h"

t_config_server* Config;

int main(void) {
	char* ConfigPath = "./SERVER.cfg";
	Config = malloc(sizeof(t_config_server));
	cargarConfiguracion(ConfigPath, Config);
	int socketServer = IniciarSocketServidor(Config->puerto);
	if (socketServer == -1) {
		printf("Error creando socket servidor.\n");
		return EXIT_FAILURE;
	}
	else{
		printf("Esperando conexion.\n");
	}
	int socketCliente = AceptarConexionCliente(socketServer);
	if (socketCliente != -1) {
		printf("Cliente %d conetado.\n", socketCliente);
	}
	else{
		printf("Error aceptando conexion.\n");
		return EXIT_FAILURE;
	}
	t_msjCabecera* msjCabecera = malloc(sizeof(t_msjCabecera));
	char* msj = recibirMsjConEncabezado(socketCliente, msjCabecera);
	if (msj != NULL) {
		if (atenderCliente(msj, msjCabecera->tipoMensaje)) {
			printf("Mensaje atendido Ok.\n");
		}
	} else {
		printf("Error recibiendo mensaje.\n");
		return EXIT_FAILURE;
	}

	finalizarConfig();
	return EXIT_SUCCESS;
}

int atenderCliente(char* msj, int tipoMsj) {
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
