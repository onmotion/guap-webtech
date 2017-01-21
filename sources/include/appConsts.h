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
 *  appConsts.h - свободная программа: вы можете перераспространять ее и/или
 * изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
 * в каком она была опубликована Фондом свободного программного обеспечения;
 * либо версии 3 лицензии, либо любой более поздней
 * версии.
 *
 *  appConsts.h распространяется в надежде, что она будет полезной,
 * но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
 * или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
 * общественной лицензии GNU.
 * Вы должны были получить копию Стандартной общественной лицензии GNU
 * вместе с этой программой. Если это не так, см.
 * <http://www.gnu.org/licenses/>.
 *
 * Данный файл распространяется по лицензии GNU/GPL v.3 или более поздней.
 *
 * appConsts.h - константы приложения
 *
 ******************************************************************************/

#ifndef _APP_CONSTS_H_
#define _APP_CONSTS_H_

#define maxNodes	4	// Максимальное количество связей для узла
#define maxCity		24	// Максимальное количество городов
#define maxBufLen	128	// Максимальный размер буфера
#define pcNameLen	12
#define osNameLen	20


#define conPort 	8422	// Порт для общения
#define listenMaxQueue	512	// Максимальное число соединений на прослушиваемом сокете,

// Сетевые команды
typedef enum {getCityNum = 1, getCityName = 2, getSimpleNode = 3,
	      getNodeCon = 4, getNewTask = 5, resReport = 6,
	      checkTripRoute = 7, printRoutesForCity = 8,
	      getOneRoute = 9
	      } netCommand;

// Упрощённая структура узла
typedef struct {
  int nodeNum;  // Номер узла
  int xPos;
  int yPos;
  int variance [maxNodes]; // Разброс расстояния
} simpleNode;

// Структура представления данных в памяти
typedef struct {
 unsigned char pcName [pcNameLen];
 unsigned char osName [osNameLen];
 short int tripPrice;
 unsigned char tripMas [maxBufLen - pcNameLen - osNameLen - 2 - 1];
} tripInfo;



#endif
