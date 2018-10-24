/*
 * Server.h
 */

#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include "common_Parser.h"
#include <list>
#include <string>
#include "server_AdministradorEstadoRio.h"
#include "server_Hilo.h"
#include "server_ManejadorDeCliente.h"
#include "server_SocketAceptador.h"

/*
 * Clase que implementa el server que acepta coneciones de los conectores y
 * contesta las consultas sobre el estado del rio.
 */
class Server: public Hilo {
	Parser & parser;
	SocketAceptador skt_server;
	AdministradorEstadoRio admin_rio;
	std::list<ManejadorDeCliente *> lista_clientes;
	bool vivo;

	/*
	 * Dado un socket de comunicación, crea un Manejador de Cliente con este
	 * socket y lo agrega a la lista de manejadores.
	 */
	void agregarCliente(SocketComunicador * un_cliente);

	/*
	 * Recorre la lista de manejadores de clientes y luego libera los recursos
	 * y borra de la lista a todos los clientes que no están activos (es decir,
	 * los que se joinearon solos porque ya terminaron su tarea)
	 */
	void recolectarClientesMuertos();

	/*
	 * Recorre la lista de manejadores de clientes y luego libera los recursos
	 * y borra de la lista a todos los clientes.
	 */
	void recolectarTodosLosClientes();

public:
	/*
	 * Inicializa los atributos de la clase con lor valores recibidos
	 */
	Server(Parser & parser, const std::string & puerto,
			int cant_clientes_en_cola);

	/*
	 * Implementa el método virtual de la clase padre Hilo.
	 * Empieza a aceptar conexiones entrantes por el server, aceptando nuevos
	 * clientes y creando los manejadores necesarios. Cada vez que se acepta
	 * un nuevo cliente, recolecta los clientes inactivos.
	 */
	void run();

	/*
	 * Cierra el socket aceptador y a partir de ese momento no se pueden
	 * aceptar más conexiones entrantes. Luego recolecta todos los clientes
	 */
	void apagar();
};

#endif /* SERVER_SERVER_H_ */
