#ifndef _3DSOLID_H_
#define _3DSOLID_H_

#include "vector.h"
#include "threed.h"

#define NUM_SHADES 255

// 32-bit number in 0x00BBGGRR form
typedef unsigned int RGBCOLOR;

#define MAKERGB(Red, Green, Blue)  static_cast<RGBCOLOR>( \
     ((Red)   & 0xFF)        |                            \
    (((Green) & 0xFF) <<  8) |                            \
    (((Blue)  & 0xFF) << 16)                              \
    )                                                     \

#define RedValue(RgbColor)    (0xFF & (RgbColor))
#define GreenValue(RgbColor)  (0xFF & ((RgbColor) >> 8))
#define BlueValue(RgbColor)   (0xFF & ((RgbColor) >> 16))

typedef VECTOR Point;

struct VERTEXLIST
{
    Point Vertex;
    VERTEXLIST *Next;
    VERTEXLIST *Prev;
    VERTEXLIST *Share;
};

struct POLYGON
{
    VERTEXLIST* Vertices;  // The vertices of the polygon
    VECTOR      Normal;    // The normal of the POLYGON
    double      d;         // The d term of the plane which contains the POLYGON
    Point       Centroid;  // Centroid of the POLYGON
    RGBCOLOR    ColorNdx;  // POLYGON's color
};

// Points to the POLYGON list data in TriL
struct PLIST
{
    POLYGON *T;     // Points to a specific polygon in the TriL
    PLIST   *Next;  // Next PLIST structure
};

struct BSPNode
{
    POLYGON* Poly;
    BSPNode* Inside;
    BSPNode* Outside;
};

#define HC_ON       0
#define HC_IN       1
#define HC_OUT      2
#define HC_SPANNING 3

// This class supports solid three-dimensional objects
class TThreeDSolid : public TThreeD
{
 public: // HACK: should be private
    long m_iPolyCount;

    BSPNode* m_Tree;     // Pointer to the root of the BSP tree

    double m_Ambient;
    double m_Diffuse;     // Contributions of light. 0 <- >- 1.0

 private:
    int m_PolyClass;      // Local variables to Recursive AddtoBSPTree

    int m_ThisPointClass;
    int m_LastInOutPointClass;

    POLYGON* m_PolyA;
    POLYGON* m_PolyB;

    double m_SideA;
    double m_SideB;

    Point m_PtA;
    Point m_PtB;

    VERTEXLIST* m_VerticesStart;
    VERTEXLIST* m_Vertices;
    VERTEXLIST* m_VerticesIn;

    VERTEXLIST* m_ShareA;
    VERTEXLIST* m_ShareB;
    VERTEXLIST* m_DeferVerticesOut;
    VERTEXLIST* m_DeferVerticesIn;

 public:
    TThreeDSolid();
    ~TThreeDSolid();

    void DisposeVertices(VERTEXLIST* v);
    void DisposeTree();
    void View();
    void AddPolygon(VERTEXLIST* Vertices, RGBCOLOR ColorNdx);
    void AddPoint(VERTEXLIST** v, Point &pt);

 private:
    void DisposePolygon(POLYGON* Poly);
    void RemovePoint(VERTEXLIST* v);
    void InsertPoint(VERTEXLIST* v, Point &pt);
    void DisposeFalseShares(VERTEXLIST* v);
    void CalcPlaneEq(POLYGON *Poly);
    void CalcPolyNormal(POLYGON *Poly);
    void PrecomputeCentroid(POLYGON *Poly);
    void DisposeBSP(BSPNode* tree);
    BSPNode* MakeBSPNode(POLYGON* Poly);
    void AddList(PLIST** tlist, POLYGON* Poly);
    double CalcSign(Point& p, POLYGON* Poly);
    void Intersect(POLYGON* Poly, Point& v1, Point& v2, Point& bc);
    void AddToBSPTree(POLYGON* T, BSPNode** Root);
    bool WorldToDisplay(double x, double y, double z, class wxPoint & disp);
    RGBCOLOR ComputeColor(Point& p, VECTOR& normal, RGBCOLOR colorNdx);
    void DisplayPolygon(POLYGON* Poly, class wxDC * DeviceContext);
    void TraverseTree(BSPNode* Tree, class wxDC * DeviceContext);
};

// global variables
extern TThreeDSolid ThreeD;

#endif // _3DSOLID_H_
