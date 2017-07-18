#include   "ri.h"
#include   <string.h>
#include   <ctype.h>
#include   <math.h>

extern void DrawSurface(mat4 patch, int niveau);  // pour RiPatch

// --- le vecteur des surfaces ---
Surfaces_Pt    surf_list[MAX_SURFACE],
	       Current_Surf = NULL;
Surfaces_PtPt  current_surf_list = NULL;


// --- le vecteur des surfaces pour liste intermediaire ---
Surfaces_Pt    surf_int_list[MAX_SURFACE];

// --- le vecteur des lumieres ---
Lights_Pt    light_list[MAX_LIGHT],
	     Current_Light = NULL;
Lights_PtPt  current_light_list = NULL;
	     
// --- pile qui maintient les listes d'objets
pile objectlist_pile;     


// --- definition des parametres globaux
char       filename[180] ;
RtInt      NumLight;
RtInt	   NumSurf;
RtInt      resolution_x = 100 ;
RtInt      resolution_y = 100 ;
RtFloat    camera_angle = 90.0 ;
RtInt	   MAX_RAY = 8 ;

RtFloat    inc_x, inc_y ;


// --- Variables globales RenderMan (cf mini-projet 2)
RtColor     Cs ;                // Surface color
RtColor     Os ;                // Surface opacity
RtPoint     P ;                 // Surface position
RtPoint     N ;                 // Surface shading normal
RtPoint     Ng ;                // Surface geometric normal
RtPoint     L ;                 // Dir. from surf. to light source
RtColor     Cl ;                // Light color
RtPoint     I ;                 // Dir. off incoming ray
RtColor     Ci ;                // Color of light from surface
RtColor     Oi ;                // Opacity of surface
RtPoint     E ;                 // Position of the camera
RtPoint     R ;			// Rayon reflechi
RtPoint     T ; 		// Rayon refracte

RtFloat     ka, kd, ks ;	// Coefficients pour une surface
RtFloat     roughness ; 
RtColor     specularcolor ;
RtPoint	    H ; 		// vecteur H entre L et l'oeil

RtFloat     Window_Right  = +1 ; // Dimension de la fenetre
RtFloat     Window_Left   = -1 ;
RtFloat     Window_Bottom = +1 ;
RtFloat     Window_Top    = -1 ;

RtBoolean   Flag_Stool = RI_TRUE,
	    Flag_Illuminate = RI_FALSE,
	    Flag_Shadow = RI_FALSE ;

RtMatrix    current_transfo;    // Matrice de transformation 
Attributes  current_attribute;  // Attributs de la surface

StackMatrix        PPMatrix;	// Stack pour conserver les matrices 
StackAttributes    PPAttribute;	// Stack pour conserver les attributs


// **************************************************************************
// *** *** *** *** *** *** les fonctions de RenderMan *** *** *** *** *** ***
// **************************************************************************

// --- --- --- --- --- --- Ri Area Light Source --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.225)
//
RtLightHandle     RiAreaLightSource( char *name, ... )
{
      cerr << "fonction: \"RiAreaLightSource\" non suportee \n";
      return( RI_NULL );
}


// --- --- --- --- --- --- Ri Atmosphere --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.235)
//
RtVoid            RiAtmosphere( char* name, ... )
{
      cerr << "fonction: \"RiAtmosphere\" non suportee \n";
}



// --- --- --- --- --- --- Ri Attribute Begin --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.50)
//
RtVoid            RiAttributeBegin()
{
    // Faire un push de la matrice de transformation

    if (PPMatrix.full() == RI_FALSE)
	PPMatrix.push(current_transfo);

    // Faire un push des attributs courants

    if (PPAttribute.full() == RI_FALSE)
	PPAttribute.push(current_attribute);
}

