#include "ri.h"
#include <stdio.h>



//----------------------------------------------------------------------------
// Methodes de la classe Sphere
//----------------------------------------------------------------------------
Surfaces_Pt Sphere::dup()
{
Sphere_Pt  surf = NULL;

    // Creer une nouvelle sphere
    surf = new Sphere;

    // Copier les infos dans cette nouvelle sphere
    *surf = *this;
    
    // Retourner le pointeur sur la nouvelle sphere
    return( Surfaces_Pt(surf) );
}


RtVoid  Sphere::transfo( 
                        RtMatrix trans   // matrice de transformation
                       )
{
    // Transformer le centre de la sphere avec la matrice
    centre = centre * trans;

}


RtVoid  Sphere::stool()              // mini-projet 1
{

	cout << "Sphere \n";
	cout << form(" Centre a (%3.3f,%3.3f,%3.3f) de rayon %3.3f \n\n", centre.x, centre.y,
							centre.z, rayon);

	cout << form( "Couleur  R: %3.3f G: %3.3f B: %3.3f\n", couleur.rouge, 
					      couleur.vert,
					      couleur.bleu);

	cout << "Attributs \n";
	cout << form( "Ka: %3.3f Kd: %3.3f Ks: %3.3f Kr: %3.3f Kt: %3.3f \nN: %3.3f Size : %3.3f\n", ka, kd, ks,
							 kr, kt, n, size);

	cout << "\n Lumieres affectant la sphere\n\n";
	for (int loop = 0 ; loop < nb_lumiere; loop++)
	{
		cout << "Lumiere no." << loop << "\n";
		cout << form( "Position X: %3.3f   Y: %3.3f   Z: %3.3f\n",
 					light_pt[loop]->position.x,
					light_pt[loop]->position.y,
					light_pt[loop]->position.z);
		cout << "Intensite : " << light_pt[loop]->intensite << "\n";
		cout << form( "Couleur  R: %3.3f  G: %3.3f  B: %3.3f\n\n",
 					light_pt[loop]->couleur.rouge,
					light_pt[loop]->couleur.vert,	
					light_pt[loop]->couleur.bleu);
	} // for loop


}


RtFloat  Sphere::intersect(RtPoint& position,  RtPoint& direction )  
{
 RtFloat B, C ;
 RtFloat T0, T1 ;
 RtFloat Delta ;

  
 RtFloat X,Y,Z;

   X = position.x - centre.x ;
   Y = position.y - centre.y ;
   Z = position.z - centre.z ;

     B = 2 * ( direction.x * X + direction.y * Y +  direction.z * Z);
    
     C =  X*X + Y*Y + Z*Z - rayon*rayon;
     Delta = (B*B) - (4 * C);

     if (Delta < 0.0) return (RI_INFINITY) ; // pas d'intersection

     if (Delta == 0.0) return (-1.0*B / 2.0) ;

     // sinon deux intersections 
     T0 = (-1*B - sqrt(Delta))/2.0; 
     if (T0 > RI_EPSILON) return (T0);

     T1 = (-1*B + sqrt(Delta))/2.0; 
     if (T1 > RI_EPSILON) return (T1) ;
     return (RI_INFINITY);



}




RtPoint  Sphere::normale(const RtPoint& P)  
{
 RtPoint Rn ;
 RtFloat Inverse ;

 Inverse = (1 / rayon) ;

	Rn.x = (P.x - centre.x) / rayon ; // * Inverse ;
	Rn.y = (P.y - centre.y) / rayon ; // * Inverse ;
	Rn.z = (P.z - centre.z) / rayon ; // * Inverse ;

  return (Rn); 
}


RtVoid  Sphere::preproc()            
{
//****
// c'est une fonction bidon car
// nous avons besoin que de preproc pour les surfaces de types Triangles
//
}





