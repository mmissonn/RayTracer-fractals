#ifndef _Attributes_h
#define _Attributes_h

#include "ri.h"

class Attributes {
  public:
    RtColor  couleur;    //                  (0 <= val <= 1.0)
    RtColor  opacite;    // non implemente   (0 <= val <= 1.0)
    RtFloat  ka;         // ambiant          (0 <= val <= 1.0)
    RtFloat  kd;         // diffus (gouraud) (0 <= val <= 1.0)
    RtFloat  ks;         // specular (phong) (0 <= val <= 1.0)
    RtFloat  kr;         // reflected        (0 <= val <= 1.0)
    RtFloat  kt;         // transmitted      (0 <= val <= 1.0)
    RtFloat  n;          // index refract.   (val >= 1.0)
    RtFloat  size;       // exp. of phong    (val >= 1.0)

    RtColor  specularcolor ;	// couleur speculaire

    RtFunc   shader_pt;  // pointe sur la fonction realisant le shading


    Attributes();                         // Constructeur

    Attributes& operator= (Attributes&);  // Overload du egal

    void shadeur_pt(RtFunc shadeur_pt) { shader_pt = shadeur_pt; }

 

    RtVoid  RiColor( RtColor );
    RtVoid  RiSurface( RtFunc, ... );
};


//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------
inline Attributes::Attributes()
{
	couleur.RtColor() ;
	opacite.RtColor() ;
	specularcolor = 1.0  ;	// blanc par defaut
	ka   = 0.5;
	kd   = 0.5;
	ks   = 0.0;
	kr   = 0.0;
	kt   = 0.0;
	n    = 1.0;
	size = 1.0;
	shader_pt = NULL;


}



//--------------------------------------------------------------------------
// Overload des operateurs
//--------------------------------------------------------------------------
inline Attributes& Attributes::operator= (Attributes& a)
{
  	couleur = a.couleur;
	specularcolor = a.specularcolor;
	opacite = a.opacite;
  	ka = a.ka;
	kd = a.kd;
	ks = a.ks;
	kr = a.kr;
	kt = a.kt;
	n  = a.n;
	size = a.size;
	shader_pt = a.shader_pt;

	
}




class StackAttributes {
	private:
		Attributes	A[20];	// Matrice qui sera poussee
		RtInt		top;
	public:
		RtVoid	   reset()  { top = 0; }
		RtVoid	   push(const Attributes& B) { top++; A[top] = B ;  }
		Attributes& pop() { return(A[top--]); }
		RtBoolean  empty() { return(top == 0); }
		RtBoolean  full() { return (top == 19); }
};


#endif
