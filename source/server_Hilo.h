/*
 * Hilo.h
 */

#ifndef SERVER_HILO_H_
#define SERVER_HILO_H_

#include <pthread.h>

/*
 * Clase que encapsula el manejo de Threads de C.
 * Basta con heredar de ella y llamar al método start para que se lance un
 * nuevo hilo y se ejecute el código que definen las "hijas" para el metodo run
 */
class Hilo {
	pthread_t hilo;
	static void * starter(void * data);

protected:
	/*
	 * Hago que la clase sea abstracta, es decir, cualquier clase que herede
	 * de Hilo tiene que implementar el método run si o sí.
	 * Este método debe redefinirse en las clases hijas y es el código que va
	 * a ejecutarse en un nuevo hilo luego de llamar al método start().
	 */
	virtual void run()=0;

public:
	/*
	 * Inicializa los atributos de la clase
	 */
	Hilo();

	/*
	 * Libera los recursos utilizados por la clase
	 */
	virtual ~Hilo();

	/*
	 * Lanza un nuevo hilo, e invoca al método run() que debe definirse
	 * obligatoriamente en la clases que hereden.
	 */
	void start();

	/*
	 * Joinea el hilo que fue lanzado por start()
	 */
	void join();
};

#endif /* SERVER_HILO_H_ */
