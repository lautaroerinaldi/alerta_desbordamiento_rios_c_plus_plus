/*
 * Lock.cpp
 */

#include "server_Lock.h"

Lock::Lock(Mutex & mutex) :
		mutex(mutex) {
	this->mutex.lock();
}

Lock::~Lock() {
	this->mutex.unlock();
}

