// Check user does not do Down,Up, RR, LR
// Check user turns between vertices
// Check number of points


// 3DSOLID.CPP: Displays a solid representation of a three-dimensional
// object. Implements the BSP algorithm described in Chapter 17 in order
// to display the surfaces of objects correctly.
#include "pch.h"

#ifndef USE_PRECOMPILED_HEADER
   #include "3dsolid.h"
   #include <stdio.h>

   #include <wx/gdicmn.h> // wxPoint
   #include <wx/dc.h>
   #include <wx/brush.h>
   #include <wx/pen.h>
   #include <wx/window.h>
#include <wx/brush.h>
   #ifndef _WINDOWS
     #define GetRValue(rgb) (((rgb) >> 0)  & 0xFF)
     #define GetGValue(rgb) (((rgb) >> 8)  & 0xFF)
     #define GetBValue(rgb) (((rgb) >> 16) & 0xFF)
     #define RGB(r, g, b) (((r) & 0xFF) | (((g) & 0xFF) << 8) | (((b) & 0xFF) << 16))
   #endif

  #include "logocore.h"
  #include "status.h"
  #include "graphics.h"
  #include "graphwin.h"
  #include "ibmterm.h"
  #include "unix.h"
  #include "screenwindow.h"
//  #include "debugheap.h"

  #include "localizedstrings.h"
#endif

const double epsilon2=0.001;
// const double epsilon3=0.001;

// Sets up the dimensions of the window and various default values
TThreeDSolid::TThreeDSolid() : TThreeD()
{
    m_Ambient = 0.30; 
    m_Diffuse = 0.60;

    Light.x = -10.0; 
    Light.y = 100; 
    Light.z = 50;

    m_Tree = NULL;
    m_iPolyCount = 0;
}

TThreeDSolid::~TThreeDSolid()
{
    DisposeTree();
}

void TThreeDSolid::DisposePolygon(POLYGON* Poly)
{
    DisposeVertices(Poly->Vertices);
    delete Poly;
}

void TThreeDSolid::DisposeTree()
{
    DisposeBSP(m_Tree);
    m_Tree = NULL;
    m_iPolyCount = 0;
}

// Sets up the dimensions of the window and various default values
void TThreeDSolid::AddPolygon(VERTEXLIST* Vertices, RGBCOLOR ColorNdx)
{
    POLYGON *t = new POLYGON;
    t->Vertices = Vertices;
    t->ColorNdx = ColorNdx;

    CalcPolyNormal(t);
    CalcPlaneEq(t);
    PrecomputeCentroid(t);

    AddToBSPTree(t, &m_Tree);
    m_iPolyCount++;
    update_status_vectors();
}

// Precompute the d term in the plane equation for each polygon.
// The normal of the plane and a point on the plane- -one of
// its vertices--are used to solve for d.
void TThreeDSolid::CalcPlaneEq(POLYGON *Poly)
{
    Poly->d = -(
        Poly->Normal.x * Poly->Vertices->Vertex.x +
        Poly->Normal.y * Poly->Vertices->Vertex.y +
        Poly->Normal.z * Poly->Vertices->Vertex.z);
}

// Calculate the normals of the POLYGONs
void TThreeDSolid::CalcPolyNormal(POLYGON *Poly)
{
    VECTOR dl = Subtract(Poly->Vertices->Vertex, Poly->Vertices->Next->Vertex);
    VECTOR d2 = Subtract(Poly->Vertices->Vertex, Poly->Vertices->Next->Next->Vertex);
    Poly->Normal = Cross(dl, d2);
    Normalize(Poly->Normal);
}

// precompute the centrolds of all the POLYGONs
void TThreeDSolid::PrecomputeCentroid(POLYGON *Poly)
{
    VERTEXLIST* vertices = Poly->Vertices;

    Poly->Centroid.x = 0;
    Poly->Centroid.y = 0;
    Poly->Centroid.z = 0;

    double d = 0;

    do
    {
        Poly->Centroid.x += vertices->Vertex.x;
        Poly->Centroid.y += vertices->Vertex.y;
        Poly->Centroid.z += vertices->Vertex.z;
        vertices = vertices->Next;
        d += 1.0;
    } while (vertices != Poly->Vertices);

    Poly->Centroid.x /= d;
    Poly->Centroid.y /= d;
    Poly->Centroid.z /= d;
}

