

#include <math.h>
#ifndef __MSDOS__
#include <stream.h>
#else 
#include <iostream.h>
#endif

#include "ray.h"
#include "ray_2.h"
#include "shader.h"

// --- variables externes ---
extern Surfaces_Pt  surf_list[];
extern Lights_Pt    light_list[];
extern RtColor     Cs ;                // Surface color
extern RtColor     Os ;                // Surface opacity
extern RtPoint     P ;                 // Surface position
extern RtPoint     N ;                 // Surface shading normal
extern RtPoint     Ng ;                // Surface geometric normal
extern RtPoint     L ;                 // Dir. from surf. to light source
extern RtColor     Cl ;                // Light color
extern RtPoint     I ;                 // Dir. of incoming ray
extern RtColor     Ci ;                // Color of light from surface
extern RtColor     Oi ;                // Opacity of surface
extern RtPoint     E ;                 // Position of the camera
 
// --- variables globalles ---
extern Lights_Pt       current_light ;
extern Surfaces_Pt     current_surf ;

#define illuminance(a,b,c)  for (int i=0; Poly_Illuminance(&i,a,b,c);i++)
#define illuminate(a,b,c)   if ( Poly_Illuminate(a,b,c) )



// ********************** Standard Shaders ***********************************

// --- --- --- --- matte --- --- --- --- ---
//
//   simple diffusely-reflecting surface
//   (cf: RenderMan p.335)
//
RtVoid matte()
{
RtFloat  Ka, Kd;
RtColor  temp1,temp2;

Ka = current_surf->ka;
Kd = current_surf->kd;

if (Ka > RI_EPSILON)
  temp1 = Ka * ambient();
if (Kd > RI_EPSILON)
  temp2 = Kd * diffuse(N);
Oi = Os ;
Ci = Os * Cs * (temp1  + temp2 ) ;
}

RtColor specular(const RtPoint& N, const RtPoint& I1, RtFloat rg)
{
  RtColor temp;
  RtFloat a1,a2;
  
  illuminance(N,I1,rg)
    {
      a1 = RtFloat(reflect(normalize(-L),N) * I);
      if (a1 < 0.0)
	{
	  a2 = RtFloat(pow_1(double(-a1),double(rg)));
	  temp = temp + (a2 * Cl);
	}
    }
  return (temp);
}

RtFloat pow_1(RtFloat x,RtFloat a)
{
int i = int(1*a);
RtFloat temp = x;

if (i == 0)
   return (1.0);
if (i == 1)
   return (x);
if (x == 0)
   return (x);
for(i = abs(i); i > 1; i--)
   temp *= x;
return (temp);
}

RtVoid constant()
{
         Oi = Os;
	 Ci = Cs * Os;
}

RtVoid metal()
{
   Oi = Os;
   Ci = Os * Cs * ( (current_surf->ka * ambient()) + 
        (current_surf->ks * specular(N,I,current_surf->size))); 
}
RtVoid checker()
{
 RtFloat xm = (fmod(P.x * current_surf->Freq,1.0));
 RtFloat ym = (fmod(P.y * current_surf->Freq,1.0));
 RtFloat zm = (fmod(P.z * current_surf->Freq,1.0));
 RtColor temp;
 RtBoolean flag;

 if (P.x < 0.0)
   xm += 1.0;
 if (P.y < 0.0)
   ym += 1.0;
 if (P.z < 0.0)
   zm += 1.0;
 if (zm < 0.5 )
   {
     if ( xm < 0.5)
       {
	 if( ym < 0.5)
	   temp = Cs;
	 else
	   temp = current_surf->coul_car;
       }
     else
       {
	 if (ym > 0.5)
	   temp = Cs;
	 else
	   temp  = current_surf->coul_car;
       }
   }
 else
   {
     if ( xm < 0.5)
       {
	 if( ym < 0.5)
	   temp  = current_surf->coul_car;
	 else
	   temp = Cs;
       }
     else
       {
	 if (ym > 0.5)
	   temp  = current_surf->coul_car;
	 else
	   temp = Cs;
       }
   }

 Ci = temp;
 Oi = Os;
 Ci = Oi*Ci*((current_surf->ka * ambient()) +
              (current_surf->kd * diffuse(N)) ); 
}


