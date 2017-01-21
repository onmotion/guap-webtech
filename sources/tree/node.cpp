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
 *  node.cpp - свободная программа: вы можете перераспространять ее и/или
 * изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
 * в каком она была опубликована Фондом свободного программного обеспечения;
 * либо версии 3 лицензии, либо любой более поздней
 * версии.
 *
 *  node.cpp распространяется в надежде, что она будет полезной,
 * но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
 * или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
 * общественной лицензии GNU.
 * Вы должны были получить копию Стандартной общественной лицензии GNU
 * вместе с этой программой. Если это не так, см.
 * <http://www.gnu.org/licenses/>.
 *
 * Данный файл распространяется по лицензии GNU/GPL v.3 или более поздней.
 *
 * node.cpp - файл реализации класса узла.
 *
 ******************************************************************************/

#include "node.h"

nodeCity::nodeCity (int num, int x, int y) {
 // <--- - ---> Конструктор
 nodeNum = num;  // Номер узла
 xPos = x;
 yPos = y;
 for (int i = 0; i < maxNodes; i++) {
  pNodeCon [i] = 0;
  variance [i] = -1;
 }
 lastConnection = 0;
}	

nodeCity::~nodeCity () {
}

void nodeCity::setNodeNum (int num) {
 nodeNum = num;
}

int nodeCity::getNodeNum () {
 return nodeNum;
}

void nodeCity::setPos (int _x, int _y) {
 xPos = _x;
 yPos = _y;
}

int nodeCity::getX () {
 return xPos;
}

int nodeCity::getY () {
 return yPos;
}

void nodeCity::setVariance (int farNode, int var) {
 if (farNode > maxNodes) {
  farNode = maxNodes;
 }
 variance [farNode] = var;
}

int nodeCity::getFreeCon () {
 return maxNodes - lastConnection;
}

int nodeCity::getConNum () {
 return lastConnection;
}

int nodeCity::setNextNodeConn (nodeCity* pNode) {
 for (int i = lastConnection; i < maxNodes; i++) {
  if (pNodeCon [i] != 0) {
   continue;
  }
  pNodeCon [i] = pNode;
  lastConnection++;
  return i;
 }
 return -1;
}

nodeCity* nodeCity::getNodeViaCon (int num) {
 if (num > lastConnection) {
  return 0;
 }
 return pNodeCon [num];
}

int nodeCity::getVarianceViaCon (int num) {
 if (num > maxNodes) {
  return -1;
 }
 return variance [num];
}


