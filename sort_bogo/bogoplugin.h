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

#ifndef BOGOPLUGIN_H
#define BOGOPLUGIN_H

#include <iplugin.h>
#include <isort.h>

#include <QObject>

#include "bogosort.h"

class Q_DECL_EXPORT BogoPlugin : public QObject, IPlugin
{
    Q_OBJECT
    Q_INTERFACES(IPlugin)
    Q_PLUGIN_METADATA(IID "de.buschinski.bogoplugin")

public:
    BogoPlugin();
    ~BogoPlugin();

    ISort* init();

    QString name() const;
private:
    BogoSort* mySort;
};

#endif //BOGOPLUGIN_H
