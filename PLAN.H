#ifndef _Plan_h
#define _Plan_h

#include "ri.h"
#include "Surfaces.h"
#include "Lights.h"

class Plan : public Surfaces {
  public:         
    RtFloat   a;
    RtFloat   b;
    RtFloat   c;
    RtFloat   d;
    RtMatrix  matrice;

    RtVoid    plan_to_mat();
    RtVoid    mat_to_plan();

 
    Plan();		      // Constructeur Goineau et Bousquet
    Plan(RtFloat, RtFloat, RtFloat, RtFloat);

    Plan& operator= (Plan&);  // Overload du egal
    
    Surfaces_Pt dup();
    RtVoid      transfo( RtMatrix );
    RtVoid      stool();
    RtFloat	mat(RtInt i, RtInt j) { return (matrice.matrice[i][j]); }
    RtFloat     intersect(RtPoint& ,  RtPoint& );   
    RtPoint     normale( const RtPoint& );  // mini-projet 2
    RtVoid      preproc();           // mini-projet 2
    

};
typedef Plan  *Plan_Pt;
typedef Plan  **Plan_PtPt;


//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------

inline Plan::Plan()
{
 	a = 0.0;
	b = 0.0;
	c = 0.0;
	d = 0.0;
	matrice.RtMatrix();
}


inline Plan::Plan(RtFloat Fa, RtFloat Fb, RtFloat Fc, RtFloat Fd) 
{
 	a = Fa ;
	b = Fb ;
	c = Fc ;
	d = Fd ;

}

//--------------------------------------------------------------------------
// Overload des operateurs
//--------------------------------------------------------------------------
inline Plan& Plan::operator= (Plan& p)
{

	a = p.a;
	b = p.b;
	c = p.c;
	d = p.d;
	matrice = p.matrice;
}

#endif _Plan_h
