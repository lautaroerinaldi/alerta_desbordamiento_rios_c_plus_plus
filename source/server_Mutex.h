/*
 * Mutex.h
 */

#ifndef SERVER_MUTEX_H_
#define SERVER_MUTEX_H_
#include <pthread.h>

/*
 * Clase que encapsula el manejo de Semáforos Binarios (mutex) de C.
 */
class Mutex {
	pthread_mutex_t mutex;

public:
	/*
	 * Inicializa los un semáforo binario en estado desbloqueado
	 */
	Mutex();

	/*
	 * Libera los recursos utilizados por la clase
	 */
	virtual ~Mutex();

	/*
	 * Bloquea el semáforo binario
	 */
	void lock();

	/*
	 * Desbloquea el semáforo binario
	 */
	void unlock();
};

#endif /* SERVER_MUTEX_H_ */