// Dispose of the BSP tree
void TThreeDSolid::DisposeBSP(BSPNode* tree)
{
    if (tree)
    {
        DisposeBSP(tree->Outside);
        DisposeBSP(tree->Inside);
        DisposePolygon(tree->Poly);
        delete tree;
    }
}

// Create a new node for the BSP tree
BSPNode* TThreeDSolid::MakeBSPNode(POLYGON* Poly)
{
    BSPNode *node = new BSPNode;
    node->Poly = Poly;    // Point to the POLYGON's data
    node->Outside = 0;
    node->Inside = 0;
    return node;
}

// Add the POLYGON to the POLYGON list
void TThreeDSolid::AddList(PLIST** tlist, POLYGON* Poly)
{
    PLIST *l    = *tlist;
    PLIST *back = *tlist;

    PLIST *nuL = new PLIST;
    nuL->T = Poly;
    nuL->Next = 0;
    if (l)
    {
        while (l)
        {
            back = l;
            l = l->Next;
        }
        back->Next = nuL;
    }
    else
    {
        // List is empty. This is the first node.
        *tlist = nuL;
    }
}

// Calculate the sign that indicates which side of the separation
// plane vertex p is on. Note that a tolerance value is used to account
// for arithmetic round off errors by the computer. This function uses
// the fact that a plane equation is: ax + by + cz + d = 0. If p is
// on the plane and plugged into the equation, the result will be 0.
// If p is not on the plane, the sign of the result indicates which
// side of the plane the point is on.
double TThreeDSolid::CalcSign(Point& p, POLYGON* Poly)
{
    // REVISIT: use dot product here?
    double value =
        p.x * Poly->Normal.x +
        p.y * Poly->Normal.y +
        p.z * Poly->Normal.z + Poly->d;
    //	if (fabs(value) < epsilon2) return 0.0;  // The point is on the plane
    /*	else */
    return value;   // The sign of the value indicates which side p is on
}

// Uses a parameteric equation to determine where a line intersects the
// plane. The two vertices v1 and v2 are the endpoints of the line.
void TThreeDSolid::Intersect(
    POLYGON* Poly,
    Point& v1,
    Point& v2,
    Point& loc
    )
{
    double t = -
        (Poly->Normal.x * (       v1.x) + Poly->Normal.y * (       v1.y) + Poly->Normal.z * (       v1.z) + Poly->d) /
        (Poly->Normal.x * (v2.x - v1.x) + Poly->Normal.y * (v2.y - v1.y) + Poly->Normal.z * (v2.z - v1.z));

    loc.x = v1.x + t * (v2.x - v1.x);
    loc.y = v1.y + t * (v2.y - v1.y);
    loc.z = v1.z + t * (v2.z - v1.z);
}

void TThreeDSolid::AddPoint(VERTEXLIST** v, Point &pt)
{
    VERTEXLIST * vn = new VERTEXLIST;

    vn->Vertex = pt;
    vn->Share = NULL;

    if (*v)
    {
        VERTEXLIST* vp = (*v)->Prev;
        (*v)->Prev = vn;
        vp->Next = vn;
        vn->Next = *v;
        vn->Prev = vp;
    }
    else
    {
        *v = vn;
        (*v)->Next = vn;
        (*v)->Prev = vn;
    }
}

void TThreeDSolid::RemovePoint(VERTEXLIST* v)
{
    VERTEXLIST * vp = v->Prev;
    VERTEXLIST * vn = v->Next;

    delete v;
    vp->Next = vn;
    vn->Prev = vp;
}

void TThreeDSolid::InsertPoint(VERTEXLIST* v, Point &pt)
{
    VERTEXLIST* vn = new VERTEXLIST;

    vn->Vertex = pt;

    vn->Next = v->Next;
    vn->Prev = v;

    v->Next = vn;
    vn->Next->Prev = vn;
}

void TThreeDSolid::DisposeVertices(VERTEXLIST* list)
{
    VERTEXLIST* next;
    VERTEXLIST* curr;

    if (!list) return;

    curr = list;

    do
    {
        next = curr->Next;
        delete curr;
        curr = next;
    } while (curr != list);
}

void TThreeDSolid::DisposeFalseShares(VERTEXLIST* list)
{
    VERTEXLIST* curr;

    if (!list) return;
   
    curr = list;

    do
    {
        if (curr->Share)
        {
            if (curr->Share->Share == NULL)
            {
                RemovePoint(curr->Share);
            }
        }
        curr = curr->Next;
    } while (curr != list);
}

