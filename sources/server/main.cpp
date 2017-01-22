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
 *  main.cpp - свободная программа: вы можете перераспространять ее и/или
 * изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
 * в каком она была опубликована Фондом свободного программного обеспечения;
 * либо версии 3 лицензии, либо любой более поздней
 * версии.
 *
 *  main.cpp распространяется в надежде, что она будет полезной,
 * но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
 * или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
 * общественной лицензии GNU.
 * Вы должны были получить копию Стандартной общественной лицензии GNU
 * вместе с этой программой. Если это не так, см.
 * <http://www.gnu.org/licenses/>.
 *
 * Данный файл распространяется по лицензии GNU/GPL v.3 или более поздней.
 *
 * main.cpp - основной файл сервера. Простой. Без разбиения на классы
 *
 ******************************************************************************/

#include "../tree/tree.h"
#include "definition.h"
#include <cstdlib> // rand, srand
#include <ctime> // time

#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <iostream>
using std::cin;
using std::cout;
using std::endl;



// Без отношения к сети
const int lowLim = 4;
const int upLim = 37 - lowLim;
short int* startCity;
short int* endCity;
// Максимальное количество сообщений, которые хранятся для каждого маршрута
unsigned char tripHistory [maxCity * maxCity * sizeof (tripInfo)];
unsigned char* pHist;// = &tripHistory [0];
tripInfo* pInfo = reinterpret_cast <tripInfo*>(pHist);

// Прототипы
void fullData (treeCity* pWorld);
void readAndExec (int fd, treeCity* pWorld);
void initTcpServer (treeCity* pWorld);


