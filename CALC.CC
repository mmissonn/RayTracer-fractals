#include   "ri.h"
#include   "Global.h"
#include   <string.h>
#include   <ctype.h>
#include   <math.h>


// ********************** Mathematical Functions *****************************

// ------------------------------- degre a radian ----------------------------
RtFloat    radians ( RtFloat a )
{
	return ( a * PI / 180 ) ;
}

// ------------------------------- radian a degre ----------------------------
RtFloat    degrees ( RtFloat a )
{
	return ( a * 180 / PI ) ;
}

// ------------------------------ minimum de a et b -------------------------
//RtFloat    min ( RtFloat a,   RtFloat b )
//{
//	return ( (a <= b ) ? a : b );
//}

// ------------------------------ maximum de a et b -------------------------
//RtFloat    max ( RtFloat a,   RtFloat b )
//{
//	return ( (a >= b ) ? a : b );
//}



// ------------------------------ signe de a --------------------------------
RtFloat    sign ( RtFloat a )
{
	return ( ( a >= 0 ) ? 1 : -1 );
}

// ----------------------------- arrondis de a ------------------------------
RtFloat    round ( RtFloat a )
{
	return ( (RtFloat) ((int) a) ) ;
}


// ------------------------------ a modulo b --------------------------------
RtFloat    mod (RtFloat a , RtFloat b ) 
{
  
	return (a - (round(a / b)) * b);
}

// ----------------------------- step --------------------------------------
RtFloat    step( RtFloat min, RtFloat val )
{
        return( ( val < min ) ? 0.0 : 1.0 ) ;
}

RtFloat    smoothstep(RtFloat min, RtFloat max, RtFloat val)
{
	if (val <= min) return (0.0);
	if (val >= max) return (1.0);
	
	RtFloat outval = val / (max - min) ;
	return (outval) ;
}
 

// ********************** Geometric Functions ********************************

// --- --- --- ---  x comp  --- --- --- ---
//
//   Fetch the x component from P
//   (cf: RenderMan p.326)
//
RtFloat		xcomp (RtPoint P)
{
	return (P.x);
}

// --- --- --- ---  y comp  --- --- --- ---
//
//   Fetch the y component from P
//   (cf: RenderMan p.326)
//
RtFloat		ycomp (RtPoint P)
{
	return (P.y);
}

// --- --- --- ---  z comp  --- --- --- ---
//
//   Fetch the z component from P
//   (cf: RenderMan p.326)
//
RtFloat		zcomp (RtPoint P)
{
	return (P.z);
}

// --- --- --- ---  setxcomp --- --- --- ---
//
//   Set the x component of P to val
//   (cf: RenderMan p.326)
//
RtVoid		setxcomp( RtPoint& P , RtFloat val)
{
	P.x = val ;
}


// --- --- --- ---  setycomp --- --- --- ---
//
//   Set the y component of P to val
//   (cf: RenderMan p.326)
//
RtVoid		setycomp( RtPoint& P , RtFloat val)
{
	P.y = val ;
}

// --- --- --- ---  setzcomp --- --- --- ---
//
//   Set the z component of P to val
//   (cf: RenderMan p.326)
//
RtVoid		setzcomp( RtPoint& P , RtFloat val)
{
	P.z = val ;
}



// --- --- --- ---  length  --- --- --- ---
//
//   Returns the Euclidean length of the vector V
//   (cf: Renderman p.326)
//
RtFloat		length ( RtPoint& V )
{
  RtFloat temp ;

	temp = sqrt ( ( V.x * V.x ) + ( V.y * V.y ) + ( V.z * V.z ) );

	return (temp);
}


// --- --- --- --- distance --- --- --- ---
//
//   Calculate the Euclidian distance between two points
//   (cf: RenderMan p.327)
//
RtFloat         distance(RtPoint& P1, RtPoint& P2 )
{

	return ( length (P1 - P2) );
}


// --- --- --- --- normalize --- --- --- ---
//
//   (cf: RenderMan p.327)
//
RtPoint         normalize( RtPoint& V )
{


	return ( V / length(V) ) ;
}


// --- --- --- --- faceforward --- --- --- ---
//
//  Return V flipped to point opposite R
//  (cf: RenderMan p.328)
//
RtPoint		faceforward (RtPoint& V , RtPoint& R)
{
 RtFloat temp ;

 temp = V * R ;

  if (temp > 0.0) 
	return (-1 * V)  ;
  else 
  return (V) ;
}


// --- --- --- --- reflect --- --- --- ---
//
//  direction du rayon reflechi
//
//   methode de P.S. Heckbert
//   (c.f. An Introduction to Ray Tracing, A.Glasner, p.290)
//
RtPoint         reflect(RtPoint& I, RtPoint& N )
{
  RtFloat c1 ;
  RtPoint R ;

	c1 = (-1*I) * N;
	R = I + (2*c1) * N ;

 return (R); 
}

// --- --- --- --- refract --- --- --- ---
//
//   direction du rayon reflechi
//
//   methode de P.S. Heckbert
//   (c.f. An Introduction to Ray Tracing, A.Glasner, p.288)
//
//   (cf: RenderMan p.328)
//
RtPoint         refract(RtPoint& I, RtPoint& N, RtFloat n )
{
RtFloat c1,c2;

    n=1/n;
    c1 = (-1*I)*N;
    c2 = 1-n*n*(1-c1*c1);
    if (c2 > RI_EPSILON)	// verifier si c2 est imaginaire
    {
	c2= sqrt(c2);
    	return (I*n+N*(n*c1-c2));
    }
    else
    {
	 RtPoint tmp(0.0,0.0,0.0);
	return tmp;
    }

}


// --- --- --- --- fresnel --- --- --- ---
//
//   (cf: RenderMan p.329)
//
RtVoid          fresnel( RtPoint I,
                         RtPoint N,
                         RtFloat n,
                         RtFloat kr,
                         RtFloat kt,
                         RtPoint& R,
                         RtPoint& T )
{
        // --- rayon reflechi ---
        if ( kr > RI_EPSILON )
             R = reflect( I, N ) ;
        else
             R = 0.0 ;

        // --- rayon refracte ---
        if ( kt > RI_EPSILON )
	{
	     N=faceforward(N,I);
             T = refract( I, N, n ) ;
	}
        else
             T = 0.0 ;
}


// --- --- --- --- calculatenormal --- --- --- ---
//
//   return the normal to a surface at point P
//   (cf: RenderMan p.330)
//
RtPoint       calculatenormal( RtPoint& P )
{
         // --- apelle la bonne fonction selon le type de la surface ---
         return( Current_Surf->normale(P) ) ;
}


// --- --- --- --- color mix --- --- --- --- --- ---
//
//  Intermixing of two colors
//  (cf: RenderMan p.331)
//
RtColor		mix ( RtColor& color0, RtColor& color1, RtFloat a)
{

	return ( ((1 - a)*color0) + (a*color1) ) ;
}

 
