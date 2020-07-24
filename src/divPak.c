#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "div.h"
#include "divPak.h"

int divPak_load(FILE *f, stDivPak *a)
{
    int res;

    res=div_loadHeader(f,&a->hdr);
    if(res<0)
        return res;

    if(strncmp(a->hdr.type,"dat",3))
        return DIV_ERR_FTYPE;

    fseek(f,20,SEEK_SET);
    res=fread(&a->numFiles,sizeof(a->numFiles),1,f);
    if(res<1)
        return DIV_ERR_LOAD;

    a->files = malloc(a->numFiles * sizeof(stDivPakFileDef));
	if (a->files == NULL)
		return DIV_ERR_MEM; 

	res = fread(a->files, sizeof(stDivPakFileDef), a->numFiles, f);
	if (res < a->numFiles)
		return DIV_ERR_LOAD;

    int t = ftell(f);   
    printf("Tell: %u\n",t);
    printf("1: %u, %u\n",a->files[0].offset,a->files[0].offset+8);

    return 0;

}

void divPak_unload(stDivPak *a)
{
    if(a->files != NULL)
    {
        free(a->files);
    }
}