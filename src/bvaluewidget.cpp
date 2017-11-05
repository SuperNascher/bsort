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

#include "bvaluewidget.h"

#include <QLabel>
#include <QPixmap>
#include <QGridLayout>
#include <QPainter>

#include "isort.h"

BValueWidget::BValueWidget(ISort* aISortAlgo)
    : QWidget()
{
    mySort = aISortAlgo;

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    layout->setSpacing(0);

    myPixLabel = new QLabel();
    myPixLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred );
    myTextLabel = new QLabel();
    myTextLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);

    layout->addWidget(myPixLabel);
    layout->addWidget(myTextLabel);
    setLayout( layout );
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred );

    myPix = QPixmap(200,200);
    //myPixLabel->setPixmap( myPix ); //fake label, to know the width and height

    myIsFinished = false;
    myChangeCount = 0;
    myCompareCount = 0;
    myName = mySort->name();

    slotValuesChanged();
    updateTextLabel();

    connect(mySort,SIGNAL(change(int, int)),this,SLOT(highlightChange(int, int)));
    connect(mySort,SIGNAL(compare(int, int)),this,SLOT(highlightCompare(int, int)));
    connect(mySort,SIGNAL(sortFinished()),this,SLOT(sortFinished()));
    connect(mySort,SIGNAL(valuesChanged()),this,SLOT(slotValuesChanged()));
}

BValueWidget::~ BValueWidget()
{
}

void BValueWidget::highlightCompare(int aIndex1, int aIndex2)
{
    resetChangeVal();
    resetCount();
    myCompareHigh1 = aIndex1;
    myCompareHigh2 = aIndex2;
    ++myCompareCount;
    updateTextLabel();
    update();
}

void BValueWidget::highlightChange(int aIndex1, int aIndex2)
{
    resetCompareVal();
    resetCount();
    myChangeHigh1 = aIndex1;
    myChangeHigh2 = aIndex2;
    ++myChangeCount;
    updateTextLabel();
    update();
}

void BValueWidget::resetCompareVal()
{
    myCompareHigh1 = -1;
    myCompareHigh2 = -1;
}

void BValueWidget::resetChangeVal()
{
    myChangeHigh1 = -1;
    myChangeHigh2 = -1;
}

void BValueWidget::paintEvent(QPaintEvent* aEvent)
{
    if (myPix.width() != myPixLabel->width() || myPix.height() != myPixLabel->height())
    {
        myPix = QPixmap(myPixLabel->width(), myPixLabel->height());
    }

    QPainter tPaint(&myPix);
    QList<int> tList = mySort->values();
    tPaint.fillRect(0 ,0 ,myPixLabel->width(), myPixLabel->height(), Qt::white);
    float tWidth = float(myPixLabel->width()) / float(qMax(tList.size(), 1));
    int i = 0;
    for (float tPos = 0.0f; tPos < myPixLabel->width() && i < tList.size(); tPos += tWidth, ++i)
    {
        if (tList.at(i) == 0) continue;
        if ((i == myChangeHigh1 || i == myChangeHigh2))
        {
            tPaint.setBrush( Qt::red);
            tPaint.setPen( Qt::red);
        } else if ((i == myCompareHigh1 || i == myCompareHigh2))
        {
            tPaint.setBrush( Qt::green);
            tPaint.setPen( Qt::green);
        } else {
            tPaint.setBrush( Qt::black);
            tPaint.setPen( Qt::black);
        }

        float tPer = float(myPixLabel->height())*(float(tList.value(i))/float(myHighestVal));
        tPaint.drawRect(tPos, myPixLabel->height() - tPer,tWidth, tPer );
    }
    tPaint.end();
    //myPixLabel->setPixmap( myPix ); //looks like this causes huge cpu load, but dont remove the label, we need to know the width and height
    QPainter tPaint2(this);
    tPaint2.drawPixmap(0,0,myPix);
    tPaint2.end();
    QWidget::paintEvent(aEvent);
}

void BValueWidget::sortFinished()
{
    resetChangeVal();
    resetCompareVal();
    myIsFinished = true;
    update();
}

void BValueWidget::updateTextLabel()
{
    myTextLabel->setText(myName + " Compare: " + QString::number(myCompareCount)
                         + " Change: " + QString::number(myChangeCount) );
}

void BValueWidget::resetCount()
{
    if (myIsFinished)
    {
        myChangeCount = 0;
        myCompareCount = 0;
        myIsFinished = false;
    }
}

void BValueWidget::slotValuesChanged()
{
    resetChangeVal();
    resetCompareVal();

    myHighestVal = -1;
    QList<int> tList = mySort->values();
    foreach(int tVal, tList)
        if (tVal > myHighestVal)
            myHighestVal = tVal;
    update();
}
