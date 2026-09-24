/**
 * \brief eeprom device header
 *
 * \author Pedro Ferrari Barbosa <pedro.ferraribarbosa2007@gmail.com>
 *
 * \version 1.0
 *
 * \date 20/9/2026
 *
 * \defgroup eeprom EEPROM
 * \ingroup devices
 * \{
 */

 #ifndef DEVICES_EEPROM_H
 #define DEVICES_EEPROM_H

 int eeprom_fopen(void);
 int eeprom_fwrite(void);
 int eeprom_fread(void);
 
 #endif /*DEVICES_EEPROM_H*/
/** } End of DefL*/
