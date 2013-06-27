#pragma once

#include <string>
#include <cstdarg>
#include <cstdio>
#include "utils/iTypes.h"
#include "core/concurrent/iLockable.h"

typedef enum e_debug_level
{
  SILENT        =-1,
  NO_DEBUG      = 0,
  LOW_LEVEL     = 1,
  MEDIUM_LEVEL  = 2,
  HIGH_LEVEL    = 3,
  MAX_LEVEL     = 4,
  DISABLE       = 5
} e_debug;

#define LOGGER  Logger::getInstance ()
#define LOGMSG  Logger::getInstance ()->print

namespace Comm
{

#ifdef USE_THREADS
class Logger : private Lockable
#else

class Logger
#endif
{
  public:
      typedef struct tagLogSession
     {
     	unsigned int threadId;
	char sessionId[32];
     }LogSession;

  public:
    static  Logger*  getInstance ();
    static  void  finalize ();

  protected:
    Logger (const Logger&);
    Logger (const e_debug &debug = NO_DEBUG,
        const std::string &log_file = "", FILE *pFP = NULL);

  public:
    virtual  ~Logger ();

  protected:
    Logger& operator=(const Logger& rLogger);

  private:
    void  openLogFile ();
    void  closeLogFile ();

  public:
    void  setDebugLevel (e_debug debug);
	
    void  setLogFile (const std::string &file);
    std::string& getLogFile();
    void setLogPath( const std::string &path );

    void setSessionId(const std::string &id);
    std::string getSessionId();
	
    void setMoudleName(const std::string &module_name);
	
    void makeLog(char* buffer, e_debug debug, const char* format, va_list ap );
    void  print (e_debug debug, const char *msg, va_list ap);
    void  print (e_debug debug, const char *msg, ...);

  private:
    static  Logger*  mspInstance;

  private:
    e_debug     m_debug_level;
    std::string m_log_file;
    std::string m_log_path;
    FILE*       mpFP;
    std::string m_module_name;

  public:
    static  const uint32  MSG_BUFF_SIZE     = BUFSIZ;  
    static  const uint32  DATE_BUFF_SIZE    = 32;  
	
#ifndef HAVE_SYS_SYSCALL_H
  #ifdef _LP64
    static  const uint32  GETTID_SYSCALL_ID = 186;
  #else
    static  const uint32  GETTID_SYSCALL_ID = 224;
  #endif
#endif
};
}
