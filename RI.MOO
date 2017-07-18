//**************************************************************************
//
// 	IMAGE #2 - pour le concours. test
//
//**************************************************************************





#include "ri.h"

void UsageMenu();       // Fonction pour l'affichage de l'usage du programme

main(int argc, char *argv[])
{
RtFloat         Ca, Cd, Cr ,Ct,n ,Cs, size;

RtFloat         intens = 0.5 , intens3 = 0.7;
RtFloat         intens2 = 0.5;
RtFloat         fov = 50.0 ;

RtPoint         ponct , ponct2, ponct3;

//------------------------------------------------------------------------------

ponct[0] = -5.25 ;
ponct[1] = 5.2 ;
ponct[2] = 5.0 ;

ponct2[0] = 4.0 ;
ponct2[1] = 4.25 ;
ponct2[2] = 4.0 ;

ponct3[0] = -3.0 ;
ponct3[1] = 3.0 ;
ponct3[2] = 4.0 ;

char file[20] ;


int size_x, size_y;      // Taille de l'image de sortie, en pixels.

// --- Verification des arguments ---

    if ( (argc < 2) || (argc == 3) ) 
    {
	UsageMenu();
	exit(0);
    }
    if (argc == 4) 
    {
	size_x=atoi(argv[2]);       // Assignation de la grosseur de l'image
	size_y=atoi(argv[3]);
	if ( (size_x < 1) || (size_y < 1) )
	{
	    cout << "\n\nTaille de l'image non valide.\n";
	    UsageMenu();
	    exit(0);
	}
    }
    else 
    {
	size_x = size_y = 100;      // Taille de defaut.
    }



RiBegin();

 RiWorldBegin();

    MAX_RAY =  7; 
    Flag_Stool = RI_TRUE ;
    RtColor couleur;


// --- definition dimension  de l'image et perspective -----

    RiFormat(size_x, size_y, 1.0);
    if (argc<2)                                 // Aucun parametre
	RiDisplay("image", RI_FILE, RI_RGB, RI_NULL);
    else
	RiDisplay(argv[1], RI_FILE, RI_RGB, RI_NULL);
    RiProjection("perspective", RI_FOV, &fov, RI_NULL);

// --- declaration des lumieres -----

	RiLightSource((RtFunc)ambientlight, "intensity" , &intens, RI_NULL);
	RiLightSource((RtFunc)pointlight  , "intensity", &intens, "from", &ponct3, RI_NULL);

	RiTranslate(0.0, 0.0, -5.0);

	RiLightSource((RtFunc)pointlight  , "intensity", &intens2, "from", &ponct2,  RI_NULL);



// ***********************************************************
//
// plan #1 - ciel avec les nuages
//

	couleur[0] = 0.0 ; couleur[1] = 0.0 ; couleur[2] = 0.9 ;


	RiTransformBegin();
		Ca = 0.9; Cd = 0.6 ; Cr = 0.0 ; Ct = 0.0 ; n = 0.1 ; Cs = 0.4 ; size = 35.0 ;
		RiSurface((RtFunc)clouds, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		//RiTranslate( 0.0, 0.0, -3.0);
		RiColor(couleur);
		PolyPlane(0.0, 0.0, 1.0, 3.0, RI_NULL);

	RiTransformEnd();


// ***********************************************************
//
// plan #2 - flocons
//


	couleur[0] = 0.0 ; couleur[1] = 0.0 ; couleur[2] = 1.0 ;

	RiTransformBegin();
		Ca = 0.5 ; Cd = 0.5 ; Cr = 0.0 ; Ct = 0.0 ; n = 0.5 ; Cs = 0.5 ; size = 35.0 ;
		RiSurface((RtFunc)flake, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(couleur);
		PolyPlane(0.0, 4.0, 1.0, 3.0, RI_NULL);

	RiTransformEnd();


// ***********************************************************
// SPHERE #1 - sphere granite 
//

    couleur[0] = 1.0 ; couleur[1] = 0.8 ; couleur[2] = 0.0 ;
    RiTransformBegin();
        Ca = 0.4 ; Cd = 0.5 ; Cr = 0.0 ; Ct = 0.0 ; n = 1.0 ; Cs = 0.5 ;size = 35.0 ;
        RiSurface((RtFunc)granite, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd,RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
        RiColor(couleur);
        RiTranslate(1.5, 1.3, -1.0);
        RiSphere(.5, 0.0, 0.0, 360.0, RI_NULL);
    RiTransformEnd();




// ***********************************************************
// SPHERE #2 - sphere volcanique 
//

    couleur[0] = 0.4 ; couleur[1] = 0.2; couleur[2] = 0.12 ;
    RiTransformBegin();
        Ca = 0.5 ; Cd = 0.5 ; Cr = 0.0 ; Ct = 0.0 ; n = 1.0 ; Cs = 0.5 ;size = 35.0 ;
        RiSurface((RtFunc)volcan, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd,RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
        RiColor(couleur);
        RiTranslate(-2.0, 2.0, -3.0);
        RiSphere(1.5, 0.0, 0.0, 360.0, RI_NULL);
    RiTransformEnd();


// ***********************************************************



    // le ray se fait dans world.cc
    RiWorldEnd();
RiEnd();
}



/////////////////////////////////////////////////////////////////////////
// UsageMenu(): Affiche le menu d'utilisation du programme
/////////////////////////////////////////////////////////////////////////
void
UsageMenu()
{
	cout << "\nUsage: rayt image_filename [pixels_x pixels_y]";
	cout << "\navec: image_filename = nom du fichier image a generer";
	cout << "\npixelx_x et pixels_y: Taille en X et Y de l'image (default 100x100)\n";
}