// --- --- --- --- --- --- Ri Attribute End --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.50)
//
RtVoid            RiAttributeEnd()
{
    // Faire un pop de la matrice de transformation

    if (PPMatrix.empty() == RI_FALSE)
	current_transfo = PPMatrix.pop();

    // Faire un pop des attributs courants

    if (PPAttribute.empty() == RI_FALSE)
	current_attribute = PPAttribute.pop();
}



// --- --- --- --- --- --- Ri Begin --- --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.48)
//
RtVoid            RiBegin()
{
    // --- prepare certaines variables globales ---
    current_light_list = light_list;
    NumLight = 0;
    NumSurf  = 0;

    // --- les def. de RiObject peuvent changer current_surf_list ---
    current_surf_list  = surf_list;
    current_surf_list[0] = 0;

}



	
// --- --- --- --- --- --- Ri Color --- --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.213)
//
RtVoid            RiColor(RtColor Cs )
{
  RtColor temp ;
      temp[0] = Cs[0]; // .rouge ;
      temp[1] = Cs[1]; // .vert  ;
      temp[2] = Cs[2]; // .bleu  ;

   current_attribute.couleur = temp ;

}

// --- --- --- --- --- --- Ri Concat Transform --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.116)
//
RtVoid            RiConcatTransform( RtMatrix trans )
{
      // Effectuer l'addition des matrices
      current_transfo = trans * current_transfo;
}


// --- --- --- --- --- --- Ri Display --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.155)
//
RtVoid            RiDisplay( char* name, RtToken type, RtToken mode, ... )
{
 va_list    ap;               // pointeur d'argument
 RtToken    nom = NULL;       // nom du parametre

   va_start(ap, mode);

   if ( ! strcmp ( type, RI_FILE))		// resultat dans un fichier
   	strcpy (filename, name) ;
   if ( ! strcmp ( type, RI_FRAMEBUFFER))	// resultat a l'ecran
	cout << "Affichage a l'ecran \n";
   if ( ! strcmp ( mode, RI_RGB))
	cout << "Mode RGB \n";
   else
	cerr << "Autres modes que RGB non supportes\n";

    for (;;) {

	nom    = va_arg(ap, RtToken);
        if ((nom == RI_NULL))    break;
              
    } // for (;;)

}

// --- --- --- --- --- --- Ri End --- --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.48)
//
RtVoid            RiEnd()
{

	cout << "Fin de l'execution\n";
	exit(0);
}

// --- --- --- --- --- --- Ri Format --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.156)
//
RtVoid            RiFormat( RtInt xresol, RtInt yresol, RtFloat pix_ratio )
{
      resolution_x = xresol ;
      resolution_y = yresol ;
      // on prend pour acquis que pix_ratio = 1.0
}




// --- --- --- --- --- --- Ri Identity --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.117)
//
RtVoid            RiIdentity()
{
    for (int i = 0 ; i < 4 ; i++)
    {
	for (int j = 0 ; j < 4 ; j++)
      		current_transfo[i][j] = 0.0 ;
	current_transfo[i][i] = 1.0 ; 
    }
}

// --- --- --- --- --- --- Ri Illuminate --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.217)
//
RtVoid            RiIlluminate( RtLightHandle light, RtBoolean onoff )
{
      for (int loop = 0; loop < NumLight; loop++)
      	if ( RtLightHandle(light_list[loop]) == light)
		{
	
		light_list[loop]->on_off = onoff;
		}
}

