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
 *  tree.cpp - свободная программа: вы можете перераспространять ее и/или
 * изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
 * в каком она была опубликована Фондом свободного программного обеспечения;
 * либо версии 3 лицензии, либо любой более поздней
 * версии.
 *
 *  tree.cpp распространяется в надежде, что она будет полезной,
 * но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
 * или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
 * общественной лицензии GNU.
 * Вы должны были получить копию Стандартной общественной лицензии GNU
 * вместе с этой программой. Если это не так, см.
 * <http://www.gnu.org/licenses/>.
 *
 * Данный файл распространяется по лицензии GNU/GPL v.3 или более поздней.
 *
 * tree.cpp - файл реализации класса "дерева".
 *
 ******************************************************************************/

#include "tree.h"
#include <cstring>
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#define OK	0
#define ERROR	-1

treeCity::treeCity () {
 // <--- - ---> Конструктор
 lastNode = 0;
 for (int i = 0; i < maxCity; i++) {
  cityMas [i] = 0;
 }
 strcpy (reinterpret_cast <char*> (masNames [0]), "Париж"); 
 strcpy (reinterpret_cast <char*> (masNames [1]), "Брюсель"); 
 strcpy (reinterpret_cast <char*> (masNames [2]), "Амстердам"); 
 strcpy (reinterpret_cast <char*> (masNames [3]), "Лион"); 
 strcpy (reinterpret_cast <char*> (masNames [4]), "Берн"); 
 strcpy (reinterpret_cast <char*> (masNames [5]), "Люксембург"); 
 strcpy (reinterpret_cast <char*> (masNames [6]), "Гамбург"); 
 strcpy (reinterpret_cast <char*> (masNames [7]), "Осло"); 
 strcpy (reinterpret_cast <char*> (masNames [8]), "Флоренция"); 
 strcpy (reinterpret_cast <char*> (masNames [9]), "Рим"); 
 strcpy (reinterpret_cast <char*> (masNames [10]), "Берлин"); 
 strcpy (reinterpret_cast <char*> (masNames [11]), "Прага"); 
 strcpy (reinterpret_cast <char*> (masNames [12]), "Неаполь"); 
 strcpy (reinterpret_cast <char*> (masNames [13]), "Вена"); 
 strcpy (reinterpret_cast <char*> (masNames [14]), "Будапешт"); 
 strcpy (reinterpret_cast <char*> (masNames [15]), "Сараево"); 
 strcpy (reinterpret_cast <char*> (masNames [16]), "Варшава"); 
 strcpy (reinterpret_cast <char*> (masNames [17]), "Белград"); 
 strcpy (reinterpret_cast <char*> (masNames [18]), "София"); 
 strcpy (reinterpret_cast <char*> (masNames [19]), "Рига"); 
 strcpy (reinterpret_cast <char*> (masNames [20]), "Хельсинки"); 
 strcpy (reinterpret_cast <char*> (masNames [21]), "Вильнюс"); 
 strcpy (reinterpret_cast <char*> (masNames [22]), "Минск"); 
 strcpy (reinterpret_cast <char*> (masNames [23]), "Кишенёв"); 
 strcpy (reinterpret_cast <char*> (masNames [24]), "Псков"); 
 strcpy (reinterpret_cast <char*> (masNames [25]), "Витебск"); 
 strcpy (reinterpret_cast <char*> (masNames [26]), "Могилёв"); 
 strcpy (reinterpret_cast <char*> (masNames [27]), "Санкт-Петербург"); 
 strcpy (reinterpret_cast <char*> (masNames [28]), "Киев"); 
 strcpy (reinterpret_cast <char*> (masNames [29]), "В. Новгород"); 
 strcpy (reinterpret_cast <char*> (masNames [30]), "Смоленск"); 
 strcpy (reinterpret_cast <char*> (masNames [31]), "Севастополь"); 
 strcpy (reinterpret_cast <char*> (masNames [32]), "Анкара"); 
 strcpy (reinterpret_cast <char*> (masNames [33]), "Сумы"); 
 strcpy (reinterpret_cast <char*> (masNames [34]), "Симферополь"); 
 strcpy (reinterpret_cast <char*> (masNames [35]), "Тверь"); 
 strcpy (reinterpret_cast <char*> (masNames [36]), "Орёл"); 
 strcpy (reinterpret_cast <char*> (masNames [37]), "Курск"); 
 strcpy (reinterpret_cast <char*> (masNames [38]), "Харьков"); 
 strcpy (reinterpret_cast <char*> (masNames [39]), "Москва"); 
 strcpy (reinterpret_cast <char*> (masNames [40]), "Тула"); 
 strcpy (reinterpret_cast <char*> (masNames [41]), "Донецк"); 
 strcpy (reinterpret_cast <char*> (masNames [42]), "Воронеж"); 
 strcpy (reinterpret_cast <char*> (masNames [43]), "Ростов-на-Дону"); 
 strcpy (reinterpret_cast <char*> (masNames [44]), "Краснодар"); 
 strcpy (reinterpret_cast <char*> (masNames [45]), "Вологда"); 
 strcpy (reinterpret_cast <char*> (masNames [46]), "Рязань"); 
 strcpy (reinterpret_cast <char*> (masNames [47]), "Луганск"); 
 strcpy (reinterpret_cast <char*> (masNames [48]), "Нальчик"); 
 strcpy (reinterpret_cast <char*> (masNames [49]), "Тамбов"); 
 strcpy (reinterpret_cast <char*> (masNames [50]), "Ставрополь"); 
 strcpy (reinterpret_cast <char*> (masNames [51]), "Н. Новгород"); 
 strcpy (reinterpret_cast <char*> (masNames [52]), "Цхинвал"); 
 strcpy (reinterpret_cast <char*> (masNames [53]), "Волгоград"); 
 strcpy (reinterpret_cast <char*> (masNames [54]), "Пенза"); 
 strcpy (reinterpret_cast <char*> (masNames [55]), "Ереван"); 
 strcpy (reinterpret_cast <char*> (masNames [56]), "Саратов"); 
 strcpy (reinterpret_cast <char*> (masNames [57]), "Казань"); 
 strcpy (reinterpret_cast <char*> (masNames [58]), "Киров"); 
 strcpy (reinterpret_cast <char*> (masNames [59]), "Самара"); 
 strcpy (reinterpret_cast <char*> (masNames [60]), "Баку"); 
 strcpy (reinterpret_cast <char*> (masNames [61]), "Ижевск"); 
 strcpy (reinterpret_cast <char*> (masNames [62]), "Уфа"); 
 strcpy (reinterpret_cast <char*> (masNames [63]), "Оренбург"); 
}
 
