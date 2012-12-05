#pragma once

#include <sys/shm.h>
#include <sys/ipc.h>

/**
 * If use shm, better inherit from this class
 * 
 * @author pandaxu (2012/11/30)
 */
class Shm
{
public:
    Shm( key_t tKey, size_t tSize, int iMode = 0600 );

    virtal ~Shm();

    void Init();

    void* GetShm();

    void Attach();

    void Detach();
}

/**
 * If use more than one block shm, better inherit from this 
 * class 
 * 
 * @author pandaxu (2012/11/30)
 */
class ShmManager
{
public:
    ShmManager();

    virtal ~ShmManager();

    void Init();

    void* GetShm( const int index );

    void Attach();

    void Detach();
}
