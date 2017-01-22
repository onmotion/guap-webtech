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
 * main.cpp - основной файл клиента. Простой. Без разбиения на классы
 *
 ******************************************************************************/

#include "definition.h"
#include "../tree/tree.h"
#include <cstdlib> // rand, srand
#include <ctime> // time
#include <cmath> // time

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

// Переменные
short int numOfCity = 0;
unsigned char masNames [maxCity] [maxBufLen];
bool stepMode = false;

const int pathLen = maxBufLen - pcNameLen - osNameLen - 2 - 1 - 2;

unsigned char pcName [pcNameLen];
unsigned char osName [osNameLen];
unsigned char path [pathLen];
/*
 Путь представляет собой набор городов
 максимально-допустимое количество городов, вычисляется так:
 int searchLimit = pathLen / (sizeof (short int));
 при этом  начальный и конечный города должны быть
 включены в путь.
*/

// Прототипы
void initTcpClient (treeCity* pWorld);
short int gotCityNum (int fd);			// Запросить у сервера количество городов
void tryGetCityName (int fd, int cityNum);	// Поучить имя города
void tryGetCityNode (int fd, int cityNum, treeCity* pWorld);
void tryMakeConnections (int fd, short int begNode, treeCity* pWorld);
void getUserData ();
void tryGetNewTask (int fd, int& startCity, int& endCity, treeCity* pWorld);
void trySearchPath  (int fd, int startCity, int endCity, treeCity* pWorld);
void checkBestPath (int fd, int startCity, int endCity);
void serverPrintRoutes (int fd, int startCity, int endCity);
void getRoute (int fd, int startCity, int endCity);
void resetServRoutes (int fd);



int main (int argc, char** argv) {
 if (argc > 1) {
  if (strcmp (argv [1], "--iteration") == 0) {
   stepMode = true;
   cout << "Запущенно в пошаговом режиме\n";
  }
 }
 treeCity* pWorld = new treeCity ();
 srand (time (NULL));
 memset (pcName, 0x00, pcNameLen);
 memset (osName, 0x00, osNameLen);
 strcpy (reinterpret_cast <char*> (pcName), "user");
 strcpy (reinterpret_cast <char*> (osName), "some os");

 initTcpClient (pWorld);
 return 0;
}


void initTcpClient (treeCity* pWorld) {
 // Настройка tcp-сервера
 int sockFd = 0;
 struct sockaddr_in servAddr;

 sockFd = socket (AF_INET, SOCK_STREAM, 0);

 bzero (&servAddr, sizeof (servAddr));
 servAddr.sin_family = AF_INET;
 servAddr.sin_addr.s_addr = htonl (INADDR_ANY);
 servAddr.sin_port = htons (conPort);
 inet_pton (AF_INET, "127.0.0.1", &servAddr.sin_addr);
 //inet_pton (AF_INET, "104.160.36.183", &servAddr.sin_addr);
 connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));

 // Сценарий
 // Получить данные для идентификации
 getUserData ();
 // Получаем количество городов
 numOfCity = gotCityNum (sockFd);
 //cout << numOfCity << " городов в \"дереве\"\n";
 close (sockFd);

 //Названия всех городов
 for (int i = 0; i < numOfCity; i++) {
  sockFd = socket (AF_INET, SOCK_STREAM, 0);
  connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
  tryGetCityName (sockFd, i);
  close (sockFd);
 }

 // Все города
 for (int i = 0; i < numOfCity; i++) {
  sockFd = socket (AF_INET, SOCK_STREAM, 0);
  connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
  tryGetCityNode (sockFd, i, pWorld);
  close (sockFd);
 }

 // Связи между городами
 for (int i = 0; i < numOfCity; i++) {
  sockFd = socket (AF_INET, SOCK_STREAM, 0);
  connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
  tryMakeConnections (sockFd, i, pWorld);
  close (sockFd);
 }


 //pWorld->printTree ();


 int startCity = 0, endCity = 0;
 cout << "Символ и ввод для итерации. Ctrl-C для выхода\n";
 forever () {

  if (stepMode) {
   // Если пошаговый режим
   cout << "9 - для печати сервером маршрутов для любого города\n";
   cout << "0 - для сброса всех найденных маршрутов\n";
   int r;
   cin >> r;
   cout << endl;
   if (r == 9) {
   cout << "Введите номер города от 0 до " << numOfCity - 1 << endl;
   cin >> startCity;
   cout << endl;
   for (int i = 0; i < numOfCity; i++) {
    sockFd = socket (AF_INET, SOCK_STREAM, 0);
    connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
    if (startCity == i) {
     i++;
    }
    if (i >= numOfCity) {
     break;
    }
    getRoute (sockFd, startCity, i);
    close (sockFd);
   }

    //sockFd = socket (AF_INET, SOCK_STREAM, 0);
    //connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
    //serverPrintRoutes (sockFd, startCity, endCity);
    //close (sockFd);
    continue;
   }
   if (r == 0) {
    cout << "Серверу отправлена команда сброса существующих маршрутов\n";
    sockFd = socket (AF_INET, SOCK_STREAM, 0);
    connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
    resetServRoutes (sockFd);
    close (sockFd);
    continue;
   }

  }

  sockFd = socket (AF_INET, SOCK_STREAM, 0);
  connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
  tryGetNewTask (sockFd, startCity, endCity, pWorld);
  close (sockFd);

  sockFd = socket (AF_INET, SOCK_STREAM, 0);
  connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
  trySearchPath (sockFd, startCity, endCity, pWorld);
  close (sockFd);

  //sockFd = socket (AF_INET, SOCK_STREAM, 0);
  //connect (sockFd, reinterpret_cast <sockaddr*> (&servAddr), sizeof (sockaddr));
  //checkBestPath (sockFd, startCity, endCity);
  //close (sockFd);


 }

 //pWorld->printTree ();

}

