#ifndef _Surfaces_h
#define _Surfaces_h


#include "ri.h"

class Surfaces : public Attributes {
  public:

    Lights_Pt  light_pt[MAX_LIGHT];   // light list
    RtInt      nb_lumiere = 0;
        
    Affecte(Lights_Pt Lumiere);
    Affecte(Surfaces *);

    virtual Surfaces*  dup() { return 0 ; }
    virtual RtVoid     transfo( RtMatrix ) { return; }
    virtual RtVoid     stool() { return; }
    virtual RtFloat    intersect(RtPoint& , RtPoint&) { return 0.0 ; }   
    virtual RtPoint    normale(const RtPoint& ) { RtPoint ret; ret = 0.0 ; return ret; }  
    virtual RtVoid     preproc() { return ; } 
          
};
typedef Surfaces  *Surfaces_Pt;
typedef Surfaces  **Surfaces_PtPt;

//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------




//--------------------------------------------------------------------------
// Overload des operateurs
//--------------------------------------------------------------------------


inline Surfaces::Affecte(Lights_Pt Lumiere)
{
 if (nb_lumiere  <  MAX_LIGHT)
		light_pt[nb_lumiere++] = Lumiere;
    else {
	cerr << "\nDepassement du nombre de lumieres disponibles ! ";       
	} // else 

}

inline Surfaces::Affecte(Surfaces *object)
{
  couleur = object->couleur;
  ka = object-> ka;
  kd = object-> kd;
  ks = object-> ks;
  kr = object-> kr;
  kt = object-> kt;
  n = object-> n;
  size = object-> size;
  shader_pt = object->shader_pt;
}

inline Surfaces** operator += (Surfaces** vect, Surfaces& l)
{
  // Trouver la fin de la liste indiquee par un NULL
  for(int i = 0; (vect[i]!=0) && (i < MAX_SURFACE); i++);
  
  if(i < MAX_SURFACE)
  {
      vect[i] = &l;

      // Met un NULL a la fin de la liste
      if(++i < MAX_SURFACE)
        vect[i] = 0;
  }
  else
  {
     cerr << "\n\nErreur : table saturee-> manque de memoire\n";
     delete &l;
  }

  return vect;

}


#endif
