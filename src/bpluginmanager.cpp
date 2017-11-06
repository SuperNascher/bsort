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

#include "bpluginmanager.h"

#include <QDebug>
#include <QDir>
#include <QPluginLoader>
#include <iplugin.h>
#include <QThread>

BPluginManager::BPluginManager()
{
    myFinishedCount = 0;
}

BPluginManager::~ BPluginManager()
{
    unload();
}

void BPluginManager::unload()
{
    ; //no need to call me
}

QList< IPlugin* > BPluginManager::load(const QString & aPath)
{
    QDir tDir(aPath);
    if (!tDir.exists())
    {
        qWarning("path does not exists");
        return myPluginList;
    }

    QFileInfoList tList = tDir.entryInfoList(QDir::Files|QDir::NoDotAndDotDot|QDir::NoSymLinks, QDir::Name);
    foreach(QFileInfo tFile, tList)
    {
        if (!QLibrary::isLibrary(tFile.absoluteFilePath()))
            continue;
        QPluginLoader tLoader(tFile.absoluteFilePath());
        QObject *tPlugin = tLoader.instance();
        if (tPlugin)
        {
            IPlugin* tIPlugin = qobject_cast<IPlugin*>(tPlugin);
            if (tIPlugin)
            {
                myPluginList.append( tIPlugin );
                connect( tIPlugin->init(),SIGNAL(sortFinished()), this, SLOT(slotFinished()));
                qWarning() << "loaded: " << tIPlugin->name();
            }
        } else
            qWarning() << tLoader.errorString();
    }
    return myPluginList;
}

void BPluginManager::setValues(QList< int > aList)
{
    foreach(IPlugin *tPlugin, myPluginList)
    {
        aList.detach();
        tPlugin->init()->load( aList );
    }
}

void BPluginManager::run()
{
    myFinishedCount = 0;
    foreach(IPlugin *tPlugin, myPluginList)
    {
        tPlugin->init()->setCanStop(false);
        tPlugin->init()->start(QThread::NormalPriority);
    }
}

void BPluginManager::stop()
{
    foreach(IPlugin *tPlugin, myPluginList)
    {
        tPlugin->init()->setCanStop(true);
    }
}

void BPluginManager::setSleepTime(uint aMSecs)
{
    foreach(IPlugin *tPlugin, myPluginList)
    {
        tPlugin->init()->setSleepTime(aMSecs);
    }
}

void BPluginManager::slotFinished()
{
    myFinishedCount += 1;
    if (myFinishedCount == myPluginList.size())
    {
        emit finished();
        myFinishedCount = 0;
    }
}

void BPluginManager::reserveValues()
{
    foreach(IPlugin *tPlugin, myPluginList)
    {
        tPlugin->init()->reverse();
    }
}