// --- --- --- --- --- --- Ri Light Source --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.216)
//
RtLightHandle     RiLightSource( RtFunc shader_pt, ...)
{
Lights_Pt  lumiere = NULL;   // Pointeur temporaire sur une lumiere
va_list    ap;               // pointeur d'argument
RtToken    nom 	   = NULL;   // nom du parametre
RtToken    valeur  = NULL;   // valeur du parametre


    // Initialiser la liste des parametres
    va_start(ap, shader_pt);

    // --- cree une nouvelle lumiere (lumiere) ---
    lumiere = new Lights;

    // --- ajoute la lumiere a la liste ---

    if (NumLight  <=  MAX_LIGHT)
		light_list[NumLight++] = lumiere;
    else {
	cerr << "\nDepassement du nombre de lumieres disponibles ! ";
        return(RtLightHandle(NULL));
	} // else 

    // --- pointeur au shader de lumiere ---
    lumiere->shader_pt = shader_pt;

    // --- parcours la liste des parametres ---
    for (;;) {

	nom    = va_arg(ap, RtToken);
        if ((nom == RI_NULL))    break;
        
    
         if ( ! strcmp( nom, "from" ))
               lumiere->position =  *(va_arg (ap, RtPoint*));
         if ( ! strcmp( nom, "intensity" ))
               lumiere->intensite =  *(va_arg (ap, RtFloat*));
         if ( ! strcmp( nom, "lightcolor" ))
               lumiere->couleur = *(va_arg (ap, RtColor*));

        
    } // for (;;)

    // affectation du deplacement et rotation sur lumiere
    lumiere->position = lumiere->position * current_transfo ;	
    // Reseter les liste des parametres
    va_end(ap);

    return( RtLightHandle(lumiere) );
}



// --- --- --- --- --- --- Ri Polygon --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.70)
//
RtVoid            RiPolygon( RtInt nvertices, RtToken type, ...)

{
va_list      ap;
RtToken	     nom = NULL;
RtToken	     valeur = NULL;

RtPoint	     Pa,Pb,Pc,Pd;
Triangle_Pt  surf  = NULL;   // nouvelle surface cree
Triangle_Pt  surf2 = NULL;

    // Initialiser la liste des parametres
    va_start(ap, type);

    if ( nvertices == 3 ) {

	RtPoint *Poly;

          // --- cree une nouvelle surface (surf) ---
          surf = new Triangle;

          // --- ajoute la surface a la liste ---
    
          if (NumSurf  <=  MAX_SURFACE){
            current_surf_list += *surf;
            NumSurf++;
          }

	  else {
		cerr << "\nDepassement du nombre de surfaces disponibles ! ";
       	      }	

          // --- extrais les 3 points de la liste des param ---


	for (;;) {

         if ( ! strcmp( type, RI_P ))
	  {
		Poly = va_arg (ap, RtPoint*);

		surf->a = Poly[0];
		surf->b = Poly[1];
		surf->c = Poly[2];

           
          } // if RI_P

		nom  = va_arg(ap, RtToken);
        	if ((nom == NULL))    break;

    	} // for (;;)


          // --- transforme la surface avec la matrice ---
          surf->transfo(current_transfo);

          // --- transfert les attributs ---

		*surf = current_attribute;

          // --- transfert les lumieres qui sont a On ---

	  for (int i=0; i < NumLight; i++) 
            if (light_list[i]->on_off == RI_TRUE)
              Surfaces_Pt(surf)->Affecte(light_list[i]);



    } // if nvectices == 3

    else if ( nvertices == 4 ) {

	RtPoint	*Poly;

          // --- cree 2 nouvelles surfaces ---
	 surf  = new Triangle;
	 surf2 = new Triangle;

	for (;;) {

         if ( ! strcmp( type, RI_P ))
	    {
	       Poly = va_arg (ap, RtPoint*);

		Pa = Poly[0];
		Pb = Poly[1];
		Pc = Poly[2];
		Pd = Poly[3];

             
	    } // if RI_P

	 nom    = va_arg(ap, RtToken);
         if ((nom == NULL))    break;
       
       	 } // for (;;)


	// apres avoir transforme en deux triangles 
	// on cree deux triangles (comme pour nvectices == 3)
	// et on fait les transformations necessaires + transferts attributs 
	// et des lumieres 
	

        // --- ajoute la surface a la liste ---
    
          if (NumSurf  <=  MAX_SURFACE){
            current_surf_list += *surf;
            NumSurf++;
          }

          else {
		cerr << "\nDepassement du nombre de surfaces disponibles ! ";
       	  } // else

          if (NumSurf  <=  MAX_SURFACE){
            current_surf_list += *surf2;
            NumSurf++;
          }

    	 else {
		cerr << "\nDepassement du nombre de surfaces disponibles ! ";
       	      } // else

	 surf->a = Pa; surf->b = Pb; surf->c = Pc;
	 surf2->a = Pa; surf2->b = Pd; surf2->c = Pc;

          
          // --- transforme les surfaces avec la matrice ---
          surf->transfo(current_transfo);
          surf2->transfo(current_transfo);

          // --- transfert les attributs ---

           *surf  = current_attribute;
           *surf2 = current_attribute;

	  // --- transfert les lumieres qui sont a On ---
	  for (int i=0; i < NumLight; i++) 
            if (light_list[i]->on_off == RI_TRUE){
              Surfaces_Pt(surf)->Affecte(light_list[i]);
	      Surfaces_Pt(surf2)->Affecte(light_list[i]); }


    }	// else if 


    // si plus de 4 points : on ne peut pas la traiter ...
    else {
        cerr << "fonction: \"RiPolygon\" bad nvertices: " << nvertices << "\n";
    }

    // Reseter la liste de parametres
    va_end(ap);
}


