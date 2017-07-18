//**************************************************************************
//
// 	IMAGE #2 - pour le concours. test
//
//**************************************************************************






#include   "ri.h"
#include   "Global.h"
#include   <string.h>
#include   <ctype.h>
#include   <math.h>

#define Window_far 100



// --- les "construct" de RenderMan sont approximes par des macros ---


#define    illuminate(a,b,c)   if ( Poly_Illuminate(a,b,c) )

#define    illuminance(P,axis,angle)  for (RtInt illum ; Poly_Illuminance(illum) ; illum++) \
                                          if (Flag_Shadow == RI_TRUE && Flag_Illuminate ==  RI_TRUE)

 

// ********************** Lighting Functions *********************************

// --- --- --- --- ambient --- --- --- ---
//
//   sums the contributions of all ambient light sources
//   (cf: RenderMan p.315)
//
RtColor         ambient()
{
RtColor C ;
      
	C = 0.0 ;
	 
        for (RtInt illum = 0 ; illum < Current_Surf->nb_lumiere ; illum++)
	{
            // --- prepare quelques variables ---
            Flag_Illuminate = RI_FALSE ;
            Current_Light = Current_Surf->light_pt[illum] ;
	    L = Current_Light->position - P ;

            // --- shader de la lumiere ---
            (Current_Light->shader_pt)() ;

            // --- on saute les lumieres non-ambientes ---
            // (qui n'utilisent pas illuminate())
             if ( Flag_Illuminate == RI_FALSE)
                 C += Cl ;		
	}

        return( C );

}

// --- --- --- --- diffuse --- --- --- ---
//
//   Calculate diffuse reflection for a given surf. normal
//   (cf: RenderMan p.316)
//
RtColor         diffuse( RtPoint& norm )
{
RtColor C ;
RtPoint unitform ;


	C = 0.0 ;
        unitform = normalize(norm) ;

 	for (RtInt illum = 0 ; illum < Current_Surf->nb_lumiere ; illum++)
	{
	RtFloat   new_dist , old_dist;				  
	RtFloat   dist = RI_INFINITY ;

	Surfaces_Pt Marker ;


		
	// --- parcours toutes les sources de lumieres associes ---						    
	    	Flag_Illuminate =  RI_FALSE ;			   	
	    	Flag_Shadow =  RI_TRUE ;				  
	    	dist = RI_INFINITY ;				   
            	Current_Light = Current_Surf->light_pt[illum];			   
            	Cl = Current_Light->couleur ;		           
            	L  = Current_Light->position - P;		   
            	(Current_Light->shader_pt)() ;	       	           
	        if (Flag_Illuminate ==  RI_TRUE)		  
	    	{				                  
		 RtPoint lite = normalize(L) ;	                          
	         for (int i = 0; i < NumSurf ; i++)		   
                 {   
		   Marker = (Surfaces_Pt)(surf_list[i]) ;   	         
		   new_dist = Marker->intersect(Current_Light->position, -1.0*lite);
		   
		   		                           
		     if ((new_dist > RI_EPSILON)  && (length(L) - new_dist > RI_EPSILON ))  
		     {	 	       
		       Flag_Shadow = RI_FALSE ;	
		       break ;
		     }	

		   
              	  } // for 
		} // if Flag_Illuminate

 
	   if (Flag_Shadow == RI_TRUE && Flag_Illuminate ==  RI_TRUE)
       	     C += Cl * (normalize(L) * unitform) ;
	
	} // pour toutes les surfaces 
	return (C) ;
}