void getUserData () {
 // <--- - ---> Данные пользователя
 cout << "Укажите данные для статистики сервера:\n"
      << "логин (имя машины): ";
 cin >> pcName;
 cout << endl;
 cout << "имя операционной системы: ";
 cin >> osName;
 cout << endl;
}

short int gotCityNum (int fd) {
 // <--- - ---> Узнать у сервера сколько городов существует?
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 //netCommand com = getCityNum;
 buf [0] = getCityNum;
 write (fd, reinterpret_cast <unsigned char*> (buf), sizeof (unsigned char));
 read (fd, buf, maxBufLen);
 return *(reinterpret_cast <short int*> (buf));
}

void tryGetCityName (int fd, int cityNum) {
 // <--- - ---> Получить название города
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 buf [0] = getCityName;
 buf [1] = cityNum;
 buf [2] = (cityNum >> 8);
 write (fd, reinterpret_cast <unsigned char*> (buf), 3);
 read (fd, buf, maxBufLen);
 strcpy (reinterpret_cast <char*> (masNames [cityNum]), buf);
}

void tryGetCityNode (int fd, int cityNum, treeCity* pWorld) {
 // <--- - ---> Получить узел, добавить в структуру
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 //netCommand com = getSimpleNode;
 buf [0] = getSimpleNode;
 buf [1] = cityNum;
 buf [2] = (cityNum >> 8);
 write (fd, reinterpret_cast <unsigned char*> (buf), 3);
 read (fd, buf, maxBufLen);
 simpleNode* pNode = reinterpret_cast <simpleNode*> (&buf [0]); 
 pWorld->addNode (pNode->nodeNum, pNode->xPos, pNode->yPos);
 for (int i = 0; i < maxNodes; i++) {
  pWorld->getNode (pNode->nodeNum)->setVariance (i, pNode->variance [i]);
 }
}

void tryMakeConnections (int fd, short int begNode, treeCity* pWorld) {
 // <--- - ---> Налаживаем связи между городами
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 buf [0] = getNodeCon;
 buf [1] = begNode;
 buf [2] = (begNode >> 8);
 write (fd, reinterpret_cast <unsigned char*> (buf), 3);
 read (fd, buf, maxBufLen);

 for (int j = 0; j < maxNodes; j++) {
  short int endNode = *(reinterpret_cast <short int*> (&buf [j * sizeof (short int)]));
  if (endNode == -1) {
   // Нет связи
   continue;
  }
  if (begNode >= endNode) {
   continue;
  }
  pWorld->addNodesConnection (begNode, endNode, pWorld->getNode (begNode)->getVarianceViaCon (j));
 }
}

void tryGetNewTask (int fd, int& startCity, int& endCity, treeCity* pWorld) {
 // <--- - ---> Получение нового задания
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 buf [0] = getNewTask;
 write (fd, buf, 1);
 read (fd, buf, maxBufLen);
 startCity = *(reinterpret_cast <short int*> (&buf [0]));
 endCity = *(reinterpret_cast <short int*> (&buf [2]));
#ifdef DEBUG
 cout << "New task: " << startCity << " -> " << endCity << endl;
 cout.flush ();
#endif
}


