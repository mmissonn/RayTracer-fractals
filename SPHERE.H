#ifndef _Sphere_h
#define _Sphere_h

#include "ri.h"
#include "Surfaces.h"
#include "Lights.h"


class Sphere : public Surfaces {
  public:
    RtPoint centre;
    RtFloat rayon;

    Sphere();			  // Constructeur 
    Sphere& operator= (Sphere&);  // Overload du egal
    
    Surfaces_Pt dup();
    RtVoid      transfo( RtMatrix );
    RtVoid      stool();
    RtFloat     intersect(RtPoint&, RtPoint& );  
    RtPoint     normale(const RtPoint& );  
    RtVoid      preproc();           
    

    friend  RtVoid RiSphere(RtFloat, RtFloat, RtFloat, RtFloat, ... );
};
typedef Sphere  *Sphere_Pt;
typedef Sphere  **Sphere_PtPt;


//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------


inline Sphere::Sphere() 
{
 
  centre.x = 0;
  centre.y = 0;
  centre.z = 0;
  rayon  = 1;		
}


//--------------------------------------------------------------------------
// Overload des operateurs
//--------------------------------------------------------------------------
inline Sphere& Sphere::operator= (Sphere& a) 
{

	centre = a.centre;
	rayon  = a.rayon;
}

#endif
