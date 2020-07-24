#ifndef __DIVPAK_H_INC__
#define __DIVPAK_H_INC__

/**
 * \typedef stDivArchiverFileDef
 * \brief Estructura con los metadatos de un fichero dentro del archivador
 */
typedef struct _filedef
{
    uint8_t name[16]; /**< Nombre del fichero */
    uint32_t offset; /**< Posición dentro del fichero (menos el header) */
    uint32_t packedLen; 
    uint32_t len; /**< Longitud del fichero */

} stDivPakFileDef;

typedef struct 
{
    stDivArchiveHeader hdr;
    uint32_t numFiles;
    stDivPakFileDef* files;
} stDivPak;



int divPak_load(FILE *f, stDivPak *a);
void divPak_unload(stDivPak *a);

#endif