// Make the BSP tree structure
void TThreeDSolid::AddToBSPTree(POLYGON* Poly, BSPNode** Root)
{
    if (!*Root)
    {
        *Root = MakeBSPNode(Poly);
    }
    else
    {
        VERTEXLIST* VerticesOut = NULL;

        m_VerticesIn = NULL;

        m_DeferVerticesIn = NULL;
        m_DeferVerticesOut = NULL;

        m_LastInOutPointClass = HC_ON;

        m_PolyClass = HC_ON;  // assume plane_3d and polygon coincident for starters

        m_Vertices = Poly->Vertices;

        m_PtA    = m_Vertices->Vertex;
        m_SideA  = CalcSign(m_PtA, (*Root)->Poly);  // classify it relative to the plane_3d
        m_ShareA = m_Vertices->Share;

        m_Vertices = m_Vertices->Next;

        m_VerticesStart = m_Vertices;

      do
      {
          m_PtB    = m_Vertices->Vertex;
          m_SideB  = CalcSign(m_PtB, (*Root)->Poly);  // classify it relative to the plane_3d
          m_ShareB = m_Vertices->Share;

          if (m_SideB > epsilon2)  // if the current point_3d is on the positive side
          { // begin
              m_ThisPointClass = HC_OUT;
              if (m_PolyClass == HC_ON)        // if the polygon classification is on
              {
                  m_PolyClass = HC_OUT;         // classify the polygon as out
              }
              else if (m_PolyClass != HC_OUT)  // else if the polygon classification is not out
              {
                  m_PolyClass = HC_SPANNING;    // set the polygon classification to spanning
              }

              if (m_SideA < -epsilon2)         // if the previous point_3d was on the opposite side of the plane_3d
              { // begin
                  Point pt;
                  Intersect((*Root)->Poly, m_PtA, m_PtB, pt);

                  // if we are potentially on a shared seqment
                  if (m_ShareA && m_ShareB)
                  {
                      // if we are on a shared segment
                      if (m_ShareB->Next == m_ShareA)
                      {
                          AddPoint(&m_VerticesIn, pt);
                          InsertPoint(m_ShareB, pt);
                          m_VerticesIn->Prev->Share = m_ShareB->Next;

                          AddPoint(&m_VerticesIn,  pt);
                          AddPoint(&VerticesOut, pt);

                          m_VerticesIn->Prev->Share = VerticesOut->Prev;
                          VerticesOut->Prev->Share = m_VerticesIn->Prev;

                          InsertPoint(m_ShareB, pt);
                          AddPoint(&VerticesOut, pt);
                          VerticesOut->Prev->Share = m_ShareB->Next;
                      }
                      else
                      {
                          AddPoint(&m_VerticesIn,  pt);
                          AddPoint(&VerticesOut, pt);

                          m_VerticesIn->Prev->Share = VerticesOut->Prev;
                          VerticesOut->Prev->Share = m_VerticesIn->Prev;
                      }
                  }
                  else
                  {
                      AddPoint(&m_VerticesIn,  pt);
                      AddPoint(&VerticesOut, pt);

                      m_VerticesIn->Prev->Share = VerticesOut->Prev;
                      VerticesOut->Prev->Share = m_VerticesIn->Prev;
                  }
                  m_PolyClass = HC_SPANNING; // set the PolyClass appropriately
              } // end

              AddPoint(&VerticesOut, m_PtB);

              // If old vertex was share copy it to the new poly (back link later)
              if (m_ShareB)
              {
                  VerticesOut->Prev->Share = m_ShareB;
              }
          } // end
          else if (m_SideB < -epsilon2)  // the current point_3d is on the negative side
          { // begin

              m_ThisPointClass = HC_IN;
              if (m_PolyClass == HC_ON)      // if the polygon classification is on
              {
                  m_PolyClass = HC_IN;        // classify the polygon as out
              }
              else if (m_PolyClass != HC_IN) // else if the polygon classification is not out
              {
                  m_PolyClass = HC_SPANNING;	 // set the polygon classification to spanning
              }

              // if the previous point_3d was on the opposite side of the plane_3d
              if (m_SideA > epsilon2)
              { // begin
                  Point pt;
                  Intersect((*Root)->Poly, m_PtA, m_PtB, pt);

                  // if we are potentially on a shared seqment
                  if (m_ShareA && m_ShareB)
                  {
                      // if we are on a shared segment

                      if (m_ShareB->Next == m_ShareA)
                      {
                          AddPoint(&VerticesOut, pt);
                          InsertPoint(m_ShareB, pt);
                          VerticesOut->Prev->Share = m_ShareB->Next;

                          AddPoint(&VerticesOut, pt);
                          AddPoint(&m_VerticesIn,  pt);

                          VerticesOut->Prev->Share = m_VerticesIn->Prev;
                          m_VerticesIn->Prev->Share = VerticesOut->Prev;

                          InsertPoint(m_ShareB, pt);
                          AddPoint(&m_VerticesIn, pt);
                          m_VerticesIn->Prev->Share = m_ShareB->Next;
                      }
                      else
                      {
                          AddPoint(&m_VerticesIn, pt);
                          AddPoint(&VerticesOut, pt);

                          m_VerticesIn->Prev->Share  = VerticesOut->Prev;
                          VerticesOut->Prev->Share = m_VerticesIn->Prev;
                      }
                  }
                  else
                  {
                      AddPoint(&m_VerticesIn, pt);
                      AddPoint(&VerticesOut, pt);

                      m_VerticesIn->Prev->Share  = VerticesOut->Prev;
                      VerticesOut->Prev->Share = m_VerticesIn->Prev;
                  }

                  m_PolyClass = HC_SPANNING; // set the PolyClass appropriately
              } // end

              AddPoint(&m_VerticesIn, m_PtB);

              if (m_ShareB)
              {
                  m_VerticesIn->Prev->Share = m_ShareB;
              }
          } // end
          else // the current point_3d is on the plane_3d
          {
              m_ThisPointClass = HC_ON;

              if (m_ShareB)
              {
                  // If we have previous point's IN or OUT classification
                  if (m_LastInOutPointClass != HC_ON)
                  {
                      if (m_LastInOutPointClass == HC_OUT)
                      {
                          AddPoint(&m_VerticesIn, m_PtB);
                          AddPoint(&VerticesOut, m_PtB);

                          m_VerticesIn->Prev->Share = VerticesOut->Prev;
                          VerticesOut->Prev->Share  = m_VerticesIn->Prev;

                          AddPoint(&VerticesOut, m_PtB);
                          VerticesOut->Prev->Share = m_ShareB;
                      }
                      else // must be HC_IN
                      {
                          AddPoint(&VerticesOut, m_PtB);
                          AddPoint(&m_VerticesIn,  m_PtB);

                          VerticesOut->Prev->Share = m_VerticesIn->Prev;
                          m_VerticesIn->Prev->Share = VerticesOut->Prev;

                          AddPoint(&m_VerticesIn, m_PtB);
                          m_VerticesIn->Prev->Share = m_ShareB;
                      }
                  }

                  // Add both links and remove the wrong one later
                  else
                  {
                      AddPoint(&m_VerticesIn, m_PtB);
                      AddPoint(&VerticesOut, m_PtB);

                      m_VerticesIn->Prev->Share = VerticesOut->Prev;
                      VerticesOut->Prev->Share = m_VerticesIn->Prev;

                      AddPoint(&VerticesOut, m_PtB);
                      AddPoint(&m_VerticesIn, m_PtB);
                      VerticesOut->Prev->Share = m_ShareB;
                      m_VerticesIn->Prev->Share = m_ShareB;
                      // if (m_DeferVerticesIn)
                      // {
                      //     RemovePoint(m_DeferVerticesIn); // We don't handle queing these up
                      //     RemovePoint(m_DeferVerticesOut);
                      // }
                      m_DeferVerticesOut = VerticesOut->Prev;
                      m_DeferVerticesIn  = m_VerticesIn->Prev;
                  }

                  m_LastInOutPointClass = HC_ON;
              }
              else
              {
                  AddPoint(&m_VerticesIn, m_PtB);
                  AddPoint(&VerticesOut, m_PtB);

                  m_VerticesIn->Prev->Share  = VerticesOut->Prev;
                  VerticesOut->Prev->Share = m_VerticesIn->Prev;
              }
          }

          m_PtA    = m_PtB;   // copy the current point_3d to the last point_3d
          m_SideA  = m_SideB; // copy the current point_3d's side information...

          m_ShareA = m_ShareB;

          if (m_ThisPointClass == HC_IN || m_ThisPointClass == HC_OUT)
          {
              m_LastInOutPointClass = m_ThisPointClass;

              // If we deferred we can clean up now
              if (m_DeferVerticesIn)
              {
                  if (m_ThisPointClass == HC_IN)
                  {
                      RemovePoint(m_DeferVerticesOut);
                  }
                  else
                  {
                      RemovePoint(m_DeferVerticesIn);
                  }

                  m_DeferVerticesIn = NULL;
                  m_DeferVerticesOut = NULL;
              }
          }

          m_Vertices = m_Vertices->Next;

      } while (m_Vertices != m_VerticesStart);

      if (m_DeferVerticesIn)
      {
          RemovePoint(m_DeferVerticesIn);
          RemovePoint(m_DeferVerticesOut);
      }

      switch (m_PolyClass) // perform the appropriate action based on the classification
      { // begin
      case HC_OUT: // if the polygon is entirely positive
          if (m_VerticesIn ) DisposeFalseShares(m_VerticesIn);
          if (VerticesOut) DisposeFalseShares(VerticesOut);
          if (m_VerticesIn ) DisposeVertices(m_VerticesIn);
          if (VerticesOut) DisposeVertices(VerticesOut);
          AddToBSPTree(Poly, &((*Root)->Outside));
          break; // end positive

      case HC_IN: // if the polygon is entirely negative
          if (m_VerticesIn ) DisposeFalseShares(m_VerticesIn);
          if (VerticesOut) DisposeFalseShares(VerticesOut);
          if (m_VerticesIn ) DisposeVertices(m_VerticesIn);
          if (VerticesOut) DisposeVertices(VerticesOut);
          AddToBSPTree(Poly, &((*Root)->Inside));
          break; // end negative

      case HC_SPANNING: // if the polygon was plane

//        if (iPolyCount == POLYCOUNT)
//        {
//            iPolyCount = iPolyCount*1;
//        }

          // Do all back share links now

          m_Vertices = m_VerticesIn;
          do
          {
              if (m_Vertices->Share) 
              {
                  m_Vertices->Share->Share = m_Vertices;
              }
              m_Vertices = m_Vertices->Next;
          } while (m_Vertices != m_VerticesIn);


          m_Vertices = VerticesOut;
          do
          {
              if (m_Vertices->Share) 
              {
                  m_Vertices->Share->Share = m_Vertices;
              }
              m_Vertices = m_Vertices->Next;
          } while (m_Vertices != VerticesOut);

          m_PolyA = new POLYGON;
          *m_PolyA = *Poly;

          m_PolyA->Vertices = m_VerticesIn;

          AddToBSPTree(m_PolyA, &(*Root)->Inside);

          m_PolyB = new POLYGON;
          *m_PolyB = *Poly;

          m_PolyB->Vertices=VerticesOut;

          AddToBSPTree(m_PolyB, &(*Root)->Outside);

          DisposePolygon(Poly);
          break; // end spanning

      case HC_ON: // if the polygon was plane
          if (m_VerticesIn ) DisposeFalseShares(m_VerticesIn);
          if (VerticesOut) DisposeFalseShares(VerticesOut);
          if (m_VerticesIn ) DisposeVertices(m_VerticesIn);
          if (VerticesOut) DisposeVertices(VerticesOut);
          AddToBSPTree(Poly, &((*Root)->Outside));
          break; // end positive
      } // end
    }
}

