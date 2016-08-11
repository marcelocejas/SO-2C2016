/*
 * Mensajes.c
 *
 *  Created on: 5/8/2016
 *      Author: utnso
 */

#include "Mensajes.h"

char* recibirMsjConEncabezado(int socketEmisor) {
	int totalLeido = 0;
	t_msjCabecera msjCabecera;

	int msjTamanio = sizeof(msjCabecera);
	char* buffer = malloc(msjTamanio);

	if ((socketEmisor < 0) || (buffer == NULL)){
	printf("Error inicando el buffer para la cabecera.");
		return NULL;
	}

	if ((totalLeido = recibirMsjCompleto(socketEmisor, buffer, msjTamanio)) > 0) {
		msjCabecera = desempaquetarCabecera(buffer);
	} else {
		printf("Error recibiendo msj cabecera");
		free(buffer);
		return NULL;
	}

	buffer = realloc(msjCabecera.logitudMensaje);
	if ((totalLeido = recibirMsjCompleto(socketEmisor, buffer, msjCabecera.logitudMensaje)) < 0) {
		free(buffer);
		return NULL;
	}

	if (totalLeido != msjCabecera.logitudMensaje)
		printf("Mensaje recibido incompleto.");

	return buffer;
}

int recibirMsjCompleto(int socketEmisor, char* buffer, int tamanio) {
	int totalLeido = 0, aux = 0;

	while (totalLeido < tamanio && totalLeido != -1) {
		aux = recv(socketEmisor, buffer + totalLeido, tamanio - totalLeido, 0);
		if (aux > 0) {
			totalLeido = totalLeido + aux;
		} else {
			if (aux == 0)
				break;
			if (aux == -1) {
				switch (errno) {
				case EINTR:
				case EAGAIN:
					usleep(100);
					break;
				default:
				totalLeido = -1;
				}
			}
		}
	}
	return totalLeido;
}

int enviarMsjConEncabezado(int socketDestino, char* msj, t_msjCabecera msjCabecera) {
	int totalEnviado = 0;

	if ((socketDestino == -1) || (socketDestino < 1))
		return -1;

	char* buffer;
	int16_t* largoBuffer;
	buffer = empaquetarCabecera(msjCabecera, largoBuffer);

	totalEnviado = enviarMsjCompleto(socketDestino, buffer, largoBuffer);
	if(totalEnviado != sizeof(t_msjCabecera)){
		printf("Error enviando cabecera de mensaje.");
		totalEnviado = -1;
	}
	else{
		totalEnviado = enviarMsjCompleto(socketDestino, msj, msjCabecera.logitudMensaje);
		if(totalEnviado != msjCabecera.logitudMensaje){
			totalEnviado = -1;
			printf("Error enviando mensaje principal.");
		}
	}
	free(buffer);

	return totalEnviado;
}

int enviarMsjCompleto(int socketDestino, char* buffer, int longitudMensaje) {
	int totalEnviado = 0, aux = 0;

	while (totalEnviado < longitudMensaje && totalEnviado != -1) {
		aux = send(socketDestino, buffer + totalEnviado, longitudMensaje - totalEnviado, 0);
		if (aux > 0) {

			totalEnviado = totalEnviado + aux;
		} else {

			if (aux == 0)
				return totalEnviado;
			else
				switch (errno) {
				case EINTR:
				case EAGAIN:
					usleep(100);
					break;
				default:
				totalEnviado = -1;
				}
		}
	}
	return totalEnviado;
}

char* empaquetarCabecera(t_msjCabecera* mensaje, int16_t* largo) {
	char *empaquetado = malloc(sizeof(mensaje->tipoMensaje) + sizeof(mensaje->logitudMensaje));

	int offset = 0, tmp_size = 0;
	memcpy(empaquetado + offset, &mensaje->tipoMensaje, tmp_size = sizeof(mensaje->tipoMensaje));
	offset = tmp_size;
	memcpy(empaquetado + offset, &mensaje->logitudMensaje, tmp_size = sizeof(mensaje->logitudMensaje));
	offset += tmp_size;

	offset += tmp_size;
	*largo = offset;
	return empaquetado;
}

t_msjCabecera* desempaquetarCabecera(char* empaquetado) {
	t_msjCabecera* mensaje = malloc(sizeof(t_msjCabecera));
	int offset = 0, tmp_len = 0;
	memcpy(&mensaje->tipoMensaje, empaquetado + offset, tmp_len = sizeof(mensaje->tipoMensaje));
	offset = tmp_len;
	memcpy(&mensaje->logitudMensaje, empaquetado + offset, tmp_len = sizeof(mensaje->logitudMensaje));
	return mensaje;
}
