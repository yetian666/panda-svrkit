#include "iLockable.h"
#include "iThread.h"
#include "core/log/iLogger.h"

#include <unistd.h>
#include <signal.h>

#ifdef HAVE_SYS_SYSCALL_H
#include <sys/syscall.h>
#endif

namespace Comm
{
	uint32	Thread::ms_sleep_secs	= Thread::SLEEP_SECS;

	Thread::Thread ()
			: m_pthread (0), m_pthread_attr ()
	{
	  m_tid = 0;

	  pthread_attr_init (&m_pthread_attr);
	  pthread_attr_setdetachstate(&m_pthread_attr, PTHREAD_CREATE_JOINABLE);
	}

	Thread::~Thread ()
	{
	  pthread_attr_destroy (&m_pthread_attr);
	}

	void* Thread::runThread (void *p)
	{
	  Thread *pThread = static_cast<Thread *>(p);

#ifdef HAVE_SYS_SYSCALL_H
	  pThread->setTID (syscall (__NR_gettid));
#else
	  pThread->setTID (syscall (Logger::GETTID_SYSCALL_ID));
#endif

	  pThread->run ();

	  pthread_exit (0);

	  return NULL;
	}

	void Thread::setTID (const uint64 &tid)
	{
	  m_tid = tid;
	}

	void Thread::sleep (const uint32 &sleep_secs) const
	{
	  int oldstate = Thread::setCancelState (PTHREAD_CANCEL_DISABLE);

	  if (sleep_secs)
	    sleep (sleep_secs);
	  else
	    sleep (Thread::ms_sleep_secs);

	  Thread::setCancelState (oldstate);
	}

	const int Thread::setCancelState (const int &state)
	{
	  int oldstate;

	  switch (state)
	  {
	    case PTHREAD_CANCEL_ENABLE:
	      pthread_setcancelstate (PTHREAD_CANCEL_ENABLE, &oldstate);
	      pthread_testcancel ();
	      break;

	    case PTHREAD_CANCEL_DISABLE:
	      pthread_testcancel ();
	      pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &oldstate);
	      break;

	    default:
	      break;
	  }

	  return oldstate;
	}

	const int Thread::disableCancel ()
	{
	  pthread_testcancel ();
	  int oldstate = pthread_setcancelstate (PTHREAD_CANCEL_DISABLE, &oldstate);

	  return oldstate;
	}

	void Thread::cancellationPoint () const
	{
	  pthread_testcancel();
	}

	void Thread::start ()
	{
	  pthread_create (&m_pthread, &m_pthread_attr, Thread::runThread, this);
	}

	void Thread::join () const
	{
		pthread_join (m_pthread, NULL);
	}

	void Thread::cancel () const
	{
	  pthread_cancel (m_pthread);
	}

	void Thread::kill (int32 &signal) const
	{
	  pthread_kill (m_pthread, signal);
	}

	void Thread::setSleepSecs (const uint32 &sleep_secs)
	{
		Thread::ms_sleep_secs = sleep_secs;
	}
}