// --- --- --- --- specular --- --- --- ---
//
//   Calculate specular reflection for a given surf. normal
//   (cf: RenderMan p.317)
//
RtColor         specular( RtPoint& norm , RtPoint& eye, RtFloat roughness)
{
RtColor C ;
RtPoint unitform ;

	C = 0.0 ;
        unitform = normalize(norm) ;
	
	
	for (RtInt illum = 0 ; illum < Current_Surf->nb_lumiere ; illum++)
	{
	RtFloat   new_dist , old_dist;				  
	RtFloat   dist = RI_INFINITY ;

	Surfaces_Pt Marker ;


		
	// --- parcours toutes les sources de lumieres associes ---						    
	    	Flag_Illuminate =  RI_FALSE ;			   	
	    	Flag_Shadow =  RI_TRUE ;				  
	    	dist = RI_INFINITY ;				   
            	Current_Light = Current_Surf->light_pt[illum];			   
            	Cl = Current_Light->couleur ;		           
            	L  = Current_Light->position - P;		   
            	(Current_Light->shader_pt)() ;	       	           
	        if (Flag_Illuminate ==  RI_TRUE)		  
	    	{				                  
		 RtPoint lite = normalize(L) ;	                          
	         for (int i = 0; i < NumSurf ; i++)		   
                 {   
		   Marker = (Surfaces_Pt)(surf_list[i]) ;   	         
		   new_dist = Marker->intersect(Current_Light->position, -1.0*lite);
		   
		   		                           
		     if ((new_dist > RI_EPSILON)  && (length(L) - new_dist > RI_EPSILON ))  
		     {	 	       
		       Flag_Shadow = RI_FALSE ;	
		       break ;
		     }	

		   
              	  } // for 
		} // if Flag_Illuminate

		if (Flag_Shadow == RI_TRUE && Flag_Illuminate ==  RI_TRUE)
		{	
			H = (L + eye) / 2.0 ;
        		C +=  Cl * pow( fabs(((norm * H)) / (length(norm)*length(H))) , 1.0/roughness) ;
		}
		  
	} // pour toutes les surfaces 
	return(C) ;
}


// ********************** Mapping Functions **********************************



// ********************** Standard Shaders ***********************************


// --- --- --- --- matte --- --- --- --- ---
//
//   simple diffusely-reflecting surface
//   (cf: RenderMan p.335)
//
RtVoid     matte()
{
RtPoint Nf ;


        Nf = faceforward( N, I) ;

        Oi = Os = 1.0;
	Ci = Os * Cs *  ((ka*ambient())  + (kd*diffuse(Nf))) ;
	
}

 
// --- --- --- --- plastic --- --- --- --- ---
// 
//   give a surface a plastic appearance
//   (cd: RenderMan p.337)
//
RtVoid     plastic ()
{
 RtPoint Nf ;
 
        Nf = faceforward( N, I) ;

        Oi = Os = 1.0 ;
        Ci = Os * Cs * ((ka*ambient()) + (kd*diffuse(Nf)) + (specularcolor*ks*specular(Nf, -1.0*I, roughness)) );
}
      


// --- --- --- --- granite() --- --- --- --- ---
// 
//  
//  renderman p. 354
//
RtVoid   granite()
{ 
double sum = 0.0;
float i, freq = 1.0;
for(i = 0; i < 6; i++)
	{
	sum = sum + abs(0.5 - noise(4.0 * freq * I)) / freq;
	freq *= 2;
	}
Ci = Cs * sum * ((0.2 + 0.8) * diffuse(faceforward(normalize(N), I)));

}


// --- --- --- --- clouds() --- --- --- --- ---
// 
// Renderman p.282 
//  
//
RtVoid   clouds()
{ 
double sum = 0.0;
float i, freq = 0.8;

for(i = 0; i < 6; i++)
	{
	sum = sum + abs(0.5 - noise(freq * P)) / freq;
	freq *= 2;
	}

Ci = Cs * sum * (ka*ambient() + kd*diffuse(faceforward(normalize(N),I)));
Oi = 1.0;

}

                 
// --- --- --- --- checker() --- --- --- --- ---
// 
// Checker board
//  
//
RtVoid checker()
{                         
 RtFloat Freq = 2;
 RtFloat xm = (mod(P.x * Freq,1.0));
 RtFloat ym = (mod(P.y * Freq,1.0));
 RtFloat zm = (mod(P.z * Freq,1.0));
 RtColor temp;      
 RtColor coul_car;
 RtBoolean flag;
                
 coul_car.rouge = 0.0;
 coul_car.vert = 0.0;
 coul_car.bleu = 0.0;

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
           temp = coul_car;
       }
     else
       {
         if (ym > 0.5)
           temp = Cs;
         else
           temp  = coul_car;
       }
   }
 else
   {
     if ( xm < 0.5)
       {
         if( ym < 0.5)
           temp  = coul_car;
         else
           temp = Cs;
       }
     else
       {
         if (ym > 0.5)
           temp  = coul_car;
         else
           temp = Cs;
       }
   }

 Ci = temp;
 Oi = Os;
 Ci = Oi*Ci*( ka * ambient() + kd * diffuse(N) ) ; 
}
                    

