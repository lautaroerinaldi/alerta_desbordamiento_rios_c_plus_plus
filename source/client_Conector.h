/*
 * Conector.h
 */

#ifndef CLIENT_CONECTOR_H_
#define CLIENT_CONECTOR_H_

#include <string>
#include <map>

#include "common_SocketComunicador.h"

#define OK 0
#define ERROR 1

/*
 * Permite crear un objeto que dadas las muestras que va recibiendo, calcula y
 * envia las modas al servidor mediantes una conexion utilizando un socket.
 */
class Conector {
	std::string nombre_seccion;
	unsigned int cant_muestras_para_moda;
	std::map<int, int> niveles;
	std::map<int, int> caudales;
	unsigned int cant_muestras_leidas;
	SocketComunicador socket;

	/*
	 * Dado un mapa que tiene la cantidad EXACTA de muestras necesaria para
	 * calcular la moda, lo recorre y devuelve el valor que tiene frecuencia
	 * máxima; en caso de empate en frecuencia, retorna la de mayor módulo.
	 */
	int getModa(std::map<int, int> & mapa);

	/*
	 * Envía al server datos procesados (las muestras MODA DE NIVEL y CAUDAL).
	 * Estas muestras MODA son las que se reciben por parametro
	 * Vendría a ser el mensaje "actualizar nivel <xxxx> caudal <yyyy>\n"
	 */
	int actualizar(int nivel, int caudal);

	/*
	 * Envía al server el mensaje inicial informando el nombre de seccion;
	 * Vendría a ser el encabezado "conector seccion <xxxx>\n"
	 */
	int informarSeccion();

	/*
	 * Envía al server el mensaje final antes de que se cierre la conexion;
	 * Vendría a ser el mensaje de despedida "fin\n"
	 */
	int finalizar();

public:
	/*
	 * Inicializa la clase y abre un socket de comunicacion en la IP y puerto
	 * pasados por parametro. Luego envia el nombre de seccion al servidor.
	 */
	Conector(const std::string & ip, const std::string & puerto,
			const std::string & nombre_seccion,
			unsigned int cant_muestras_para_moda);

	/* Dados un valor de nivel y caudal, las almacena en el mapa y actualiza
	 * su frecuencia de aparición. En caso de que se hayan alcanzado el numero
	 * de muestras EXACTAS para calcular la moda, las obtiene, las envia al
	 * server y reinicia el mapa y las cuentas de frecuencias de niveles y
	 * caudales.
	 * Supone que la conexion con el servidor es valida (puede consultarse
	 * desde fuera con el metodo conexionExitosa().
	 */
	void procesarMuestra(int nivel_leido, int caudal_leido);

	/*
	 * Retorna true si la conexion con el server fue exitosa y false en otro
	 * caso
	 */
	bool conexionExitosa();

	/*
	 * Envia el mensaje de finalizar transmision al servidor, cierra el socket
	 * de conexion y libera los recursos utilizados por el conector.
	 */
	~Conector();
};

#endif /* CLIENT_CONECTOR_H_ */
