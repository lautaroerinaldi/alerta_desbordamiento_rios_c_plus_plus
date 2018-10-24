/*
 * Conector.cpp
 */

#include "client_Conector.h"

#include <sstream>
#include <map>
#include <string>

Conector::Conector(const std::string & ip, const std::string & puerto,
		const std::string & nombre_seccion,
		unsigned int cant_muestras_para_moda) :
		nombre_seccion(nombre_seccion), cant_muestras_para_moda(
				cant_muestras_para_moda), cant_muestras_leidas(0), socket(ip,
				puerto) {
	this->informarSeccion();
}

int Conector::actualizar(int nivel, int caudal) {
	std::ostringstream mensaje;
	mensaje << "actualizar nivel " << nivel << " caudal " << caudal
			<< std::endl;
	this->socket.enviarDatos(mensaje.str());
	return OK;
}

int Conector::finalizar() {
	std::ostringstream mensaje;
	mensaje << "fin" << std::endl;
	this->socket.enviarDatos(mensaje.str());
	return OK;
}

int Conector::informarSeccion() {
	std::ostringstream mensaje;
	mensaje << "conector seccion " << this->nombre_seccion << std::endl;
	this->socket.enviarDatos(mensaje.str());
	return OK;
}

int Conector::getModa(std::map<int, int> & mapa) {
	int frec_max;
	int valor_max;
	std::map<int, int>::iterator it;
	it = mapa.begin();
	valor_max = 0;
	frec_max = 0;

	for (it = mapa.begin(); it != mapa.end(); ++it) {
		if (it->second >= frec_max) {
			if (it->second > frec_max) {
				valor_max = it->first;
				frec_max = it->second;
			} else {
				if (it->first > valor_max) {
					valor_max = it->first;
					frec_max = it->second;
				}
			}
		}
	}
	return valor_max;
}

void Conector::procesarMuestra(int nivel_leido, int caudal_leido) {
	++this->cant_muestras_leidas;
	++niveles[nivel_leido];	// sumo 1 a la frecuencia del nivel leido
	++caudales[caudal_leido];	// sumo 1 a la frecuencia del caudal leido

	// si ya lei suficientes muestras (N) como para calcular la moda
	if (this->cant_muestras_para_moda == this->cant_muestras_leidas) {
		// Busco el nivel más frecuente
		int nivel_moda = getModa(this->niveles);
		// Busco el caudal más frecuente
		int caudal_moda = getModa(this->caudales);
		// envio los valores de nivel y caudal
		this->actualizar(nivel_moda, caudal_moda);

		// limpio el map de niveles, vuelve a iniciar la cuenta
		this->niveles.clear();
		// limpio el map de caudales, vuelve a iniciar la cuenta
		this->caudales.clear();
		// reinicio la cuenta de niveles y caudales leidos
		this->cant_muestras_leidas = 0;
	}
}

bool Conector::conexionExitosa() {
	return (this->socket.conexionValida());
}

Conector::~Conector() {
	this->finalizar();
	this->socket.cerrarSocket();
}
