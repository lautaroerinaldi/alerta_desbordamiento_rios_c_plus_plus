/*
 * SocketComunicador.cpp
 */

#include "common_SocketComunicador.h"

#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <string>

#define MAXDATASIZE 512 // máximo número de bytes que se pueden leer de una vez

bool SocketComunicador::conexionValida() {
	return (this->conexion_valida && this->socket_fd != SOCKET_FD_INVALIDO);
}

SocketComunicador::SocketComunicador(int socket_fd) :
		puerto(""), ip(""), socket_fd(socket_fd), leidos(""), lista_direcciones(
		NULL), conexion_valida(true) {
}

SocketComunicador::SocketComunicador(const std::string & ip,
		const std::string & puerto) {
	this->conexion_valida = false;
	this->puerto = puerto;
	this->ip = ip;
	this->lista_direcciones = NULL;
	leidos = "";
	this->socket_fd = SOCKET_FD_INVALIDO;
	if (this->crearSocket() == OPERACION_SOCKET_OK)
		if (this->conectar() == OPERACION_SOCKET_OK) {
			this->conexion_valida = true;
		}
}

bool SocketComunicador::crearSocket() {
	// cargo el struct con 0s
	memset(&this->encabezado, 0, sizeof(struct addrinfo));

	// AF_INET significa usar 'dominio' IPv4 - Protocolo de Internet
	this->encabezado.ai_family = AF_INET;
	// SOCK_STREAM significa usar 'tipo' TCP
	this->encabezado.ai_socktype = SOCK_STREAM;
	// 0 es el 'protocolo'. Puede ponerse de este modo ya que normalmente hay
	// un único protocolo implementado para un determinado 'tipo de socket'
	this->encabezado.ai_protocol = 0;
	this->encabezado.ai_flags = 0;

	if ((this->socket_fd = socket(this->encabezado.ai_family,
			this->encabezado.ai_socktype, this->encabezado.ai_protocol)) < 0) {
		// Falla creando el socket
		return ERROR_EN_SOCKET;
	} else {
		return OPERACION_SOCKET_OK;
	}
}

// pre: espera que ya se haya creado el socket
bool SocketComunicador::conectar() {
	int rc;
	// en lista_direcciones se obtiene una lista donde cada nodo es una
	// posible direccion con la cual uno se "podría" conectar
	rc = getaddrinfo(this->ip.c_str(), this->puerto.c_str(), &this->encabezado,
			&this->lista_direcciones);
	if (rc) {
		//Falla al decodificar HOST_NAME / SERVICE_NAME con getaddrinfo
		freeaddrinfo(lista_direcciones);
		return ERROR_EN_SOCKET;
	}
	rc = connect(this->socket_fd, lista_direcciones->ai_addr,
			lista_direcciones->ai_addrlen);
	if (rc < 0) {
		//Falla al conectar
		freeaddrinfo(lista_direcciones);
		return ERROR_EN_SOCKET;
	}
	freeaddrinfo(lista_direcciones);

	return OPERACION_SOCKET_OK;
}

int SocketComunicador::enviarDatos(const std::string & mensaje) {
	if (this->conexionValida()) {
		int bytes_a_enviar = mensaje.length();
		bool hubo_error = false;
		int cant_enviados = 0;
		int posicion_inicial = 0;
		while (cant_enviados < bytes_a_enviar && hubo_error == false) {
			cant_enviados = send(this->socket_fd, &mensaje[posicion_inicial],
					mensaje.length(), MSG_NOSIGNAL);

			// si nos cerraron el socket o hubo otro tipo de error
			if (cant_enviados <= 0)
				hubo_error = true;
		}
		if (hubo_error)
			return ERROR_EN_SOCKET;
		else
			return OPERACION_SOCKET_OK;
	} else {
		//No se pudo enviar. Socket invalido
		return ERROR_EN_SOCKET;
	}
}

std::string SocketComunicador::recibirDatos(char delimitador) {
	size_t posicion = leidos.find(delimitador, 0);
	if (posicion != std::string::npos) {
		std::string a_retornar = leidos.substr(0, posicion);
		if (posicion != leidos.length() - 1)
			leidos = leidos.substr(posicion + 1, leidos.length() - posicion);
		else
			leidos = "";
		return a_retornar;
	}

	if (this->conexionValida()) {
		int numbytes = 0;
		bool hubo_error = false;
		bool delim_encontrado = false;
		while (delim_encontrado == false && hubo_error == false) {
			char buf[MAXDATASIZE];
			memset(buf, 0, MAXDATASIZE);
			buf[MAXDATASIZE - 1] = '\0';
			numbytes = recv(this->socket_fd, buf, MAXDATASIZE - 1,
			MSG_NOSIGNAL);
			if (numbytes <= 0) {
				//Falla al recibir
				hubo_error = true;
				this->cerrarSocket();
				return "";
			} else {
				leidos.append(buf, numbytes);
				posicion = leidos.find(delimitador, 0);
				if (posicion != std::string::npos) {
					std::string a_retornar = leidos.substr(0, posicion);

					if (posicion != leidos.length() - 1)
						leidos = leidos.substr(posicion + 1,
								leidos.length() - posicion);
					else
						leidos = "";
					delim_encontrado = true;
					return a_retornar;
				}
			}
		}
		return "";
	} else {
		//No se pudo recibir. Socket invalido.
		return "";
	}
}

void SocketComunicador::cerrarSocket() {
	// Finaliza la transmision tanto para lectura como para escritura
	shutdown(this->socket_fd, SHUT_RDWR);
	close(this->socket_fd);
	this->socket_fd = SOCKET_FD_INVALIDO;
	this->conexion_valida = false;
}
