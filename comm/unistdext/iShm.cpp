#include "iShm.h"
#include "iException.h"

#include <errno.h>

Shm::Shm(key_t tKey, size_t tSize, int iMode )
{
    _tKey = tKey;
    _tSize = tSize;
    _iMode = iMode;
    _bCreate = false;
    _iShmId = -1;
}

void Shm::Init()
{
    if( (_iShmId = shmget( _tKey, _tSize, IPC_CREAT|IPC_EXCL|_iMode )) < 0 )
    {
        if( errno != EEXIST)
        {
		throw MemException( errno, "", __func__, __FILE__, __LINE__ );
        }
    }
}
