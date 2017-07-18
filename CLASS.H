

// ----------------------------------------------------------------------------
//
// RenderMan Interface Standard Include File
//
// ----------------------------------------------------------------------------

#ifndef _Class_h
#define _Class_h




// --- Declaration des types specifiques a RI ---


class RtMatrix {
  public:
    RtFloat  matrice[4][4];  

    RtMatrix();

    RtFloat* operator[](int);

    friend RtMatrix operator! ( RtMatrix&);              // inverse
    friend RtMatrix operator~ ( RtMatrix&);              // transpose
    friend RtMatrix operator+ ( RtMatrix& ,  RtMatrix&);  // addition
    friend RtMatrix operator* ( RtMatrix& ,  RtMatrix&);  // multiplication
  };



class RtPoint {
  public:
    RtFloat  x;
    RtFloat  y;
    RtFloat  z;

    RtPoint();			      // Constructeur 
    RtPoint(RtFloat, RtFloat, RtFloat);
    RtPoint(const RtPoint&) ;

    RtPoint& operator= (RtPoint&);    // Overload du egal
    RtFloat& operator[] (int);	      // overload de []
    RtPoint& operator= (RtFloat);

    friend RtPoint operator^ (RtPoint&, RtPoint&);     // prod. vect
    friend RtPoint operator^ (RtPoint&, RtMatrix&);
    friend RtFloat operator* (RtPoint&, RtPoint&);     // prod. scalaire
    friend RtPoint operator+ (RtPoint&, RtPoint&);     // addition
    friend RtPoint operator- (RtPoint&, RtPoint&);     // soustraction
    
    friend RtPoint operator* (RtPoint&,  RtMatrix&);   // vecteur* mat
    friend RtPoint operator*= (RtPoint&, RtFloat);     // vect*float=vect

    friend RtPoint operator* (RtFloat, RtPoint&);      // multiplication
    friend RtPoint operator* (RtPoint&, RtFloat);      // autre sens mult.
    friend RtPoint  operator/ (RtPoint&, RtFloat);     // division
   
};



class mat4 {
  public:
	RtPoint p00; RtPoint p01;
	RtPoint p02; RtPoint p03;
	RtPoint p10; RtPoint p11;
	RtPoint p12; RtPoint p13;
	RtPoint p20; RtPoint p21;
	RtPoint p22; RtPoint p23;
	RtPoint p30; RtPoint p31;
	RtPoint p32; RtPoint p33;   

    mat4();   // Constructeur
 
    //mat4(int, int);
    mat4(const mat4&) ;
    RtPoint mat4::p(int i, int j);
    mat4::set(int i, int j, RtPoint point);
    RtFloat mat4::px(int i, int j);
    RtFloat mat4::py(int i, int j);
    RtFloat mat4::pz(int i, int j);
    mat4::setx(int i, int j, RtFloat point);
    mat4::sety(int i, int j, RtFloat point);
    mat4::setz(int i, int j, RtFloat point);
    void stool(int i, int j)
    {
	cout << " (" << px(i,j) << "," << py(i,j) << "," << pz(i,j) << ")";
    }



    mat4& operator= (mat4&);          // Overload du egal
    RtPoint& operator[] (int);	      // overload de []
    mat4& operator= (RtFloat);
    mat4& operator= (RtPoint);

    //friend RtFloat operator* (RtPoint&, RtPoint&);     // prod. scalaire
    //friend RtPoint operator+ (RtPoint&, RtPoint&);     // addition
    //friend RtPoint operator- (RtPoint&, RtPoint&);     // soustraction
    
    //friend RtPoint operator* (RtPoint&,  RtMatrix&);   // vecteur* mat
    //friend RtPoint operator*= (RtPoint&, RtFloat);     // vect*float=vect

    //friend RtPoint operator* (RtFloat, RtPoint&);      // multiplication
    //friend RtPoint operator* (RtPoint&, RtFloat);      // autre sens mult.
    //friend RtPoint  operator/ (RtPoint&, RtFloat);     // division
   
};





