
#include "ri.h"

RtMatrix operator! (RtMatrix& a)
{
RtMatrix  resultat, sol;
RtInt     ipivot, isave, jrow, krow, kcol, perm[4] ;
double    val_a;



// Verifier si la matrice est inversible

RtFloat possible = 0.0;

possible  = a.matrice[0][0] * 
          ( a.matrice[1][1] * a.matrice[2][2] * a.matrice[3][3]
          + a.matrice[2][1] * a.matrice[3][2] * a.matrice[1][3]
          + a.matrice[3][1] * a.matrice[1][2] * a.matrice[2][3]       
          - a.matrice[3][1] * a.matrice[2][2] * a.matrice[1][3]
          - a.matrice[3][2] * a.matrice[2][3] * a.matrice[1][1]
          - a.matrice[3][3] * a.matrice[2][1] * a.matrice[1][2]);


possible += a.matrice[1][0] * 
          ( a.matrice[0][1] * a.matrice[2][2] * a.matrice[3][3]
          + a.matrice[2][1] * a.matrice[3][2] * a.matrice[0][3]
          + a.matrice[3][1] * a.matrice[0][2] * a.matrice[2][3]       
          - a.matrice[3][1] * a.matrice[2][2] * a.matrice[0][3]
          - a.matrice[3][2] * a.matrice[2][3] * a.matrice[0][1]
          - a.matrice[3][3] * a.matrice[2][1] * a.matrice[0][2]);

    
possible += a.matrice[2][0] * 
          ( a.matrice[0][1] * a.matrice[1][2] * a.matrice[3][3]
          + a.matrice[1][1] * a.matrice[3][2] * a.matrice[0][3]
          + a.matrice[3][1] * a.matrice[0][2] * a.matrice[1][3]       
          - a.matrice[3][1] * a.matrice[1][2] * a.matrice[0][3]
          - a.matrice[3][2] * a.matrice[1][3] * a.matrice[0][1]
          - a.matrice[3][3] * a.matrice[1][1] * a.matrice[0][2]);


possible += a.matrice[3][0] * 
          ( a.matrice[0][1] * a.matrice[1][2] * a.matrice[2][3]
          + a.matrice[1][1] * a.matrice[2][2] * a.matrice[0][3]
          + a.matrice[2][1] * a.matrice[0][2] * a.matrice[1][3]       
          - a.matrice[2][1] * a.matrice[1][2] * a.matrice[0][3]
          - a.matrice[2][2] * a.matrice[1][3] * a.matrice[0][1]
          - a.matrice[2][3] * a.matrice[1][1] * a.matrice[0][2]);

if (possible == 0.0){
    cout << "La matrice n'est pas inversible\n";
    return(a);}     //retour la matrice originale si pas inversible





    // Inverser la matrice

    	resultat = a;
	for(int i=0; i<4; i++)
		perm[i]=i;

	for(int j=0; j<4; j++)
	{
		// --- trouver la rangee pivot ---

		ipivot=perm[j];
		for(i=j+1; i<4; i++)
		{
			jrow=perm[i];
			val_a = abs(a.matrice[ipivot][j]);
			if(val_a < abs(a.matrice[jrow][j]))
			{
				ipivot=jrow;
				isave=i;
			}
		}

		// --- echanger les indices des rangees dans
		//     perm si le pivot n'est pas perm[j]    ---

		if(ipivot!=perm[j])
		{
			perm[isave]=perm[j];
			perm[j]=ipivot;
		}

		// --- normaliser les rangees ---

		for(kcol=j+1; kcol<4; kcol++)
			resultat.matrice[ipivot][kcol] /= resultat.matrice[ipivot][j];
		for(kcol=0; kcol<4; kcol++)
			sol.matrice[ipivot][kcol] /= resultat.matrice[ipivot][j];

		// --- reduire les rangees ---

		for(i=j+1; i<4; i++)
		{
			jrow=perm[i];
			for(kcol=j+1; kcol<4; kcol++)
				resultat.matrice[jrow][kcol] -= resultat.matrice[ipivot][kcol]*resultat.matrice[jrow][j];
			for(kcol=0; kcol<4; kcol++)
				sol.matrice[jrow][kcol] -= sol.matrice[ipivot][kcol]*resultat.matrice[jrow][j];
		}
	}

	// --- substitution en arriere ---

	for(i=3; i>=0; i--)
	{
		jrow = perm[i];
		for(kcol=0; kcol<4; kcol++)
			for(j=i+1; j<4; j++)
			{
				krow=perm[j];
				sol.matrice[jrow][kcol] -= resultat.matrice[jrow][j]*sol.matrice[krow][kcol];
			}
	}

	// --- transferer la solution

	for(i=0; i<4; i++)
	{
		jrow=perm[i];
		for(j=0; j<4; j++)
			resultat.matrice[i][j]=sol.matrice[jrow][j];
	}

	return(resultat);
}

  
    

