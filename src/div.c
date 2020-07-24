#include <stdint.h>
#include <stdio.h>
#include <errno.h>
#include "div.h"

int div_loadHeader(FILE* src, stDivArchiveHeader* hdr)
{
	int res;

	printf("tell: %d\n",ftell(src));
	res=fread(hdr->type,sizeof(hdr->type),1,src);
	if(res<1)
		return DIV_ERR_LOAD;

    res=fread(&hdr->magic,sizeof(hdr->magic),1,src);
    if(res<0)
        return DIV_ERR_LOAD;

	res=fread(&hdr->version,sizeof(hdr->version),1,src);
	if(res<1)
		return DIV_ERR_LOAD;

	if(hdr->magic != DIV_FILE_MAGIC)
		return DIV_ERR_MAGIC;

	return 0;
}
