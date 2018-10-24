/*
 * Server.cpp
 */

#include "server_Server.h"
#include <string>
#include <list>

Server::Server(Parser & parser, const std::string & puerto,
		int cant_clientes_en_cola) :
		parser(parser), skt_server(puerto, cant_clientes_en_cola), vivo(true) {
}

void Server::agregarCliente(SocketComunicador * un_cliente) {
	ManejadorDeCliente * primer_cliente = new ManejadorDeCliente(
			this->admin_rio, un_cliente, this->parser);
	primer_cliente->start();
	this->lista_clientes.push_back(primer_cliente);
}

void Server::run() {
	while (this->vivo) {
		SocketComunicador * un_cliente = NULL;
		un_cliente = this->skt_server.aceptarConexion();
		if (un_cliente != NULL) {
			this->agregarCliente(un_cliente);
			this->recolectarClientesMuertos();
		}
	}
}

void Server::recolectarClientesMuertos() {
	for (std::list<ManejadorDeCliente *>::iterator it =
			this->lista_clientes.begin(); it != this->lista_clientes.end();
			++it) {
		if (!(*it)->estaActivo()) {
			(*it)->join();
			delete (*it);
			(*it) = NULL;
			it = this->lista_clientes.erase(it);
		}
	}
}

void Server::recolectarTodosLosClientes() {
	for (std::list<ManejadorDeCliente *>::iterator it =
			this->lista_clientes.begin(); it != this->lista_clientes.end();
			++it) {
		(*it)->apagarConexion();
		(*it)->join();
		delete (*it);
		(*it) = NULL;
		it = this->lista_clientes.erase(it);
	}
}

void Server::apagar() {
	this->vivo = false;
	this->skt_server.cerrarSocket();
	this->recolectarClientesMuertos();
	this->recolectarTodosLosClientes();
}
