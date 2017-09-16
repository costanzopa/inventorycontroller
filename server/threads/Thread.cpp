/*
 * Thread.cpp
 *
 *  Created on: 27/05/2015
 *      Author: pablito
 */

#include "Thread.h"

namespace threads {

void *Thread::execute(void *pThread) {
	return ((Thread *) pThread)->process();
}
Thread::Thread() {
	this->setRunning(false);
	this->thread = 0;
}

Thread::~Thread() {
	try {
		this->close();
	} catch (exceptions::ThreadException& e) {
	}
}

bool Thread::isRunning() {
	return (this->running);
}

void Thread::start() {
	if (this->getRunning() == false) {
	    if (::pthread_create(&thread, NULL, &execute, this) != 0) {
	       throw exceptions::ThreadException("ERROR al crear el thread.");
	    }
	    this->setRunning(true);
	    } else {
	      throw exceptions::ThreadException("ERROR thread ya iniciado.");
	    }
}

void Thread::stop() {
	 this->setRunning(false);
}

void Thread::close() {
	if ((this->getRunning() == true)) {
	      if (::pthread_join(thread, NULL) != 0) {
	        throw exceptions::ThreadException("ERROR join hilo");
	      }
	 } else {
	      throw exceptions::ThreadException("ERROR hilo cerrado");
	 }
}

void Thread::setRunning(const bool running) {
	this->running = running;
}

const bool& Thread::getRunning() const {
	return this->running;
}
} /* namespace threads */