void trySearchPath  (int fd, int startCity, int endCity, treeCity* pWorld) {
 // <--- - ---> Пробуем найти путь для данного задания
   /* Формат посылки:
    КОП |    pcName    |    osName    | Оценка | Узел 0 | ... | Узел n | Маркер конца (-1)
     1б   pcNameLen б    osNameLen б      2б       2б             2б           2б
   */
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 // Отправить данные
 buf [0] = resReport;
 int existLen = 1;
 strcpy (reinterpret_cast <char*> (&buf [existLen]), reinterpret_cast <const char*> (pcName));
 existLen += pcNameLen;
 strcpy (reinterpret_cast <char*> (&buf [existLen]), reinterpret_cast <const char*> (osName));
 existLen += osNameLen;
 // Надо добавить оценку пути и, возможно, подумать о истории путей
 int pricePos = existLen;
 short int price = 0; // "Стоимость" путешествия
 existLen += 2;

 int searchLimit = pathLen / (sizeof (short int));
 int currentDeep = 0;
 int currNode = startCity;
 int parNode = -1;
 int conNum = -1;
 
 while (currentDeep < searchLimit) {
  // Добавляем узел в историю поиска
  buf [existLen] = currNode;
  buf [existLen + 1] = (currNode >> 8);
  existLen += 2;
  currentDeep++;

  bool exit = false;

  while (!exit) {
   nodeCity* pNode = pWorld->getNode (currNode);
   conNum = rand () % pNode->getConNum ();
   if ((pNode->getNodeViaCon (conNum)->getNodeNum () != parNode) || (pNode->getConNum () == 1)) {
    // Второй случай - всего одная связь
    parNode = currNode;
    currNode = pNode->getNodeViaCon (conNum)->getNodeNum ();
    exit = true;
   }
  }

  int x1 = pWorld->getNode (parNode)->getX ();
  int x2 = pWorld->getNode (currNode)->getX ();
  int y1 = pWorld->getNode (parNode)->getY ();
  int y2 = pWorld->getNode (currNode)->getY ();
  int var = pWorld->getNode (currNode)->getVarianceViaCon (conNum);
  price += ((sqrt ((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)) * (100 + var)) / 100);
  if (currNode == endCity) {
   buf [existLen] = currNode;
   buf [existLen + 1] = (currNode >> 8);
   existLen += 2;
   buf [pricePos] = price;
   buf [pricePos + 1] = (price >> 8);
   // Маркер конца 0xFFFF (-1)
   buf [existLen] = 0xFF;
   buf [existLen + 1] = 0xFF;
   existLen += 2;
   write (fd, buf, existLen);

   cout << "Найден маршрут из " << startCity << " в " << endCity << " c "
        << "ценой пути " << price << " км" << endl;
   short int* pPtr = reinterpret_cast <short int*> (&buf [pcNameLen + osNameLen + 2 + 1]);
   while ((*pPtr != -1)) {
    cout << *pPtr << " ->  ";
    pPtr++;
   }

   return;
  }
 }
 cout << "Превышен лимит поиска\n";
}



void checkBestPath (int fd, int startCity, int endCity) {
 // <--- - ---> Проверяем путь
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 buf [0] = checkTripRoute;
 buf [1] = startCity;
 buf [2] = (startCity >> 8);
 buf [3] = endCity;
 buf [4] = (endCity >> 8);
 write (fd, buf, 5);
}

void serverPrintRoutes (int fd, int startCity, int endCity) {
 // <--- - ---> Печать всех маршрутов из города на стороне сервера
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 buf [0] = printRoutesForCity;
 buf [1] = startCity;
 buf [2] = (startCity >> 8);
 write (fd, buf, 3);
}

void getRoute (int fd, int startCity, int endCity) {
 // <--- - ---> Получить маршрут для заданной пары городов
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 buf [0] = getOneRoute;
 buf [1] = startCity;
 buf [2] = (startCity >> 8);
 buf [3] = endCity;
 buf [4] = (endCity >> 8);
 write (fd, buf, 5);
 read (fd, buf, maxBufLen);

 tripInfo* pInfo = reinterpret_cast <tripInfo*> (buf);
 cout << "[" << startCity << "] [" << endCity << "]: ";
 if (pInfo->tripPrice == -1) {
  cout << "Данный маршрут ещё не построен" << endl;
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
   }
  }
 }
}


void resetServRoutes (int fd) {
 // <--- - ---> Сброс всех найденных маршрутов
 char buf [maxBufLen];
 memset (buf, 0x00, maxBufLen);
 buf [0] = resetData;
 write (fd, buf, 1);
}

