 /*
 *      threed.cpp          logo 3D functions module              dvb
 *
 *       Copyright (C) 1995 by George Mills
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program; if not, write to the Free Software
 *      Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "pch.h"
#ifndef USE_PRECOMPILED_HEADER
    #include "threed.h"

    #include <math.h>
    #include <algorithm>

    #include <wx/gdicmn.h> // wxPoint

    #include "graphics.h"
    #include "graphwin.h"
    #include "const.h"
    #include "debugheap.h"

    #ifdef max // MS compilers #define max in windows.h
        #undef max
    #endif

    #ifdef min // MS compilers #define min in windows.h
        #undef min
    #endif
#endif

TThreeDSolid ThreeD;

TThreeD::TThreeD()
{
    // Set default values for FROM, AT, UP
    //   From.x = 1.0;  From.y = 0.0;  From.z = 0.0;
    //   At.x   = 0.0;  At.y   = 0.0;  At.z   = 0.0;
    //   Up.x   = 0.0;  Up.y   = 0.0;  Up.z   = 1.0;

    Angle = 60.0 * rads_per_degree;

    Zmin = 1000000.0;
    Zmax = -1000000.0;
}

// Convert Clipped coordinates to window coordinates
void TThreeD::WORLDtoPC(double xw, double yw, wxPoint &pc)
{
    pc.x = g_round((A * xw + B));
    pc.y = g_round((C * yw + D));
}

// Default value for AT
void TThreeD::SetAt()
{
    At.x = g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Position.x / WorldWidth;
    At.y = g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Position.y / WorldHeight;
    At.z = g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Position.z / WorldDepth;
}

void TThreeD::SetClip(double _Angle, double _Zmin, double _Zmax)
{
    Angle = _Angle * rads_per_degree;

    Zmin =  _Zmin / WorldDepth + Offset.z;
    Zmax =  _Zmax / WorldDepth + Offset.z;
    Zmin =  _Zmin / WorldDepth;
    Zmax =  _Zmax / WorldDepth;
    Zmin = -_Zmax / WorldDepth + Offset.z;
    Zmax = -_Zmin / WorldDepth + Offset.z;
    Zmin = (A3.z * (_Zmax / WorldDepth) + Offset.z);
    Zmax = (A3.z * (_Zmin / WorldDepth) + Offset.z);
}


void TThreeD::SetUp()
{
    VECTOR v;

    v.x = 0.0;
    v.y = 1.0;
    v.z = 0.0;

    Up = MVy1Multiply(g_SpecialTurtles[SPECIAL_TURTLE_EYE_FIXATION].Matrix, v);
}

void TThreeD::SetVolume()
{
    long Vt =  std::max(xoffset, yoffset);
    long Vb = -std::max(xoffset, yoffset);
    long Vr =  std::max(xoffset, yoffset);
    long Vl = -std::max(xoffset, yoffset);

    A = (Vr - Vl) / 2.0;
    B = Vl + A;
    C = (Vt - Vb) / 2.0;
    D = Vb + C;
}

// default value for FROM
void TThreeD::SetLight()
{
    Light.x = g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Position.x / WorldWidth;
    Light.y = g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Position.y / WorldHeight;
    Light.z = g_SpecialTurtles[SPECIAL_TURTLE_LIGHT_LOCATION].Position.z / WorldDepth;
}

// default value for FROM
void TThreeD::SetFrom()
{
    From.x = g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Position.x / WorldWidth;
    From.y = g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Position.y / WorldHeight;
    From.z = g_SpecialTurtles[SPECIAL_TURTLE_EYE_LOCATION].Position.z / WorldDepth;
}

// Set up parameters in the world to eye transformation.
void TThreeD::SetEye()
{
    DVal = cos(Angle / 2.0) / sin(Angle / 2.0);

    // A3 is VPN
    A3 = Subtract(At, From);
    Normalize(A3);

    // Up is VUP
    A1 = Cross(A3, Up);
    Normalize(A1);

    A2 = Cross(A1, A3);
    Normalize(A2);

    // From is VRP
    Offset.x = -A1.x * From.x - A1.y * From.y - A1.z * From.z;
    Offset.y = -A2.x * From.x - A2.y * From.y - A2.z * From.z;
    Offset.z = -A3.x * From.x - A3.y * From.y - A3.z * From.z;
}

const unsigned int NOEDGE = 0;
const unsigned int LEFTEDGE = 1;
const unsigned int RIGHTEDGE = 2;
const unsigned int BOTTOMEDGE = 4;
const unsigned int TOPEDGE = 8;
const unsigned int FRONTEDGE = 16;
const unsigned int BACKEDGE = 32;

unsigned int TThreeD::Code(const VECTOR & p) const
{
    long c = NOEDGE;

    if (p.x < -p.z) c |= LEFTEDGE;
    if (p.x > p.z) c |= RIGHTEDGE;
    if (p.y < -p.z) c |= BOTTOMEDGE;
    if (p.y > p.z) c |= TOPEDGE;
    if (p.z < Zmax) c |= BACKEDGE;
    if (p.z > Zmin) c |= FRONTEDGE;

    return (c);
}

// Clip the line in 3d coordinates
bool TThreeD::Clip3DSegment(VECTOR &p1, VECTOR &p2, wxPoint &from2d, wxPoint &to2d)
{
    double t;
    VECTOR p;

    unsigned int c1 = Code(p1);
    unsigned int c2 = Code(p2);

    while (c1 || c2)
    {
        if (c1 & c2) 
        {
            return false;
        }

        if (c1)
        {
            if (c1 & FRONTEDGE)
            {
                t = (Zmin - p1.z) / (p2.z - p1.z);
                p.x = t * (p2.x - p1.x) + p1.x;
                p.y = t * (p2.y - p1.y) + p1.y;
                p.z = t * (p2.z - p1.z) + p1.z;
                p.z = Zmin;

                p1 = p;
            }
            else if (c1 & BACKEDGE)
            {
                t = (p1.z - Zmax) / (p1.z - p2.z);
                p.x = t * (p2.x - p1.x) + p1.x;
                p.y = t * (p2.y - p1.y) + p1.y;
                p.z = t * (p2.z - p1.z) + p1.z;
                p.z = Zmax;

                p1 = p;
            }
            else if (c1 & LEFTEDGE)
            {
                t = (p1.z + p1.x) / ((p1.x - p2.x) - (p2.z - p1.z));
                p.z = t * (p2.z - p1.z) + p1.z;
                p.x = -p.z;
                p.y = t * (p2.y - p1.y) + p1.y;
                p1 = p;
            }
            else if (c1 & RIGHTEDGE)
            {
                t = (p1.z - p1.x) / ((p2.x - p1.x) - (p2.z - p1.z));
                p.z = t * (p2.z - p1.z) + p1.z;
                p.x = p.z;
                p.y = t * (p2.y - p1.y) + p1.y;
                p1 = p;
            }
            else if (c1 & BOTTOMEDGE)
            {
                t = (p1.z + p1.y) / ((p1.y - p2.y) - (p2.z - p1.z));
                p.z = t * (p2.z - p1.z) + p1.z;
                p.x = t * (p2.x - p1.x) + p1.x;
                p.y = -p.z;
                p1 = p;
            }
            else if (c1 & TOPEDGE)
            {
                t = (p1.z - p1.y) / ((p2.y - p1.y) - (p2.z - p1.z));
                p.z = t * (p2.z - p1.z) + p1.z;
                p.x = t * (p2.x - p1.x) + p1.x;
                p.y = p.z;
                p1 = p;
            }
            c1 = Code(p1);
        }
        else
        {
            if (c2 & FRONTEDGE)
            {
                t = (Zmin - p1.z) / (p2.z - p1.z);
                p.x = t * (p2.x - p1.x) + p1.x;
                p.y = t * (p2.y - p1.y) + p1.y;
                p.z = t * (p2.z - p1.z) + p1.z;
                p.z = Zmin;

                p2 = p;
            }
            else if (c2 & BACKEDGE)
            {
                t = (p1.z - Zmax) / (p1.z - p2.z);
                p.x = t * (p2.x - p1.x) + p1.x;
                p.y = t * (p2.y - p1.y) + p1.y;
                p.z = t * (p2.z - p1.z) + p1.z;
                p.z = Zmax;

                p2 = p;
            }
            else if (c2 & LEFTEDGE)
            {
                t = (p1.z + p1.x) / ((p1.x - p2.x) - (p2.z - p1.z));
                p.z = t * (p2.z - p1.z) + p1.z;
                p.x = -p.z;
                p.y = t * (p2.y - p1.y) + p1.y;
                p2 = p;
            }
            else if (c2 & RIGHTEDGE)
            {
                t = (p1.z - p1.x) / ((p2.x - p1.x) - (p2.z - p1.z));
                p.z = t * (p2.z - p1.z) + p1.z;
                p.x = p.z;
                p.y = t * (p2.y - p1.y) + p1.y;
                p2 = p;
            }
            else if (c2 & BOTTOMEDGE)
            {
                t = (p1.z + p1.y) / ((p1.y - p2.y) - (p2.z - p1.z));
                p.z = t * (p2.z - p1.z) + p1.z;
                p.x = t * (p2.x - p1.x) + p1.x;
                p.y = -p.z;
                p2 = p;
            }
            else if (c2 & TOPEDGE)
            {
                t = (p1.z - p1.y) / ((p2.y - p1.y) - (p2.z - p1.z));
                p.z = t * (p2.z - p1.z) + p1.z;
                p.x = t * (p2.x - p1.x) + p1.x;
                p.y = p.z;
                p2 = p;
            }
            c2 = Code(p2);
        }
    }

    if (p1.z == 0.0)
    {
        WORLDtoPC(p1.x, p1.y, from2d);
    }
    else
    {
        WORLDtoPC(p1.x / p1.z, p1.y / p1.z, from2d);
    }

    if (p2.z == 0.0)
    {
        WORLDtoPC(p2.x, p2.y, to2d);
    }
    else
    {
        WORLDtoPC(p2.x / p2.z, p2.y / p2.z, to2d);
    }

    return true;
}

// Clip the line in 3d coordinates
bool TThreeD::Clip3DPoint(VECTOR &p1, wxPoint &from2d)
{
    unsigned int c1 = Code(p1);

    if (c1) 
    {
        return false;
    }

    if (p1.z == 0.0)
    {
        WORLDtoPC(p1.x, p1.y, from2d);
    }
    else
    {
        WORLDtoPC(p1.x / p1.z, p1.y / p1.z, from2d);
    }

    return true;
}

// Transform 3d line to screen coordinates
bool TThreeD::TransformSegment(VECTOR &from3d, VECTOR &to3d, wxPoint &from2d, wxPoint &to2d)
{
    VECTOR p1;
    VECTOR p2;

    p1.x = (from3d.x * A1.x + A1.y * from3d.y + A1.z * from3d.z + Offset.x) * DVal;
    p1.y = (from3d.x * A2.x + A2.y * from3d.y + A2.z * from3d.z + Offset.y) * DVal;
    p1.z = (from3d.x * A3.x + A3.y * from3d.y + A3.z * from3d.z + Offset.z);

    p2.x = (to3d.x * A1.x + A1.y * to3d.y + A1.z * to3d.z + Offset.x) * DVal;
    p2.y = (to3d.x * A2.x + A2.y * to3d.y + A2.z * to3d.z + Offset.y) * DVal;
    p2.z = (to3d.x * A3.x + A3.y * to3d.y + A3.z * to3d.z + Offset.z);

    return Clip3DSegment(p1, p2, from2d, to2d);
}

// Transform 3d line to screen coordinates
bool TThreeD::TransformPoint(VECTOR &from3d, wxPoint &from2d)
{
    VECTOR p1;

    p1.x = (from3d.x * A1.x + A1.y * from3d.y + A1.z * from3d.z + Offset.x) * DVal;
    p1.y = (from3d.x * A2.x + A2.y * from3d.y + A2.z * from3d.z + Offset.y) * DVal;
    p1.z = (from3d.x * A3.x + A3.y * from3d.y + A3.z * from3d.z + Offset.z);

    return Clip3DPoint(p1, from2d);
}

