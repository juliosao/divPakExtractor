#include <stdio.h>
#include <stdint.h>
#include <string.h>
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

    

    return 0;

}

void divPak_unload(stDivPak *a)
{

}