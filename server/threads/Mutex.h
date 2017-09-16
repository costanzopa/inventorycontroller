/*
 * Mutex.h
 *	Encapsula a un mutex en una clase.
 *  Created on:
 *      Author:
 */

#ifndef SERVER_MUTEX_H_
#define SERVER_MUTEX_H_

#include <pthread.h>
#include "../../common/Exception.h"

namespace threads {
enum MutexInicializarModo {
    MUTEX_DEFAULT = 0, MUTEX_ERRORCHECK = 1
  };

class Mutex {
private:
      pthread_mutex_t mutex;

      Mutex(const Mutex &mutex);
      Mutex& operator=(const Mutex &mutex);

public:
      /**
       * Intenta crear y abrir un mutex en modo "ERRORCHECK",
       * que brinda mayor ayuda para depurar errores que el modo "DEFAULT"
       */
      Mutex();
      explicit Mutex(const MutexInicializarModo modo);
      virtual ~Mutex() throw();
      /**
       * Intenta tomar el mutex. Si el mutex ya esta tomado por otro hilo,
       *  el hilo que invoco la función sera bloqueado hasta que el mutex
       *  sea liberado, y una vez que esto ocurra,
       *  lo intentara tomar nuevamente.
       */
      virtual void lock();
      /**
       * Intenta liberar el mutex.
       */
      virtual void unLock();
 };
}
#endif /* SERVER_MUTEX_H_ */