// --- --- --- --- --- --- RiObjectBegin --- --- --- --- --- --- --- ---
RtObjectHandle  RiObjectBegin()
{

  // Sauve sur la pile la matrice de transformation

    if (PPMatrix.full() == RI_FALSE)
	PPMatrix.push(current_transfo);

    // cree une liste de surfaces qui contient tous les objets
    // jusqu'a RiObjectEnd. La liste sera copiee dans la liste
    // surf_list a l'appel de RiObjectInstance.

    if((current_surf_list = new Surfaces_Pt[MAX_SURFACE]) != 0)
    {    
      current_surf_list[0] = 0 ;
      
      objectlist_pile.push(new object_list_node(*current_surf_list));
      return (RtObjectHandle (current_surf_list));
    }
    else 
    {
      cout << "\n\nRiObjectBegin: impossible d'allouer l'espace memoire\n\n";
      current_surf_list = surf_list;
      return (NULL);
    }
}


// --- --- --- --- --- --- RiObjectEnd --- --- --- --- --- --- --- ---
RtVoid RiObjectEnd()
{
    // Restaure la matrice de transformation
    if (PPMatrix.empty() == RI_FALSE)
      current_transfo = PPMatrix.pop();


    current_surf_list = surf_list ;
}


// --- --- --- --- --- --- RiObjectInstance --- --- --- --- --- --- --- ---
RtVoid RiObjectInstance( RtObjectHandle handle )
{

  Surfaces_Pt p;

  // pour toutes les surfaces de cette liste provisoire

  for(int i=0; (Surfaces_PtPt(handle)[i]!=0) && (i < MAX_SURFACE); i++)
  {

    // copie la surface et l'ajoute a la liste

   p = Surfaces_PtPt(handle)[i]->dup();

   current_surf_list += *p;

   // --- transforme la surface avec la matrice ---
      p->transfo(current_transfo);
   // --- transfert les attributs ---
   ((Attributes*)p)->operator=(current_attribute);

   // --- transfert les lumieres qui sont a On ---

	  for (int j=0; j < NumLight; j++) 
            if (light_list[j]->on_off == RI_TRUE)
              (p)->Affecte(light_list[j]);

   // --- ajoute la surface a la liste
     surf_list[NumSurf++] = p;

 
     
  }

}




// --- --- --- --- --- --- Ri Projection --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.149)
//
RtVoid            RiProjection(RtToken name, ...)