treeCity::~treeCity () {
 // <--- - ---> Деструктор
 for (int i = 0; i < maxCity; i++) {
  if (cityMas [i] != 0) {
   delete cityMas [i];
  }
 }
}

int treeCity::addNode (int node, int xPos, int yPos) {
 // <--- - ---> Добавление узла
#ifdef DEBUG
 cout << "Add new node [" << node << "] x = " << xPos << " y = " << yPos << endl;
#endif
 if (node >= maxCity) {
  return -1;
 }
 cityMas [lastNode] = new nodeCity (node, xPos, yPos);
 lastNode++;
 return 0;
}

int treeCity::addNodesConnection (int nodeOneNum, int nodeTwoNum, int variance) {
 // <--- - ---> Добавление связей
 if ((nodeOneNum >= lastNode) || (nodeTwoNum >= lastNode)) {
  cout << "Неверный номер узла\n";
  return -1;
 }
 if (nodeOneNum == lastNode) {
  cout << "Один и тот же узел\n";
  return -1;
 }
 nodeCity* pNodeOne = 0;
 nodeCity* pNodeTwo = 0;
 for (int i = 0; i < maxCity; i++) {
  if (cityMas [i] != 0) {
   if (cityMas [i]->getNodeNum () == nodeOneNum) {
    pNodeOne = cityMas [i];
   }
   if (cityMas [i]->getNodeNum () == nodeTwoNum) {
    pNodeTwo = cityMas [i];
   }
  }
  if ((pNodeOne != 0) && (pNodeTwo != 0)) {
   if ((!pNodeOne->getFreeCon ()) && (!pNodeTwo->getFreeCon ())) {
    cout << "У одного из городов нет свободных линий связи\n";
    return -1;
   }
   break;
  }
 }

 // Без проверок - на весь проект всего пара дней >_<
 int res = pNodeOne->setNextNodeConn (pNodeTwo);
 pNodeOne->setVariance (res, variance); 
 res = pNodeTwo->setNextNodeConn (pNodeOne);
 pNodeTwo->setVariance (res, variance); 
 
 return OK;
}

int treeCity::getNodesNum () {
 return lastNode;
}

unsigned char* treeCity::getCityName (int num) {
 if (num > maxCity) {
  num = maxCity - 1;
 }
 return masNames [num];
}

nodeCity* treeCity::getNode (int num) {
 if (num >= lastNode) {
  return 0;
 }
 return cityMas [num];
}

void treeCity::printTree () {
 // <--- - ---> "Распечатать дерево"
 if (lastNode > 0) {
  cout << "we have " << lastNode << endl;
  for (int i = 0; i < maxCity; i++) {
   if (cityMas [i] != 0) {
    cout << masNames [i] << "\t";
    cout << " - номер [" << i << "],";
    cout << " xPos = " << cityMas [i]->getX ();
    cout << " yPos = " << cityMas [i]->getY ();
    cout << endl;
    cout << "Связи с другими городами: \n";
    int num = cityMas [i]->getConNum ();
    if (num == 0) {
     cout << "нет\n";
     cout << "----------------------------------------------------\n";
    }
    else {
     for (int j = 0; j < num; j++) {
      cout << "[" << cityMas [i]->getNodeViaCon (j)->getNodeNum () << "] ";
      cout << "\"" << masNames [cityMas [i]->getNodeViaCon (j)->getNodeNum ()] << "\"\t";
     }
     cout << endl;
     cout << "----------------------------------------------------\n";
    }
   }
  }
 }
}







