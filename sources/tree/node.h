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
 *  node.h - свободная программа: вы можете перераспространять ее и/или
 * изменять ее на условиях Стандартной общественной лицензии GNU в том виде,
 * в каком она была опубликована Фондом свободного программного обеспечения;
 * либо версии 3 лицензии, либо любой более поздней
 * версии.
 *
 *  node.h распространяется в надежде, что она будет полезной,
 * но БЕЗО ВСЯКИХ ГАРАНТИЙ; даже без неявной гарантии ТОВАРНОГО ВИДА
 * или ПРИГОДНОСТИ ДЛЯ ОПРЕДЕЛЕННЫХ ЦЕЛЕЙ. Подробнее см. в Стандартной
 * общественной лицензии GNU.
 * Вы должны были получить копию Стандартной общественной лицензии GNU
 * вместе с этой программой. Если это не так, см.
 * <http://www.gnu.org/licenses/>.
 *
 * Данный файл распространяется по лицензии GNU/GPL v.3 или более поздней.
 *
 * node.h - заголовочный файл класса узла.
 *
 ******************************************************************************/

#ifndef _cityNode_h_
#define _cityNode_h_
#include "appConsts.h"


class nodeCity {
 public:
 nodeCity (int num, int x, int y);
 ~nodeCity ();
 void setVariance (int farNode, int var);
 void setPos (int x, int y);
 void setNodeNum (int num);
 int setNextNodeConn (nodeCity* pNode);

 int getNodeNum ();
 int getY ();
 int getX ();
 int getFreeCon ();
 int getConNum ();
 nodeCity* getNodeViaCon (int num);
 int getVarianceViaCon (int num);

 private:
  int nodeNum;  // Номер узла
  int xPos;
  int yPos;
  nodeCity* pNodeCon [maxNodes];
  int variance [maxNodes]; // Разброс расстояния
  int lastConnection;
};
#endif
