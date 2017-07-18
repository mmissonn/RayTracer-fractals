
#include "ri.h"
#include "Surfaces.h"
#include "Lights.h"

// on pourra rajouter une fonction qui a partir d'un cube retourne le centre
// et le rayon d'une sphere qui englobe le cube

MakeBBox(mat4& C, mat4& A) // C : Matrice points de controle
				      
{
   RtFloat xmin=RI_INFINITY, ymin=RI_INFINITY, zmin=RI_INFINITY, 
           xmax= -RI_INFINITY, ymax= -RI_INFINITY, zmax= -RI_INFINITY;
   int i, j;
    
   for( j = 0; j<=3 ; j++ )
     for( i = 0; i<=3; i++ )
     {
     xmin = min(xmin, C.p(i,j).x);
     ymin = min(ymin, C.p(i,j).y);
     zmin = min(zmin, C.p(i,j).z);

     xmax = min(xmax, C.p(i,j).x);
     ymax = min(ymax, C.p(i,j).y);
     zmax = min(zmax, C.p(i,j).z);
     }

   A[0].x = xmin;
   A[0].y = ymax;
   A[0].z = zmin;

   A[1].x = xmax;
   A[1].y = ymax;
   A[1].z = zmin;

   A[2].x = xmin;
   A[2].y = ymin;
   A[2].z = zmin;

   A[3].x = xmax;
   A[3].y = ymin;
   A[3].z = zmin;
   
   A[4].x = xmin;
   A[4].y = ymax;
   A[4].z = zmax;

   A[5].x = xmax;
   A[5].y = ymax;
   A[5].z = zmax;

   A[6].x = xmin;
   A[6].y = ymin;
   A[6].z = zmax;

   A[7].x = xmax;
   A[7].y = ymin;
   A[7].z = zmax;

   return(A);

}


RtFloat InterceptCube(RtPoint& A[8]) 
{
   int stop = 0;
   RtFloat tmin = RI_INFINITY;
   RtFloat temp;


   // Pour chacune des 6 faces on examine l'intersection

   temp = FaceCube(0,1,2,3, A);
   if (temp != RI_INFINITY) 
     { 
     stop++;
     tmin = temp;
     }

   temp = FaceCube(4,5,6,7, A);
   if (temp != RI_INFINITY)
     { 
     stop++;
     tmin = min(tmin,temp);
     if (stop == 2)
       return(tmin);
     }

   temp = FaceCube(1,5,3,7, A);
   if (temp != RI_INFINITY)
     { 
     stop++;
     tmin = min(tmin,temp);
     if (stop == 2)
       return(tmin);
     }

          
   temp = FaceCube(0,4,2,6, A);
   if (temp != RI_INFINITY)
     { 
     stop++;
     tmin = min(tmin,temp);
     if (stop == 2)
       return(tmin);
     }

  temp = FaceCube(2,3,6,7, A);
   if (temp != RI_INFINITY)
     { 
     stop++;
     tmin = min(tmin,temp);
     if (stop == 2)
       return(tmin);
     }


  temp = FaceCube(0,4,1,5, A); 
   if (temp != RI_INFINITY)
     { 
     stop++;
     tmin = min(tmin,temp);
     if (stop == 2)
       return(tmin);
     }

   return(RI_INFINITY);  
 
}



RtFloat FaceCube(int b0, b1, b2, b3, mat4& A) // Divise en deux triangles une face du cube
{

    RtFloat dist;

    dist = SubTriangle(A[b0], A[b1], A[b2]);
    
    if (dist == RI_INFINITY)
       dist = SubTriangle(A[b2], A[b3], A[b1]);

    return(dist);
        
}





RtFloat  SubTriangle(RtPoint& a, b, c) // Retourne l'intersection du triangle 
{
     RtFloat t,t1,t2;
     RtPoint Q;
     RtFloat b1;
     RtPoint norm;                  
     RtFloat norm_max;              
     RtFloat d;                     
     RtInt   index ;

     
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

Cu		 return (t);
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

 
