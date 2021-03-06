/***************************************************************************
 *   Copyright (C) 2012 by santiago González                               *
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

#include "e-latch_d.h"

eLatchD::eLatchD( std::string id, int channels )
    : eLogicDevice( id )
{
    //setNumChannels( channels );
}
eLatchD::~eLatchD()
{ 
}

void eLatchD::initialize()
{
    if( !m_clockPin )
    {
        //qDebug() << "eLatchD::initialize !m_clockPin";
        for( uint i=0; i<m_input.size(); i++ )
        {
            eNode* enode = m_input[i]->getEpin()->getEnode();
            if( enode ) enode->addToChangedFast(this);
        }
    }
    eLogicDevice::initialize();
}

/*void eLatchD::setInverted( bool inverted )
{
    for( int i=0; i>m_numOutputs; i++ )
        m_output[i]->setInverted( inverted );
}*/

void eLatchD::setVChanged()
{
    if( m_outEnablePin )
    {
        bool outEnPrev = m_outEnable;
        bool outEn = eLogicDevice::outputEnabled();
        
        if( outEnPrev != outEn ) eLogicDevice::setOutputEnabled( outEn );
    }
    if( m_inEnablePin )
    {
        if( !eLogicDevice::inputEnabled() ) return;
    }
    if( !m_clockPin || (eLogicDevice::getClockState()==Rising) )
    {
        for( int i=0; i<m_numOutputs; i++ )
            eLogicDevice::setOut( i, getInputState( i ) );
    }
}

void eLatchD::setNumChannels( int channels ) { createPins( channels, channels); }

