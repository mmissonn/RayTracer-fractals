#ifndef  _Global_h
#define  _Global_h



// --- le vecteur des surfaces ---
extern Surfaces_Pt    surf_list[],
	       Current_Surf ;
extern Surfaces_PtPt  current_surf_list;


// --- le vecteur des surfaces pour liste intermediaire ---
extern Surfaces_Pt    surf_int_list[];

// --- le vecteur des lumieres ---
extern Lights_Pt    light_list[],
	     Current_Light;
extern Lights_PtPt  current_light_list;
	     

// --- definition des parametres globaux
extern char       filename[] ;
extern RtInt      NumLight;
extern RtInt	  NumSurf;
extern RtInt      resolution_x ;
extern RtInt      resolution_y ;
extern RtFloat    camera_angle ;
extern RtInt	  MAX_RAY ;

extern RtFloat   inc_x, inc_y ;


// --- Variables globales RenderMan (cf mini-projet 2)
extern RtColor     Cs ;                 // Surface color
extern RtColor     Os ;                 // Surface opacity
extern RtPoint     P ;                  // Surface position
extern RtPoint     N ;                  // Surface shading normal
extern RtPoint     Ng ;                 // Surface geometric normal
extern RtPoint     L ;                  // Dir. from surf. to light source
extern RtColor     Cl ;                 // Light color
extern RtPoint     I ;                  // Dir. off incoming ray
extern RtColor     Ci ;                 // Color of light from surface
extern RtColor     Oi ;                 // Opacity of surface
extern RtPoint     E ;                  // Position of the camera
extern RtPoint     R ;	  		// Rayon reflechi
extern RtPoint     T ; 		        // Rayon refracte

extern RtFloat     ka, kd, ks ;		// Coefficients pour une surface
extern RtFloat     roughness ;
extern RtColor     specularcolor ;

extern RtPoint	    H ; 		// vecteur H entre L et l'oeil


extern RtFloat     Window_Right  ; 	// Dimension de la fenetre
extern RtFloat     Window_Left   ;
extern RtFloat     Window_Bottom ;
extern RtFloat     Window_Top   ;



extern RtBoolean   Flag_Illuminate, 
	           Flag_Stool,
	    	   Flag_Shadow ;


extern RtMatrix    current_transfo;    // Matrice de transformation 
extern Attributes  current_attribute;  // Attributs de la surface

extern StackMatrix        PPMatrix;	// Stack pour conserver les matrices 
extern StackAttributes    PPAttribute;	// Stack pour conserver les attributs



#endif