class RtColor {
  public:
    RtFloat  rouge;
    RtFloat  vert;
    RtFloat  bleu;

    RtColor();                       // Constructeur
    RtColor(RtFloat, RtFloat, RtFloat);
    RtColor(const RtColor&) ;

    RtColor&  operator= (RtColor&);  // Overload du egal
    RtColor&  operator= (RtFloat);
    RtFloat&  operator[] (int);     // overdose de []
   
    RtColor&  operator*= (RtColor&);
    RtColor&  operator+= (RtColor&);

    friend RtColor operator* (RtFloat, RtColor&);      // multiplication
    friend RtColor operator* (RtColor&, RtFloat);      // autre sens mult.
    friend RtColor operator* (RtColor&, RtColor&);
    friend RtColor operator+ (RtColor&, RtColor&);
    friend RtColor operator/ (RtColor&, RtFloat);
};







//--------------------------------------------------------------------------
// Constructeurs 
//--------------------------------------------------------------------------
inline RtColor::RtColor()
{
    // Initialiser la couleur a noir
    rouge = 0.0;
    vert  = 0.0;
    bleu  = 0.0;
}


inline RtColor::RtColor(const RtColor& c)
{
    rouge = c.rouge;
    vert  = c.vert ;
    bleu  = c.bleu ;
}

inline RtColor::RtColor(RtFloat R, RtFloat G, RtFloat B)
{
    // Initialiser la couleur
    rouge = R;
    vert  = G;
    bleu  = B;
}

inline RtPoint::RtPoint()
{
   // On place le point a (0,0,0)
   x = 0.0;
   y = 0.0;
   z = 0.0;
}


inline RtPoint::RtPoint(const RtPoint& a)
{
  x = a.x ;
  y = a.y ;
  z = a.z ;
}


inline RtPoint::RtPoint(RtFloat Px, RtFloat Py, RtFloat Pz)
{
   // On place le point a (Px, Py, Pz)
   x = Px;
   y = Py;
   z = Pz;
}



inline mat4::mat4()
{
// initialisation de la matrice de patch
p00 = 0.0; p01 = 0.0; p02 = 0.0; p03 = 0.0;
p10 = 0.0; p11 = 0.0; p12 = 0.0; p13 = 0.0;
p20 = 0.0; p21 = 0.0; p22 = 0.0; p23 = 0.0;
p30 = 0.0; p31 = 0.0; p32 = 0.0; p33 = 0.0;
}


inline mat4::mat4(const mat4& a)
{
p00 = a.p00; p01 = a.p01; p02 = a.p02; p03 = a.p03;
p10 = a.p10; p11 = a.p11; p12 = a.p12; p13 = a.p13;
p20 = a.p20; p21 = a.p21; p22 = a.p22; p23 = a.p23;
p30 = a.p30; p31 = a.p31; p32 = a.p32; p33 = a.p33;
}


inline RtPoint mat4::p(int i, int j)
{
if ((i == 0) && (j == 0)) return(p00);
if ((i == 0) && (j == 1)) return(p01);
if ((i == 0) && (j == 2)) return(p02);
if ((i == 0) && (j == 3)) return(p03);
if ((i == 1) && (j == 0)) return(p10);
if ((i == 1) && (j == 1)) return(p11);
if ((i == 1) && (j == 2)) return(p12);
if ((i == 1) && (j == 3)) return(p13);
if ((i == 2) && (j == 0)) return(p20);
if ((i == 2) && (j == 1)) return(p21);
if ((i == 2) && (j == 2)) return(p22);
if ((i == 2) && (j == 3)) return(p23);
if ((i == 3) && (j == 0)) return(p30);
if ((i == 3) && (j == 1)) return(p31);
if ((i == 3) && (j == 2)) return(p32);
if ((i == 3) && (j == 3)) return(p33);
	else return(p00);
}


