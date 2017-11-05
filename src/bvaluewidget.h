/***************************************************************************
 *   Copyright (C) 2008 by Bernd Buschinski   *
 *   b.buschinski@web.de   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#ifndef BVALUEWIDGET_H
#define BVALUEWIDGET_H

#include <QWidget>

class ISort;
class QLabel;

class BValueWidget : public QWidget
{
Q_OBJECT

public:
    BValueWidget(ISort* aISortAlgo);
    ~BValueWidget();

public slots:
    void highlightCompare(int aIndex1, int aIndex2);
    void highlightChange(int aIndex1, int aIndex2);
    void sortFinished();
    void slotValuesChanged();

protected:
    void paintEvent( QPaintEvent * aEvent );

private:
    void inline updateTextLabel();

    void inline resetCompareVal();
    void inline resetChangeVal();

    void inline resetCount();

    ISort* mySort;

    int myCompareHigh1;
    int myCompareHigh2;
    int myChangeHigh1;
    int myChangeHigh2;
    int myHighestVal;

    quint64 myChangeCount;
    quint64 myCompareCount;

    QLabel* myPixLabel;
    QLabel* myTextLabel;
    QPixmap myPix;
    QString myName;

    bool myIsFinished;
};

#endif //BVALUEWIDGET_H