RtMatrix operator~ (RtMatrix& a)
{
RtMatrix  resultat;
int     i, j ;


    // Transposer la matrice


    for ( i=0; i<4; i++ )
        for ( j=0; j<4; j++ )
            resultat.matrice[i][j] = a.matrice[j][i] ;


    // Retourner la matrice inverse
    return(resultat);
}

RtMatrix operator+ (RtMatrix& a, RtMatrix& b)
{
RtMatrix resultat;

    // Aditionner les deux matrices
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            resultat.matrice[i][j] = a.matrice[i][j] + b.matrice[i][j];

    // Retourner la matrice des sommes
    return(resultat);
} 


RtMatrix operator* (RtMatrix& a, RtMatrix& b)
{
RtMatrix resultat;
int     i, j ;


    // Produit matricel


    for ( i=0; i<4; i++ )
        for ( j=0; j<4; j++ )

            resultat.matrice[i][j] = a.matrice[i][0] * b.matrice[0][j]
               		           + a.matrice[i][1] * b.matrice[1][j]
                 	           + a.matrice[i][2] * b.matrice[2][j]
                 	           + a.matrice[i][3] * b.matrice[3][j] ;


    // Retourner la matrice obtenue
    return(resultat);
} 



RtPoint  operator^ (RtPoint& vectA , RtPoint& vectB)
{
  RtPoint	resultat;

  
  resultat.x = (vectA.y * vectB.z)  -  (vectA.z * vectB.y);
  resultat.y = (vectA.z * vectB.x)  -  (vectA.x * vectB.z);
  resultat.z = (vectA.x * vectB.y)  -  (vectA.y * vectB.x);

 return (resultat);
}


RtPoint operator^ (RtPoint& v1, RtMatrix& m1)
{
RtPoint v2;
double k;

   v2.x = v1.x * m1[0][0]
	 + v1.y * m1[1][0]
	 + v1.z * m1[2][0]
	 +        m1[3][0];

   v2.y = v1.x * m1[0][1]
	 + v1.y * m1[1][1]
	 + v1.z * m1[2][1]
	 +        m1[3][1];

   v2.z = v1.x * m1[0][2]
	 + v1.y * m1[1][2]
	 + v1.z * m1[2][2]
	 +        m1[3][2];

   k     = v1.x * m1[0][3]
	 + v1.y * m1[1][3]
	 + v1.z * m1[2][3]
	 +        m1[3][3];

   if (k != 1.0){
      k = 1.0/k;
      v2.x *= k;
      v2.y *= k;
      v2.z *= k;
   }
  
 return (v2);
}


RtPoint operator* (RtFloat A , RtPoint& vectB)
{
  RtPoint	resultat;

  
  resultat.x = A * vectB.x ;
  resultat.y = A * vectB.y ;
  resultat.z = A * vectB.z ;

 return (resultat);
}


RtPoint operator* (RtPoint& vectA , RtFloat B)
{
  RtPoint	resultat;

  
  resultat.x = vectA.x * B ;
  resultat.y = vectA.y * B ;
  resultat.z = vectA.z * B;

 return (resultat);
}


