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

#ifndef ISORT_H
#define ISORT_H

#include <QObject>
#include <QThread>

class ISort : public QObject
{
    Q_OBJECT

public:
    ISort();
    ~ISort();

    void setSleepTime(uint aMSecs);
    uint sleeptime();

    bool canStop();
    void setCanStop(bool aStop);

    void reverse();

    virtual bool load(QList<int> aList);
    //virtual void run();
    virtual void start(QThread::Priority aVal);
    virtual QList<int> values() const;
    virtual QString name() const;

signals:
    void compare(int aIndex1, int aIndex2);
    void change(int aIndex1, int aIndex2);
    void sortFinished();
    void valuesChanged();

protected:
    bool myCanStop;
    uint mySleepMSecs;
    QList<int> myList;
};

#endif //ISORT_H
