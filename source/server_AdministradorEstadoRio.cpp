/*
 * AdministradorEstadoRio.cpp
 */
#include "server_AdministradorEstadoRio.h"

#include <iostream>
#include <sstream>
#include <utility>
#include <map>
#include <string>

void AdministradorEstadoRio::actualizarMuestra(
		const std::string& nombre_seccion, int nivel_moda, int caudal_moda) {
	Lock lock(this->mutex);

	std::pair<std::map<std::string, Muestra>::iterator, bool> ret;
	// si el map no tiene un conector con ese nombre de seccion lo agrega
	ret = this->estado_rio.insert(
			std::pair<std::string, Muestra>(nombre_seccion,
					Muestra(nombre_seccion, nivel_moda, caudal_moda)));

	// pero si el elemento ya estaba, retorna un iterador a ese elemento del map
	if (ret.second == false) {
		// como ya estaba, no hay que agregarlo, sino actualizar los valores
		ret.first->second.setValores(nivel_moda, caudal_moda);
	}
}

std::string AdministradorEstadoRio::responderConsultaGeneral() {
	Lock lock(this->mutex);
	std::ostringstream respuesta("");
	respuesta << "respuesta" << std::endl;
	// recorro la totalidad del map y muestro sus valores
	for (std::map<std::string, Muestra>::iterator it = this->estado_rio.begin();
			it != this->estado_rio.end(); ++it) {
		respuesta << it->second.toString() << std::endl;
	}
	respuesta << "fin" << std::endl;

	return respuesta.str();
}

std::string AdministradorEstadoRio::responderConsultaPorSeccion(
		const std::string& nombre_seccion) {
	Lock lock(this->mutex);
	std::ostringstream respuesta("");
	respuesta << "respuesta" << std::endl;
	std::map<std::string, Muestra>::iterator it;
	it = this->estado_rio.find(nombre_seccion);
	// si el map contenia alguna muestra para ese nombre de seccion, se muestra
	if (it != this->estado_rio.end())
		respuesta << it->second.toString() << std::endl;
	respuesta << "fin" << std::endl;

	return respuesta.str();
}
