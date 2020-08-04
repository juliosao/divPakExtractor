#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <zlib.h>
#include "div.h"
#include "divPak.h"

DIV_RESULT divPak_load(FILE *f, stDivPak *a)
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
    
    return DIV_OK;

}

// Extrae un fichero de un archivador en la ruta actual
DIV_RESULT divPak_extractChunk(FILE *src, stDivPak *desc, unsigned pos)
{
	FILE *dst = fopen(desc->files[pos].name, "wb");
	unsigned char *buff;
	unsigned long lenb;
	unsigned char *uncompressBfr;

	if (!dst)
	{
		fprintf(stderr, "Error al escribir %s", desc->files[pos].name);
		return DIV_ERR_WRITE;
	}

	buff = malloc(desc->files[pos].compressedLength * sizeof(unsigned char));
	if (buff == NULL)
		return DIV_ERR_MEM;

	fseek(src, desc->files[pos].offset, SEEK_SET);
    fread(buff, desc->files[pos].compressedLength, sizeof(unsigned char), src);

	if( desc->files[pos].compressedLength == desc->files[pos].length )
	{
		fwrite(buff, desc->files[pos].compressedLength, sizeof(unsigned char), dst);
	}
	else
	{
		uncompressBfr = malloc(desc->files[pos].length+1 * sizeof(unsigned char));
		if (uncompressBfr == NULL)
		{
			fclose(dst);
			free(buff);
	        return DIV_ERR_MEM;		
		}
			
		lenb=desc->files[pos].length;
		printf("%ul,%ul > %ul\n",lenb,desc->files[pos].length, desc->files[pos].compressedLength);
		int res = uncompress(uncompressBfr, &lenb, buff, (unsigned long) desc->files[pos].compressedLength );
		if( res != Z_OK)
		{
			printf("Error al descomprimir...%d,%d,%d,%d\n",res,res==Z_BUF_ERROR,res==Z_MEM_ERROR,res==Z_DATA_ERROR);
			fclose(dst);
			free(uncompressBfr);
            free(buff);
            return DIV_ERR_OTHER;
		}
		printf("%ul,%ul\n",lenb,desc->files[pos].length);
		
		res = fwrite(uncompressBfr, sizeof(unsigned char), desc->files[pos].length, dst);
		printf("Descomprimido: %ul\n",res);
		free(uncompressBfr);
	}
    

	fclose(dst);
	free(buff);
	return DIV_OK;
}


void divPak_unload(stDivPak *a)
{
    if(a->files != NULL)
    {
        free(a->files);
    }
}