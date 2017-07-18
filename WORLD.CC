
#include   "ri.h"
#include   "Global.h"
#include   <string.h>
#include   <ctype.h>
#include   <math.h>

#define Window_far 100

RtFloat n_courant=1.0;



// --- --- --- --- --- --- --- Ri World End --- --- --- --- --- --- ---
RtVoid     RiWorldEnd()
{


RtFloat window_x, window_y ;
RtPoint PIX ;
RtColor PIXline[resolution_x];


        // --- indique le nom du fichier de sortie ----
      
           cout << "fichier de sortie : " << filename << "\n"; 
           cout << form ("resolution : %d X %d \n", resolution_x, resolution_y);

        // --- passe de pre-proc pour les polygones ---

	for (int loop = 0 ; loop < NumSurf ; loop++)
		surf_list[loop]->preproc();

       // --- prepare les variables globales ---

      Cl = 1.0 ;                // Light color   
      R = 0.0 ;
      T = 0.0 ;
      E = 0.0 ;			// --- E: position de la camera ---

      

      imageToFile_init();
      noise_init();

      RtFloat cam_angle = radians(camera_angle) / 2 ;
 
 	Window_Right = Window_far * tan(cam_angle);
	Window_Left = -1.0* Window_Right;
 	Window_Bottom = Window_Left;
 	Window_Top = Window_Right;

       // --- calcule les caracteristiques de la camera ---
       inc_x = (Window_Right  - Window_Left) / resolution_x ;
       inc_y = (Window_Bottom - Window_Top ) / resolution_y ; 

	RtInt EX = 0, EY = 0;

	
       // --- boucle pour chaque ligne ---
       for ( window_y = Window_Top;
             window_y > Window_Bottom;	
             window_y += inc_y ) {

       

	 if ( Flag_Stool )
                cerr << "  line #" << EY << " \r" ; 

	 EY++;
	 EX = 0;

           // --- boucle pour chaque pixel ---
           for ( window_x = Window_Left; window_x < Window_Right;  window_x += inc_x ) 
	   {

	 	// position du Pixel 
	 	PIX.x = window_x ;
	 	PIX.y = window_y ;
	 	PIX.z = -1.0*Window_far;

		

		// ---- dist ray : motion blur et antialiasing ----
		

                	// --- calcule (et normalise) la direction du rayon ---
			I = normalize(PIX) ;
			
			// calcul du temps present (motion blur)
			// ajout d'une variance dans le temps  
			
               		// --- calcule la couleur raportee par ce rayon ---
                	Cs = 1.0 ; 	
               		Ci = 0.0 ;		
                	P = E ;
			
			//  Initialise la valeur courante de n
			n_courant=1.0;

                	Poly_cast( 0 ) ;
			PIXline[EX] = (Ci * 255.0) ;

                // --- Imager Shader (si suporte) ---

                // --- ecrit le pixel dans la ligne ---

		if (PIXline[EX].rouge > 255.0) PIXline[EX].rouge = 255.0 ;
		if (PIXline[EX].vert  > 255.0) PIXline[EX].vert  = 255.0 ;
		if (PIXline[EX].bleu  > 255.0) PIXline[EX].bleu  = 255.0 ;	
		EX++ ;
           }

        // --- ecrit la ligne dans le fichier output ---
	imageToFile(PIXline);
	

       }
  imageToFile_close();
  
}


// --- --- --- --- --- --- --- Poly Cast --- --- --- --- --- --- ---
//
//  ray casting recursif
//
RtVoid     Poly_cast( short level )
{
RtFloat  dist     = RI_INFINITY;
RtFloat  new_dist = RI_INFINITY;
RtFloat  old_dist ;
Surfaces_Pt oldCurrent = NULL ;


        // --- initialise quelque variables globales ---
        Current_Surf = NULL ;

        // --- intercepte ce rayon avec les objets ---
        for (int i = 0; i < NumSurf ; i++) 
	{

            // --- appelle la bonne fonction selon le type de la surf. ---
	    new_dist = surf_list[i]->intersect( P, I ) ; 
	    
            // --- garde la plus pres (>0) ---
            if ( new_dist > RI_EPSILON  &&  new_dist < dist ) {
                dist = new_dist ;
                Current_Surf = surf_list[i];
            } // if 


        } // for 

        // --- on a rien frappe ---
	if (Current_Surf == NULL)
             return ; 
	
        // --- trouve la position du point d'intersection ---
        P = P + (I * dist);
	
	
        // --- Caracteristiques de la surface ---
        Cs *= Current_Surf->couleur;
	kd = Current_Surf->kd ;
	ka = Current_Surf->ka ;
	ks = Current_Surf->ks ;
	roughness = 1.0 / Current_Surf->size ;
	specularcolor = Current_Surf->specularcolor ; 

        // --- calcule la normale a la surface ---
        N = calculatenormal( P ) ;
	
        // --- shade la surface ----
        (Current_Surf->shader_pt)() ;
	
	
        // --- rayon reflechit ---
        if ( level < MAX_RAY -1) {

             // --- calcule les direction reflechis et refractees ---
	     RtFloat KR = Current_Surf->kr ;
  	     RtFloat KT = Current_Surf->kt ;

	     if (Current_Surf->n != n_courant)
		n_courant = Current_Surf->n;
	     else		// Si on sort de la surface, inverser n1/n2
		n_courant = 1/n_courant;

	     
	     fresnel( I, N, n_courant, KR, KT, R, T ) ;

	
             // --- attention variables globales

		RtColor oldCs = Cs ;
		RtColor oldCi = Ci ;
		RtPoint oldP  = P ;
		RtPoint oldT  = T ;
	        oldCurrent = Current_Surf ;

             // --- rayon reflechi ---
             if ( KR > RI_EPSILON  &&  length(R) > 0.0 ) {
                 // --- direction du rayon ---

		I = normalize(R) ;
	
                 // --- atenuation du rayon ---
	
		Cs = oldCs * KR ;
		Ci = 0.0 ;

                 // --- calcule la couleur raportee par ce rayon ---
                 Poly_cast( level+1 ) ;

		P = oldP ;
		T = oldT ;
		Current_Surf = oldCurrent ;
		oldCi = oldCi + Ci ;
             }

             // --- rayon refracte ---
             
	     if ( (KT > RI_EPSILON)  &&  length(T) > 0.0 )
             {
		// --- direction du rayon ---
		I = normalize(T) ;

		// --- atenuation du rayon ---
		Cs = KT ;
		Ci = 0.0 ;

		// --- calcule la couleur raportee par ce rayon ---
		Poly_cast( level+1 ) ;

		P = oldP ;
		T = oldT ;
		Current_Surf = oldCurrent ;
		oldCi = oldCi + Ci ;
	     }

	Ci = oldCi ;
        }
}
