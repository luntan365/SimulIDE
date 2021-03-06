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

#include <cmath>

#include "capacitor.h"
#include "connector.h"
#include "itemlibrary.h"


Component* Capacitor::construct( QObject* parent, QString type, QString id )
{ return new Capacitor( parent, type, id ); }

LibraryItem* Capacitor::libraryItem()
{
    return new LibraryItem(
            tr( "Capacitor" ),
            tr( "Passive" ),
            "capacitor.png",
            "Capacitor",
            Capacitor::construct);
}

Capacitor::Capacitor( QObject* parent, QString type, QString id )
    : Component( parent, type, id ), eCapacitor( id.toStdString() )
{
    m_ePin.resize(2);
    m_pin.resize(2);
    
    m_area = QRectF( -10, -10, 20, 20 );

    QString nodid = m_id;
    nodid.append(QString("-lPin"));
    QPoint nodpos = QPoint(-16-8,0);
    m_pin[0] = new Pin( 180, nodpos, nodid, 0, this);
    m_pin[0]->setLength(12);
    m_pin[0]->setPos(-16, 0 );
    m_ePin[0] = m_pin[0];

    nodid = m_id;
    nodid.append( QString("-rPin") );
    nodpos = QPoint(16+8,0);
    m_pin[1] = new Pin( 0, nodpos, nodid, 1, this );
    m_pin[1]->setLength(12);
    m_pin[1]->setPos( 16, 0 );
    m_ePin[1] = m_pin[1];
    
    m_unit = "F";
    setCapac( m_cap );
    setValLabelPos(-16, 8, 0);
    setShowVal( true );

    setLabelPos(-16,-24, 0);

    /*const QFont sansFont("Helvetica [Cronyx]", 7);
    m_labelcurr = Circuit::self()->addSimpleText( id.toLatin1().data(), sansFont );
    m_labelcurr->setParentItem( this );
    m_labelcurr->setPos(-13, -5.5 );
    //m_labelcurr->rotate( 180-dir );
    m_labelcurr->setText( QString("%1").arg(m_resist) );*/
}
Capacitor::~Capacitor(){}

double Capacitor::capac() { return m_value; }

void Capacitor::setCapac( double c ) 
{ 
    Component::setValue( c );       // Takes care about units multiplier
    eCapacitor::setCap( m_value*m_unitMult );
}

void Capacitor::setUnit( QString un ) 
{
    Component::setUnit( un );
    eCapacitor::setCap( m_value*m_unitMult );
}

void Capacitor::paint( QPainter* p, const QStyleOptionGraphicsItem* option, QWidget* widget )
{
    Component::paint( p, option, widget );

    QPen pen = p->pen();
    pen.setWidth(3);
    p->setPen(pen);

    p->drawLine(-3,-6,-3, 6 );
    p->drawLine( 3,-6, 3, 6 );
}

#include "moc_capacitor.cpp"
