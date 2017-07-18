#include "ri.h"
#include <stdio.h>
#include <math.h>

 
void DrawSurface(mat4 patch, int niveau);
void SubdivisePatch(mat4& MatPatch, mat4& p1, mat4& p2, mat4& p3, mat4& p4);
 

long NIVEAU_MAX = 1; // nombre de niveau max. pour la recursivite
RtPoint triangle[3]; // definition d'un triangle...
int i, j; 	     // variables pour boucles...
mat4 p1, p2, p3, p4; // 4 variables de type mat4 qui representent
		     // une matrice de 16 RtPoint.




// DrawSurface
// Transforme une patch en triangles
// en subdivisant la patch originale recursivement
// ***********************************************
void DrawSurface(mat4 patch, int niveau)
{
if( niveau >= NIVEAU_MAX )   // si oui on a un nouvel objet...
	{
	cout << "\nniveau = " << niveau << "\n";
	for(i = 0; i <= 2; i++)
		for(j = 0; j <= 2; j++)
		{
		triangle[0] = patch.p(i,j);
		triangle[1] = patch.p(i+1,j);
		triangle[2] = patch.p(i, j+1);
		RiPolygon(3, RI_P, (RtPointer) triangle, RI_NULL);
		triangle[0] = patch.p(i+1, j+1);
		RiPolygon(3, RI_P, (RtPointer) triangle, RI_NULL);
		}
	} // if
else
	{
	niveau = niveau + 1;
	SubdivisePatch(patch, p1, p2, p3, p4);
	DrawSurface(p1, niveau);
	DrawSurface(p2, niveau);
	DrawSurface(p3, niveau);
	DrawSurface(p4, niveau);
	} // else

} // DrawSurface





// SubdivisePatch
// subdivise une patch bezier en 4 sous patch
// ******************************************
void SubdivisePatch(mat4& Mat, mat4& p1, mat4& p2, mat4& p3, mat4& p4)
{
int i;

// Subdivise une patch en 4 autres patchs (p1 a p4)
// Voir Curve and Patch Subdivision dans Silicon Graphics Pipeline page 15-16

for(i = 0; i <= 3; i++)
	{
	p1.set(i,0, Mat.p(i,0));
	p1.set(i,1, (0.5 * (Mat.p(i,0) + Mat.p(i,1))));
	p1.set(i,2, (0.25 * (Mat.p(i,0) + Mat.p(i,2)) + 0.5 * Mat.p(i,1)));
	p1.set(i,3, (0.125 * (Mat.p(i,0) + Mat.p(i,3)) + 0.375 * (Mat.p(i,1) + Mat.p(i,2))));

 /* cout << "\n\nP1\n";
  cout << "(" << p1.p(i,0).x << "," << p1.p(i,0).y << "," << p1.p(i,0).z << ") ";
  cout << "(" << p1.p(i,1).x << "," << p1.p(i,1).y << "," << p1.p(i,1).z << ") ";
  cout << "(" << p1.p(i,2).x << "," << p1.p(i,2).y << "," << p1.p(i,2).z << ") ";
  cout << "(" << p1.p(i,3).x << "," << p1.p(i,3).y << "," << p1.p(i,3).z << ")\n\n";*/


	p2.set(i,0, (Mat.p(i,3)));
	p2.set(i,1, (0.5 * (Mat.p(i,2) + Mat.p(i,3))));
	p2.set(i,2, (0.25 * (Mat.p(i,3) + Mat.p(i,1)) + 0.5 * Mat.p(i,2)));
	p2.set(i,3, (0.125 * (Mat.p(i,0) + Mat.p(i,3)) + 0.375 * (Mat.p(i,1) + Mat.p(i,2))));

//cout << "\n\nP2\n";
//cout << "(" << p2.p(i,0).x << "," << p2.p(i,0).y << "," << p2.p(i,0).z << ") ";
//cout << "(" << p2.p(i,1).x << "," << p2.p(i,1).y << "," << p2.p(i,1).z << ") ";
//cout << "(" << p2.p(i,2).x << "," << p2.p(i,2).y << "," << p2.p(i,2).z << ") ";
//cout << "(" << p2.p(i,3).x << "," << p2.p(i,3).y << "," << p2.p(i,3).z << ")\n\n";

	p3.set(0,i, Mat.p(0,i));
	p3.set(1,i, (0.5 * (Mat.p(0,i) + Mat.p(1,i))));
	p3.set(2,i, (0.25 * (Mat.p(0,i) + Mat.p(2,i)) + 0.5 * Mat.p(1,i)));
	p3.set(3,i, (0.125 * (Mat.p(0,i) + Mat.p(3,i)) + 0.375 * (Mat.p(1,i) + Mat.p(2,i))));

//cout << "\n\nP3\n";
//cout << "(" << p3.p(0,i).x << "," << p3.p(0,i).y << "," << p3.p(0,i).z << ") ";
//cout << "(" << p3.p(1,i).x << "," << p3.p(1,i).y << "," << p3.p(2,i).z << ") ";
//cout << "(" << p3.p(2,i).x << "," << p3.p(2,i).y << "," << p3.p(3,i).z << ") ";
//cout << "(" << p3.p(3,i).x << "," << p3.p(3,i).y << "," << p3.p(4,i).z << ")\n\n";

	p4.set(0,i, Mat.p(3,i));
	p4.set(1,i, (0.5 * (Mat.p(2,i) + Mat.p(3,i))));
	p4.set(2,i, (0.25 * (Mat.p(3,i) + Mat.p(1,i)) + 0.5 * Mat.p(2,i)));
	p4.set(3,i, (0.125 * (Mat.p(0,i) + Mat.p(3,i)) + 0.375 * (Mat.p(1,i) + Mat.p(2,i))));

//cout << "\n\nP4\n";
//cout << "(" << p4.p(0,i).x << "," << p4.p(0,i).y << "," << p4.p(0,i).z << ") ";
//cout << "(" << p4.p(1,i).x << "," << p4.p(1,i).y << "," << p4.p(2,i).z << ") ";
//cout << "(" << p4.p(2,i).x << "," << p4.p(2,i).y << "," << p4.p(3,i).z << ") ";
//cout << "(" << p4.p(3,i).x << "," << p4.p(3,i).y << "," << p4.p(4,i).z << ")\n\n";

	}

} // SubdivisePatch



