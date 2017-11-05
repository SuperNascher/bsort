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

#include "bmainwindow.h"

#include <iplugin.h>

#include "bpluginmanager.h"
#include "bvaluewidget.h"
#include "brand.h"


BMainWindow::BMainWindow()
    : QMainWindow()
{
    setupUi(this);
    statusBar()->setVisible(false);
    myManager = new BPluginManager();
    myPluginList = myManager->load(QApplication::applicationDirPath());
    slotGenerateRandomData();
    myManager->setSleepTime( mySpeedSlider->value() );
    QVBoxLayout *layout = new QVBoxLayout;
    for (int i = 0; i < myPluginList.size(); ++i)
    {
        ISort* tSort = myPluginList.at(i)->init();
        layout->addWidget( new BValueWidget(tSort) );
    }

    mySortFrame->setLayout( layout );
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred );

    enableButtons();

    connect(myStartButton, SIGNAL(clicked()),this,SLOT(slotStart()));
    connect(mySpeedSlider, SIGNAL(valueChanged(int)),this,SLOT(slotUpdateTime(int)));
    connect(myStopButton,SIGNAL(clicked()),this,SLOT(slotStop()));
    connect(myManager, SIGNAL(finished()),this,SLOT(slotFinished()));
    connect(myGenerateDataButton, SIGNAL(clicked()),this,SLOT(slotGenerateRandomData()));
    connect(myReverseButton, SIGNAL(clicked()),myManager,SLOT(reserveValues()));
}

void BMainWindow::slotStart()
{
    myManager->run();
    disableButtons();
}

void BMainWindow::slotStop()
{
    myManager->stop();
    enableButtons();
}

void BMainWindow::slotUpdateTime(int aValue)
{
    myManager->setSleepTime(aValue);
}

void BMainWindow::slotFinished()
{
    enableButtons();
}

void BMainWindow::slotGenerateRandomData()
{
    QList<int> tList;
    for (int i = 0; i < myCountSpinBox->value(); ++i)
        tList.append(brand(100));
    myManager->setValues(tList);
}

void BMainWindow::enableButtons()
{
    myStartButton->setEnabled(true);
    myGenerateDataButton->setEnabled(true);
    myReverseButton->setEnabled(true);

    myStopButton->setEnabled(false);
}

void BMainWindow::disableButtons()
{
    myStartButton->setEnabled(false);
    myGenerateDataButton->setEnabled(false);
    myReverseButton->setEnabled(false);

    myStopButton->setEnabled(true);
}
