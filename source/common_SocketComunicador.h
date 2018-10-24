/*
 * SocketComunicador.h
 */

#ifndef COMMON_SOCKETCOMUNICADOR_H_
#define COMMON_SOCKETCOMUNICADOR_H_

#include <iostream>
#include <netdb.h>
#include <string>

#define SOCKET_FD_INVALIDO -1
#define SOCKET_VALIDO 0
#define SOCKET_INVALIDO 1

#define OPERACION_SOCKET_OK 0
#define ERROR_EN_SOCKET 1

/*
 * Socket TCP/IP para comunicacion
 */
class SocketComunicador {
private:
	std::string puerto;
	std::string ip;
	int socket_fd;
	std::string leidos;

	struct addrinfo encabezado; // suelen llamarlo hints
	// para almacenar los resultados de connect
	struct addrinfo * lista_direcciones;
	bool conexion_valida;

	/*
	 * Muestra por CERR una descripción del número de error errno pasado como
	 * argumento
	 */
	void reportarError(const std::string & mensaje, int error_number);

	/*
	 * Crea un socket TCP/IP v4. Retorna OPERACION_SOCKET_OK en caso de
	 * éxito y ERROR_EN_SOCKET en otro caso.
	 */
	bool crearSocket();

	/*
	 * Hace getaddrinfo y connect. Retorna OPERACION_SOCKET_OK en caso de
	 * éxito y ERROR_EN_SOCKET en otro caso.
	 */
	bool conectar();

public:
	/*
	 * Retorna true en caso de que se haya podido crear el socket y establecer
	 * la conexion, y false si hubo algun error o si cerraron la conexión.
	 */
	bool conexionValida();

	/*
	 * Crea un socket TCP/IP y se conecta al puerto (o servicename) y a la ip
	 * (o hostname) especificados.
	 * Debe consultarse si esValido después de esta operacion
	 */
	explicit SocketComunicador(const std::string & ip,
			const std::string & puerto);

	/*
	 * Inicializa un socket TCP/IP con el File Descriptor recibido por parametro
	 */
	explicit SocketComunicador(int socket_fd);

	/*
	 * Envía por el socket de comunicación el mensaje recibido por parámetro.
	 * Retorna OPERACION_SOCKET_OK en caso de éxito y ERROR_EN_SOCKET en caso
	 * de que no se haya podido transmitir la totalidad del mensaje.
	 */
	int enviarDatos(const std::string & mensaje);

	/*
	 * Retorna todos los bytes que se reciben hasta encontrar el caracter
	 * delimitador que no se retorna.
	 */
	std::string recibirDatos(char delimitador);

	/*
	 * Finaliza la transmision y cierra el socket
	 */
	void cerrarSocket();
};

#endif /* COMMON_SOCKETCOMUNICADOR_H_ */
