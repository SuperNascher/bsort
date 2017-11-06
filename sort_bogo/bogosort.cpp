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

#include "bogosort.h"
#include <brand.h>

BogoSort::BogoSort()
    : ISort()
{
}

BogoSort::~BogoSort()
{
}

bool BogoSort::isSorted()
{
    for (int i = 1; i < myList.size(); i++)
    {
        emit compare(i-1, i);
        msleep(sleeptime());
        if (myList.at(i) < myList.at(i-1))
            return false;
    }
    return true;
}

void BogoSort::run()
{
    if (myList.isEmpty())
    {
        qWarning("sorting empty list?");
    }

    int i, j, tmp;
    int const maxIndex = myList.size() - 1;

    while (isSorted() == false)
    {
        if (canStop())
            return; // do not mark sort as finished

        // Get random list positions and swap the list entries.
        do
        {
            i = brand(maxIndex);
            j = brand(maxIndex);
        } while (i == j);

        emit change(i, j);
        msleep( sleeptime() );
        tmp = myList[i];
        myList[i] = myList[j];
        myList[j] = tmp;
    }
    emit sortFinished();
}

void BogoSort::start(QThread::Priority aVal)
{
    QThread::start( aVal );
}

QString BogoSort::name() const
{
    return "BogoSort";
}
