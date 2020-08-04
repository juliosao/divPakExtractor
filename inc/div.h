#ifndef __DIV_H_INC__
#define __DIV_H_INC__

/**
 * \brief Numero "magico" comun a todos los ficheros de DIV
 */
#define DIV_FILE_MAGIC 0x000A0D1A

/**
 * \brief Valores de retorno de multiples funciones
 */
typedef enum _DIV_RESULT {
	DIV_OK = 0, /**< Todo OK */
	DIV_ERR_OTHER = -1, /**< Error generico */
	DIV_ERR_LOAD = -2, /**< Error al leer un fichero */
	DIV_ERR_MAGIC = -3, /**< Error al comprobar la magia de un fichero*/
	DIV_ERR_FTYPE = -4, /**< El tipo de fichero no es correcto */
	DIV_ERR_MEM = -5, /**< Sin memoria para la operación*/
	DIV_ERR_WRITE = -6 /**< Error al escribir un fichero */
} DIV_RESULT;


/**
 * \brief Longitud del header en disco
 */
#define DIV_FILE_HDR_LEN 8

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
DIV_RESULT div_loadHeader(FILE* src, stDivArchiveHeader* hdr);


#endif
