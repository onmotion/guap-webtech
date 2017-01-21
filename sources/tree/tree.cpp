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
 strcpy (reinterpret_cast <char*> (masNames [0]), "Кронштадт"); 
 strcpy (reinterpret_cast <char*> (masNames [1]), "Ленинград"); 
 strcpy (reinterpret_cast <char*> (masNames [2]), "Москва"); 
 strcpy (reinterpret_cast <char*> (masNames [3]), "Новосибирск"); 
 strcpy (reinterpret_cast <char*> (masNames [4]), "Шахты"); 
 strcpy (reinterpret_cast <char*> (masNames [5]), "Новгород"); 
 strcpy (reinterpret_cast <char*> (masNames [6]), "Минск"); 
 strcpy (reinterpret_cast <char*> (masNames [7]), "Киев"); 
 strcpy (reinterpret_cast <char*> (masNames [8]), "Ростов"); 
 strcpy (reinterpret_cast <char*> (masNames [9]), "Приозерск"); 
 strcpy (reinterpret_cast <char*> (masNames [10]), "Омск"); 
 strcpy (reinterpret_cast <char*> (masNames [11]), "Владивосток"); 
 strcpy (reinterpret_cast <char*> (masNames [12]), "Тихвин"); 
 strcpy (reinterpret_cast <char*> (masNames [13]), "Курск"); 
 strcpy (reinterpret_cast <char*> (masNames [14]), "Ейск"); 
 strcpy (reinterpret_cast <char*> (masNames [15]), "Харьков"); 
 strcpy (reinterpret_cast <char*> (masNames [16]), "Краснодар"); 
 strcpy (reinterpret_cast <char*> (masNames [17]), "Киров"); 
 strcpy (reinterpret_cast <char*> (masNames [18]), "Петергоф"); 
 strcpy (reinterpret_cast <char*> (masNames [19]), "Ломоносов"); 
 strcpy (reinterpret_cast <char*> (masNames [20]), "Сталинград"); 
 strcpy (reinterpret_cast <char*> (masNames [21]), "Тула"); 
 strcpy (reinterpret_cast <char*> (masNames [22]), "Самара"); 
 strcpy (reinterpret_cast <char*> (masNames [23]), "Рязань"); 
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







