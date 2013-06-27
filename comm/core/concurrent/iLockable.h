#pragma once 

#include <pthread.h>
#include <sys/time.h>

#include "utils/iTypes.h"

namespace Comm
{
	class Lockable
    {
      protected:
        Lockable (const int& type = PTHREAD_MUTEX_DEFAULT);
        virtual ~Lockable ();

      public:
        void lock () const;
        void unlock () const;
        bool tryLock () const;

        int cond_wait (const uint32& timeout = 0) const;
        int cond_wait (const struct timeval& timeout) const;
        int cond_wait (const struct timespec& timeout) const;
        void cond_broadcast () const;
        void cond_signal () const;

      private:
        pthread_mutexattr_t     m_mutex_attr;
        mutable pthread_mutex_t m_mutex;
        mutable pthread_cond_t  m_cond;
    };
}
