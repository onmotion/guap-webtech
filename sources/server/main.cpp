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
const int maxHistRow = 3;
//tripInfo tripHistory [maxCity] [maxCity];
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
 fullData (pWorld);
 srand (time (NULL));

#ifdef DEBUG
 pWorld->printTree ();
#endif
 initTcpServer (pWorld);
 return 0;
}


void fullData (treeCity* pWorld) {
 // <--- - ---> Заполнение данными
 pWorld->addNode (0, 35, 155);
 pWorld->addNode (1, 220, 250);
 pWorld->addNode (2, 105, 380);
 pWorld->addNode (3, 35, 480);
 pWorld->addNode (4, 275, 470);
 pWorld->addNode (5, 390, 360);
 pWorld->addNode (6, 545, 400);
 pWorld->addNode (7, 645, 300);
 pWorld->addNode (8, 765, 180);
 pWorld->addNode (9, 660, 80);
 pWorld->addNode (10, 530, 130);
 pWorld->addNode (11, 390, 50);
 pWorld->addNode (12, 320, 150);
 pWorld->addNode (13, 150, 20);
 pWorld->addNode (14, 540, 20);
 pWorld->addNode (15, 821, 70);
 pWorld->addNode (16, 824, 270);
 pWorld->addNode (17, 670, 400);
 pWorld->addNode (18, 810, 380);
 pWorld->addNode (19, 760, 490);
 pWorld->addNode (20, 650, 520);
 pWorld->addNode (21, 530, 505);
 pWorld->addNode (22, 470, 585);
 pWorld->addNode (23, 140, 535);

 // Устанавливаем связи
 pWorld->addNodesConnection (0, 2, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (0, 12, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (0, 13, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (1, 2, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (1, 5, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (1, 12, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (2, 3, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (3, 4, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (3, 23, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (4, 5, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (4, 6, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (5, 7, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (6, 7, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (6, 17, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (7, 8, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (8, 9, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (8, 10, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (9, 11, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (9, 15, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (10, 11, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (10, 12, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (11, 13, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (11, 14, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (13, 14, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (14, 15, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (15, 16, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (16, 17, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (16, 18, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (17, 21, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (18, 19, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (18, 20, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (19, 20, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (20, 21, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (21, 22, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (21, 23, ((rand () % upLim) + lowLim));
 pWorld->addNodesConnection (22, 23, ((rand () % upLim) + lowLim));
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
 read (fd, buf, maxBufLen);

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


  default:
   cout << "wrong comm: " << (int) buf [0] << endl;
   break;
 }
}

