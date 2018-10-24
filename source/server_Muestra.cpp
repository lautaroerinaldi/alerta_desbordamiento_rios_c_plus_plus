/*
 * Muestra.cpp
 */

#include "server_Muestra.h"

#include <sstream>
#include <string>

Muestra::Muestra(const std::string & nombre, int nivel_moda, int caudal_moda) :
		nombre_seccion(nombre), nivel(nivel_moda), caudal(caudal_moda) {
}

int Muestra::getCaudal() const {
	return caudal;
}

int Muestra::getNivel() const {
	return nivel;
}

const std::string& Muestra::getNombreSeccion() const {
	return nombre_seccion;
}

std::string Muestra::toString() {
	std::ostringstream mensaje("");
	mensaje << "seccion " << this->nombre_seccion << " nivel " << this->nivel
			<< " caudal " << this->caudal;
	return mensaje.str();
}

void Muestra::setValores(int nivel_moda, int caudal_moda) {
	this->nivel = nivel_moda;
	this->caudal = caudal_moda;
}
