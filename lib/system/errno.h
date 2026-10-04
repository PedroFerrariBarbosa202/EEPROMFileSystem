/**
 * \brief error number protocol implementatipn
 *
 * \author Pedro Ferrari Barbosa
 *
 * \version 1.0
 *
 * \date 9/16/2026
 *
 * \defgroup errno ERRNO
 * \ingroup Shared
 * \{
 */

 /* sucess cases */
 #ifndef SHARED_ERRNO_H
 #define SHARED_ERRNO_H

 #define ERRNO_SUCCESS 0x00U

 /* error cases*/
 #define ERRNO_ERROR 0x10U
 #define ERRNO_INVALID_ARG 0x11U
 #define ERRNO_NO_FILE_FOUND 0x12U

 #define ERRNO_EOF 0xffU

 #endif

/** } End of errno*/
