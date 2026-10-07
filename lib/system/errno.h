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

#ifndef SHARED_ERRNO_H
#define SHARED_ERRNO_H

/*
 * \brief error enum type
 */
typedef enum error_t{
#define ERROR(errno) errno, 
  #include "details/errno.inc"
#undef ERROR /*avoid global namespace pollution*/

  ERRNO_LIST_LENGTH
}error_t;

/**
 * \brief converts errno value to its string representation.
 *
 * \param error is the error that will be converted.
 *
 * \return the string representation of the parameter.
 */
static const char *error_as_string(error_t error)
{
    switch (error) {
#define ERROR(errno) case errno: return #errno;
  #include "details/errno.inc"
#undef ERROR
      case ERRNO_LIST_LENGTH: return "ERROR_LIST_LENGTH";
    }

    return "ERROR_FAILED_STRING_CONVERSION";
}

 #endif

/** } End of errno*/