// Converts a 3D world coordinate to the 2D display coordinates and stores
// it in disp.
// Returns true on success.
// Returns false, otherwise (in which case disp is not modified).
bool TThreeDSolid::WorldToDisplay(double x, double y, double z, wxPoint & disp)
{
    double xc = (x * A1.x + A1.y * y + A1.z * z + Offset.x) * DVal;
    double yc = (x * A2.x + A2.y * y + A2.z * z + Offset.y) * DVal;
    double zc = (x * A3.x + A3.y * y + A3.z * z + Offset.z);

    if (zc == 0.0) return false;

    double xm = xc /  zc;
    double ym = yc / -zc;

    if (xm >  1.0) return false;
    else if (xm < -1.0) return false;
    else if (ym >  1.0) return false;
    else if (ym < -1.0) return false;

    disp.x = ((long) g_round((A * xm + B))) + xoffset;
    disp.y = ((long) g_round((C * ym + D))) + yoffset;

    return true;
}

// Return the color to paint a polygon. Only ambient and diffuse
// lighting is used. You are looking at point p and the variable
// "normal" is the normal of the polygon. colorNdx specifies the
// desired color of the polygon.
RGBCOLOR TThreeDSolid::ComputeColor(Point& p, VECTOR& normal, RGBCOLOR colorNdx)
{
    VECTOR l = Subtract(Light, p);  // Find vector from light to point p
    Normalize(l);
    double lDotN = Dot(l, normal);
    // Calculate diffuse lighting contribution to object's color
    if (lDotN <= 0)
    {
        lDotN *= -m_Diffuse * NUM_SHADES;
    }
    else 
    {
        lDotN *= m_Diffuse * NUM_SHADES;
    }

    // Add ambient coefficient
    int Red   = (int)(GetRValue(colorNdx) + m_Ambient * NUM_SHADES + lDotN);
    int Green = (int)(GetGValue(colorNdx) + m_Ambient * NUM_SHADES + lDotN);
    int Blue  = (int)(GetBValue(colorNdx) + m_Ambient * NUM_SHADES + lDotN);
    if (Red   > 255) Red   = 255;
    if (Green > 255) Green = 255;
    if (Blue  > 255) Blue  = 255;
    return RGB(Red, Green, Blue);
}


