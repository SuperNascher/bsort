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

#include "shellsort.h"

ShellSort::ShellSort()
{
}

ShellSort::~ ShellSort()
{
}

QString ShellSort::name() const
{
    return "ShellSort";
}

void ShellSort::start(QThread::Priority aVal)
{
    QThread::start(aVal); //FIXME kind of hack to workaround plugin issue
}

void ShellSort::run()
{
    if (myList.isEmpty())
    {
        qWarning("sorting empty list?");
    }

    int tStep = myList.size() -1;
    int start,i,j;

    do
    {
        tStep/=2;
        for(start = 0 ; start < tStep ; ++start)
        {
            for(i= start + 1 ; i < myList.size() ; i += tStep)
            {
                for( j = i - 1 ; j >= 0 ; j-= tStep)
                {
                    if(canStop())
                        break;
                    emit compare(j,j + tStep);
                    msleep( sleeptime() );
                    if( (j+tStep) < myList.size() && myList.at(j) > myList.at(j+tStep) )
                    {
                        emit change(j,j+tStep);
                        msleep( sleeptime() );
                        int tmp = myList.at(j+tStep);
                        myList[j+tStep] = myList[j];
                        myList[j] = tmp;
                    } else
                        break;
                }
                if(canStop())
                    break;
            }
            if(canStop())
                break;
        }
        if(canStop())
            break;
    } while(tStep > 0);
    emit sortFinished();
}
