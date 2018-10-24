/*
 * Lock.h
 */

#ifndef SERVER_LOCK_H_
#define SERVER_LOCK_H_

#include "server_Mutex.h"

/*
 * Aplica RAII sobre una instancia de la clase Mutex
 */
class Lock {
	Mutex & mutex;

public:
	/*
	 * Recibe por referencia un Mutex previamente inicializado en estado
	 * desbloqueado y luego lo bloquea (toma la llave binaria)
	 */
	explicit Lock(Mutex & mutex);

	/*
	 * Libera el Mutex bloqueado por el constructor.
	 */
	virtual ~Lock();
};

#endif /* SERVER_LOCK_H_ */
