 #include "ri.h"
 #include <stdio.h>


//----------------------------------------------------------------------------
// Methodes de la classe Plan
//----------------------------------------------------------------------------
RtVoid  Plan::plan_to_mat()
{

// Equation d'un plan ax + by + cz + d = 0

    matrice.matrice[0][0] = 0 ;
    matrice.matrice[1][1] = 0 ;
    matrice.matrice[2][2] = 0 ;
    matrice.matrice[3][3] = d ;

    matrice.matrice[0][1] = matrice.matrice[1][0] = 0 ;
    matrice.matrice[0][2] = matrice.matrice[2][0] = 0 ;
    matrice.matrice[0][3] = matrice.matrice[3][0] = a * 0.5 ;
   
    matrice.matrice[1][2] = matrice.matrice[2][1] = 0 ;
    matrice.matrice[1][3] = matrice.matrice[3][1] = b * 0.5 ;
    
    matrice.matrice[2][3] = matrice.matrice[3][2] = c * 0.5 ;



}


RtVoid  Plan::mat_to_plan()
{

    a = 2.0 * mat(0,3) ;
    b = 2.0 * mat(1,3) ;
    c = 2.0 * mat(2,3) ;
 
    d = mat(3,3) ;
   

}


Surfaces_Pt Plan::dup()
{
Plan_Pt  surf = NULL;

    // Creer un nouveau plan
    surf = new Plan;

    // Copier les infos dans ce nouveau plan
    *surf = *this;
    
    // Retourner le pointeur sur le nouveau plan
    return( Surfaces_Pt(surf) );
}


RtVoid  Plan::transfo( 
                      RtMatrix trans   // matrice de transformation
                     )
{
    // --- meme transformation que la quadrique ---
    // --- un plan c'est une simplification d'une quadrique ...
    // --- new_quad = inverse[mat] * quad * transpose[inverse[mat]]

    // Placer le plan dans une matrice
    plan_to_mat();
    
    // Transformer la matrice du plan
    matrice = ((!trans) * matrice * (~(!trans)));

    // Replacer la matrice dans les coefficients du plan
    mat_to_plan();
}


RtVoid  Plan::stool()              
{

  cout << "Un plan \n";
  cout << form( "A : %3.3f  B : %3.3f  C : %3.3f  D: %3.3f\n", a,b,c,d);
  cout << form( "matrice : [ %3.3f  %3.3f  %3.3f  %3.3f ]\n", mat(0,0), mat(1,0), 
					   mat(2,0), mat(3,0));
  cout << form( "          [ %3.3f  %3.3f  %3.3f  %3.3f ]\n", mat(0,1), mat(1,1),
					   mat(2,1), mat(3,1));
  cout << form( "          [ %3.3f  %3.3f  %3.3f  %3.3f ]\n", mat(0,2), mat(1,2),
					   mat(2,2), mat(3,2));
  cout << form( "          [ %3.3f  %3.3f  %3.3f  %3.3f ]\n", mat(0,3), mat(1,3),
					   mat(2,3), mat(3,3));
  cout << "\n\n";

  cout << form("Couleur  R: %3.3f G: %3.3f B: %3.3f\n", couleur.rouge, 
					      couleur.vert,
					      couleur.bleu);

  cout << "Attributs \n";
  cout << form( "Ka: %3.3f Kd: %3.3f Ks: %3.3f Kr: %3.3f Kt: %3.3f N: %3.3f\n", ka, kd, ks,
					         kr, kt, n, size);

  cout << "\n Lumieres affectant le plan\n\n";
  for (int loop = 0 ; loop < nb_lumiere; loop++)
 {
		cout << "Lumiere no." << loop << "\n";
		cout << form( "Position X: %3.3f   Y: %3.3f   Z: %3.3f\n",
 					light_pt[loop]->position.x,
					light_pt[loop]->position.y,
					light_pt[loop]->position.z);
		cout << "Intensite : " << light_pt[loop]->intensite << "\n";
		cout << form(" Couleur  R: %3.3f  G: %3.3f  B: %3.3f\n\n",
 					light_pt[loop]->couleur.rouge,
					light_pt[loop]->couleur.vert,	
					light_pt[loop]->couleur.bleu);
} // for loop



 }


RtFloat  Plan::intersect( RtPoint& position,  RtPoint& direction )  
{
 RtFloat Bq, Cq ;
 

	Bq = a * direction.x +  
	     b * direction.y +  
	     c * direction.z  ;

	if ( Bq == 0.0 ) return(RI_INFINITY); 
	Cq = -1.0 * (a * position.x  +  
		     b * position.y  +  
		     c * position.z  + d) ;
	 
	return (Cq / Bq < 0.0 ? RI_INFINITY : Cq/Bq) ;

}


RtPoint  Plan::normale(const RtPoint& P)  
{
  RtPoint Rn ;

	Rn.x = a ;
	Rn.y = b ;
	Rn.z = c ;

  return (Rn);
}


RtVoid  Plan::preproc()            
{
//****
// c'est une fonction bidon car
// nous avons besoin que de preproc pour les surfaces de types Triangles
//
}



