#ifndef _Quad_h
#define _Quad_h

#include "ri.h"
#include "Surfaces.h"
#include "Lights.h"

class Quad : public Surfaces {
  public:         
    RtFloat   a;
    RtFloat   b;
    RtFloat   c;
    RtFloat   d; 
    RtFloat   e;
    RtFloat   f;
    RtFloat   g;
    RtFloat   h;
    RtFloat   j;
    RtFloat   k;

    RtMatrix  matrice;

    RtVoid    quad_to_mat();
    RtVoid    mat_to_quad();

    Quad();   // Constructeur
    Quad(RtFloat, RtFloat, RtFloat, RtFloat,
         RtFloat, RtFloat, RtFloat, RtFloat,
         RtFloat, RtFloat); 
 
    Quad& operator= (Quad&);  // Overload du egal
    
    Surfaces_Pt dup();
    RtVoid      transfo( RtMatrix );
    RtVoid      stool();
    RtFloat	mat(RtInt i, RtInt j) { return (matrice.matrice[i][j]); }
    RtFloat     intersect(RtPoint& ,  RtPoint& );   
    RtPoint     normale( const RtPoint& );  
    RtVoid      preproc();          
    friend RtVoid PolyQuadric( RtFloat a, RtFloat b, RtFloat c, RtFloat d,
                               RtFloat e, RtFloat f, RtFloat g, RtFloat h,
                               RtFloat j, RtFloat k, ...);
};
typedef Quad  *Quad_Pt;
typedef Quad  **Quad_PtPt;


//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------

inline Quad::Quad()
{
 	a = 0.0;
	b = 0.0;
	c = 0.0;
	d = 0.0;
        e = 0.0;
        f = 0.0;
        g = 0.0;
        h = 0.0;
        j = 0.0;
        k = 0.0;
	matrice.RtMatrix();
}

inline Quad::Quad( RtFloat Fa, RtFloat Fb, RtFloat Fc, RtFloat Fd,
                   RtFloat Fe, RtFloat Ff, RtFloat Fg, RtFloat Fh,
                   RtFloat Fj, RtFloat Fk )
{
 	a = Fa ;
	b = Fb ;
	c = Fc ;
	d = Fd ;
        e = Fe ;
	f = Ff ;
	g = Fg ;
	h = Fh ;
	j = Fj ;
	k = Fk ;


}

//--------------------------------------------------------------------------
// Overload des operateurs
//--------------------------------------------------------------------------
inline Quad& Quad::operator= (Quad& p)
{

	a = p.a;
	b = p.b;
	c = p.c;
	d = p.d;
	e = p.e;
	f = p.f;
	g = p.g;
	h = p.h;
	j = p.j;
	k = p.k;
	
	matrice = p.matrice;
}

#endif _Quad_h
