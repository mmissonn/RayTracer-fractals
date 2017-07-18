#ifndef _Lights_h
#define _Lights_h

#include "ri.h"
#include <ctype.h>

class Lights {
  public:
    RtBoolean on_off;
    RtPoint   position;
    RtFloat   intensite;     // (0 <= val <= 1.0)
    RtColor   couleur;       // (0 <= val <= 1.0)

  
    RtFunc    shader_pt;
    Lights();			// Constructeur DISMAT

  
    RtBoolean  LiteBrite();
    Lights& operator= (Lights&);  // Overdose du egal

   
    RtVoid RiIlluminate(RtLightHandle, RtBoolean);
};
typedef Lights  *Lights_Pt;
typedef Lights  **Lights_PtPt;


//--------------------------------------------------------------------------
// Constructeurs
//--------------------------------------------------------------------------

inline Lights::Lights()
{
	on_off = RI_TRUE;
	position.RtPoint(0,0,1);
	intensite = 1.0;
	couleur.RtColor(1,1,1);
}



//--------------------------------------------------------------------------
// Overload des operateurs
//--------------------------------------------------------------------------


inline Lights& Lights::operator= (Lights& a)
{
	on_off = a.on_off;
	position = a.position;
	intensite = a.intensite;
	couleur = a.couleur;
}


inline RtBoolean Lights::LiteBrite()
{
 if (on_off == RI_TRUE)
	return RI_TRUE;
 else return RI_FALSE;
}


 


#endif _Lights_h
