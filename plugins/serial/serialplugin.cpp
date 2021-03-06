/***************************************************************************
 *   Copyright (C) 2017 by santiago González                               *
 *   santigoro@gmail.com                                                   *
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
 *   along with this program; if not, see <http://www.gnu.org/licenses/>.  *
 *                                                                         *
 ***************************************************************************/

#include "serialplugin.h"
#include "circuitwidget.h"

void SerialPlugin::initialize()
{
    m_serial = new SerialPortWidget( CircuitWidget::self() );
    CircuitWidget::self()->setSerialPortWidget( m_serial );
    
    connect( CircuitWidget::self(), &CircuitWidget::dataAvailable,
                          m_serial, &SerialPortWidget::slotWriteData );
}

void SerialPlugin::terminate()
{
    delete m_serial;
}


#include "moc_serialplugin.cpp"
