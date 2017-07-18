 #include "ri.h"
 #include <stdio.h>
 #include <math.h>


//----------------------------------------------------------------------------
// Methodes de la classe Quad
//----------------------------------------------------------------------------
RtVoid Quad::quad_to_mat()
{

// Equation d'une quadrique aX2+bY2+cZ2+dXY+eYZ+fxz+gX+hY+jZ+k=0

    matrice.matrice[0][0] = a ;
    matrice.matrice[1][1] = b ;
    matrice.matrice[2][2] = c ;
    matrice.matrice[3][3] = k ;

    matrice.matrice[0][1] = d * 0.5;
    matrice.matrice[1][0] = d * 0.5;
    matrice.matrice[0][2] = f * 0.5;
    matrice.matrice[2][0] = f * 0.5;
    matrice.matrice[0][3] = g * 0.5;
    matrice.matrice[3][0] = g * 0.5;
   
    matrice.matrice[1][2] = e * 0.5;
    matrice.matrice[2][1] = e * 0.5;
    matrice.matrice[1][3] = h * 0.5;
    matrice.matrice[3][1] = h * 0.5;
    
    matrice.matrice[2][3] = j * 0.5;
    matrice.matrice[3][2] = j * 0.5;



}


RtVoid  Quad::mat_to_quad()
{

    a = mat(0,0) ;
    b = mat(1,1) ;
    c = mat(2,2) ;
    d = 2 * mat(0,1) ;
    e = 2 * mat(1,2) ;
    f = 2 * mat(0,2) ;
    g = 2 * mat(0,3) ;
    h = 2 * mat(1,3) ;
    j = 2 * mat(2,3) ;
    k = mat(3,3) ;

   

}


Surfaces_Pt Quad::dup()
{
Quad_Pt  surf = NULL;

    // Creer une nouvelle quadrique
    surf = new Quad;

    // Copier les infos dans cette nouvelle quadrique
    *surf = *this;
    
    // Retourner le pointeur sur la nouvelle quadrique
    return( Surfaces_Pt(surf) );
}


RtVoid  Quad::transfo( RtMatrix trans )
{
    // --- new_quad = inverse[mat] * quad * transpose[inverse[mat]]

    // Placer la quadrique dans une matrice
    quad_to_mat();
    
    // Transformer la matrice de la quadrique
    matrice = ((!trans) * matrice * (~(!trans)));

    // Replacer la matrice dans les coefficients de la quadrique
    mat_to_quad();
}


RtVoid  Quad::stool()              
{

  cout << "Une quadrique \n";
  cout << form( "A : %3.3f  B : %3.3f  C : %3.3f  D: %3.3f E: %3.3f F: %3.3f G: %3.3f H: %3.3f J: %3.3f K: %3.3f\n", a,b,c,d,e,f,g,h,j,k);
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

  cout << "\n Lumieres affectant la quadrique\n\n";
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


RtFloat  Quad::intersect( RtPoint& pos,  RtPoint& dir )  
{
 RtFloat t, t1, Aq, Bq, Cq;      // p = position, d = direction (x, y, z)

 Aq =   ( dir.x * (a * dir.x + d * dir.y + f * dir.z) +
        dir.y * (b * dir.y + e * dir.z) + c * dir.z * dir.z);

 Bq =   (dir.x * (2.0 * a * pos.x + d * pos.y + f * pos.z + g) + dir.y * (d * pos.x +
	2.0 * b * pos.y + e * pos.z + h) + dir.z * (f * pos.x + e * pos.y + 2.0 * c * pos.z +
	j));

 Cq =   ( pos.x * (a * pos.x + d * pos.y + f * pos.z + g)
	+ pos.y * (b * pos.y + e * pos.z + h)
	+ pos.z * (c * pos.z + j)
	+ k);

 if (Aq != 0.0) 
	{
	  if (((Bq * Bq) - 4.0 * Aq * Cq) < 0.0)    // si discriminant < 0
	  	return(RI_INFINITY);
	  t  = (- Bq - (RtFloat) sqrt( ( Bq * Bq - 4.0 * Aq * Cq) ) ) / (2.0 * Aq);
	  t1 = (- Bq + (RtFloat) sqrt( ( Bq * Bq - 4.0 * Aq * Cq) ) ) / (2.0 * Aq);
	  if (t < t1) return( t );
	     else return( t1 );
	}
  if (Bq == 0)
	return(RI_INFINITY);
 return (-Cq/Bq);	 
}


RtPoint  Quad::normale(const RtPoint& p)   
{
  RtPoint Rn ;

	Rn.x = 2 * a * p.x + d * p.y + f * p.z + g;
	Rn.y = 2 * b * p.y + d * p.x + e * p.z + h;
	Rn.z = 2 * c * p.z + e * p.y + f * p.x + j;

  return (Rn);
}


RtVoid  Quad::preproc()            
{
//****
// c'est une fonction bidon car
// nous avons besoin que de preproc pour les surfaces de types Triangles
//
}



