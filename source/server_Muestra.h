/*
 * Muestra.h
 */

#ifndef SERVER_MUESTRA_H_
#define SERVER_MUESTRA_H_

#include <string>

/*
 * Clase que encapsula las valores nivel y caudal que se corresponden a un
 * conector en particular que tiene un nombre determinado nombre.
 */
class Muestra {
	std::string nombre_seccion;
	int nivel;
	int caudal;

public:
	/*
	 * Inicializa la clase con los atributos nombre del conector, y con los
	 * valores nivel_moda y caudal_moda para nivel y caudal respectivamente.
	 * Una vez que a una muestra se le ha fijado un nombre de seccion, este
	 * no puede modificarse.
	 */
	explicit Muestra(const std::string & nombre, int nivel_moda,
			int caudal_moda);

	/*
	 * Retorna los atributos de la clase en un string con el formato:
	 * 		seccion <nombre_seccion> nivel <nivel> caudal <caudal>
	 * obs: no se devuelve un salto de linea al final
	 */
	std::string toString();

	/*
	 * Retorna el valor numérico que tiene el caudal
	 */
	int getCaudal() const;

	/*
	 * Retorna el valor numérico que tiene el nivel
	 */
	int getNivel() const;

	/*
	 * Se actualizan los valores nivel y caudal previos con los valores
	 * nivel_moda y caudal_moda pasados por parametro.
	 * El nombre de seccion permanece inalterado.
	 */
	void setValores(int nivel_moda, int caudal_moda);

	/*
	 * Retorna el nombre de seccion al que corresponden las muestras que ha
	 * sido especificado en el constructor.
	 */
	const std::string& getNombreSeccion() const;
};

#endif /* SERVER_MUESTRA_H_ */
