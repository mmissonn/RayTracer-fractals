#include "Class.h"


void       MakeBBox(RtPoint& C[4][4], RtPoint& A[8]); // C : Matrice points de controle
RtFloat    InterceptCube(RtPoint& A[8]); 
RtFloat    FaceCube(int b0, b1, b2, b3, RtPoint& A[8]);
RtFloat    SubTriangle(RtPoint& a, b, c);