RtVoid plastic()
{
  Oi = Os;
  Ci = Os *((Cs *((current_surf->ka*ambient()) + 
		   (current_surf->kd*diffuse(N))))
	    + (current_surf->ks *(current_surf->specularcolor * 
				  specular(N,I,current_surf->size))));
}

RtVoid wave()
{
  RtFloat mdsin = sqrt((current_surf->ref - P) * (current_surf->ref - P));
  if (mdsin >= 1.0)
    Ng = Ng *(0.7+fabs(0.3*sin(M_PI * current_surf->Freq * mdsin ))/ mdsin);
  else
    Ng = Ng *(0.7+fabs(0.3*sin(M_PI * current_surf->Freq * mdsin )));
  Oi = Os;
  Ci = Cs *( (current_surf->ka*ambient()) + (current_surf->kd*diffuse(Ng)));
}

RtVoid granite()
{
  RtFloat sum = 0.0;
  RtFloat freq = 1.0;

  for(int i = 0; i < 8; i++)
    {
      sum = sum + fabs(0.5 - fabs(noise(I*(4.0*freq))[2]))/freq;
      freq *= 2.0;
    }
  Ci = sum *(Cs * ((current_surf->ka*ambient())+(current_surf->kd*diffuse(N))));
}

RtVoid hyper()
{
  RtPoint pt1;
  RtFloat temp = 0.2 + fabs(noise(P * current_surf->Freq)[2]);
  
  Ci =  temp *(Cs * ((current_surf->ka*ambient())+
			   (current_surf->kd*diffuse(Ng))));
}

RtVoid hyper2()
{
  RtPoint pt1;
  Ci =  Cs * ( (current_surf->ka * ambient()) +
	       (current_surf->kd *
	       diffuse(faceforward(normalize(noise(P * current_surf->Freq)), I))));
}
RtVoid hyper3()
{
  RtPoint pt1;
  Ci =  Cs * ( (current_surf->ka * ambient()) +
	       (current_surf->kd *
	       diffuse(faceforward(normalize(noise2(P * current_surf->Freq)), I))));
}

RtVoid hyper4()
{
  RtPoint pt1(0.0,0.0,0.0);
  RtFloat freq = current_surf->Freq;
  for(int i=1; i < 4; i++)
    {
      pt1 = pt1 + (noise(P * freq)*(1.0/freq));
      freq *= 2.0;
    }
  Ci =  Cs * ( (current_surf->ka * ambient()) +
	       (current_surf->kd *
	       diffuse(faceforward(normalize(pt1), I))));
}  

RtVoid hyper5()
{
  RtFloat pt1;
  RtFloat freq = current_surf->Freq;
  for(int i=1; i < 4; i++)
    {
      pt1  +=  fabs((noise(P * freq)[2])/freq);
      freq *= 2.0;
    }
  Ci = pt1 * (Cs * ( (current_surf->ka * ambient()) +
	       (current_surf->kd *
	       diffuse(N))));
}

RtVoid hyper6()
{
  RtPoint pt1(0.0,0.0,0.0);
  RtFloat freq = current_surf->Freq;
  for(int i=1; i < 4 ; i++)
    {
      pt1 = pt1 + (noise(P * freq) * (1.0/freq));
      freq *= 2.0;
    }
  
  pt1 = normalize((normalize(pt1) * 0.40) + (N * 0.60));
  Ci =  Cs * ( (current_surf->ka * ambient()) +
	       (current_surf->kd * diffuse(pt1)));
}
RtVoid checkerp()
{
  RtFloat smod = fmod(current_surf->gets(P) * current_surf->Freq,1.0);
  RtFloat tmod = fmod(current_surf->gett(P) * current_surf->Freq,1.0);

  
  if ( smod < 0.0)
    smod += 1.0;
  if (tmod < 0 )
    tmod += 1.0;
  if (smod < 0.5)
    {
      if (tmod < 0.5)
	Ci = Cs;
      else
	Ci = current_surf->coul_car;
    }
  else
    {
      if ( tmod < 0.5)
	Ci = current_surf->coul_car;
      else
	Ci = Cs;
    }
  Oi = Os;
  Ci = Oi*Ci*((current_surf->ka * ambient())+(current_surf->kd * diffuse(Ng))); 
}