int main (int argc, char** argv) {
 // <--- - ---> Стартовая точка приложения
 startCity = new short int;
 endCity = new short int;
 *startCity = 0;
 *endCity = 0;

 startCity = (short int*) mmap (NULL, sizeof (*startCity), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
 endCity = (short int*) mmap (NULL, sizeof (*endCity), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

 pHist = (unsigned char*) mmap (NULL, maxCity * maxCity * sizeof (tripInfo), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

 memset (pHist, 0xFF, maxCity * maxCity * sizeof (tripInfo));

 treeCity* pWorld = new treeCity ();
 srand (time (NULL));
 fullData (pWorld);

#ifdef DEBUG
 pWorld->printTree ();
#endif
 initTcpServer (pWorld);
 return 0;
}


void fullData (treeCity* pWorld) {
 // <--- - ---> Заполнение данными
 pWorld->addNode (0, 20, 440);
 pWorld->addNode (1, 70, 370);
 pWorld->addNode (2, 85, 315);
 pWorld->addNode (3, 80, 540);
 pWorld->addNode (4, 135, 495);
 pWorld->addNode (5, 145, 395);
 pWorld->addNode (6, 190, 280);
 pWorld->addNode (7, 200, 25);
 pWorld->addNode (8, 215, 595);
 pWorld->addNode (9, 245, 650);
 pWorld->addNode (10, 265, 305);
 pWorld->addNode (11, 280, 400);
 pWorld->addNode (12, 295, 680);
 pWorld->addNode (13, 325, 460);
 pWorld->addNode (14, 385, 485);
 pWorld->addNode (15, 415, 565);
 pWorld->addNode (16, 425, 320);
 pWorld->addNode (17, 435, 535);
 pWorld->addNode (18, 485, 615);
 pWorld->addNode (19, 490, 145);
 pWorld->addNode (20, 515, 10);
 pWorld->addNode (21, 515, 230);
 pWorld->addNode (22, 570, 260);
 pWorld->addNode (23, 600, 500);
 pWorld->addNode (24, 600, 120);
 pWorld->addNode (25, 625, 210);
 pWorld->addNode (26, 635, 260);
 pWorld->addNode (27, 640, 20);
 pWorld->addNode (28, 640, 380);
 pWorld->addNode (29, 650, 80);
 pWorld->addNode (30, 670, 230);
 pWorld->addNode (31, 680, 575);
 pWorld->addNode (32, 680, 700);
 pWorld->addNode (33, 705, 355);
 pWorld->addNode (34, 730, 560);
 pWorld->addNode (35, 750, 155);
 pWorld->addNode (36, 750, 295);
 pWorld->addNode (37, 760, 340);
 pWorld->addNode (38, 760, 400);
 pWorld->addNode (39, 790, 200);
 pWorld->addNode (40, 790, 255);
 pWorld->addNode (41, 795, 465);
 pWorld->addNode (42, 820, 345);
 pWorld->addNode (43, 820, 495);
 pWorld->addNode (44, 815, 560);
 pWorld->addNode (45, 830, 55);
 pWorld->addNode (46, 835, 245);
 pWorld->addNode (47, 835, 445);
 pWorld->addNode (48, 850, 620);
 pWorld->addNode (49, 875, 305);
 pWorld->addNode (50, 885, 560);
 pWorld->addNode (51, 930, 170);
 pWorld->addNode (52, 920, 640);
 pWorld->addNode (53, 940, 440);
 pWorld->addNode (54, 950, 280);
 pWorld->addNode (55, 940, 700);
 pWorld->addNode (56, 975, 345);
 pWorld->addNode (57, 1035, 190);
 pWorld->addNode (58, 1050, 75);
 pWorld->addNode (59, 1055, 295);
 pWorld->addNode (60, 1065, 700);
 pWorld->addNode (61, 1120, 155);
 pWorld->addNode (62, 1180, 235);
 pWorld->addNode (63, 1170, 345);

 // Устанавливаем связи
 pWorld->addNodesConnection (0, 1, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (0, 3, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (0, 4, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (1, 2, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (1, 5, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (2, 6, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (2, 7, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (3, 4, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (3, 8, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (4, 8, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (5, 6, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (5, 11, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (6, 10, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (7, 19, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (7, 20, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (8, 9, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (9, 12, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (9, 15, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (10, 11, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (10, 16, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (10, 21, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (11, 13, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (12, 18, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (13, 14, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (13, 28, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (14, 17, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (14, 23, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (15, 17, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (15, 18, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (16, 22, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (16, 28, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (17, 23, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (18, 32, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (19, 21, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (19, 24, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (20, 24, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (20, 27, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (21, 22, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (22, 26, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (23, 32, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (24, 29, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (25, 26, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (25, 29, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (26, 30, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (27, 29, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (28, 38, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (30, 35, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (30, 36, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (31, 32, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (31, 34, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (33, 36, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (33, 37, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (33, 38, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (34, 43, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (34, 44, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (35, 39, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (35, 45, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (37, 42, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (39, 40, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (39, 46, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (40, 42, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (41, 42, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (41, 43, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (43, 47, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (44, 48, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (44, 50, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (45, 58, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (46, 49, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (46, 51, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (47, 49, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (47, 53, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (48, 50, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (48, 52, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (49, 54, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (50, 53, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (51, 57, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (51, 59, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (52, 55, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (52, 60, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (53, 56, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (54, 56, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (55, 60, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (56, 59, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (57, 61, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (57, 62, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (59, 63, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (61, 62, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (62, 63, ((rand () % upLim) + lowLim));
}

void initTcpServer (treeCity* pWorld) {
 // <--- - ---> Настройка tcp-сервера
 int listenFd = 0, connFd = 0;
 pid_t childPid;
 socklen_t cliLen;
 struct sockaddr_in servAddr, cliAddr;


 listenFd = socket (AF_INET, SOCK_STREAM, 0);

 bzero (&servAddr, sizeof (servAddr));
 servAddr.sin_family = AF_INET;
 servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
 servAddr.sin_port = htons (conPort);

 bind (listenFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
 listen (listenFd, listenMaxQueue);

#ifdef DEBUG
 cout << "\nЗапущен сервер Ctrl-C для остановки\n";
#endif
 forever () {
  cliLen = sizeof (cliAddr);
  connFd = accept (listenFd, reinterpret_cast <sockaddr*> (&cliAddr), &cliLen);
  if ((childPid = fork ()) == 0 ) {
   // Дочерний процесс
   close (listenFd);
   readAndExec (connFd, pWorld);
   _exit (0);
  }
  wait (NULL);
  close (connFd);
 }


}

void readAndExec (int fd, treeCity* pWorld) {
 // <--- - ---> Считать команду и выполнить
 /*
 Команды:
 0x01 - Запросить количество существующих городов
 Возвращает число в short int (2б)

 0x02 0xXXXX - Запросить название города, где 0xXXXX - номер города
 Возвращает: Длина (1б), Название (Длина б)

 0x03 - 0xXXXX - Запросить упрощённый узел
 */
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 if (!read (fd, buf, maxBufLen)) {
  return; // Клиент закрыл соединение
 }
 switch (buf [0]) {
  case getCityNum: {
    // 2 байта
    buf [0] = static_cast <unsigned char> (pWorld->getNodesNum ());
    buf [1] = static_cast <unsigned char> (pWorld->getNodesNum () >> 8);
    write (fd, buf, 2);
   }
   break;
  case getCityName: {
    // Вернуть название города
    short int num = *(reinterpret_cast <short int*> (&buf [1]));
    strcpy (buf, reinterpret_cast <const char*> (pWorld->getCityName (num)));
    write (fd, buf, strlen (reinterpret_cast <const char*> (pWorld->getCityName (num))));
   }
   break;
  case getSimpleNode: {
    // Нет проверок. Можно крах поймать
    simpleNode node;
    node.nodeNum = *(reinterpret_cast <short int*> (&buf [1]));
    node.xPos = pWorld->getNode (node.nodeNum)->getX ();
    node.yPos = pWorld->getNode (node.nodeNum)->getY ();
    for (int i = 0; i < maxNodes; i++) {
     if (pWorld->getNode (node.nodeNum)->getNodeViaCon (i) == 0) {
      node.variance [i] = -1;
     }
     else {
      node.variance [i] = pWorld->getNode (node.nodeNum)->getNodeViaCon (i)->getNodeNum ();
     }
    }
    write (fd, reinterpret_cast <unsigned char*> (&node), sizeof (simpleNode));
   }
   break;
  case getNodeCon: {
    // Нет проверок. Можно крах поймать
    int num = *(reinterpret_cast <short int*> (&buf [1]));
    short int conMas [maxNodes];

    for (int i = 0; i < maxNodes; i++) {
     nodeCity* pNode = pWorld->getNode (num)->getNodeViaCon (i);
     if (pNode == 0) {
      conMas [i] = -1;
      continue;
     }
     conMas [i] = pNode->getNodeNum ();
    }
    write (fd, reinterpret_cast <unsigned char*> (&conMas [0]), (sizeof (short int) * maxNodes));
   }
   break;
  case getNewTask: {
   // Дать задание (откуда - куда)
   *endCity += 1; //++;
   if (*endCity == *startCity) {
    *endCity += 1;
   }
   if (*endCity >= pWorld->getNodesNum ()) {
    *endCity = 0;
    *startCity += 1;
   }
   if (*startCity >= pWorld->getNodesNum ()) {
    *startCity = 0;
    *endCity = 1;
   }

   buf [0] = static_cast <unsigned char> (*startCity);
   buf [1] = static_cast <unsigned char> ((*startCity) >> 8);
   buf [2] = static_cast <unsigned char> (*endCity);
   buf [3] = static_cast <unsigned char> ((*endCity) >> 8);
   write (fd, buf, 4);
   /* Тут нельзя менять значение номера города, т.к. это
    * дочерний процесс, который скоро будет
    * закрыт. startCity и endCity всего лишь копии
    * родительского процесса, поэтому после завершения 
    * дочернего процесса, они при следующем создании
    * НОВОГО дочернего процесса опять попадут со
    * значениями 0 и 1.
    * --------- Теперь можно - работа через общую память
    */

  }
  break;

  case resReport: {
   // Получаем сообщение о выполненном задании

   /* Формат посылки:
    КОП |    pcName    |    osName    | Оценка | Узел 0 | ... | Узел n | Маркер конца (-1)
     1б   pcNameLen б    osNameLen б      2б       2б             2б           2б
   */

   short int start = *(reinterpret_cast <short int*> (&buf [pcNameLen + osNameLen + 3]));
   short int end = *(reinterpret_cast <short int*> (&buf [pcNameLen + osNameLen + 3]));
   short int* pPtr = reinterpret_cast <short int*> (&buf [pcNameLen + osNameLen + 2 + 1]);
   while ((*pPtr != -1)) {
    end = *pPtr;
    pPtr++;
   }
   tripInfo* pInfo = reinterpret_cast <tripInfo*> (pHist);

   pInfo += start * maxCity + end; // Позиционируем на нужное место в памяти

   if ((pInfo->tripPrice == -1) || 
       (*(reinterpret_cast <short int*> (&buf [1 + pcNameLen + osNameLen])) < pInfo->tripPrice)) {
    // Очистка перед заполнением
    memset (pInfo->pcName, 0x00, pcNameLen);
    memset (pInfo->osName, 0x00, osNameLen);
    pInfo->tripPrice = -1;
    memset (pInfo->tripMas, 0x00, maxBufLen - pcNameLen - osNameLen - 2 - 1 - 2);
    
    // Имеет смысл заносить в историю
    strcpy (reinterpret_cast <char*> (pInfo->pcName),
	    reinterpret_cast <const char*> (&buf [1]));
    strcpy (reinterpret_cast <char*> (pInfo->osName),
	    reinterpret_cast <const char*> (&buf [1 + pcNameLen]));
    pInfo->tripPrice = *(reinterpret_cast <short int*> (&buf [1 + pcNameLen + osNameLen]));

    memcpy (reinterpret_cast <char*> (pInfo->tripMas),
	    reinterpret_cast <const char*> (&buf [1 + pcNameLen + osNameLen + 2]),
	    maxBufLen - pcNameLen - osNameLen - 1 - 2);
   }

  }
  break;
  case checkTripRoute: {
   tripInfo* pInfo = reinterpret_cast <tripInfo*> (pHist);
   short int start = *(reinterpret_cast <short int*> (&buf [1]));
   short int end = *(reinterpret_cast <short int*> (&buf [3]));
   cout << "[" << start << "] [" << end << "]: ";
   pInfo += start * maxCity + end; // Позиционируем на нужное место в памяти
   if (pInfo->tripPrice == -1) {
    cout << "Данный маршрут ещё не построен" << endl;
   }
   else {
    cout << "Маршрут найден машиной \""
         << pInfo->pcName << "\", "
	 << "под управлением ОС: "
         << pInfo->osName << ": "
	 << "Цена пути: " 
	 << pInfo->tripPrice << " км"<< endl;
    short int* pPtr = reinterpret_cast <short int*> (pInfo->tripMas);
    while ((*pPtr != -1)) {
     cout << *pPtr;
     pPtr++;
     if (*pPtr != -1) {
      cout << " -> ";
     }
     else {
      cout << endl;
     }
    }
   }
  }
  break;

  case printRoutesForCity: {
   // Распечатать все маршруты для города
   cout << endl << endl << endl << endl;
   tripInfo* pInfo = reinterpret_cast <tripInfo*> (pHist);
   //cout << "memory dump:\n";
   //int limit = (sizeof (tripInfo) * 4 / 8);
   //for (int i = 0; i < limit; i++) {
   // for (int j = 0; j < 8; j++) {
   //  //cout << std::hex << "0x" << pHist [i * 8 + j];
   //  printf ("0x%02X ", pHist [i * 8 + j]);
   //  if ((j > 0) && (((j + 1) % 4) == 0)) {
   //   cout << "    ";
   //  }
   //  if (((i * 8 + j + 1) % sizeof (tripInfo)) == 0) {
   //   if (!((i == 0) && (j == 0))) {
   //    cout << endl;
   //   }
   //  }
   // }
   // cout << endl;
   //}
   //cout << endl;

   short int start = *(reinterpret_cast <short int*> (&buf [1]));
   short int end = 0;
   if (end == start) {
    end++;
   }
   while (end < pWorld->getNodesNum ()) {
    cout << "Маршрут из " << pWorld->getCityName (start) << " [" << start << "] "
         << " в " << pWorld->getCityName (end) << " [" << end << "] "
	 << ":\n";
    pInfo = reinterpret_cast <tripInfo*> (pHist); // Надо обновлять, чтобы += не "играло" против нас :)
    pInfo += start * maxCity + end; // Позиционируем на нужное место в памяти

    if (pInfo->tripPrice == -1) {
     cout << "Данный маршрут ещё не построен" << endl;
     cout << "------------------------------------------------------------------\n";
    }
    else {
     cout << "Маршрут найден машиной \""
	  << pInfo->pcName << "\", "
	  << "под управлением ОС \""
	  << pInfo->osName << ": "
	  << "\", \"цена\" пути: " 
	  << pInfo->tripPrice << " км"<< endl;
     short int* pPtr = reinterpret_cast <short int*> (pInfo->tripMas);
     while ((*pPtr != -1)) {
      cout << *pPtr;
      pPtr++;
      if (*pPtr != -1) {
       cout << " -> ";
      }
      else {
       cout << endl;
       cout << "------------------------------------------------------------------\n";
      }
     }

    }

    end++;
    if (end == start) {
     end++;
    }
   }
  }
  break;

  case getOneRoute: {
   // Вернуть один маршрут
   tripInfo* pInfo = reinterpret_cast <tripInfo*> (pHist);
   short int start = *(reinterpret_cast <short int*> (&buf [1]));
   short int end = *(reinterpret_cast <short int*> (&buf [3]));

   pInfo += start * maxCity + end; // Позиционируем на нужное место в памяти
   write (fd, reinterpret_cast <unsigned char*>(pInfo), sizeof (tripInfo));
  }
  break;

  case resetData: {
   // Сбросить все найденные маршруты
   memset (pHist, 0xFF, maxCity * maxCity * sizeof (tripInfo));
  }
  break;

  default:
   cout << "wrong comm: " << (int) buf [0] << endl;
   break;
 }
}

