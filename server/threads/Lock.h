/*
 * Lock.h
 *
 *  Created on: 02/07/2015
 *      Author: pablito
 */

#ifndef LOCK_H_
#define LOCK_H_
#include "Mutex.h"

namespace threads {

class Lock {
public:
	Lock(Mutex& m);
	virtual ~Lock();
private:
	Mutex& mutex;

	Lock(const Lock &mutex);
	Lock& operator=(const Lock &mutex);
	Lock();
};

} /* namespace threadsa */
#endif /* LOCK_H_ */
