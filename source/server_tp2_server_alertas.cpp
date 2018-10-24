#include "common_Parser.h"
#include <iostream>
#include "server_Server.h"

#define OK 0
#define ERROR 1
#define CANT_CLIENTES_EN_COLA 10

/*
 * El server recibe al iniciarse: <puerto>
 */
int main(int argc, char * argv[]) {
	Parser parser;

	if (parser.parsearLineaComandosServer(argc, argv) == PARAMETROS_OK) {
		Server server(parser, parser.getPuertoServer(), CANT_CLIENTES_EN_COLA);
		server.start();
		char caracter = 0;
		do {
			caracter = std::cin.get();
		} while (caracter != 'q');
		server.apagar();
		server.join();
		return OK;
	} else {
		// Hay un error en los parametros de conexion
		return ERROR;
	}
}
