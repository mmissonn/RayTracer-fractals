#include "ri.h"

// Eric Boule, 19 fevrier 1992
// ri.cc

main()
{
RtFloat		Ca, Cd, Cr ,Ct,n ,Cs, size;

RtFloat		intens = 0.8 , intens3 = 0.6;
RtFloat	        intens2 = 0.5;
RtFloat		fov = 75.0 ;

RtPoint		ponct , ponct2, ponct3;

RtPoint carre[4] = { {0.5, 0.5, 0.5}, {-0.5, 0.5, 0.5}, {-0.5, -0.5, 0.5},
			{0.5, -0.5, 0.5} };


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



RiBegin();

 RiWorldBegin();

    MAX_RAY =  7;
    Flag_Stool = RI_TRUE ;
    RtColor sphere , plan, quad, cube;


// --- definition dimension  de l'image et perspective -----

	RiFormat(300, 300, 1.0);
	RiDisplay("login", RI_FILE, RI_RGB, RI_NULL);
	RiProjection("perspective", RI_FOV, &fov, RI_NULL);

// --- declaration des lumieres -----

	RiLightSource((RtFunc)ambientlight, "intensity" , &intens, RI_NULL);
	RiLightSource((RtFunc)pointlight  , "intensity", &intens, "from", &ponct3, RI_NULL);


	RiTranslate(0.0, 0.0, -10.0);

	RiLightSource((RtFunc)pointlight  , "intensity", &intens2, "from", &ponct2,  RI_NULL);
	RiLightSource((RtFunc)pointlight  , "intensity", &intens, "from", &ponct,  RI_NULL);


	// **********************************************************


	quad[0] = 1.0 ; quad[1] = 1.0 ; quad[2] = 1.0 ;

	RiTransformBegin();
		Ca = 0.9; Cd = 0.1; Cr = 0.0; Ct = 0.0; n = 1.0; Cs = 3.0; size = 35.0;
		RiSurface((RtFunc)granite, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(quad);
		RiTranslate(-4.0, 0.0, 2.0);
		PolyQuadric(2.0, 0.0, 2.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -1.0);
	RiTransformEnd();


	// **********************************************************


	sphere[0] = 1.0 ; sphere[1] = 0.9 ; sphere[2] = 0.2 ;

	RiTransformBegin();
		Ca = 0.5; Cd = 0.5; Cr = 1.0; Ct = 0.0; n = 0.5; Cs = 1.0; size = 35.0;
		RiSurface((RtFunc)plastic, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(sphere);
		RiTranslate(3.25, 1.5, 2.0);
		RiSphere(2.0, 0.0, 0.0, 360.0, RI_NULL);

	RiTransformEnd();


	// **********************************************************


	sphere[0] = 0.9 ; sphere[1] = 0.1 ; sphere[2] = 0.2 ;

	RiTransformBegin();
		Ca = 0.5; Cd = 0.5; Cr = 0.2; Ct = 0.2; n = 0.8; Cs = 2.6; size = 35.0;
		RiSurface((RtFunc)matte, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(sphere);
		RiTranslate(2.75, -1.5, 3.75);
		RiSphere(1.0, 0.0, 0.0, 360.0, RI_NULL);

	RiTransformEnd();

	// **********************************************************


	plan[0] = 0.0; plan[1] = 0.0; plan[2] = 0.9; // 3 composantes R G B, plan --> type  couleur

	RiTransformBegin();
		Ca = 0.5; Cd = 0.5; Cr = 0.2; Ct = 0.0; n = 0.9; Cs = 2.5; size = 35.0;
		RiSurface((RtFunc)plastic, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(plan);
		RiTranslate(0.0, -2.0, 0.0);
		PolyPlane(0.0, 4.0, 1.0, 3.0, RI_NULL);

	RiTransformEnd();

	// ***********************************************************


    // le ray se fait dans world.cc
    RiWorldEnd();
RiEnd();
}


