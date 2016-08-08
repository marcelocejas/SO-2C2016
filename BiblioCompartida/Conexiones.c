/*
 * Conexiones.c
 *
 *  Created on: 5/8/2016
 *      Author: utnso
 */

#include "Conexiones.h"
#include "Mensajes.h"

//CLIENTE
/*
* Conecta con un servidor remoto a traves de socket INET
  y me devuelve el descriptor al socket creado.
*/
int conectarConServer(char *ipServer, int puertoServer)
{
	struct sockaddr_in socket_info;
	int nuevoSocket;
	// Se carga informacion del socket
	socket_info.sin_family = AF_INET;
	socket_info.sin_addr.s_addr = inet_addr(ipServer);
	socket_info.sin_port = htons(puertoServer);

	// Crear un socket:
	// AF_INET, SOCK_STREM, 0
	nuevoSocket = socket (AF_INET, SOCK_STREAM, 0);
	if (nuevoSocket < 0)
		return -1;
	// Conectar el socket con la direccion 'socketInfo'.
	if (connect (nuevoSocket,(struct sockaddr *)&socket_info,sizeof (socket_info)) != 0)
	{
		return -1;
	}

	return nuevoSocket;
}

//SERVIDOR
//abro un servidor de tipo AF_INET y me devuelve descriptor del socket servidor o -1 si hay error
int IniciarSocketServidor(int puertoServer)
{
	struct sockaddr_in socketInfo;
		int socketEscucha;
		int optval = 1;

		// Crear un socket
		socketEscucha = socket (AF_INET, SOCK_STREAM, 0);
		if (socketEscucha == -1)
		 	return -1;

		setsockopt(socketEscucha, SOL_SOCKET, SO_REUSEADDR, &optval,
				sizeof(optval));
		socketInfo.sin_family = AF_INET;
		socketInfo.sin_port = htons(puertoServer);
		socketInfo.sin_addr.s_addr = INADDR_ANY;
		if (bind (socketEscucha,(struct sockaddr *)&socketInfo,sizeof (socketInfo)) != 0)
		{
			close (socketEscucha);
			return -1;
		}

		/*
		* Se avisa al sistema que comience a atender llamadas de clientes
		*/
		if (listen (socketEscucha, 10) == -1)
		{
			close (socketEscucha);
			return -1;
		}
		/*
		* Se devuelve el descriptor del socket servidor
		*/
		return socketEscucha;
	}

int AceptarConexionCliente(int socketServer)
{
	socklen_t longitudCliente;//esta variable tiene inicialmente el tamaño de la estructura cliente que se le pase
	struct sockaddr cliente;
	int socketNuevaConexion;//esta variable va a tener la descripcion del nuevo socket que estaria creando
	longitudCliente = sizeof(cliente);
	socketNuevaConexion = accept (socketServer, &cliente, &longitudCliente);//acepto la conexion del cliente
	if (socketNuevaConexion < 0)
		return -1;

	return socketNuevaConexion;

}