// Display the POLYGON
void TThreeDSolid::DisplayPolygon(POLYGON* Poly, wxDC * DeviceContext)
{
    wxPoint t[4096]; // holds screen coordinates of Poly

    // PrecomputeCentroid(Poly);

    // Transform all of this polygon's verticies from 3D world coordinates to
    // 2D screen coordidates.
    VERTEXLIST * vertices = Poly->Vertices;
    size_t i = 0;
    do
    {
        if (!WorldToDisplay(vertices->Vertex.x, vertices->Vertex.y, vertices->Vertex.z, t[i]))
        {
            // There was an error that prevents us from rendering
            // this polygon.
            i = 0;
            break;
        }
        if ((i < ARRAYSIZE(t) - 1) &&
            (i == 0 || t[i-1].x != t[i].x || t[i-1].y != t[i].y))
        {
            i++;
        }
        vertices = vertices->Next;
    } while (vertices != Poly->Vertices);

    // Render the resulting polygon
    if (i > 2)
    {
        // We have at least two points, which defines an area.
        // Render the polygon onto the device context.
        const wxBrush & oldBrush = DeviceContext->GetBrush();

        RGBCOLOR color = ComputeColor(Poly->Centroid, Poly->Normal, Poly->ColorNdx);
        wxBrush polygonBrush = wxBrush(wxColor(color));
        DeviceContext->SetBrush(polygonBrush);

        DeviceContext->DrawPolygon(i, t); 

        DeviceContext->SetBrush(oldBrush);
    }
}

