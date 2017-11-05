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

#include "test.h"

#include <QDebug>

Test::Test()
{
    {
        QPluginLoader tLoader("/home/buscher/QT/bsort/bin/libsort_bubble.so");
        qWarning() << tLoader.errorString();



        IPlugin* tPlugin = qobject_cast<IPlugin *>(tLoader.instance());
        if (tPlugin)
            qDebug("yes tPlugin");
        else
            qDebug("no tPlugin");
        qWarning() << tPlugin->name();

        ISort* tSort = tPlugin->init();
        if (tSort)
            qDebug("yes tSort");
        else
            qDebug("no tSort");
    // tSort->run();

        //ISort *tbla = new ISort();
        QObject::connect(tSort, SIGNAL(compare(int, int)),this,SLOT(doit(int,int)));
//         tSort->run();

    }
}
