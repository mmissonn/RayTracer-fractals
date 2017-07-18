#include "ri.h"
#include <stdio.h>


                                  
//----------------------------------------------------------------------------
// Methodes de la classe Triangle
//----------------------------------------------------------------------------
Surfaces_Pt Triangle::dup()
{
Triangle_Pt  surf = NULL;

    // Creer un nouveau triangle
    surf = new Triangle;

    // Copier les infos dans ce nouveau triangle
    *surf = *this;

    // Retourner le pointeur sur le nouveau triangle
    return( Surfaces_Pt(surf) );
}


RtVoid  Triangle::transfo( 
                          RtMatrix current_transfo   // matrice de transformation
				
                         )
{
      // Transformer les trois points du triangle avec la matrice
      a = a * current_transfo;
      b = b * current_transfo;
      c = c * current_transfo;
}


RtVoid  Triangle::stool()
{
	cout << "Triangle \n";
	cout << form( "Point A : (%3.3f,%3.3f,%3.3f)   Point B : (%3.3f,%3.3f,%3.3f)    Point C : (%3.3f,%3.3f,%3.3f) \n", a.x, a.y, a.z, 
		b.x, b.y, b.z, 
		c.x, c.y, c.z);
	cout << form( "Couleur  R: %3.3f G: %3.3f B: %3.3f\n", couleur.rouge, 
					      couleur.vert,
					      couleur.bleu);

	cout << "Attributs \n";
	cout << form( "Ka: %3.3f Kd: %3.3f Ks: %3.3f Kr: %3.3f Kt: %3.3f N: %3.3f\n", ka, kd, ks,
							 kr, kt, n, size);

	cout << "\n Lumieres affectant le triangle\n\n";
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
} // stool



RtFloat  Triangle::intersect( RtPoint& position, RtPoint& direction )  
{
    RtFloat t,t1,t2;
    RtPoint Q;
    RtFloat b1;
    RtPoint MBa, MBb, MBc, mini, maxi ;

    RtBoolean Hit(RtPoint& position, RtPoint& direction , RtPoint& Min, RtPoint& Max);    
 
    mini.x = min ( min(MBa.x, MBb.x), MBc.x);
    mini.y = min ( min(MBa.y, MBb.y), MBc.y);
    mini.z = min ( min(MBa.z, MBb.z), MBc.z);

    maxi.x = max ( max(MBa.x, MBb.x), MBc.x);
    maxi.y = max ( max(MBa.y, MBb.y), MBc.y);
    maxi.z = max ( max(MBa.z, MBb.z), MBc.z);
            
    if(Hit(position, direction, mini, maxi))
    {
      t1 = norm*direction ;
      t2 = norm*position ;
      if (t1 == 0.0) return (RI_INFINITY); // position est dans le plan

      t = ((-1.0*d - t2) / t1) ; // distance avec le plan qui contient le triangle
      if (t < RI_EPSILON) return(0.0);

	 if (index == 0)
	    { 
            Q.y = position.y + direction.y*t;
            Q.z = position.z + direction.z*t;
            if ( norm.x > 0.0)
                 {
		 b1 = ((c.y-b.y) * (Q.z-b.z)) - ((Q.y-b.y) * (c.z-b.z));
	         if ( (b1 <= 0) || (b1 >= norm.x)) return (0.0);

		 b1 = ((a.y-c.y) * (Q.z-c.z)) - ((Q.y-c.y) * (a.z-c.z));
		 if ( (b1 <= 0) || (b1 >= norm.x)) return (0.0);

		 b1 = ((b.y-a.y) * (Q.z-a.z)) - ((Q.y-a.y) * (b.z-a.z));
		 if ( (b1 <= 0) || (b1 >= norm.x)) return (0.0);

		 return (t);
                 }
             else
                 {
		 b1 = ((c.y-b.y) * (Q.z-b.z)) - ((Q.y-b.y) * (c.z-b.z));
	         if ( (b1 >= 0) || (b1 <= norm.x)) return (0.0);

		 b1 = ((a.y-c.y) * (Q.z-c.z)) - ((Q.y-c.y) * (a.z-c.z));
		 if ( (b1 >= 0) || (b1 <= norm.x)) return (0.0);

		 b1 = ((b.y-a.y) * (Q.z-a.z)) - ((Q.y-a.y) * (b.z-a.z));
		 if ( (b1 >= 0) || (b1 <= norm.x)) return (0.0);

		 return (t);
                 }
	    }

	 if (index == 1)
	    {
            Q.x = position.x + direction.x*t;
            Q.z = position.z + direction.z*t;
            if ( norm.y > 0.0)
                 {
		 b1 = ((Q.x-b.x)*(c.z-b.z)) - ((c.x-b.x)*(Q.z-b.z));
		 if ( (b1 <= 0) || (b1 >= norm.y)) return (0.0);

		 b1 = (Q.x-c.x)*(a.z-c.z) - (a.x-c.x)*(Q.z-c.z);
		 if ( (b1 <= 0) || (b1 >= norm.y)) return (0.0);

		 b1 = (Q.x-a.x)*(b.z-a.z) - (b.x-a.x)*(Q.z-a.z);
		 if ( (b1 <= 0) || (b1 >= norm.y)) return (0.0);

		 return (t);
                 }
            else
                 {
		 b1 = (Q.x-b.x)*(c.z-b.z) - (c.x-b.x)*(Q.z-b.z);
		 if ( (b1 >= 0) || (b1 <= norm.y)) return (0.0);

		 b1 = (Q.x-c.x)*(a.z-c.z) - (a.x-c.x)*(Q.z-c.z);
		 if ( (b1 >= 0) || (b1 <= norm.y)) return (0.0);

		 b1 = (Q.x-a.x)*(b.z-a.z) - (b.x-a.x)*(Q.z-a.z);
		 if ( (b1 >= 0) || (b1 <= norm.y)) return (0.0);

		 return (t);
                 }
	    }

	 if (index == 2)
	    {
            Q.x = position.x + direction.x*t;
            Q.y = position.y + direction.y*t;
            if ( norm.z > 0.0)
                 {
		 b1 = ((c.x-b.x)*(Q.y-b.y)) - ((Q.x-b.x)*(c.y-b.y));
		 if ( (b1 <= 0) || (b1 >= norm.z)) return (0.0);

		 b1 = ((a.x-c.x)*(Q.y-c.y)) - ((Q.x-c.x)*(a.y-c.y));
		 if ( (b1 <= 0) || (b1 >= norm.z)) return (0.0);

		 b1 = ((b.x-a.x)*(Q.y-a.y)) - ((Q.x-a.x)*(b.y-a.y));
		 if ( (b1 <= 0) || (b1 >= norm.z)) return (0.0);
		 return (t);
                 }
            else
                {
		 b1 = ((c.x-b.x)*(Q.y-b.y)) - ((Q.x-b.x)*(c.y-b.y));
		 if ( (b1 >= 0) || (b1 <= norm.z)) return 0.0;

		 b1 = ((a.x-c.x)*(Q.y-c.y)) - ((Q.x-c.x)*(a.y-c.y));
		 if ( (b1 >= 0) || (b1 <= norm.z)) return (0.0);

		 b1 = ((b.x-a.x)*(Q.y-a.y)) - ((Q.x-a.x)*(b.y-a.y));
		 if ( (b1 >= 0) || (b1 <= norm.z)) return (0.0);
		 return (t);
                 }
            }
    }
    else
      return(RI_INFINITY);
}




