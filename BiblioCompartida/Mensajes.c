/*
 * Mensajes.c
 *
 *  Created on: 5/8/2016
 *      Author: utnso
 */

#include "Mensajes.h"

typedef struct{
	int unsigned tipoMensaje;
	int unsigned logitudMensaje;
}__attribute__((__packed__)) t_msjCabecera;

char* recibirMsjConEncabezado(int socketEmisor) {
	int totalLeido = 0;
	t_msjCabecera msjCabecera;

	int msjTamanio = malloc(sizeof(msjCabecera));
	char* buffer = msjTamanio;

	if ((socket < 0) || (buffer == NULL)){
	printf("Error inicando el buffer para la cabecera.");
		return -1;
	}

	if ((totalLeido = recibirMsjCompleto(socketEmisor, buffer, msjTamanio)) > 0) {
		memcpy(msjCabecera.logitudMensaje, buffer, sizeof(int));
		memcpy(msjCabecera.tipoMensaje, buffer + sizeof(int), sizeof(int));
	} else {
		printf("Error recibiendo msj cabecera");
		free(buffer);
		return -1;
	}
	free(buffer);

	if ((totalLeido = receiveCompleteMsj(socket, buffer, msjCabecera.logitudMensaje)) < 0) {
		free(buffer);
		return -1;
	}

	if (totalLeido != msjCabecera.logitudMensaje)
		printf("Mensaje recibido incompleto.");

	return buffer;
}


int recibirMsjCompleto(int ptrSender, char* buffer, int size) {
	int totalRead = 0, aux = 0;

	while (totalRead < size && totalRead != -1) {
		aux = recv(ptrSender, buffer + totalRead, size - totalRead, 0);
		if (aux > 0) {
			totalRead = totalRead + aux;
		} else {
			if (aux == 0)
				break;
			if (aux == -1) {
				/*switch (errno) {
				case EINTR:
				case EAGAIN:
					usleep(100);
					break;
				default:*/
					totalRead = -1;
				//}
			}
		}
	}
	return totalRead;
}

int enviarMsjConEncabezado(int ptrDestination, char* ptrBuffer, uint32_t size, uint32_t operation, uint32_t sender) {
	int totalWrite = 0;

	if ((ptrDestination == -1) || (size < 1))
		return -1;

	char* buffer = malloc(size + (3 * sizeof(uint32_t)));
	memcpy(buffer, &operation, sizeof(uint32_t));
	memcpy(buffer + sizeof(uint32_t), &sender, sizeof(uint32_t));
	memcpy(buffer + (2 * sizeof(uint32_t)), &size, sizeof(uint32_t));
	memcpy(buffer + (3 * sizeof(uint32_t)), ptrBuffer, size);

	totalWrite = sendCompleteMsj(ptrDestination, buffer, size + (3 * sizeof(uint32_t)));
	free(buffer);

	return totalWrite;
}

int enviarMsjCompleto(int ptrDestination, char* buffer, int size) {
	int totalWrite = 0, aux = 0;

	while (totalWrite < size && totalWrite != -1) {
		aux = send(ptrDestination, buffer + totalWrite, size - totalWrite, 0);
		if (aux > 0) {

			totalWrite = totalWrite + aux;
		} else {

			if (aux == 0)
				return totalWrite;
			else
				/*switch (errno) {
				case EINTR:
				case EAGAIN:
					usleep(100);
					break;
				default:
					totalWrite = -1;

				}*/
				;
		}
	}
	return totalWrite;
}

char* mensaje_serializer(mensaje_t* self, int16_t* length) {
	char *serialized = malloc(sizeof(self->tipoMensaje) + sizeof(self->logitudMensaje));

	int offset = 0, tmp_size = 0;
	memcpy(serialized + offset, &self->tipoMensaje, tmp_size = sizeof(self->tipoMensaje));
	offset = tmp_size;
	memcpy(serialized + offset, &self->logitudMensaje, tmp_size = sizeof(self->logitudMensaje));
	offset += tmp_size;

	offset += tmp_size;
	*length = offset;
	return serialized;
}

mensaje_t* mensaje_deserializer(char* serialized) {
	mensaje_t* self = malloc(sizeof(mensaje_t));
	int offset = 0, tmp_len = 0;
	memcpy(&self->tipoMensaje, serialized + offset, tmp_len = sizeof(self->tipoMensaje));
	offset = tmp_len;
	memcpy(&self->logitudMensaje, serialized + offset, tmp_len = sizeof(self->logitudMensaje));
	return self;
}
