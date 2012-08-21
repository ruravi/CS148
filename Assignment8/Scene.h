#ifndef SCENE_H
#define SCENE_H

#include "st.h"
#include "Camera.h"
#include "ImagePlane.h"
#include "Ray.h"
#include "Shape.h"
#include "AmbientLight.h"
#include "Material.h"
#include "PointLight.h"
#include "SpecularLight.h"
#include "DirectionalLight.h"



class Scene
{
public:
	Scene(std::string sceneFilename);

	/** CS 148 TODO: Add methods for the scene to render itself, etc. 
     **/
     
    void RenderScene( float, float );
    int imgHeight;
    int imgWidth;
    void DrawScene( void );

private:

	/** Parsing helpers **/
	void Parse(std::string sceneFilename);
	void BeganParsing();
	void FinishedParsing();
	void ParsedCamera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect);
	void ParsedOutput(int imgWidth, int imgHeight, const std::string& outputFilename);
	void ParsedBounceDepth(int depth);
	void ParsedShadowBias(float bias);
	void ParsedPushMatrix();
	void ParsedPopMatrix();
	void ParsedRotate(float rx, float ry, float rz);
	void ParsedScale(float sx, float sy, float sz);
	void ParsedTranslate(float tx, float ty, float tz);
	void ParsedSphere(const STPoint3& center, float radius);
	void ParsedTriangle(const STPoint3& v1, const STPoint3& v2, const STPoint3& v3);
	void ParsedAmbientLight(const STColor3f& col);
	void ParsedPointLight(const STPoint3& loc, const STColor3f& col);
	void ParsedDirectionalLight(const STVector3& dir, const STColor3f& col);
	void ParsedMaterial(const STColor3f& amb, const STColor3f& diff, const STColor3f& spec, const STColor3f& mirr, float shine);

	/** CS 148 TODO: Add instance vars to store camera, lights, objects, etc. 
     **/
    Camera *myCamera;
    std::vector<Shape *> mShapes;
    ImagePlane *mImagePlane;
    std::vector<Material *> mMaterial;
    std::vector<Light *>Lights;
    AmbientLight * mAmbientLight;
    PointLight * mPointLight;
    SpecularLight *mSpecularLight;
    DirectionalLight *mDirectionalLight;
    bool IsDirectional;
    float ShadowBias;
    int BounceDepth;
    STTransform4 currentMatrix;
    std::vector<STTransform4> TransformationMatrixStack;
    
    Ray *GetRay(float, float, float);
    Ray *GenerateShadowRay(STPoint3, STPoint3);
    Ray *GenerateReflectionRay(STPoint3, STVector3, STPoint3);
    STColor4ub calculateShading(STPoint3, STVector3, int index, bool, Shape *, STPoint3);
    STColor4ub TraceRay( float u, float v);
    STColor3f TraceReflections(float , STPoint3 , STVector3, STPoint3 );
};


#endif //SCENE_H

