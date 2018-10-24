/*
 * ManejadorDeCliente.h
 */

#ifndef SERVER_MANEJADORDECLIENTE_H_
#define SERVER_MANEJADORDECLIENTE_H_

#include "common_Parser.h"
#include "common_SocketComunicador.h"

#include "server_AdministradorEstadoRio.h"
#include "server_Hilo.h"

#include <string>

/*
 * Clase que administra los mensajes recibidos o a enviar por los clientes que
 * se conectan al server.
 */
class ManejadorDeCliente: public Hilo {
	AdministradorEstadoRio & admin_rio;
	SocketComunicador * cliente_skt;
	Parser & parser;
	std::string nombre_seccion;
	bool vivo;

	/*
	 * Libera la memoria dinámica utilizada por el socket recibido com
	 * argumento del constructor.
	 */
	void liberarSocket();

public:
	/*
	 * Inicializa la clase con los atributos recibidos
	 */
	ManejadorDeCliente(AdministradorEstadoRio & admin_rio,
			SocketComunicador * socket, Parser & parser);

	/*
	 * Si el socket de comunicación recibido en el constructor corresponde a
	 * un conector, recibe los valores de nivel y caudal que que el conector
	 * va enviando y los agrega en las estructuras necesarias para mantener
	 * actualizado el estado del rio.
	 *
	 * Si el socket de comunicacion recibido en el constructor corresponde a un
	 * cliente que va a efectuar una consulta, envia el estado del rio o de la
	 * seccion según el tipo de consulta que reciba y luego cierra el socket
	 * de comunicacion, y marca al cliente como inactivo.
	 *
	 * En cualquier caso, luego de que se haya cerrado el socket de comunicación
	 * ya sea porque hubo un error, ya se haya contestado la consulta o no se
	 * reciban más datos del conector, joinea el hilo.
	 */
	void run();

	/*
	 * Retorna "true" en caso de que el cliente tenga su socket de comunicación
	 * abierto y se sigan enviando (cliente) o recibiendo mensajes (conector).
	 * En caso de que ya se haya contestado la consulta o se haya cerrado el
	 * conector y por ende este no envia más mensajes, retorna "false".
	 */
	bool estaActivo();

	/*
	 * Establece al manejador como inactivo (vivo = false) y cierra el socket
	 * de comunicacion
	 */
	void apagarConexion();
};

#endif /* SERVER_MANEJADORDECLIENTE_H_ */
