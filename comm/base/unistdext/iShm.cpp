#include "iShm.h"
#include "iException.h"
#include <errno.h>

using namespace stdext;

namespace unistdext
{
	Shm::Shm(key_t tKey, size_t tSize, int iMode )
	{
	    _tKey = tKey;
	    _tSize = tSize;
	    _iMode = iMode;
	    _bCreate = true;
	    _iShmId = -1;
		_pchShm = NULL;
	}

	Shm::~Shm()
	{
		if( shmdt(_pchShm)<0 )
			throw MemException( errno, __func__, __FILE__, __LINE__ );
	}

	void Shm::Init()
	{
		//get
		if( (_iShmId = shmget( _tKey, _tSize, IPC_CREAT|IPC_EXCL|_iMode )) < 0 )
		{
			if( errno != EEXIST)
			{
				throw MemException( errno, __func__, __FILE__, __LINE__ );
			}

			if( (_iShmId = shmget( _tKey, _tSize, _iMode )) < 0 )
				throw MemException( errno,  __func__, __FILE__, __LINE__ );

			_bCreate = false;
		}

		//attch
		if( (_pchShm = (char*)shmat( _iShmId, NULL, 0)) <0 )
			throw MemException( errno, __func__, __FILE__, __LINE__ );

		//init 
		if( _bCreate )
			memset( _pchShm, 0, _tSize );

	}


	char* Shm::GetShmAddr()
	{
		return _pchShm;
	}

}