{
va_list  ap;
RtToken  nom	= NULL;
RtToken  valeur = NULL;

		

      // Initialiser la liste de parametres
      va_start(ap, name);

      if ( ! strcmp( name, "perspective" ) ) {

          
            //  for ( each param token ) {
      
            // RenderMan dit qu'il faut limiter camera_angle < 180 degres

    	for (;;) {
		
		 nom    = va_arg(ap, RtToken);
       		 if ((nom == RI_NULL))    break;
        
   	       	if ( ! strcmp( nom, RI_FOV ))
			camera_angle =  *(va_arg (ap, RtFloat*));
	} // for (;;)

	if (camera_angle > 180.0) camera_angle = 180.0 ;


    // Reseter les liste des parametres
    va_end(ap);
	
      } // if perspective

      else {
          cerr << "fonction: \"RiProjection\" type: " << name << " non suporte\n";
      } // else non supportee

      // Reseter la liste de parametres
      va_end(ap);
}

// --- --- --- --- --- --- Ri Rotate --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.112)
//
RtVoid            RiRotate( RtFloat angle, RtFloat dx, RtFloat dy, RtFloat dz )
{
RtMatrix Rz1, Ry1, Rx, Ry, Rz;
RtFloat norme, cosphi, sinphi, cospsi, sinpsi, cosangle, sinangle;
RtFloat a, b, c, racine;

norme = sqrt(dx*dx+dy*dy+dz*dz); 
a = dx/norme;
b = dy/norme;
c = dz/norme;


angle = (angle * 3.141592654)/180.0;    // conversion degre a radian

sinangle = sin(angle);
cosangle = cos(angle);


if (b==0.0 && a==0.0)
	{  		  // rotation autour de Oz
 	cosphi = 1.0;
  	sinphi = 0.0;
  	cospsi = 0.0;
  	sinpsi = 1.0;
	}

else
	{
	racine = sqrt((b*b)+(a*a));
  	cosphi = a/racine;
  	sinphi = b/racine;
  	cospsi = racine;
  	sinpsi = c;
	}


// Rz`(-phi)
Rz1[0][0] = cosphi;
Rz1[0][1] = sinphi;
Rz1[1][0] = -sinphi;
Rz1[1][1] = cosphi;

// Ry`(-psi)
Ry1[0][0] = cospsi;
Ry1[0][2] = sinpsi;
Ry1[2][0] = -sinpsi;
Ry1[2][2] = cospsi;

// Rx`(angle)
Rx[1][1] = cosangle;
Rx[1][2] = -sinangle;
Rx[2][1] = sinangle;
Rx[2][2] = cosangle;

// Ry`(psi)
Ry[0][0] = cospsi;
Ry[0][2] = -sinpsi;
Ry[2][0] = sinpsi;
Ry[2][2] = cospsi;

// Rz`(phi)
Rz[0][0] = cosphi;
Rz[0][1] = -sinphi;
Rz[1][0] = sinphi;
Rz[1][1] = cosphi;

current_transfo = (Rz1*Ry1*Rx*Ry*Rz) * current_transfo;
 
}



// --- --- --- --- --- --- Ri Scale --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.113)
//
RtVoid            RiScale( RtFloat sx, RtFloat sy, RtFloat sz )
{
RtMatrix  scale;

    

      // --- ajoute un scale a la matrice ---
      scale[0][0] = sx ;
      scale[1][1] = sy ;
      scale[2][2] = sz ;

      current_transfo = scale * current_transfo;
}

