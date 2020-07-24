#ifndef __DIV_H_INC__

/**
 * \brief Numero "magico" comun a todos los ficheros de DIV
 */
#define DIV_FILE_MAGIC 0x000A0D1A

/**
 * \brief Longitud del header en disco
 */
#define DIV_FILE_HDR_LEN 8

/**
 * \brief Error al leer del fichero
 */
#define DIV_ERR_LOAD -1

/**
 * \brief Error al comprobar la "magia"
 */
#define DIV_ERR_MAGIC -2

/**
 * \brief Error al comprobar el tipo de fichero
 */
#define DIV_ERR_FTYPE -3

/**
 * \brief Sin memoria para realizar la operación
 */
#define DIV_ERR_MEM -4

/**
 * \typedef stDivArchiveHeader
 * \brief Describe los campos comunes a todos los ficheros de DIV
 */
typedef struct _stDivArchiveHeader
{
    char type[3]; /**< Tipo de fichero, suele coincidir con la extensión */
    uint32_t magic; /**< Magia del fichero, siempre debería valer 0x000A0D1A */
    uint8_t version; /**< Versión del fichero, suele valer 0 */
} stDivArchiveHeader;

/**
 * \fn div_loadHeader(FILE* src, stDivArchiveHeader* hdr);
 * \brief Carga en memoria los datos del header del fichero
 * \param src El fichero con los datos
 * \param hdr Puntero a estructura de tipo stDivArchiveHeader a rellenar con los datos leidos
 */
int div_loadHeader(FILE* src, stDivArchiveHeader* hdr);


#endif
