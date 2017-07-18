#ifndef _Prototypes_h
#define _Prototypes_h



// --- Declaration des prototypes de RenderMan -----

extern RtToken		RiDeclare();

extern RtVoid		RiBegin(), RiEnd(),
			RiFrameBegin(), RiFrameEnd(),
			RiWorldBegin(), RiWorldEnd();

extern RtVoid		RiFormat(RtInt, RtInt, RtFloat), 
			RiFrameAspectRatio(), 
			RiScreenWindow(),
			RiCropWindow(), 
			RiProjection(RtToken, ...), 
			RiProjectionV(),
			RiClipping(), 
			RiDepthOfField(), 
			RiShutter();

extern RtVoid		RiPixelVariance(), 
			RiPixelSamples(), 
			RiPixelFilter(),
			RiExposure(), RiImager(), RiImagerV(),
			RiQuantize(), 
			RiDisplay(char *name, RtToken type, RtToken mode, ...), 
			RiDisplayV();

extern RtFloat		RiGaussianFilter(), RiBoxFilter(),
			RiTriangleFilter(), RiCatmullRomFilter(), RiSincFilter();

extern RtVoid		RiHider(), RiHiderV(),
			RiColorSamples(), RiRelativeDetail(),
			RiOption(), RiOptionV();

extern RtVoid		RiAttributeBegin(), 
			RiAttributeEnd(),
			RiColor(RtColor), 
			RiOpacity(), 
			RiTextureCoordinates();

extern RtLightHandle	RiLightSource(RtFunc, ...), 
			RiLightSourceV(),
			RiAreaLightSource(char *, ...), 
			RiAreaLightSourceV();

extern RtVoid		RiIlluminate(RtLightHandle, RtBoolean), 
			RiSurface(RtFunc, ...), 
			RiSurfaceV(),
			RiAtmosphere(char *, ...),
			RiAtmosphereV(),
			RiInterior(), 
			RiInteriorV(), 
			RiExterior(),
			RiExteriorV(), 
			RiShadingRate(),
			RiShadingInterpolation(), 
			RiMatte();

extern RtVoid		RiBound(), 
			RiDetail(), RiDetailRange(),
			RiGeometricApproximation(),
			RiOrientation(), RiReverseOrientation(), RiSides();

extern RtVoid		RiIdentity(), 
			RiTransform(RtMatrix), 
			RiConcatTransform(RtMatrix),
			RiPerspective(), 
			RiTranslate(RtFloat, RtFloat, RtFloat),
			RiRotate(RtFloat, RtFloat, RtFloat, RtFloat),
			RiScale(RtFloat, RtFloat, RtFloat), 
			RiSkew(), 
			RiDeformation(),
			RiDeformationV(), 
			RiDisplacement(), 
			RiDisplacementV(),
			RiCoordinateSystem();

extern RtPoint		*RiTransformPoints();
extern RtVoid		RiTransformBegin(), 
			RiTransformEnd();

extern RtVoid		RiAttribute(), 
			RiAttributeV();

extern RtVoid           RiPolygon(RtInt, RtToken, ...), 
			RiPolygonV(), 
			RiGeneralPolygon(),
			RiGeneralPolygonV(), 
			RiPointsPolygons(),
			RiPointsPolygonsV(), 
			RiPointsGeneralPolygons(),
			RiGeneralPolygonsV(), 
			RiBasis(), 
			//RiPatch (RtToken type, ...),
			RiPatchV(), 
			RiPatchMesh(), 
			RiPatchMeshV(),
			RiNuPatch(), 
			RiNuPatchV(), 
			RiTrimCurve();

extern RtVoid		RiSphere(RtFloat, RtFloat, RtFloat, RtFloat, ...), 
			RiSphereV(),  
			RiConeV(), 
			RiCylinderV(), 
			RiHyperboloid(),
			RiHyperboloidV(), 
			RiParaboloid(), 
			RiParaboloidV(),
			RiDisk(), 
			RiDiskV(), 
			RiTorus(), 
			RiTorusV(),
			RiProcedural(), 
			RiGeometry(), 
			RiGeometryV();

extern RtVoid		RiSolidBegin(), RiSolidEnd();
extern RtObjectHandle	RiObjectBegin();
extern RtVoid		RiObjectEnd(), 
			RiObjectInstance(RtObjectHandle), 
			RiMotionBegin(),
			RiMotionBeginV(), 
			RiMotionEnd();

