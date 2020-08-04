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
    uint32_t compressedLength; /**< Longitud del fichero (Comprimido) */
    uint32_t length; /**< Longitud del fichero */

} stDivPakFileDef;

typedef struct 
{
    stDivArchiveHeader hdr;
    uint32_t numFiles;
    stDivPakFileDef* files;
} stDivPak;



int divPak_load(FILE *f, stDivPak *a);
void divPak_unload(stDivPak *a);

/**
 * \fn divPak_extractChunk(FILE* src, stDivArchiver* desc, unsigned pos);
 * \brief Extrae un fichero del archivador que le pasen
 * \param src Descriptor de fichero a usar para la operación de leer los datos del archivador
 * \param desc Estructura con la descripcion de los metadatos del archivador
 * \param pos Numero de fichero a extraer
 * 
 * El fichero se extaerá en la ruta actual con el nombre que tenga asignado en la estructura.
 */
DIV_RESULT divPak_extractChunk(FILE* src, stDivPak* desc, unsigned pos);

#endif
