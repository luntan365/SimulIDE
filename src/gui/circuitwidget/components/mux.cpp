/***************************************************************************
 *   Copyright (C) 2016 by santiago González                               *
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

#include "mux.h"
#include "pin.h"


Component* Mux::construct( QObject* parent, QString type, QString id )
{
        return new Mux( parent, type, id );
}

LibraryItem* Mux::libraryItem()
{
    return new LibraryItem(
        tr( "Mux" ),
        tr( "Logic" ),
        "subc.png",
        "Mux",
        Mux::construct );
}

Mux::Mux( QObject* parent, QString type, QString id )
        : LogicComponent( parent, type, id ), eMux( id.toStdString() )
{
    m_width  = 4;
    m_height = 10;

    QStringList pinList;

    pinList // Inputs:
            << "IL01 D0"
            << "IL02 D1"
            << "IL03 D2"
            << "IL04 D3"
            << "IL05 D4"
            << "IL06 D5"
            << "IL07 D6"
            << "IL08 D7"
            
            << "ID03 S0"
            << "ID02 S1 "
            << "ID01 S2 "
            
            << "IU03OE "
            
            // Outputs:
            << "OR04Y "
            << "OR06!Y "
            ;
    init( pinList );
    
    
    eLogicDevice::createOutEnablePin( m_inPin[11] );    // IOutput Enable
    
    for( int i=0; i<11; i++ )
        eLogicDevice::createInput( m_inPin[i] );
        
    eLogicDevice::createOutput( m_outPin[0] );
    eLogicDevice::createOutput( m_outPin[1] );
}
Mux::~Mux(){}

void Mux::setInvertInps( bool invert )
{
    m_invInputs = invert;
    for( int i=0; i<8; i++ )
    {
        m_input[i]->setInverted( invert );
    }
}

#include "moc_mux.cpp"