// --- --- --- --- wave() --- --- --- --- ---
//
// Propagation d'un onde 
//

RtVoid wave()
{

RtPoint G; // Centre de propagation de l'onde
G.x = 0.0;
G.y = 0.50;
G.z = -5.0;

RtFloat Freq = 7.0; //7.0
RtFloat mdsin = sqr((G-P)*(G-P));

if(mdsin >= 1.0)
  P = P + N *(0.1+(sin(1/(2*PI) * Freq * mdsin))/mdsin);
else
  P = P + N *(0.1+(sin(1/(2*PI) * Freq * mdsin)));

N = calculatenormal(P);

Oi = Os;
Ci = Cs * (ka*ambient() + kd*diffuse(N));

}           

            
// --- --- --- --- ocean() --- --- --- --- ---
// ---- non fonctionnel helas!
// vagues oceaniques 
//

RtVoid ocean()
{

RtFloat Freq = 2.0;


P = P + N*(0.6+sin(1/(2*PI)*Freq*(P.x + 0.5*P.y*P.y)));

N = calculatenormal(P);

Oi = Os;
Ci = Cs * (ka*ambient() + kd*diffuse(N));

}
            
                
      
// --- --- --- --- glow() --- --- --- --- ---
// 
//   rayonnement lumineux d'une surface
//   (cd: RenderMan p.369)
//
RtVoid     glow ()
{ 
 
 
 RtFloat attenuation = 4.0;
 RtFloat falloff = I*N;

        if (falloff < RI_EPSILON){
          falloff= falloff * falloff/((I*I)*(N*N)); 
          falloff= pow(falloff, attenuation);
          Ci = Cs *falloff;
          Current_Surf->kt = 1-falloff;
        }
        else
	{
	  Current_Surf->kt = 1.0;

	}

}
      
// --- --- --- --- hill() --- --- --- --- ---
// 
//   surface montagne
//   
//
RtVoid     hill ()
{ 
 
 double sum = 0.0;
 int i;

 RtColor coul;
 coul.rouge = 1.0;
 coul.vert = 1.0;
 coul.bleu = 1.0;

 RtFloat freq = 1.2;
 RtFloat bump = 7.0;
        
    /*for(i = 0; i < 6; i++)
	{
	sum = sum + abs(0.5 - noise(4.0 * bump * I)) / freq;
	bump *= 2;
	}
     */       

        N = N * (2*(noise(bump*P)));

	//N = calculatenormal(P);

	Cs = mix(Cs, coul, (noise(freq*P)));
	

      	Oi = Os = 1.0;
	Ci = Os * Cs * ((ka*ambient())  + (kd*diffuse(N))) ;
	

}

// --- --- --- --- volcan() --- --- --- --- ---
// 
//   surface volcanique
//   
//
RtVoid     volcan ()
{ 
 
 double sum = 0.0;
 int i;

 RtColor coul;
 coul.rouge = 1.0;
 coul.vert = 1.0;
 coul.bleu = 1.0; 

 RtFloat freq = 4.2; //3.2; 
 RtFloat bump = 4.0;//7;
        
  
        P = P + N*(0.1+2.5*(sin( noise(bump*P) ) ) );

	N = calculatenormal(P);

	Cs = mix(Cs, coul, 1.0 - (noise(freq*P)));
	
      	Oi = Os = 1.0;
	Ci = Os * Cs * ((ka*ambient())  + (kd*diffuse(N))) ;



}
  

