#include "iLockable.h"

#include <cstring>
#include <unistd.h>
#include <sys/time.h>

namespace Comm
{
	Lockable::Lockable (const int& type)
	  : m_mutex_attr (), m_mutex (), m_cond ()
	{
	  pthread_mutexattr_init (&m_mutex_attr);
	  pthread_mutexattr_settype (&m_mutex_attr, type);
	  pthread_mutex_init (&m_mutex, &m_mutex_attr);
	  pthread_cond_init (&m_cond, NULL);
	}

	Lockable::~Lockable ()
	{
	  int errno = 0;

	  while ((errno = pthread_mutex_destroy (&m_mutex)) != 0)
	  {
	    sleep (1);
	  }

	  pthread_mutexattr_destroy (&m_mutex_attr);
	  pthread_cond_destroy (&m_cond);
	}

	void Lockable::lock () const
	{
	  pthread_mutex_lock (&m_mutex);
	}

	void Lockable::unlock () const
	{
	  pthread_mutex_unlock (&m_mutex);
	}

	bool Lockable::tryLock () const
	{
	  return (pthread_mutex_trylock (&m_mutex) == 0);
	}

	int Lockable::cond_wait (const uint32& timeout) const
	{
	  int ret = 0;

	  if (timeout == 0)
	    ret = pthread_cond_wait (&m_cond, &m_mutex);
	  else
	  {
	    struct timeval tv_now;
	    struct timespec ts_timeout;

	    gettimeofday (&tv_now, NULL);

	    ts_timeout.tv_sec = tv_now.tv_sec + timeout;
	    ts_timeout.tv_nsec = tv_now.tv_usec * 1000;

	    ret = pthread_cond_timedwait (&m_cond, &m_mutex, &ts_timeout);
	  }

	  return ret;
	}

	int Lockable::cond_wait (const struct timeval& timeout) const
	{
	  int ret = 0;

	  struct timeval tv_now;
	  struct timespec ts_timeout;

	  gettimeofday (&tv_now, NULL);

	  ts_timeout.tv_sec = (tv_now.tv_sec + timeout.tv_sec) + (tv_now.tv_usec + timeout.tv_usec) / 1000000;
	  ts_timeout.tv_nsec = ((tv_now.tv_usec + timeout.tv_usec) % 1000000) * 1000;

	  ret = pthread_cond_timedwait (&m_cond, &m_mutex, &ts_timeout);

	  return ret;
	}

	int Lockable::cond_wait (const struct timespec& timeout) const
	{
	  return pthread_cond_timedwait (&m_cond, &m_mutex, &timeout);
	}

	void Lockable::cond_broadcast () const
	{
	  pthread_cond_broadcast (&m_cond);
	}

	void Lockable::cond_signal () const
	{
	  pthread_cond_signal (&m_cond);
	}
}
