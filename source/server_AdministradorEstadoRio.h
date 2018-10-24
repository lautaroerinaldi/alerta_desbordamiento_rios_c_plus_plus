/*
 * AdministradorEstadoRio.h
 */

#ifndef ADMINISTRADOR_ESTADO_RIO_H_
#define ADMINISTRADOR_ESTADO_RIO_H_

#include "server_Lock.h"
#include "server_Muestra.h"
#include "server_Mutex.h"

#include <string>
#include <map>

/*
 * Clase que mantiene los últimos valores de las modas de nivel y caudal
 * enviados por los conectores y que se encarga de responder las consultas
 * generales o por seccion.
 */
class AdministradorEstadoRio {
	std::map<std::string, Muestra> estado_rio;
	Mutex mutex;

public:
	/*
	 * Si el conector con nombre <nombre_seccion> ya ha enviado alguna muestra
	 * al Servidor, actualiza los valores de nivel y caudal de ese conector.
	 * Si en cambio, es la primer muestra que envia el conector con nombre
	 * <nombre_seccion> agrega la muestra para ese conector con los valores
	 * nivel y caudal pasados por parametro.
	 */
	void actualizarMuestra(const std::string & nombre_seccion, int nivel_moda,
			int caudal_moda);

	/*
	 * Retorna el estado actual del rio, listando para cada seccion el
	 * último valor de la moda de nivel y el último valor de la moda de caudal
	 * enviados. Se listan en orden alfabético por nombre de sección.
	 * El formato es:
	 * 		respuesta\n
	 * 		seccion <nombre_seccion> nivel <nivel_moda> caudal <caudal_moda>\n
	 * 		seccion <nombre_seccion> nivel <nivel_moda> caudal <caudal_moda>\n
	 * 		...
	 * 		seccion <nombre_seccion> nivel <nivel_moda> caudal <caudal_moda>\n
	 * 		fin\n
	 * 	En caso de no haber recibido ninguna muestra de ningún conector aún,
	 * 	igualmente retorna:
	 * 		respuesta\n
	 * 		fin\n
	 */
	std::string responderConsultaGeneral();

	/*
	 * Retorna el estado actual de una determinada seccion del rio con formato:
	 * 		respuesta\n
	 * 		seccion <nombre_seccion> nivel <nivel_moda> caudal <caudal_moda>\n
	 * 		fin\n
	 * 	Si dicho conector con ese nombre de seccion no ha enviado ninguna
	 * 	muestra, igualmente retorna:
	 * 		respuesta\n
	 * 		fin\n
	 */
	std::string responderConsultaPorSeccion(const std::string & nombre_seccion);
};

#endif /* ADMINISTRADOR_ESTADO_RIO_H_ */
