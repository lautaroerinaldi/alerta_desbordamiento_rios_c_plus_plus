/*
 * ManejadorDeCliente.cpp
 */

#include "server_ManejadorDeCliente.h"
#include <string>

ManejadorDeCliente::ManejadorDeCliente(AdministradorEstadoRio & admin_rio,
		SocketComunicador * socket, Parser & parser) :
		admin_rio(admin_rio), cliente_skt(socket), parser(parser), nombre_seccion(
				""), vivo(true) {
}

bool ManejadorDeCliente::estaActivo() {
	return this->vivo;
}

void ManejadorDeCliente::run() {
	// recibo y parseo el mensaje en el que el conector informa el nombre
	// de la seccion a la que pertenece
	std::string mensaje(this->cliente_skt->recibirDatos('\n'));

	int tipo_cliente = this->parser.parsearConsulta(mensaje,
			this->nombre_seccion);
	switch (tipo_cliente) {
	case CONSULTA_GENERAL:
		this->cliente_skt->enviarDatos(admin_rio.responderConsultaGeneral());
		break;
	case CONSULTA_POR_SECCION:
		this->cliente_skt->enviarDatos(
				admin_rio.responderConsultaPorSeccion(this->nombre_seccion));
		break;
	default:
		// preguntar si es un conector
		// ahora el parser muestra valores mal ingresador por cerr si falla
		this->nombre_seccion = this->parser.obtenerNombreSeccion(mensaje);
		if (this->nombre_seccion != "") {
			int nivel_moda = 0;
			int caudal_moda = 0;
			// Tiene que salir cuando se ingrese q por entrada estandar
			while (this->vivo) {
				mensaje = this->cliente_skt->recibirDatos('\n');
				if (mensaje != "fin" && mensaje != "") {
					this->parser.parsearValoresRecibidosServer(mensaje,
							nivel_moda, caudal_moda);
					admin_rio.actualizarMuestra(nombre_seccion, nivel_moda,
							caudal_moda);
				} else {
					// si llego fin, es porque se cerro la entrada estandar del conector
					// si llego "" hubo un error y nos cerraron el socket
					this->apagarConexion();
				}
			}
		}
	}
	this->apagarConexion();
	this->liberarSocket();
}

void ManejadorDeCliente::liberarSocket() {
	delete this->cliente_skt;
	this->cliente_skt = NULL;
}

void ManejadorDeCliente::apagarConexion() {
	this->vivo = false;
	if (this->cliente_skt->conexionValida())
		this->cliente_skt->cerrarSocket();
}
