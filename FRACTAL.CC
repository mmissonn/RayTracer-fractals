


#include "ri.h"
#include <math.h>
#include <stdlib.h>
#include <stream.h>

#define ligne   17
#define colonne 17


/* RtVoid Fractal(float Ex, float Ey, float Ez); */

void InitGauss(int seed);
float Gauss();
float f3(float delta, float x0, float x1, float x2);
float f4(float delta, float x0, float x1, float x2, float x3);
void MidPointFM2D(float X[][colonne], int maxlevel, float sigma, float H, int addition,
	     int seed);


double GaussAdd, GaussFac;
int Nrand, Arand;


RtVoid Fractal(float Ex, float Ey, float Ez)
// Ex, Ey : multiplie dist. en x, y et z
{
int i, j, tmp, max = 0;
RtPoint carre[4]; // 4 points qui forment un rectangle
RtColor couleur, couleur0;
int h, h3, h6, hmax;
RtFloat f = 0.3;

// matrice des hauteurs
float X[ligne][colonne];


cout << "\nCalcul de la montagne fractale : [" << ligne << ", " << colonne << "]...\n";

// clacul des hauteurs de la montagne

MidPointFM2D(X, 4, 0.001, 0.85, 1, 50);  //maxlevel = 4 => 16 lignes, 16 colonnes
// X = array ligneXcolonne  -> grosseur = (N+1)^2
// maxlevel = nombre max de recursions N = 2^maxlevel
// sigma : ecart type
// H : dimension de la fractal -> D = 3 - H
// addition : random additions on/off
// seed : valeur de depart pour generateur aleatoire

cout << "\nMidPointFM2D termine\n";


for(i = 0; i < (ligne-1); i++)
	for(j = 0; j < (colonne-1); j++)
	{
	tmp = (int) X[i][j];
	if (tmp > max)
		max = tmp;
	if (tmp < 0.001)
		X[i][j] = 0;
	else
	if ((i == 0) || (j == 0))   // limites a zero.
		X[i][j] = 0;
	else
	if (i == ligne)
		X[i][j] = 0;
	else
	if (j == colonne)
		X[i][j] = 0;
	else 
		X[i][j] = (int) tmp; // pour mettre en entier...
	}


cout << "\nDefinition des surfaces pour la montagne\n";

 //couleur0.rouge = 0.7; couleur0.vert = 1.0; couleur0.bleu = 0.7;

for(i = 0; i < ligne-1; i++)
{
	for(j = 0; j < colonne-1; j++)
	{
	carre[0].x = carre[3].x = (j * Ex);
	carre[1].x = carre[2].x = ((j+1) * Ex);

	carre[0].y = ((X[i][j]/max) * Ey);
	carre[1].y = ((X[i][j+1]/max) * Ey);
	carre[2].y = ((X[i+1][j+1]/max) * Ey);
	carre[3].y = ((X[i+1][j]/max) * Ey);

	carre[0].z = carre[1].z = (i * Ez);
	carre[2].z = carre[3].z = ((i+1) * Ez);

/*
        // Repartition des couleurs selon hauteur
            
        h6 = 0.17*(max) ; h3 = 0.47*(max); hmax = 0.67*max; h = ( X[i][j] + X[i][j+1] + X[i+1][j] + X[i+1][j+1] ) / 4;
        
	cout << "\nh6 = " << h6;
	cout << "\nh3 = " << h3;
	cout << "\nh  = " << h;
	cout << "\nmax = " << max;
	

	if( h <= h6)
        {
            couleur.rouge = (0.3/h6)*h + 0.7;
            couleur.vert = 1.0;  
            couleur.bleu = 0.0;        
        }
        else
          if( (h > h6) && (h <= h3) )  
          { 
              couleur.rouge = ( (0.2*h) + h3*0.4 - 0.6*h6 ) / (h3-h6);  
              couleur.vert = 1.0;  
              couleur.bleu = ( (0.2*h) + h3*0.4 - 0.6*h6 ) / (h3-h6);  
          }
          else 
	  if ( (h > h3) && (h < hmax) )
           { 
              couleur.rouge = ( (0.4*h) + max*0.6 - 1.0*h3 ) / (max-h3);  
              couleur.vert = 1.0;  
              couleur.bleu = ( (0.4*h) + max*0.6 - 1.0*h3 ) / (max-h3);
           }
	   else
	        couleur.rouge = couleur.vert = couleur.bleu = 1.0;
              

	//couleur = mix(couleur0, couleur, f*noise(carre[0]));
	//couleur0 = couleur;
	//RiColor(couleur);
*/

	RiPolygon(4, RI_P, (RtPointer) carre, RI_NULL);
	}
}

cout << "\nCalcul pour la montagne terminee\n";
}



