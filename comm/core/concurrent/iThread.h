#pragma once

#include "utils/iTypes.h"

namespace Comm
{
	class Thread
	{
	  public:
	    Thread ();
	    virtual ~Thread ();

	  private:
	    static void* runThread (void *p);

	  public:
	    static const int setCancelState (const int &state);
	    static const int disableCancel ();
	    static void setSleepSecs (const uint32 &sleep_secs);

	  private:
	    void setTID (const uint64 &tid);
	    virtual void run () = 0;

	  protected:
	    void sleep (const uint32 &sleep_secs = 0) const;
	    void cancellationPoint () const;

	  public:
	    virtual void start ();
	    void join () const;
	    virtual void cancel () const;
	    void kill (int32 &signal) const;

	  private:
	    static uint32 ms_sleep_secs;

	  private:
	    pthread_t m_pthread;
	    pthread_attr_t m_pthread_attr;
	    uint64 m_tid;

	  public:
	    static const uint8 SLEEP_SECS = 1;
	};
}

