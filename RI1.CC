
// exemple d'une Patch p.89 Renderman

#include "ri.h"



main()
{
RtFloat		Ca, Cd, Cr ,Ct,n ,Cs, size;

RtFloat		intens = 0.8 , intens3 = 0.6;
RtFloat	        intens2 = 0.5;
RtFloat		fov = 50.0 ;

RtPoint		ponct , ponct2, ponct3;

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

mat4 Patch;
RtPoint point;

Patch.setx(0,0, -2.5); Patch.sety(0,0, 3.0); Patch.setz(0,0, -3.0);
Patch.setx(0,1, -1.0); Patch.sety(0,1, 1.5); Patch.setz(0,1, 0.0);
Patch.setx(0,2, 1.0); Patch.sety(0,2, 1.5); Patch.setz(0,2, 0.0);
Patch.setx(0,3, 2.0); Patch.sety(0,3, 4.0); Patch.setz(0,3, -3.0);

/*cout << "\nPatch.px(0,0) = " << Patch.px(0,0);
cout << "\nPatch.py(0,0) = " << Patch.py(0,0);
cout << "\nPatch.pz(0,0) = " << Patch.pz(0,0);

cout << "\nPatch.px(0,1) = " << Patch.px(0,1);
cout << "\nPatch.py(0,1) = " << Patch.py(0,1);
cout << "\nPatch.pz(0,1) = " << Patch.pz(0,1);*/

Patch.setx(1,0, -1.5); Patch.sety(1,0, 1.0); Patch.setz(1,0, 0.0);
Patch.setx(1,1, -1.0); Patch.sety(1,1, 1.0); Patch.setz(1,1, 0.0);
Patch.setx(1,2, 1.0); Patch.sety(1,2, 1.0); Patch.setz(1,2, -3.0);
Patch.setx(1,3, 1.5); Patch.sety(1,3, 1.0); Patch.setz(1,3, 0.0);

Patch.setx(2,0, -1.5); Patch.sety(2,0, -1.0); Patch.setz(2,0, 0.0);
Patch.setx(2,1, -1.0); Patch.sety(2,1, -1.0); Patch.setz(2,1, 0.0);
Patch.setx(2,2, 1.0); Patch.sety(2,2, -1.0); Patch.setz(2,2, -3.0);
Patch.setx(2,3, 1.5); Patch.sety(2,3, -1.0); Patch.setz(2,3, 0.0);

Patch.setx(3,0, -3.0); Patch.sety(3,0, -3.0); Patch.setz(3,0, -2.0);
Patch.setx(3,1, -1.5); Patch.sety(3,1, -2.0); Patch.setz(3,1, 0.0);
Patch.setx(3,2, 1.5); Patch.sety(3,2, -2.0); Patch.setz(3,2, -1.0);
Patch.setx(3,3, 5.0); Patch.sety(3,3, -5.0); Patch.setz(3,3, -5.0);

RiBegin();

 RiWorldBegin();

    MAX_RAY =  7; 
    Flag_Stool = RI_TRUE ;
    RtColor patch, sphere, plan, quad;

// --- definition dimension  de l'image et perspective -----

	RiFormat(100, 100, 1.0);
	RiDisplay("ima1", RI_FILE, RI_RGB, RI_NULL);
	RiProjection("perspective", RI_FOV, &fov, RI_NULL);

// --- declaration des lumieres -----

	RiLightSource((RtFunc)ambientlight, "intensity" , &intens, RI_NULL);
	RiLightSource((RtFunc)pointlight  , "intensity", &intens, "from", &ponct3, RI_NULL);


	RiTranslate(0.0, 0.0, -20.0);

	RiLightSource((RtFunc)pointlight  , "intensity", &intens2, "from", &ponct2,  RI_NULL);
	RiLightSource((RtFunc)pointlight  , "intensity", &intens, "from", &ponct,  RI_NULL);


	// *************************Patch****************************


	patch[0] = 1.0 ; patch[1] = 0.0 ; patch[2] = 0.0 ;

	RiTransformBegin();
		Ca = 0.5; Cd = 0.5; Cr = 0.2; Ct = 0.0; n = 1.0; Cs = 0.0; size = 35.0;
		RiSurface((RtFunc)plastic, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(patch);
		//RiRotate(45.0, 2.0, 0.0, 0.0);
		//RiScale(1.5, 1.5, 1.5);
		//RiTranslate(0.0, 0.0, 3.0);
		RiPatch(RI_BICUBIC, RI_P, Patch);

	RiTransformEnd();

	// ***********************************************************


/*	sphere[0] = 0.1; sphere[1] = 0.9; sphere[2] = 0.9;

	RiTransformBegin();
	        Ca = 0.0 ; Cd = 0.5 ; Cr = 1.0 ; Ct = 0.5 ; n = 0.1 ; Cs = 0.0 ; size = 35.0 ;
	        RiSurface((RtFunc)plastic, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd,     RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(sphere);
		RiSphere(2.0, 0.0, 0.0, 360.0, RI_NULL);	
	RiTransformEnd();*/			

	// **********************************************************


/*	quad[0] = 0.9 ; quad[1] = 0.9 ; quad[2] = 0.9 ;

	RiTransformBegin();
		Ca = 0.2 ; Cd = 0.8 ; Cr = 0.0 ; Ct = 0.1 ; n = 0.8 ; Cs = 0.0 ; size = 35.0 ;
        	RiSurface((RtFunc)granite, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(quad);
		RiTranslate(-2.0, 0.0, 2.4);
		RiRotate(30.0, 1.0, 0.0, 1.0);
                PolyQuadric(2.0, 0.0, 1.5, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0,-2.0);		
	RiTransformEnd(); 
*/


	// **********************************************************

/*	quad[0] = 0.5; quad[1] = 0.9; quad[2] = 0.9;

	RiTransformBegin();
	        Ca = 0.3 ; Cd = 0.5 ; Cr = 0.0 ; Ct = 0.5 ; n = 0.6 ; Cs = 0.3 ; size = 35.0 ;
	        RiSurface((RtFunc)plastic, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd,     RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(quad);
		RiTranslate(0.5, 0.0, 1.0);
		RiRotate(90.0, 1.0, 0.0, 1.0);
		PolyQuadric(2.0, 2.0, 2.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.0,-3.0);	
	RiTransformEnd();							   */


	// **********************************************************

	plan[0] = 0.0 ; plan[1] = 0.0 ; plan[2] = 0.9 ; // 3 composantes R G B, plan --> type  couleur

	RiTransformBegin();
		Ca = 0.9 ; Cd = 0.2 ; Cr = 0 ; Ct = 0.0 ; n = 1.0 ; Cs = 0.0 ; size = 35.0 ;
        	RiSurface((RtFunc)plastic, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(plan);
		PolyPlane(0.0, 4.0, 1.0, 3.0, RI_NULL);
	
        // cf. le fichier ray.cc	

	RiTransformEnd();

	// ***********************************************************


	plan[0] = 0.9 ; plan[1] = 0.9 ; plan[2] = 0.9 ; // 3 composantes R G B, plan --> type  couleur

	RiTransformBegin();
		Ca = 0.9 ; Cd = 0.2 ; Cr = 0 ; Ct = 0.9 ; n = 0.1 ; Cs = 2.0 ; size = 35.0 ;
        	RiSurface((RtFunc)plastic, RI_KR, &Cr, RI_KA, &Ca, RI_KD, &Cd, RI_KT, &Ct, RI_N, &n, RI_KS, &Cs, RI_SIZE, &size, RI_NULL);
		RiColor(plan);
		PolyPlane(0.0, 0.0, 1.0, 3.0, RI_NULL);
	
        // cf. le fichier ray.cc	

	RiTransformEnd();


	// ***********************************************************


    // le ray se fait dans world.cc
    RiWorldEnd();
RiEnd();
}


