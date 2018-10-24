/*
 * Parser.h
 */

#ifndef COMMON_PARSER_H_
#define COMMON_PARSER_H_

#include <string>

#define PARAMETROS_OK 0
#define PARAMETROS_ERRONEOS 1
#define CANT_ARGS_ESPERADOS_CLIENTE 5

#define CANT_ARGS_ESPERADOS_SERVER 2

#define PARSEO_OK 0
#define PARSEO_ERROR 1

#define SI true
#define NO_O_ERROR false

#define CONSULTA_GENERAL 0
#define CONSULTA_POR_SECCION 1
#define CONSULTA_INVALIDA 2

/*
 * Permite crear un objeto capaz de parsear las lineas de comandos del servidor
 * y del conector y retornar los valores de cada uno de los argumentos.
 */
class Parser {
	/*************************************************************************/
	/************* Métodos y Atributos Privados para el CONECTOR *************/
	/*************************************************************************/

	std::string ip_cliente;
	std::string puerto_cliente;
	std::string nombre_seccion_cliente;
	int cant_N_cliente;

	/************************************************************************/
	/*************** Métodos y Atributos Privados para SERVER ***************/
	/************************************************************************/

	std::string puerto_server;

	/*
	 * Dada un mensaje proveniente de un cliente externo (que es el que efectúa
	 * las consultas), define si esta se trata de una consulta por seccion
	 * retornando SI y modificando el valor de la variable seccion con el
	 * obtenido al parsear el mensaje recibido.
	 * En caso de que no se trate una consulta por seccion (o la consulta este
	 * mal formulada) retorna NO y no altera el valor de la variable seccion.
	 */
	bool esConsultaPorSeccion(const std::string & leido, std::string & seccion);

	/*
	 * Dada un mensaje proveniente de un cliente externo (que es el que efectúa
	 * las consultas), define si esta se trata de una consulta general
	 * retornando SI.
	 * En caso de que no se trate una consulta general (o la consulta este
	 * mal formulada) retorna NO.
	 */
	bool esConsultaGeneral(const std::string & leido);

public:
	/*
	 * Inicializa la instancia de la clase con valores validos
	 */
	Parser();

	/***********************************************************************/
	/****************** Métodos Públicos para el CONECTOR ******************/
	/***********************************************************************/

	/*
	 * Dados los valores de entrada de la Linea de Comandos argc y argv de un
	 * Cliente de tipo Conector, los interpreta y separa de forma tal que luego
	 * puedan solictarse (Gets) uno a uno.
	 * Retorna PARAMETROS_OK si argc coincide con la cantidad de argumentos
	 * esperados, y PARAMETROS_ERRONEOS en otro caso.
	 */
	int parsearLineaComandosConector(int argc, char ** argv);

	/*
	 * Si previamente se llamo a parsearEntradaCliente y esta retornó
	 * PARAMETROS_OK, retorna la cantidad N de clientes que se obtuvo al
	 * parsear la línea de comandos del cliente conector y retorna 0 en otro
	 * caso.
	 */
	int getCantNCliente() const;

	/*
	 * Si previamente se llamo a parsearEntradaCliente y esta retornó
	 * PARAMETROS_OK, retorna la IP o HOSTNAME que se obtuvo al
	 * parsear la línea de comandos del cliente conector y retorna "" en otro
	 * caso.
	 */
	const std::string& getIpCliente() const;

	/*
	 * Si previamente se llamo a parsearEntradaCliente y esta retornó
	 * PARAMETROS_OK, retorna el NOMBRE DE SECCION que se obtuvo al
	 * parsear la línea de comandos del cliente conector y retorna "" en otro
	 * caso.
	 */
	const std::string& getNombreSeccionCliente() const;

	/*
	 * Si previamente se llamo a parsearEntradaCliente y esta retornó
	 * PARAMETROS_OK, retorna el PUERTO o SERVICENAME que se obtuvo al
	 * parsear la línea de comandos del cliente conector y retorna "" en otro
	 * caso.
	 */
	const std::string& getPuertoCliente() const;

	/*
	 * En leido recibe toda una linea leida en donde deberian encontrarse los
	 * valores que un conector leyo. Si la linea se encuentra bien formada
	 * escribe en las variables nivel y caudal los valores parseados y retorna
	 * PARSEO_OK, en otro caso no modifica las variables nivel y caudal, escribe
	 * por STDERR "Valores mal ingresados" y retorna PARSEO_ERROR
	 */
	int parsearValoresCliente(const std::string & leido, int & nivel,
			int & caudal);

	/********************************************************************/
	/******************* Métodos Públicos para SERVER *******************/
	/********************************************************************/

	/*
	 * Dados los valores de entrada de la Linea de Comandos argc y argv del
	 * Server, los interpreta y separa de forma tal que luego
	 * puedan solictarse (Gets) uno a uno.
	 * Retorna PARAMETROS_OK si argc coincide con la cantidad de argumentos
	 * esperados, y PARAMETROS_ERRONEOS en otro caso.
	 */
	int parsearLineaComandosServer(int argc, char ** argv);

	/*
	 * Si previamente se llamo a parsearEntradaServer y esta retornó
	 * PARAMETROS_OK, retorna la IP o HOSTNAME que se obtuvo al
	 * parsear la línea de comandos del server y retorna "" en otro
	 * caso.
	 */
	const std::string& getPuertoServer() const;

	/*
	 * Dados los valores de entrada de la Linea de Comandos argc y argv de un
	 * Server, los interpreta y separa de forma tal que luego
	 * puedan solictarse (Gets) uno a uno.
	 * Retorna PARAMETROS_OK si argc coincide con la cantidad de argumentos
	 * esperados, y PARAMETROS_ERRONEOS en otro caso.
	 */
	int parsearValoresRecibidosServer(const std::string & leido, int & nivel,
			int & caudal);

	/*
	 * Dada un mensaje proveniente de un cliente externo (que es el que efectúa
	 * las consultas), define de que tipo de consulta se trata retornando
	 * CONSULTA_GENERAL, CONSULTA_POR_SECCION o CONSULTA_INVALIDA según
	 * corresponda. Si se trata de una consulta por seccion, modifica el valor
	 * de la variable seccion con el obtenido al parsear el mensaje recibido.
	 */
	int parsearConsulta(const std::string & leido, std::string & seccion);

	/*
	 * Dado el texto del encabezado que envia un conector apenas se conecta,
	 * retorna el nombre de la seccion
	 */
	std::string obtenerNombreSeccion(const std::string & encabezado);
};

#endif /* COMMON_PARSER_H_ */
