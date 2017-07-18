#ifndef _ri_h
#define _ri_h

#include <stream.h>
#include <stdarg.h>
#include <stdio.h>


// Definition of Abstract Types used in RI
typedef short     RtBoolean;
typedef long      RtInt;
typedef float     RtFloat;
typedef double    RtDouble;

typedef char      *RtToken;

typedef RtFloat   RtBasis[4][4];
typedef RtFloat   RtBound[6];
typedef char      *RtString; 

typedef char      *RtPointer;
typedef void      RtVoid;
typedef double    (*RtFloatFunc)();
typedef int       (*RtFunc)();

typedef RtPointer RtObjectHandle;
typedef RtPointer RtLightHandle;


// Extern Declarations for Predefined RI Data Structures
const RtBoolean    RI_FALSE    = RtBoolean(0);
const RtBoolean    RI_TRUE     = RtBoolean(1);

const RtFloat  RI_INFINITY = RtFloat(1.0e38);
const RtFloat  RI_EPSILON  = RtFloat(1.0e-3);
const RtToken  RI_NULL     = RtToken(0);

const RtToken  RI_FOV      = "FOV";
const RtToken  RI_KA       = "Ka";
const RtToken  RI_KS       = "Ks";
const RtToken  RI_KD       = "Kd";
const RtToken  RI_KR       = "Kr";
const RtToken  RI_KT       = "Kt";
const RtToken  RI_SIZE	   = "Size";
const RtToken  RI_N        = "n" ;
const RtToken  RI_COLOR    = "color" ;
const RtToken  RI_SPECULARCOLOR = "specularcolor" ;

const RtToken  RI_P        = "RIP";
const RtToken  RI_FILE     = "FILE";
const RtToken  RI_FRAMEBUFFER = "BUFFER";
const RtToken  RI_RGB      = "RGB";
const RtToken  RI_ORIGIN   = "origin";
const RtToken  RI_BICUBIC  = "bicubic";

#include "Class.h"


// --- Definition des constantes ---
const  int        MAX_LIGHT   = 10;
const  int        MAX_SURFACE = 32000;
const  RtMatrix   Identite;           // toutes les matrices crees en sont

#include "lists.h"
#include "Prototypes.h"
#include "Lights.h"
#include "Attributes.h"
#include "Surfaces.h"
#include "Sphere.h"
#include "Triangle.h"
#include "Plan.h"
#include "Global.h"
#include "Quad.h"
#endif





