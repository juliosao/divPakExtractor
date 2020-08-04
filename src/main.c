#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "div.h"
#include "divPak.h"

int main(int argc, char** argv)
{
    int i;
    int idx;
    stDivPak a;

    for(int i = 1; i< argc; i++)
    {
        FILE* f = fopen(argv[i],"rb");

        if(f == NULL)
        {
            fprintf(stderr,"No se pudo abrir %s\n", argv[i]);
            continue;
        }
        
		switch (divPak_load(f,&a))
		{
		case DIV_OK:
			printf("Archivo: %s\n",argv[i]);
			printf("Tipo: %3.3s\n",a.hdr.type);
			printf("Magia: %8.8X\n",a.hdr.magic);
            printf("Version: %u\n",(unsigned int)a.hdr.version);    
            printf("Numero de ficheros encontrados: %u\n",(unsigned int)a.numFiles);

			for(idx=0; idx<a.numFiles; idx++)
            {
                printf("Fichero %d: %s. offset=%u plen=%u len=%u,\n",(idx+1),a.files[idx].name,(unsigned)a.files[idx].offset,(unsigned)a.files[idx].compressedLength,(unsigned)a.files[idx].length);
				divPak_extractChunk(f,&a,idx);
            }
			break;
		case DIV_ERR_OTHER:
			fprintf(stderr,"Error interno\n");
			break;
		case DIV_ERR_LOAD:
			fprintf(stderr,"Error de carga\n");
			break;
		case DIV_ERR_MAGIC:
			fprintf(stderr,"Tipo de fichero erroneo o fichero corrupto\n");
			break;
		case DIV_ERR_FTYPE:
			fprintf(stderr,"Tipo de fichero erroneo\n");
			break;
		case DIV_ERR_MEM:
			fprintf(stderr,"Sin memoria\n");
			break;
		case DIV_ERR_WRITE:
			fprintf(stderr,"Error al escribir en fichero\n");
			break;
		}
		divPak_unload(&a);
    }
    return 0;
}
