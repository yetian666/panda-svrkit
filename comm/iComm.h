#pragma once

/**
 *  Clolor defines for print
 */
#include "utils/iTerminalColor.h"


#include "utils/iString.h"
#include "utils/iRunTime.h"
#include "utils/iStressTest.h"
#include "utils/iServerControl.h"
#include "utils/iOptionMap.h"
#include "utils/iTypes.h"

#include "core/file/iEndpoint.h"
#include "core/file/iBaseClientConfig.h"

#include "base/unistdext/iShm.h"
#include "base/stdext/iErrno.h"
#include "base/stdext/iException.h"

#include "base/iMagicNum.h"

#include "core/log/iLog.h"

#include "core/concurrent/iLockable.h"

#include "dao/iMysqlClient.h"

#define COMM_OK 0
#define COMM_ENET -1001
#define COMM_EDECODE -1002
#define COMM_EENCODE  -1003;