// p. 77
void InitGauss(int seed)
{
Nrand = 4;
Arand = pow(2, 31) - 1;
GaussAdd = sqrt(3 * Nrand);
GaussFac = 2 * GaussAdd/(Nrand * Arand);
srand(seed);
} // InitGauss


float Gauss()
{
int sum = 0, i;

for(i = 1; i <= Nrand; i++)
	sum = sum + rand();
return(GaussFac * sum - GaussAdd);
} // Gauss



float f3(float delta, float x0, float x1, float x2)
{
return( (x0 + x1 + x2)/3 + delta * Gauss() );
} // f3


float f4(float delta, float x0, float x1, float x2, float x3)
{
return( (x0 + x1 + x2 + x3)/4 + delta * Gauss() );
} // f4




void MidPointFM2D(float X[ligne][colonne], int maxlevel, float sigma, float H, int addition,
	     int seed)
{
int i, N, stage;
float delta;
int x, y, y0, D, d;

InitGauss(seed);

N = pow(2, maxlevel);
delta = sigma;
X[0][0] = delta * Gauss();
X[0][N] = delta * Gauss();
X[N][0] = delta * Gauss();
X[N][N] = delta * Gauss();

D = N;
d = N/2;

for(stage = 1; stage <= maxlevel; stage++)
{


	delta = delta * pow(0.5, 0.5*H);

	for(x = d; x <= (N-d); x = x + D)
		for(y = d; y <= (N-d); y = y + D)
		{
		X[x][y] = f4(delta, X[x+d][y+d], X[x+d][y-d], X[x-d][y+d],
			    X[x-d][y-d]);
		}

	if (addition)
	{
	for(x = 0; x <= N; x = x + D)
		for(y = 0; y <= N; y = y + D)
		{
		X[x][y] = X[x][y] + delta * Gauss();
		}
	}

	delta = delta * pow(0.5, 0.5*H);

	for(x = d; x <= (N-d); x = x + D)
	{
	X[x][0] = f3(delta, X[x+d][0], X[x+d][0], X[x][d]);
	X[x][N] = f3(delta, X[x+d][N], X[x-d][N], X[x][N-d]);
	X[0][x] = f3(delta, X[0][x+d], X[0][x-d], X[d][x]);
	X[N][x] = f3(delta, X[N][x+d], X[N][x-d], X[N-d][x]);
	}


	for(x = d; x <= (N-d); x = x + D)
		for(y = D; y <= (N-d); y = y + D)
		{
		X[x][y] = f4(delta, X[x][y+d], X[x][y-d], X[x+d][y],
			    X[x-d][y]);
		}

	for(x = D; x <= (N-d); x = x + D)
		for(y = d; y <= (N-d); y = y + D)
		{
		X[x][y] = f4(delta, X[x][y+d], X[x][y-d], X[x+d][y],
			    X[x-d][y]);
		}

	if (addition)
	{

	for(x = 0; x <= N; x = x + D)
		for(y = 0; y <= N; y = y + D)
		{
		X[x][y] = X[x][y] + delta * Gauss();
		}

	for(x = d; x <= (N-d); x = x + D)
		for(y = d; y <= (N-d); y = y + D)
		{
		X[x][y] = X[x][y] = delta * Gauss();
		}
	} // IF

	D = D/2;
	d = d/2;

} // for stage

} // MidPointFM2D









