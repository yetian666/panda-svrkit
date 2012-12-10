#pragma once

#include <sys/shm.h>
#include <sys/ipc.h>
#include <vector>

namespace unistdext
{

	class Shm
	{
	public:
	    Shm( key_t tKey, size_t tSize, int iMode = 0600 );

	    virtal ~Shm();

	    void Init();

	    char* GetShmAddr();
		
	private:
	    key_t _tKey;
	    size_t _tSize;
	    int _iMode;
	    bool _bCreate;
	    int _iShmId;
	    char* _pchShm;
	};
}

