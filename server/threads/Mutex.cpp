/*
 * server_Mutex.cpp
 *
 *  Created on: 25/04/2015
 *      Author: pablito
 */

#include "Mutex.h"

namespace threads {

Mutex::Mutex() {
    pthread_mutexattr_t mutexAtrib;
    if (::pthread_mutexattr_init(&mutexAtrib) != 0) {
      throw exceptions::ThreadException("Error en la inicializacion del mutex.");
    }
    if (::pthread_mutexattr_settype(&mutexAtrib,
    		PTHREAD_MUTEX_ERRORCHECK) != 0) {
      ::pthread_mutexattr_destroy(&mutexAtrib);
      throw exceptions::ThreadException("Error en la inicializacion del mutex.");
    }
    if (::pthread_mutex_init(&mutex, &mutexAtrib) != 0) {
      ::pthread_mutexattr_destroy(&mutexAtrib);
      throw exceptions::ThreadException("Error en la destruccion del mutex.");
    }
    if (::pthread_mutexattr_destroy(&mutexAtrib) != 0) {
      ::pthread_mutex_destroy(&mutex);
      throw exceptions::ThreadException("Error en la destruccion del mutex.");
    }
  }

  Mutex::Mutex(const MutexInicializarModo modo) {
    switch (modo) {
      case MUTEX_DEFAULT:
        if (::pthread_mutex_init(&mutex, NULL) != 0) {
          throw exceptions::ThreadException("Error en la inicializacion del mutex.");
        }
        break;
      case MUTEX_ERRORCHECK:
        Mutex();
        break;
      default:
        throw exceptions::ThreadException("Error en la creacion del mutex.");
        break;
    }
  }

  Mutex::~Mutex() throw() {
	  ::pthread_mutex_destroy(&mutex);
  }

  void Mutex::lock() {
    if (::pthread_mutex_lock(&mutex) != 0) {
      throw exceptions::ThreadException("Error en la tomar del mutex.");
    }
  }

  void Mutex::unLock() {
    if (::pthread_mutex_unlock(&mutex) != 0) {
      throw exceptions::ThreadException("Error en la liberar del mutex.");
    }
  }
}
