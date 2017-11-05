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

#include "quicksort.h"

QuickSort::QuickSort()
{
}

QuickSort::~ QuickSort()
{
}

QString QuickSort::name() const
{
    return "QuickSort";
}

void QuickSort::start(QThread::Priority aVal)
{
    QThread::start(aVal); //FIXME kind of hack to workaround plugin issue
}

void QuickSort::run()
{
    if (myList.isEmpty())
    {
        qWarning("sorting empty list?");
    }

    quickSort(0,myList.size()-1);
    emit sortFinished();
}

void QuickSort::quickSort(int l, int r)
{
    if(canStop())
        return;
    if (r > l)
    {
        int i = l - 1;
        int j = r;
        int tmp;
        for (;;)
        {
            if(canStop())
                return;
            emit compare(i+1,r);
            msleep( sleeptime() );
            while (myList.at(++i) < myList.at(r)) ;
            emit compare(j-1,r);
            msleep( sleeptime() );
            while(myList.at(--j) > myList.at(r) && j > i) ;
            if(i >= j) break;

            emit change(i,j);
            msleep( sleeptime() );
            tmp=myList.at(i);
            myList[i] = myList[j];
            myList[j]=tmp;
        }

        if (i != r)
        {
            emit compare(i,r);
            msleep( sleeptime() );
            if (myList.at(i) > myList.at(r))
            {
                emit change(i,r);
                msleep( sleeptime() );
                tmp = myList.at(i);
                myList[i] = myList[r];
                myList[r] = tmp;
            }
        }

        quickSort(l, i-1);
        quickSort(i+1, r);
    }
}
