/*
 * Thread.h
 *
 *  Created on: 27/05/2015
 *      Author: pablito
 */

#ifndef THREAD_H_
#define THREAD_H_
#include <iostream>
#include "../../common/Exception.h"
#include <pthread.h>

namespace threads {

class Thread {
public:
	Thread();
	virtual ~Thread();
	bool isRunning();
	virtual void start();
	virtual void stop();
	const bool& getRunning() const;

private:
	//Metodos Privados
	void close();
	virtual void* process()=0;
	static void *execute(void *pThread);
	void setRunning(const bool running);
	//Miembros de clase
	bool running;
	pthread_t thread;

	Thread(const Thread &thread);
	Thread& operator=(const Thread &thread);
};

} /* namespace threads */
#endif /* THREAD_H_ */
