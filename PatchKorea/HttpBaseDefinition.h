#ifndef _HTTPBASEDEFINITION_H_
#define _HTTPBASEDEFINITION_H_

#include <Wininet.h>
#include <process.h>
#include "TypeDefinition.h"

#define MAX_HTTP_OBJ_NUM 300

#define URL_BUFFER_SIZE				500000			// �ѹ��� 500 KB �� �޾Ƽ� ������

enum { STOP_STATUS, DOWNLOAD_STATUS, DOWNLOAD_COMPLETE_STATUS, DOWNLOAD_SPEED_ERROR, DOWNLOAD_STOP, LOCALFILE_MAKE_ERROR };




#endif
