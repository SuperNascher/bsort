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

#include "bubblesort.h"

BubbleSort::BubbleSort()
    : ISort()
{
}

BubbleSort::~ BubbleSort()
{
}

void BubbleSort::run()
{
    if (myList.isEmpty())
    {
        qWarning("sorting empty list?");
    }

    for (int i = 0; i+1 < myList.size(); ++i)
    {
        if(canStop())
            break;
        bool tNotChanged = true;
        for (int j = 0; j+1 < (myList.size()-i); ++j)
        {
            if(canStop())
                break;
            emit compare(j,j+1);
            msleep( sleeptime() );
            if (myList.at(j) > myList.at(j+1))
            {
                tNotChanged = false;
                int tmp = myList.at(j+1);
                myList[j+1] = myList[j];
                myList[j] = tmp;
                emit change(j,j+1);
                msleep( sleeptime() );
            }
        }
        if (tNotChanged)
        {
            emit sortFinished();
            return;
        }
    }
    emit sortFinished();
}

void BubbleSort::start(QThread::Priority aVal)
{
    QThread::start( aVal );
}


QString BubbleSort::name() const
{
    return "BubbleSort";
}