inline RtFloat mat4::px(int i, int j)
{
if ((i == 0) && (j == 0)) return(p00.x);
if ((i == 0) && (j == 1)) return(p01.x);
if ((i == 0) && (j == 2)) return(p02.x);
if ((i == 0) && (j == 3)) return(p03.x);
if ((i == 1) && (j == 0)) return(p10.x);
if ((i == 1) && (j == 1)) return(p11.x);
if ((i == 1) && (j == 2)) return(p12.x);
if ((i == 1) && (j == 3)) return(p13.x);
if ((i == 2) && (j == 0)) return(p20.x);
if ((i == 2) && (j == 1)) return(p21.x);
if ((i == 2) && (j == 2)) return(p22.x);
if ((i == 2) && (j == 3)) return(p23.x);
if ((i == 3) && (j == 0)) return(p30.x);
if ((i == 3) && (j == 1)) return(p31.x);
if ((i == 3) && (j == 2)) return(p32.x);
if ((i == 3) && (j == 3)) return(p33.x);
	else return(p00.x);
}



inline RtFloat mat4::py(int i, int j)
{
if ((i == 0) && (j == 0)) return(p00.y);
if ((i == 0) && (j == 1)) return(p01.y);
if ((i == 0) && (j == 2)) return(p02.y);
if ((i == 0) && (j == 3)) return(p03.y);
if ((i == 1) && (j == 0)) return(p10.y);
if ((i == 1) && (j == 1)) return(p11.y);
if ((i == 1) && (j == 2)) return(p12.y);
if ((i == 1) && (j == 3)) return(p13.y);
if ((i == 2) && (j == 0)) return(p20.y);
if ((i == 2) && (j == 1)) return(p21.y);
if ((i == 2) && (j == 2)) return(p22.y);
if ((i == 2) && (j == 3)) return(p23.y);
if ((i == 3) && (j == 0)) return(p30.y);
if ((i == 3) && (j == 1)) return(p31.y);
if ((i == 3) && (j == 2)) return(p32.y);
if ((i == 3) && (j == 3)) return(p33.y);
	else return(p00.y);
}




inline RtFloat mat4::pz(int i, int j)
{
if ((i == 0) && (j == 0)) return(p00.z);
if ((i == 0) && (j == 1)) return(p01.z);
if ((i == 0) && (j == 2)) return(p02.z);
if ((i == 0) && (j == 3)) return(p03.z);
if ((i == 1) && (j == 0)) return(p10.z);
if ((i == 1) && (j == 1)) return(p11.z);
if ((i == 1) && (j == 2)) return(p12.z);
if ((i == 1) && (j == 3)) return(p13.z);
if ((i == 2) && (j == 0)) return(p20.z);
if ((i == 2) && (j == 1)) return(p21.z);
if ((i == 2) && (j == 2)) return(p22.z);
if ((i == 2) && (j == 3)) return(p23.z);
if ((i == 3) && (j == 0)) return(p30.z);
if ((i == 3) && (j == 1)) return(p31.z);
if ((i == 3) && (j == 2)) return(p32.z);
if ((i == 3) && (j == 3)) return(p33.z);
	else return(p00.z);
}




inline mat4::set(int i, int j, RtPoint point)
{
if ((i == 0) && (j == 0)) p00 = point;
if ((i == 0) && (j == 1)) p01 = point;
if ((i == 0) && (j == 2)) p02 = point;
if ((i == 0) && (j == 3)) p03 = point;
if ((i == 1) && (j == 0)) p10 = point;
if ((i == 1) && (j == 1)) p11 = point;
if ((i == 1) && (j == 2)) p12 = point;
if ((i == 1) && (j == 3)) p13 = point;
if ((i == 2) && (j == 0)) p20 = point;
if ((i == 2) && (j == 1)) p21 = point;
if ((i == 2) && (j == 2)) p22 = point;
if ((i == 2) && (j == 3)) p23 = point;
if ((i == 3) && (j == 0)) p30 = point;
if ((i == 3) && (j == 1)) p31 = point;
if ((i == 3) && (j == 2)) p32 = point;
if ((i == 3) && (j == 3)) p33 = point;
}



