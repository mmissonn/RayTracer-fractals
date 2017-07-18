
#ifndef _Triangle_h
#define _Triangle_h

#include "ri.h"
#include "Surfaces.h"
#include "Lights.h"

class Triangle : public Surfaces {
   public: 
    RtPoint a;
    RtPoint b;
    RtPoint c;
    RtPoint norm;                  
    RtFloat norm_max;              
    RtFloat d;                     
    RtInt   index ;

    
	
    Triangle();			      // Constructeur Castor Bricoleur
    Triangle(RtPoint, RtPoint, RtPoint);

    Triangle& operator= (Triangle&);  // Overload du egal
    
    Surfaces_Pt  dup();
    RtVoid       transfo( RtMatrix );
    RtVoid       stool();
    RtFloat      intersect(RtPoint&, RtPoint& );   
    RtPoint      normale( const RtPoint& );  // mini-projet 2
    RtVoid       preproc();           // mini-projet 2
    
};
typedef Triangle  *Triangle_Pt;
typedef Triangle  **Triangle_PtPt;


//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------

inline Triangle::Triangle() 
{
	RtPoint temp;

	temp.RtPoint();

	a = temp;
	b = temp;
 	c = temp;
	norm = temp;

	

	norm_max = 1.0;
	d = 0.0;
}


inline Triangle::Triangle(RtPoint PtA, RtPoint PtB, RtPoint PtC) 
{
	

	a = PtA;
	b = PtB;
 	c = PtC;

	norm = 1.0;

	norm_max = 1.0;
	d = 0.0;
}


//--------------------------------------------------------------------------
// Overload des operateurs
//--------------------------------------------------------------------------
inline Triangle& Triangle::operator= (Triangle& t)
{
//   Triangle temp;

	a = t.a;
	b = t.b;
	c = t.c;

	

	norm  = t.norm;
	norm_max = t.norm_max;
	d = t.d;

}

#endif
