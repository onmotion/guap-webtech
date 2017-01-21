/******************************************************************************
 *                                  2017 г.
 ******************************************************************************
 *
 * Авторы: Ларюшин Александр Андреевич 
 * 	  364961@mail.ru
 *
 * Кодировка - UTF-8
 *
 * Copyright (C) 2017 Ларюшин Александр Андреевич
 *
 *  defenition.h - свободная программа: вы можете перераспространять ее и/или
 * изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
 * в каком она была опубликована Фондом свободного программного обеспечения;
 * либо версии 3 лицензии, либо любой более поздней
 * версии.
 *
 *  defenition.h распространяется в надежде, что она будет полезной,
 * но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
 * или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
 * общественной лицензии GNU.
 * Вы должны были получить копию Стандартной общественной лицензии GNU
 * вместе с этой программой. Если это не так, см.
 * <http://www.gnu.org/licenses/>.
 *
 * Данный файл распространяется по лицензии GNU/GPL v.3 или более поздней.
 *
 * defenition.h - Определения констант и заголовочных файлов
 *
 ******************************************************************************/

#ifndef _DEFINITION_H_
#define _DEFINITION_H_

 // Заголовочные файлы
 #include <netinet/in.h>	// Сокеты и сетевые функции
 #include <stdio.h>		// memset
 #include <string.h>		// strcmp, etc.
 #include <stdlib.h>		// exit %)
 #include <arpa/inet.h>		// Пригодится для inet, фун-ия inet_pton
 #include <unistd.h>		// API-вызовы POSIX



 // Макросы
 //  На случай отстутствия ф-ции bzero
 // в стандартной библиотеке
 #ifndef HAVE_BZERO
  #define bzero(ptr,n)	memset(ptr, 0, n)
 #endif

 // Другое
#define forever()	for(;;)


#endif