inline mat4::setx(int i, int j, RtFloat point)
{
if ((i == 0) && (j == 0)) p00.x = point;
if ((i == 0) && (j == 1)) p01.x = point;
if ((i == 0) && (j == 2)) p02.x = point;
if ((i == 0) && (j == 3)) p03.x = point;
if ((i == 1) && (j == 0)) p10.x = point;
if ((i == 1) && (j == 1)) p11.x = point;
if ((i == 1) && (j == 2)) p12.x = point;
if ((i == 1) && (j == 3)) p13.x = point;
if ((i == 2) && (j == 0)) p20.x = point;
if ((i == 2) && (j == 1)) p21.x = point;
if ((i == 2) && (j == 2)) p22.x = point;
if ((i == 2) && (j == 3)) p23.x = point;
if ((i == 3) && (j == 0)) p30.x = point;
if ((i == 3) && (j == 1)) p31.x = point;
if ((i == 3) && (j == 2)) p32.x = point;
if ((i == 3) && (j == 3)) p33.x = point;
}


inline mat4::sety(int i, int j, RtFloat point)
{
if ((i == 0) && (j == 0)) p00.y = point;
if ((i == 0) && (j == 1)) p01.y = point;
if ((i == 0) && (j == 2)) p02.y = point;
if ((i == 0) && (j == 3)) p03.y = point;
if ((i == 1) && (j == 0)) p10.y = point;
if ((i == 1) && (j == 1)) p11.y = point;
if ((i == 1) && (j == 2)) p12.y = point;
if ((i == 1) && (j == 3)) p13.y = point;
if ((i == 2) && (j == 0)) p20.y = point;
if ((i == 2) && (j == 1)) p21.y = point;
if ((i == 2) && (j == 2)) p22.y = point;
if ((i == 2) && (j == 3)) p23.y = point;
if ((i == 3) && (j == 0)) p30.y = point;
if ((i == 3) && (j == 1)) p31.y = point;
if ((i == 3) && (j == 2)) p32.y = point;
if ((i == 3) && (j == 3)) p33.y = point;
}


inline mat4::setz(int i, int j, RtFloat point)
{
if ((i == 0) && (j == 0)) p00.z = point;
if ((i == 0) && (j == 1)) p01.z = point;
if ((i == 0) && (j == 2)) p02.z = point;
if ((i == 0) && (j == 3)) p03.z = point;
if ((i == 1) && (j == 0)) p10.z = point;
if ((i == 1) && (j == 1)) p11.z = point;
if ((i == 1) && (j == 2)) p12.z = point;
if ((i == 1) && (j == 3)) p13.z = point;
if ((i == 2) && (j == 0)) p20.z = point;
if ((i == 2) && (j == 1)) p21.z = point;
if ((i == 2) && (j == 2)) p22.z = point;
if ((i == 2) && (j == 3)) p23.z = point;
if ((i == 3) && (j == 0)) p30.z = point;
if ((i == 3) && (j == 1)) p31.z = point;
if ((i == 3) && (j == 2)) p32.z = point;
if ((i == 3) && (j == 3)) p33.z = point;
}



inline RtMatrix::RtMatrix()
{
    // Initialiser la matrice cree par une matrice identite
    matrice[0][0] = 1.0;
    matrice[0][1] = 0.0;
    matrice[0][2] = 0.0;
    matrice[0][3] = 0.0;
    matrice[1][0] = 0.0;
    matrice[1][1] = 1.0;
    matrice[1][2] = 0.0;
    matrice[1][3] = 0.0;
    matrice[2][0] = 0.0;
    matrice[2][1] = 0.0;
    matrice[2][2] = 1.0;
    matrice[2][3] = 0.0;
    matrice[3][0] = 0.0;
    matrice[3][1] = 0.0;
    matrice[3][2] = 0.0;
    matrice[3][3] = 1.0;
}