RtPoint  Triangle::normale( const RtPoint& P )  
{
  return(norm);
}


RtVoid  Triangle::preproc()           
{
      norm = (b-a) ^ (c-a);	
      d = (-1.0*a) * norm;

     index = 0;
     norm_max = norm.x ; // fabs(norm.x);
     if (fabs(norm.y) > fabs(norm_max)) 
        {
        norm_max= norm.y ; // fabs(norm.y);
        index = 1;
        }
     if (fabs(norm.z) > fabs(norm_max))
        {
        norm_max= norm.z ; // fabs(norm.z);
        index = 2;
        }


}



RtBoolean Hit(RtPoint& position, RtPoint& direction , RtPoint& Min, RtPoint& Max)                                  
{ 
     
RtFloat T0, T1, T2;
RtFloat B1, B2;

        /*cout << "\nmin.x = " << Min.x;
        cout << "\nmin.y = " << Min.y;
        cout << "\nmin.z = " << Min.z;
        cout << "\nmax.x = " << Max.x;
        cout << "\nmax.y = " << Max.y;
        cout << "\nmax.z = " << Max.z;

        cout << "\n\ndir.x = " << direction.x;
        cout << "\ndir.y = " << direction.y;
        cout << "\ndir.z = " << direction.z;
        cout << "\nO.x = " << position.x;
        cout << "\nO.y = " << position.y;
        cout << "\nO.z = " << position.z << "\n\n";*/



        T1 = 0.0 ;
        T2 = RI_INFINITY ;
     
        if (direction.x != 0.0)
        {
                if (direction.x < 0.0) {
                        B2 = Min.x - position.x ;
                        if (B2 > 0.0) 
                                return (RI_FALSE);
                        B1 = Max.x - position.x ;
                } else {
                        B2 = Max.x - position.x ;
                        if (B2 < 0.0)
                                return (RI_FALSE);
                        B1 = Min.x - position.x ;
                } // else

                T2 = B2 / direction.x ;
                T1 = B1 / direction.x ;
                if (T1 < 0.0)
                        T1 = 0.0 ;
            
        } else 
            if (position.x < Min.x || position.x > Max.x)               
                  return (RI_FALSE) ;

       
        if (direction.y != 0.0)
        {
                if (direction.y < 0.0) {
                        B2 = Min.y - position.y ;
                        if (B2 > 0.0) 
                                return (RI_FALSE);
                        B1 = Max.y - position.y ;
                } else {
                        B2 = Max.y - position.y ;
                        if (B2 < 0.0)
                                return (RI_FALSE);
                        B1 = Min.y - position.y ;
                }

                if ((T0 = B2 / direction.y) < T1) return (RI_FALSE);    
                if (T0 < T2)
                        T2 = T0 ;


                if ((T0 = B1 / direction.y) > T2) return (RI_FALSE);
                if (T0 > T1)
                        T1 = T0 ;

        } else 
           if (position.y < Min.y || position.y > Max.y)
                return (RI_FALSE) ;

        if (direction.z != 0.0)
        {
                if (direction.z < 0.0) {
                        B2 = Min.z - position.z ;
                        if (B2 > 0.0) 
                                return (RI_FALSE);
                        B1 = Max.z - position.z ;
                } else {
                        B2 = Max.z - position.z ;
                        if (B2 < 0.0)
                                return (RI_FALSE);
                        B1 = Min.x - position.z ;
                }

                if (B2 / direction.z < T1) return (RI_FALSE) ;
                if (B1 / direction.z > T2) return (RI_FALSE);

        } else
           if (position.z < Min.z || position.z > Max.z)
                return (RI_FALSE) ;

      
    return (RI_TRUE);
}   
                        
