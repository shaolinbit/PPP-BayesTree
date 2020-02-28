/// @file QZSEphemerisStore.cpp
/// Class for storing and/or computing position, velocity, and clock data using
/// tables of <SatID, <time, QZSEphemeris> >. Inherits OrbitEphStore, which includes
/// initial and final times and search methods. QZSEphemeris inherits OrbitEph and
/// adds health and accuracy information, which this class makes use of.

//============================================================================
//
//  This file is part of GPSTk, the GPS Toolkit.
//
//  The GPSTk is free software; you can redistribute it and/or modify
//  it under the terms of the GNU Lesser General Public License as published
//  by the Free Software Foundation; either version 2.1 of the License, or
//  any later version.
//
//  The GPSTk is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with GPSTk; if not, write to the Free Software Foundation,
//  Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110, USA
//
//  Copyright 2004, The University of Texas at Austin
//
//============================================================================

//============================================================================
//
//This software developed by Applied Research Laboratories at the University of
//Texas at Austin, under contract to an agency or agencies within the U.S.
//Department of Defense. The U.S. Government retains all rights to use,
//duplicate, distribute, disclose, or release this software.
//
//Pursuant to DoD Directive 523024
//
// DISTRIBUTION STATEMENT A: This software has been approved for public
//                           release, distribution is unlimited.
//
//=============================================================================

#include <iostream>
#include <fstream>
#include <iomanip>

#include "QZSEphemerisStore.hpp"
#include "QZSWeekSecond.hpp"

using namespace std;
using namespace gpstk::StringUtils;

namespace gpstk
{
//-----------------------------------------------------------------------------
// See notes in the .hpp. This function is designed to be called AFTER all elements
// are loaded. It can then make adjustments to time relationships based on
// inter-comparisons between sets of elements that cannot be performed until the
// ordering has been determined.
void QZSEphemerisStore::rationalize(void)
{
}

//-----------------------------------------------------------------------------
// Add all ephemerides to an existing list<QZSEphemeris> for given satellite
// If sat.id is -1 (the default), all ephemerides are added.
// @return the number of ephemerides added.
int QZSEphemerisStore::addToList(list<QZSEphemeris>& qzslist, SatID sat) const
{
    // get the list from OrbitEphStore
    list<OrbitEph*> oelst;
    OrbitEphStore::addToList(oelst,SatID(-1,SatID::systemQZSS));

    int n(0);
    list<OrbitEph*>::const_iterator it;
    for(it = oelst.begin(); it != oelst.end(); ++it)
    {
        OrbitEph *ptr = *it;
        QZSEphemeris *qzsptr = dynamic_cast<QZSEphemeris*>(ptr);
        QZSEphemeris qzseph(*qzsptr);
        qzslist.push_back(qzseph);
        n++;
    }

    return n;
}

} // namespace