class StackMatrix {
	private:
		RtMatrix	A[20];	// Matrice qui sera poussee
		RtInt		top;
	public:
		RtVoid	   reset()  { top = 0; }
		RtVoid	   push(RtMatrix B) { top++; A[top] = B; }
		RtMatrix   pop() { return(A[top--]); }
		RtBoolean  empty() { return(top == 0); }
		RtBoolean  full() { return (top == 19); }
};

		

		
//--------------------------------------------------------------------------
// Overload des operateurs
//--------------------------------------------------------------------------
inline RtColor&  RtColor::operator= (RtColor& couleur)
{
    rouge = couleur[0]; // .rouge;
    vert  = couleur[1]; // .vert;
    bleu  = couleur[2]; // .bleu;
}


inline RtColor&  RtColor::operator= (RtFloat couleur)
{
    rouge = couleur;
    vert  = couleur;
    bleu  = couleur;
}

inline RtFloat& RtColor::operator[] (int i)
{
 	if (i == 0)   return(rouge);
	if (i == 1)   return(vert);
	if (i == 2)   return(bleu);
}


inline RtColor&  RtColor::operator+= (RtColor& CB)
{

	rouge = rouge + CB[0]; // .rouge ;
	vert  = vert  + CB[1]; // .vert  ;
	bleu  = bleu  + CB[2]; //.bleu  ;

}




inline RtColor& RtColor::operator*= (RtColor& coul)
{
  rouge = rouge * coul[0]; // .rouge ;
  vert  = vert  * coul[1]; // .vert  ;
  bleu  = bleu  * coul[2]; // .bleu  ;
}




inline RtPoint& RtPoint::operator= (RtPoint& point3d)
{
    x = point3d[0];  // .x;
    y = point3d[1];  // .y;
    z = point3d[2];  // .z;
}



inline RtPoint& RtPoint::operator= (RtFloat data)
{
    x = data ;
    y = data ;
    z = data ;
}



inline RtFloat& RtPoint::operator[] (int i)
{
 	if (i == 0)   return(x);
	if (i == 1)   return(y);
	if (i == 2)   return(z);
}



inline mat4& mat4::operator= (mat4& a)
{
p00 = a.p00; p01 = a.p01; p02 = a.p02; p03 = a.p03;
p10 = a.p10; p11 = a.p11; p12 = a.p12; p13 = a.p13;
p20 = a.p20; p21 = a.p21; p22 = a.p22; p23 = a.p23;
p30 = a.p30; p31 = a.p31; p32 = a.p32; p33 = a.p33;
}


inline mat4& mat4::operator= (RtPoint data)
{
p00 = p01 = p02 = p03 = data;
p10 = p11 = p12 = p13 = data;
p20 = p21 = p22 = p23 = data;
p30 = p31 = p32 = p33 = data;
}


inline RtPoint& mat4::operator[] (int i)
{
if (i == 0)  return (p00);
if (i == 1)  return (p01);
if (i == 2)  return (p02);
if (i == 3)  return (p03);
if (i == 4)  return (p10);
if (i == 5)  return (p11);
if (i == 6)  return (p12);
if (i == 7)  return (p13);
if (i == 8)  return (p20);
if (i == 9)  return (p21);
if (i == 10)  return (p22);
if (i == 11)  return (p23);
if (i == 12)  return (p30);
if (i == 13)  return (p31);
if (i == 14)  return (p32);
if (i == 15)  return (p33);
	else return(p00);
}



inline mat4& mat4::operator= (RtFloat data)
{
p00 = p01 = p02 = p03 = data;
p10 = p11 = p12 = p13 = data;
p20 = p21 = p22 = p23 = data;
p30 = p31 = p32 = p33 = data;
}
 

inline RtFloat* RtMatrix::operator[](int i)
{
  	return( matrice[i] );
}

#endif
















