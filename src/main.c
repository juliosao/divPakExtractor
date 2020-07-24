#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "div.h"
#include "divArchiver.h"

int main(int argc, char** argv)
{
    int i;
    int idx;
    stDivArchiver a;

    for(int i = 1; i< argc; i++)
    {
        FILE* f = fopen(argv[i],"rb");

        if(f == NULL)
        {
            fprintf(stderr,"No se pudo abrir %s\n", argv[i]);
            continue;
        }

    }
    return 0;
}