// --- --- --- --- flake --- --- --- --- ---
// 
//  apparence de flocons 
//   
//
RtVoid	   flake ()
{
 RtColor coul;
 RtFloat h, freq = 3.0;
 RtPoint Nf ;
 
 
 h = noise(freq*P);

 if(h<=0.4)
 {
   coul[0] = 1.0;
   coul[1] = 1.0; //0.1;
   coul[2] = 0.0; //0.8;
 }
 else
 {
   coul[0] = 0.9 - (h-0.5)/(0.5);
   coul[1] = 0.9 - (h-0.5)/(0.5);
   coul[2] = 0.0;      
 }

	Nf = faceforward( N, I) ;

	Cs = coul;
        Oi = Os = 1.0 ;
        Ci = Os * Cs * ((ka*ambient()) + (kd*diffuse(Nf)) + (specularcolor*ks*specular(Nf, -1.0*I, roughness)) );

/*
 Cs = coul;
 Oi = Os = 1.0;
 Ci = Os * Cs * ((ka*ambient())  +  (kd*diffuse(N)) ) ;
*/

}

  
// --- --- --- --- metal --- --- --- --- ---
// 
//   give a surface a metallic appearance
//   (cd: RenderMan p.336)
//
RtVoid	   metal ()
{
 RtPoint Nf ;
 

	Nf = faceforward( N, I) ;

	Oi = Os = 1.0 ;
	Ci = Os * Cs * ((ka*ambient()) + (ks*specular(Nf, -1.0*I, roughness)));
}





// ********************** Standard Lights ************************************

// --- --- --- --- ambient light --- --- --- ---
//
//   non-directional ambient light shader
//   (cf: RenderMan p.338)
//
RtVoid     ambientlight(RtFloat intensity = 1,
  			RtColor color = 1.0)
{
  

	
	intensity = Current_Light->intensite ;
	color = Current_Light->couleur ;

        Cl = (intensity * color) ;

}

// --- --- --- --- point light --- --- --- ---
//
//   a light source with a position but no orientation
//   (cf: RenderMan p.339)
//
RtVoid     pointlight( RtFloat intensity = 1, 
                       RtColor color = 1,     
                       RtPoint from = 0 )
{
 RtPoint axis ;

	intensity = Current_Light->intensite ;
	color = Current_Light->couleur ;
	from  = Current_Light->position ;

	axis = from ;	// beta ...

       illuminate( from, axis, 0.0)
            Cl = intensity * color ;
}


// ***************************************************************************

// --- --- --- --- --- --- --- Poly Illuminance --- --- --- --- --- --- --- ---
RtBoolean      Poly_Illuminance(RtInt illum)
{
RtFloat   new_dist , old_dist;				  
RtFloat   dist = RI_INFINITY ;

Surfaces_Pt Marker ;


	if (illum == Current_Surf->nb_lumiere) 
	{
		Flag_Illuminate =  RI_FALSE ;			   	
	    	Flag_Shadow =  RI_FALSE ;
		return RI_FALSE ;
	}
	
	// --- parcours toutes les sources de lumieres associes ---						    
	    	Flag_Illuminate =  RI_FALSE ;			   	
	    	Flag_Shadow =  RI_TRUE ;				  
	    	dist = RI_INFINITY ;				   
            	Current_Light = Current_Surf->light_pt[illum];			   
            	Cl = Current_Light->couleur ;		           
            	L  = Current_Light->position - P;		   
            	(Current_Light->shader_pt)() ;	       	           
	        if (Flag_Illuminate ==  RI_TRUE)		  
	    	{				                  
		 RtPoint lite = normalize(L) ;	                          
	         for (int i = 0; i < NumSurf ; i++)		   
                 {   
		   Marker = (Surfaces_Pt)(surf_list[i]) ;   	         
		   new_dist = Marker->intersect(Current_Light->position, -1.0*lite);
		   
		   		                           
		     if ((new_dist > RI_EPSILON)  && (length(L) - new_dist > RI_EPSILON ))  
		     {	 	       
		       Flag_Shadow = RI_FALSE ;	
		       break ;
		     }	

		   
              	  } // for 
		} // if Flag_Illuminate

	return RI_TRUE ;

}

// --- --- --- --- --- --- --- Poly Illuminate --- --- --- --- --- --- --- ---
RtBoolean  Poly_Illuminate( RtPoint position,
                            RtPoint axis = 1,
                            RtFloat angle=0.0 )
{
        // --- pour faire la dif. avec lum. ambient ---
        Flag_Illuminate = RI_TRUE ;

//        ....
//      pour le moment, TRUE tout le temps
        return( (RtBoolean)1 ) ;

}


