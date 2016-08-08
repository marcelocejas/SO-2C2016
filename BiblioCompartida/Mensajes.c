/*
 * Mensajes.c
 *
 *  Created on: 5/8/2016
 *      Author: utnso
 */

#include "Mensajes.h"

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
