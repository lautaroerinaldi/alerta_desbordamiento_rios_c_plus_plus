/*
 * Parser.cpp
 */

#include "common_Parser.h"

#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <string>

Parser::Parser() :
		ip_cliente(""), puerto_cliente(""), nombre_seccion_cliente(""),
		cant_N_cliente(0), puerto_server("") {
}

/****************************************************************/
/******************* Métodos para el CONECTOR *******************/
/****************************************************************/

int Parser::parsearLineaComandosConector(int argc, char * argv[]) {
	if (argc == CANT_ARGS_ESPERADOS_CLIENTE) {
		this->ip_cliente = argv[1];
		this->puerto_cliente = argv[2];
		this->nombre_seccion_cliente = argv[3];
		this->cant_N_cliente = atoi(argv[4]);
		return PARAMETROS_OK;
	} else {
		return PARAMETROS_ERRONEOS;
	}
}

int Parser::getCantNCliente() const {
	return cant_N_cliente;
}

const std::string& Parser::getIpCliente() const {
	return ip_cliente;
}

const std::string& Parser::getNombreSeccionCliente() const {
	return nombre_seccion_cliente;
}

const std::string& Parser::getPuertoCliente() const {
	return puerto_cliente;
}

int Parser::parsearValoresCliente(const std::string & leido, int & nivel,
		int & caudal) {
	std::istringstream linea_leida(leido);
	char indic_nivel = 0;
	char indic_caudal = 0;
	int valor_nivel = 0;
	int valor_caudal = 0;
	linea_leida >> indic_nivel >> valor_nivel >> indic_caudal >> valor_caudal;
	if (linea_leida.eof() == 1 && linea_leida.fail() == 0 && indic_nivel == 'n'
			&& indic_caudal == 'c') {
		nivel = valor_nivel;
		caudal = valor_caudal;
		return PARSEO_OK;
	} else {
		// Valores mal ingresados"
		return PARSEO_ERROR;
	}
}

/**************************************************************/
/******************* Metodos para el SERVER *******************/
/**************************************************************/

int Parser::parsearValoresRecibidosServer(const std::string & leido,
		int & nivel, int & caudal) {
	std::istringstream linea_leida(leido);
	std::string indic_actualizar = "";
	std::string indic_nivel("");
	std::string indic_caudal("");
	int valor_nivel = 0;
	int valor_caudal = 0;
	linea_leida >> indic_actualizar >> indic_nivel >> valor_nivel
			>> indic_caudal >> valor_caudal;

	if (linea_leida.eof() == 1 && linea_leida.fail() == 0
			&& indic_actualizar == "actualizar" && indic_nivel == "nivel"
			&& indic_caudal == "caudal") {
		nivel = valor_nivel;
		caudal = valor_caudal;
		return PARSEO_OK;
	} else {
		// Valores mal ingresados"
		return PARSEO_ERROR;
	}
}

bool Parser::esConsultaPorSeccion(const std::string & leido,
		std::string & seccion) {
	std::istringstream linea_leida(leido);
	std::string indic_consulta = "";
	std::string indic_seccion = "";
	std::string valor_seccion("");
	linea_leida >> indic_consulta >> indic_seccion >> valor_seccion;

	if (linea_leida.eof() == 1 && linea_leida.fail() == 0
			&& indic_consulta == "consultar" && indic_seccion == "seccion") {
		seccion = valor_seccion;
		return SI;
	} else {
		return NO_O_ERROR;
	}
}

bool Parser::esConsultaGeneral(const std::string & leido) {
	std::istringstream linea_leida(leido);
	std::string indicador_consulta_gral("");
	linea_leida >> indicador_consulta_gral;
	if (linea_leida.eof() == 1 && linea_leida.fail() == 0
			&& indicador_consulta_gral == "consultar")
		return SI;
	else
		return NO_O_ERROR;
}

int Parser::parsearConsulta(const std::string & leido, std::string & seccion) {
	if (this->esConsultaGeneral(leido) == SI) {
		return CONSULTA_GENERAL;
	} else {
		if (this->esConsultaPorSeccion(leido, seccion) == SI) {
			return CONSULTA_POR_SECCION;
		} else {
			// consulta invalida o puede ser un mensaje del conector
			return CONSULTA_INVALIDA;
		}
	}
}

int Parser::parsearLineaComandosServer(int argc, char * argv[]) {
	if (argc == CANT_ARGS_ESPERADOS_SERVER) {
		this->puerto_server = argv[1];
		return PARAMETROS_OK;
	} else {
		return PARAMETROS_ERRONEOS;
	}
}

const std::string& Parser::getPuertoServer() const {
	return puerto_server;
}

std::string Parser::obtenerNombreSeccion(const std::string & encabezado) {
	std::istringstream mensaje(encabezado);
	std::string indic_conector;
	std::string indic_seccion;
	std::string nombre_seccion;
	mensaje >> indic_conector >> indic_seccion >> nombre_seccion;

	if (mensaje.eof() == 1 && mensaje.fail() == 0
			&& indic_conector == "conector" && indic_seccion == "seccion")
		return nombre_seccion;
	else
		return "";
}