extern RtVoid		RiMakeTexture(), RiMakeTextureV(), RiMakeBump(),
			RiMakeBumpV(), RiMakeLatLongEnvironment(),
			RiMakeLatLongEnvironmentV(),
		 	RiMakeCubeFaceEnvironment(),
			RiMakeCubeFaceEnvironmentV(), RiMakeShadow(),
			RiMakeShadowV();

extern RtVoid		RiErrorHandler();
extern RtVoid		RiErrorIgnore(), RiErrorPrint(), RiErrorAbort();

extern RtVoid           PolyPlane( RtFloat, RtFloat, RtFloat, RtFloat, ...);
extern RtVoid           PolyQuadric( RtFloat, RtFloat, RtFloat, RtFloat, 
                                     RtFloat, RtFloat, RtFloat, RtFloat, 
                                     RtFloat, RtFloat, ... ); 			

extern RtVoid           Poly_cast( short ) ;
extern RtFloat          radians ( RtFloat ) ;
extern RtFloat          degrees ( RtFloat ) ;
extern RtFloat          min ( RtFloat ,   RtFloat  ) ;
extern RtFloat          max ( RtFloat ,   RtFloat  ) ;
extern RtFloat          mod ( RtFloat ,   RtFloat  ) ;
extern RtFloat          sign ( RtFloat ) ;
extern RtFloat          round ( RtFloat ) ;
extern RtFloat          step( RtFloat, RtFloat ) ;
extern RtFloat          smoothstep(RtFloat, RtFloat, RtFloat);
extern RtColor          ambient() ;
extern RtColor          diffuse( RtPoint& ) ;
extern RtColor 		specular (RtPoint&, RtPoint&, RtFloat);
extern RtFloat		xcomp (RtPoint ) ;
extern RtFloat		ycomp (RtPoint ) ;
extern RtFloat		zcomp (RtPoint ) ;
extern RtVoid		setxcomp( RtPoint& , RtFloat ) ;
extern RtVoid		setycomp( RtPoint& , RtFloat ) ;
extern RtVoid		setzcomp( RtPoint& , RtFloat ) ;
extern RtFloat		length ( RtPoint& ) ;
extern RtFloat          distance( RtPoint& , RtPoint&  ) ;
extern RtPoint          normalize( RtPoint&  ) ;
extern RtPoint		faceforward (RtPoint&  , RtPoint& ) ;
extern RtPoint          reflect(RtPoint& , RtPoint& ) ;
extern RtPoint          refract(RtPoint& , RtPoint& , RtFloat ) ;
extern RtVoid           fresnel( RtPoint , RtPoint , RtFloat ,
                                 RtFloat , RtFloat , RtPoint& ,
                                 RtPoint& ) ;
extern RtPoint          calculatenormal( RtPoint& ) ;
extern RtColor		mix ( RtColor& color0, RtColor& color1, RtFloat );

extern RtBoolean        Poly_Illuminance(RtInt) ;
extern RtBoolean        Poly_Illuminate( RtPoint , RtPoint, RtFloat) ;


extern RtVoid           imageToFile_init(),
			imageToFile(RtColor ligne[]),
			imageToFile_close();

extern RtFloat 		noise(RtPoint&);
extern RtPoint 		Dnoise(RtPoint&);
extern RtVoid  		noise_init();

extern RtVoid 		ambientlight(RtFloat intensity = 1,RtColor color = 1.0);
extern RtVoid 		pointlight (RtFloat intensity = 1, RtColor color = 1, RtPoint from = 0 ) ;

extern RtVoid 		matte() ;
extern RtVoid 		metal();
extern RtVoid 		plastic();
extern RtVoid		granite();
extern RtVoid		volcan();
extern RtVoid		wave();
extern RtVoid		clouds();
extern RtVoid		hill();
extern RtVoid		flake();
extern RtVoid		glow();

RtVoid RiPatch(RtToken type, RtToken typeCP, mat4& matpat, ...);

RtVoid Fractal(float Ex, float Ey, float Ez);

/* void InitGauss(int seed);
   float Gauss();
   float f3(float delta, float x0, float x1, float x2);
   float f4(float delta, float x0, float x1, float x2, float x3);
   void MidPointFM2D(float X[5][5], int maxlevel, float sigma, float H, int addition,
	     int seed);
*/

#endif
