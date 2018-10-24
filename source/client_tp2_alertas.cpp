#include <iostream>

#include "client_Conector.h"
#include "common_Parser.h"
#include <string>

#define OK 0
#define ERROR 1
#define CANT_CHAR_ENTRADA 512

/*
 * El conector recibe al iniciarse: <ip> <hostname> <seccion> <N>
 * Las muestras llegan como: n <nivel> c <caudal>\n
 */
int main(int argc, char * argv[]) {
	Parser parser;

	if (parser.parsearLineaComandosConector(argc, argv) == PARAMETROS_OK) {
		Conector conector(parser.getIpCliente(), parser.getPuertoCliente(),
				parser.getNombreSeccionCliente(), parser.getCantNCliente());
		if (conector.conexionExitosa()) {
			int nivel_leido = 0;
			int caudal_leido = 0;
			char linea_leida[CANT_CHAR_ENTRADA] = "";
			std::cin.getline(linea_leida, CANT_CHAR_ENTRADA, '\n');
			std::string leido(linea_leida);
			while (!std::cin.fail()) {
				if (parser.parsearValoresCliente(leido, nivel_leido,
						caudal_leido) == PARSEO_OK)
					conector.procesarMuestra(nivel_leido, caudal_leido);
				std::cin.getline(linea_leida, CANT_CHAR_ENTRADA, '\n');
				leido = linea_leida;
			}
			return OK;
		} else {
			// No se pudo efectuar la conexión con el servidor
			return ERROR;
		}
	} else {
		return ERROR;
	}
}