RtPoint operator/ (RtPoint& vectA , RtFloat B)
{
  RtPoint	resultat;

  
  resultat.x = vectA.x / B ;
  resultat.y = vectA.y / B ;
  resultat.z = vectA.z / B;

 return (resultat);
}


RtPoint operator* (RtPoint& V1 , RtMatrix& M1)
{
RtDouble  k ;
RtPoint  V2;

        V2.x =   V1.x * M1.matrice[0][0]
               + V1.y * M1.matrice[1][0]
               + V1.z * M1.matrice[2][0]
               +        M1.matrice[3][0] ;

        V2.y =   V1.x * M1.matrice[0][1]
               + V1.y * M1.matrice[1][1]
               + V1.z * M1.matrice[2][1]
               +        M1.matrice[3][1] ;

        V2.z =   V1.x * M1.matrice[0][2]
               + V1.y * M1.matrice[1][2]
               + V1.z * M1.matrice[2][2]
               +        M1.matrice[3][2] ;

        k  =    V1.x * M1.matrice[0][3]
              + V1.y * M1.matrice[1][3]
              + V1.z * M1.matrice[2][3]
              +        M1.matrice[3][3] ;

        if ( k != 1.0 ) {
            k = 1.0 / k ;
            V2.x *= k ;
            V2.y *= k ;
            V2.z *= k ;
        }
 return (V2);
} 


RtPoint operator+ (RtPoint& V1 , RtPoint& V2)
{
RtPoint  resultat;

     resultat.x = V1.x + V2.x;
     resultat.y = V1.y + V2.y;
     resultat.z = V1.z + V2.z;

 return (resultat);
}



RtPoint operator- (RtPoint& V1 , RtPoint& V2)
{
RtPoint  resultat;

     resultat.x = V1.x - V2.x;
     resultat.y = V1.y - V2.y;
     resultat.z = V1.z - V2.z;

 return (resultat);
}


RtPoint operator*= (RtPoint& V1 , RtFloat F1)
{
RtPoint  resultat;

     resultat.x = V1.x * F1;
     resultat.y = V1.y * F1;
     resultat.z = V1.z * F1;

 return (resultat);
}



RtFloat  operator* (RtPoint& V1 , RtPoint& V2)
{
RtFloat  resultat;

     resultat = V1.x*V2.x +
                V1.y*V2.y +
                V1.z*V2.z;

 return (resultat);
}

RtColor operator* (RtFloat A , RtColor& tintB)
{
  RtColor	resultat;

  
  resultat.rouge = A * tintB.rouge ;
  resultat.vert  = A * tintB.vert  ;
  resultat.bleu  = A * tintB.bleu  ;

 return (resultat);
}


RtColor operator* (RtColor& tintA , RtFloat B)
{
  RtColor	resultat;

  
  resultat.rouge = tintA.rouge * B ;
  resultat.vert  = tintA.vert  * B ;
  resultat.bleu  = tintA.bleu  * B;

 return (resultat);
}


RtColor operator/ (RtColor& tintA , RtFloat B)
{
  RtColor	resultat;

  
  resultat.rouge = tintA.rouge / B ;
  resultat.vert  = tintA.vert  / B ;
  resultat.bleu  = tintA.bleu  / B;

 return (resultat);
}

RtColor operator* (RtColor& tintA , RtColor& tintB)
{
  RtColor	resultat;

  
  resultat.rouge = tintA.rouge * tintB.rouge ;
  resultat.vert  = tintA.vert  * tintB.vert  ;
  resultat.bleu  = tintA.bleu  * tintB.bleu  ;

 return (resultat);
}

RtColor operator+ (RtColor& tintA , RtColor& tintB)
{
  RtColor	resultat;

  
  resultat.rouge = tintA.rouge + tintB.rouge ;
  resultat.vert  = tintA.vert  + tintB.vert  ;
  resultat.bleu  = tintA.bleu  + tintB.bleu  ;

 return (resultat);
}
