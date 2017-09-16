/*
 * Lock.cpp
 *
 *  Created on: 02/07/2015
 *      Author: pablito
 */

#include "Lock.h"

namespace threads {

Lock::Lock(Mutex& m) : mutex(m) {
	mutex.lock();
}

Lock::~Lock() {
	mutex.unLock();
}

} /* namespace threadsa */