// --- --- --- --- --- --- Ri Sphere --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.62)
//
// Ici, on cree une sphere "totale" (theta=360, zmax-zmin=2*rayon)
//
RtVoid            RiSphere( RtFloat rayon, RtFloat zmin, RtFloat zmax,
                            RtFloat theta, ... )
{
Sphere_Pt  surf  = NULL;  // surface cree

    // --- cree une nouvelle surface (surf) ---
    surf = new Sphere;

    // --- ajoute la surface a la liste ---
    
  if (NumSurf  <=  MAX_SURFACE){
    current_surf_list += *surf;
    NumSurf++;
          }

    else {
	cerr << "\nDepassement du nombre de surfaces disponibles ! ";
       	} // else 

    // --- sphere de rayon "rayon" ---
    surf->rayon = rayon;

    // --- centre de la sphere: 0, 0, (zmin + (zmax-zmin)/2) ---
    surf->centre.x = 0.0;
    surf->centre.y = 0.0;
    surf->centre.z = zmin + (zmax - zmin) * 0.5;

    // --- transforme la surface avec la matrice ---
    surf->transfo(current_transfo);

    // --- transfert les attributs ---

	*surf = current_attribute;

    // --- transfert les lumieres qui sont a On ---

	  for (int i=0; i < NumLight; i++) 
            if (light_list[i]->on_off == RI_TRUE)
               Surfaces_Pt(surf)->Affecte(light_list[i]);

}


 
// --- --- --- --- ---- --- Ri Surface --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.231)
//
RtVoid            RiSurface( RtFunc shader_pt, ...)

{
va_list 	ap ;
RtToken 	nom = NULL ;



      // Initialiser la liste de parametres
      va_start(ap, shader_pt);	

	
      // --- pointeur au shader de surface ---
      current_attribute.shader_pt = shader_pt;

	
      // --- parcours la liste des parametres --- (voir RiLightSource)
      //      for ( each param token ) 

    for (;;) {

	 nom    = va_arg(ap, RtToken);
         if ((nom == NULL))    break;
  
         if ( ! strcmp( nom, "color" ))
               current_attribute.couleur = *(va_arg (ap, RtColor*));
	 if ( ! strcmp( nom, "specularcolor" ))
               current_attribute.specularcolor = *(va_arg (ap, RtColor*));
	 if ( ! strcmp( nom, "Ka" ))
               current_attribute.ka =  *(va_arg (ap, RtFloat*));
	 if ( ! strcmp( nom, "Kd" ))
               current_attribute.kd =  *(va_arg (ap, RtFloat*));
	 if ( ! strcmp( nom, "Ks" ))
               current_attribute.ks =  *(va_arg (ap, RtFloat*));
	 if ( ! strcmp( nom, "Kr" ))
               current_attribute.kr =  *(va_arg (ap, RtFloat*));
	 if ( ! strcmp( nom, "Kt" ))
               current_attribute.kt =  *(va_arg (ap, RtFloat*));
	 if ( ! strcmp( nom, "n" ))
               current_attribute.n  =  *(va_arg (ap, RtFloat*));

	 // roughness = 1/ size
	 if ( ! strcmp( nom, "Size" ))
               current_attribute.size = *(va_arg (ap, RtFloat*));

          } // for (;;)

        // Reseter la liste de parametres
        va_end(ap);
}


// --- --- --- --- --- --- Ri Transform   --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.117)
//
RtVoid		  RiTransform (RtMatrix trans)
{
  RtMatrix	Ident;

	current_transfo = (trans * Ident);
}



// --- --- --- --- --- --- Ri Transform Begin --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.111)
//
RtVoid            RiTransformBegin()
{
    // Faire un push de la matrice de transformation

   if (PPMatrix.full() == RI_FALSE)
	PPMatrix.push(current_transfo);
	
}

// --- --- --- --- --- --- Ri Transform End --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.111)
//
RtVoid            RiTransformEnd()
{
    // Faire un pop de la matrice de transformation

   if (PPMatrix.empty() == RI_FALSE)
	current_transfo = PPMatrix.pop();
	
}

// --- --- --- --- --- --- Ri Translate --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.112)
//
RtVoid            RiTranslate( RtFloat dx, RtFloat dy, RtFloat dz )
{
RtMatrix  trans ;

      // --- ajoute une translation a la matrice ---
      trans.matrice[3][0] = dx ;
      trans.matrice[3][1] = dy ;
      trans.matrice[3][2] = dz ;

      current_transfo = trans * current_transfo;
}