// Display the figure stored in the BSP tree
void TThreeDSolid::View()
{
    erase_screen();

    wxDC * memoryDeviceContext = GetWxMemoryDeviceContext();

    // Make the pen transparent so that the polygons don't have an outline.
    const wxPen oldPen(memoryDeviceContext->GetPen());
    memoryDeviceContext->SetPen(*wxTRANSPARENT_PEN);

    TraverseTree(m_Tree, memoryDeviceContext);

    memoryDeviceContext->SetPen(oldPen);

    // Refresh the screen window so that it will repainted
    // to match the memory device context.
    GetScreenWxWindow()->Refresh(false);
}

// Traverse a BSP tree, rendering a three-dimensional scene
void TThreeDSolid::TraverseTree(BSPNode* Tree, wxDC * DeviceContext)
{
    if (Tree)
    {
        VECTOR vector;
        vector.x = From.x - Tree->Poly->Vertices->Vertex.x;
        vector.y = From.y - Tree->Poly->Vertices->Vertex.y;
        vector.z = From.z - Tree->Poly->Vertices->Vertex.z;
        Normalize(vector);
        double d = Dot(vector, Tree->Poly->Normal);

        if (d > 0.0 /* epsilon3 */)
        {
            // The eye is in front of the polygon
            TraverseTree(Tree->Inside, DeviceContext); 
            DisplayPolygon(Tree->Poly, DeviceContext);
            TraverseTree(Tree->Outside, DeviceContext);
        }
        else /* if (d < -epsilon3) */
        {
            // The eye is in back of the polygon
            TraverseTree(Tree->Outside, DeviceContext);
            DisplayPolygon(Tree->Poly, DeviceContext);
            TraverseTree(Tree->Inside, DeviceContext);
        }
//      else
//      {
//          // The eye is in on the polygon
//          TraverseTree(Tree->Outside);
//          TraverseTree(Tree->Inside);
//      }
    }
}
	
