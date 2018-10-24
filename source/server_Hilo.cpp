/*
 * Hilo.cpp
 */

#include "server_Hilo.h"

#include <iostream>

void * Hilo::starter(void * data) {
	Hilo * realthread = (Hilo *) data;
	realthread->run();
	return NULL;
}

Hilo::Hilo() {
	this->hilo = 0;
}

Hilo::~Hilo() {
}

void Hilo::start() {
	pthread_create(&this->hilo, NULL, Hilo::starter, this);
}

void Hilo::join() {
	pthread_join(this->hilo, NULL);
}