// --- --- --- --- --- --- Ri World Begin --- --- --- --- --- --- --- --- ---
//
// (cf: RenderMan Companion, p.48)
//
RtVoid            RiWorldBegin()
{

     // Faire un push de la matrice de transformation

    if (PPMatrix.full() == RI_FALSE)
	PPMatrix.push(current_transfo);

    // Faire un push des attributs courants

    if (PPAttribute.full() == RI_FALSE)
	PPAttribute.push(current_attribute);

}



// --- --- --- --- ---- --- Poly Plane --- --- --- --- --- --- --- --- ---
//
// plan d'eq: ax + by + cz + d = 0 ;
//
RtVoid            PolyPlane( RtFloat PPa, RtFloat PPb, RtFloat PPc, RtFloat PPd, ...)
{
Plan_Pt  surf  = NULL;  // surface cree


    // --- cree une nouvelle surface (surf) ---
    surf = new Plan;


    // --- ajoute la surface a la liste ---
    
          if (NumSurf  <=  MAX_SURFACE){
            current_surf_list += *surf;
            NumSurf++;
          }
          else {
           cerr << "\nDepassement du nombre de surfaces disponibles ! ";
       	  } // else 

    
    // Passage des valeurs 
    surf->a = PPa;
    surf->b = PPb;
    surf->c = PPc;
    surf->d = PPd;
    surf->matrice = Identite;


    // --- transforme la surface avec la matrice ---
    surf->transfo(current_transfo);

    // --- transfert les attributs ---

	*surf = current_attribute;

    // --- transfert les lumieres qui sont a On ---

	 for (int i=0; i < NumLight; i++) 
            if (light_list[i]->on_off == RI_TRUE)
              Surfaces_Pt(surf)->Affecte(light_list[i]);


}

 
// --- --- --- --- ---- --- Poly Quadric --- --- --- --- --- --- --- --- ---
//
// Quad d'eq: ax2 + by2 + cz2 + dxy + eyz + fxz + gx + hy + jz + k= 0 ;
//
RtVoid            PolyQuadric( RtFloat PPa, RtFloat PPb, RtFloat PPc, 
                               RtFloat PPd, RtFloat PPe, RtFloat PPf, 
                               RtFloat PPg, RtFloat PPh,RtFloat PPj, 
                               RtFloat PPk, ... )
{
Quad_Pt  surf  = NULL;  // surface cree


    // --- cree une nouvelle surface (surf) ---
    surf = new Quad;

    // --- ajoute la surface a la liste ---

 	 if (NumSurf  <=  MAX_SURFACE){ 
           current_surf_list += *surf;
           NumSurf++;
          }

          else {
            cerr << "\nDepassement du nombre de surfaces disponibles ! ";
       	  } // else 

    
    // Passage des valeurs 
    surf->a = PPa;
    surf->b = PPb;
    surf->c = PPc;
    surf->d = PPd;
    surf->e = PPe;
    surf->f = PPf;
    surf->g = PPg;
    surf->h = PPh;
    surf->j = PPj;
    surf->k = PPk;

    surf->matrice = Identite;


    // --- transforme la surface avec la matrice ---
    surf->transfo(current_transfo);

    // --- transfert les attributs ---

	*surf = current_attribute;

    // --- transfert les lumieres qui sont a On ---

	 for (int i=0; i < NumLight; i++) 
            if (light_list[i]->on_off == RI_TRUE)
              Surfaces_Pt(surf)->Affecte(light_list[i]);


}

 

// --- --- --- --- ---- --- RiPatch --- --- --- --- --- --- --- --- ---
//
//  p. 87 Renderman 
//
RtVoid RiPatch(RtToken type, RtToken typeCP, mat4& patch, ...)
{


cout << "\n\nVeuillez patienter s.v.p.\n" << "subdivision de la patch en cour...\n";


DrawSurface(patch, 0);  // debute la procedure de subdivision en triangles
			// au niveau zero.

cout << "Subdivision terminee.\n"; 
cout << "Nombre de surfaces : " << NumSurf << "\n\n";

}

