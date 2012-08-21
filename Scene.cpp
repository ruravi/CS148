#include "Scene.h"
#include <fstream>
#include <sstream>
#include "Camera.h"
#include "Ray.h"
#include "Sphere.h"
#include "Triangle.h"
#include "AmbientLight.h"
#include "Material.h"

#define PI 3.14159265

Scene::Scene(std::string sceneFilename)
{
    
	Parse(sceneFilename);
    
}

void Scene::Parse(std::string sceneFilename)
{
	BeganParsing();

	std::ifstream sceneFile(sceneFilename.c_str());
	char line[1024];
	while (!sceneFile.eof())
	{
		sceneFile.getline(line, 1023);
		std::stringstream ss;
        ss.str(line);
        printf("%s \n",line);
		std::string command;
		ss >> command;

		if (command == "Camera")
		{
			float ex, ey, ez, ux, uy, uz, lx, ly, lz, f, a;
			ss >> ex >> ey >> ez >> ux >> uy >> uz >> lx >> ly >> lz >> f >> a;
			STPoint3 eye(ex, ey, ez);
			STVector3 up(ux, uy, uz);
			STPoint3 lookAt(lx, ly, lz);
			ParsedCamera(eye, up, lookAt, f, a);
		}
		else
		if (command == "Output")
		{
			int w, h;
			std::string fname;
			ss >> w >> h >> fname;
			ParsedOutput(w, h, fname);
		}
		else
		if (command == "BounceDepth")
		{
			int depth;
			ss >> depth;
			ParsedBounceDepth(depth);
		}
		else if (command == "ShadowBias")
		{
			float bias;
			ss >> bias;
			ParsedShadowBias(bias);
		}
		else
		if (command == "PushMatrix")
		{
			ParsedPushMatrix();
		}
		else
		if (command == "PopMatrix")
		{
			ParsedPopMatrix();
		}
		else
		if (command == "Rotate")
		{
			float rx, ry, rz;
			ss >> rx >> ry >> rz;
			ParsedRotate(rx, ry, rz);
		}
		else
		if (command == "Scale")
		{
			float sx, sy, sz;
			ss >> sx >> sy >> sz;
			ParsedScale(sx, sy, sz);
		}
		else
		if (command == "Translate")
		{
			float tx, ty, tz;
			ss >> tx >> ty >> tz;
			ParsedTranslate(tx, ty, tz);
		}
		else
		if (command == "Sphere")
		{
			float cx, cy, cz, r;
			ss >> cx >> cy >> cz >> r;
			STPoint3 center(cx, cy, cz);
			ParsedSphere(center, r);
		}
		else
		if (command == "Triangle")
		{
			float x1, y1, z1, x2, y2, z2, x3, y3, z3;
			ss >> x1 >> y1 >> z1 >> x2 >> y2 >> z2 >> x3 >> y3 >> z3;
			STPoint3 v[3];
			v[0] = STPoint3(x1, y1, z1);
			v[1] = STPoint3(x2, y2, z2);
			v[2] = STPoint3(x3, y3, z3);
			ParsedTriangle(v[0], v[1], v[2]);
		}
		else
		if (command == "AmbientLight")
		{
			float r, g, b;
			ss >> r >> g >> b;
			STColor3f col(r, g, b);
			ParsedAmbientLight(col);
		}
		else
		if (command == "PointLight")
		{
			float px, py, pz, r, g, b;
			ss >> px >> py >> pz >> r >> g >> b;
			STPoint3 pos(px, py, pz);
			STColor3f col(r, g, b);
			ParsedPointLight(pos, col);
		}
		else
		if (command == "DirectionalLight")
		{
			float dx, dy, dz, r, g, b;
			ss >> dx >> dy >> dz >> r >> g >> b;
			STVector3 dir(dx, dy, dz);
			STColor3f col(r, g, b);
			ParsedDirectionalLight(dir, col);
		}
		else
		if (command == "Material")
		{
			float ra, ga, ba, rd, gd, bd, rs, gs, bs, rr, gr, br, shine;
			ss >> ra >> ga >> ba >> rd >> gd >> bd >> rs >> gs >> bs >> rr >> gr >> br >> shine;
			STColor3f amb(ra, ga, ba);
			STColor3f diff(rd, gd, bd);
			STColor3f spec(rs, gs, bs);
			STColor3f mirr(rr, gr, br);
			ParsedMaterial(amb, diff, spec, mirr, shine);
		}
	}
	sceneFile.close();

	FinishedParsing();
}

void Scene::BeganParsing()
{
	mPointLight = NULL;
    mAmbientLight = NULL;
    mDirectionalLight = NULL;
    currentMatrix = STTransform4::Identity();
    TransformationMatrixStack.push_back(currentMatrix);
}

void Scene::FinishedParsing()
{
	/** CS 148 TODO: Fill this in 
     **/
}

void Scene::ParsedCamera(const STPoint3& eye, const STVector3& up, const STPoint3& lookAt, float fovy, float aspect)
{
	myCamera = new Camera(eye, up, lookAt, fovy, aspect);
}

void Scene::ParsedOutput(int imgWidth, int imgHeight, const std::string& outputFilename)
{
	mImagePlane = new ImagePlane(imgWidth, imgHeight, outputFilename, myCamera->fovy, myCamera->aspect, myCamera);
    this->imgWidth = imgWidth;
    this->imgHeight = imgHeight;
}


STColor4ub Scene::calculateShading(STPoint3 P, STVector3 N, int index, bool isShadow, Shape *thisShape, STPoint3 eye)
{
    Material *currMaterial = mMaterial[index];
    float ambient_r=0,ambient_g=0,ambient_b=0,diffuse_r=0,diffuse_g=0,diffuse_b=0,specularcolor_r=0,specularcolor_g=0,specularcolor_b = 0;
    
    if (mAmbientLight) {
        STColor3f matprop_a = currMaterial->ambient;
        STColor3f lightprop_a = mAmbientLight->calculateIntensity(P, N);
        ambient_r = matprop_a.r * lightprop_a.r;
        ambient_g = matprop_a.g * lightprop_a.g;
        ambient_b = matprop_a.b * lightprop_a.b;
    }

    if (!isShadow) {
        if (mPointLight) {
            STColor3f matprop_d = currMaterial->diffuse;
            STColor3f lightprop_d = mPointLight->calculateIntensity(P, N, thisShape);
            diffuse_r = matprop_d.r * lightprop_d.r;
            diffuse_g = matprop_d.g * lightprop_d.g;
            diffuse_b = matprop_d.b * lightprop_d.b;
            
            
            STColor3f matprop_s = currMaterial->specular;
            STColor3f lightprop_s = mPointLight->calculateSpecularLightIntensity(P, N, eye,currMaterial->shininess, thisShape);
            specularcolor_r = matprop_s.r * lightprop_s.r;
            specularcolor_g = matprop_s.g * lightprop_s.g;
            specularcolor_b = matprop_s.b * lightprop_s.b;
            
        }
        
        if (mDirectionalLight) {
            STColor3f matprop_d = currMaterial->diffuse;
            STColor3f lightprop_d = mDirectionalLight->calculateIntensity(P, N,thisShape);
            diffuse_r = matprop_d.r * lightprop_d.r;
            diffuse_g = matprop_d.g * lightprop_d.g;
            diffuse_b = matprop_d.b * lightprop_d.b;
            
            // Change specular light settings
            STColor3f matprop_s = currMaterial->specular;
            STColor3f lightprop_s = mDirectionalLight->calculateSpecularLightIntensity(P, N, eye,currMaterial->shininess, thisShape);
            specularcolor_r = matprop_s.r * lightprop_s.r;
            specularcolor_g = matprop_s.g * lightprop_s.g;
            specularcolor_b = matprop_s.b * lightprop_s.b;
            
        }
    }
    
    float total_r = (ambient_r + diffuse_r + specularcolor_r) * 255.;
    float total_g = (ambient_g + diffuse_g + specularcolor_g) * 255.;
    float total_b = (ambient_b + diffuse_b + specularcolor_b) * 255.;
    
    total_r = ((total_r) < 0) ? 0 : ((total_r) > 255 ? 255 : total_r);
    total_g = ((total_g) < 0) ? 0 : ((total_g) > 255 ? 255 : total_g);
    total_b = ((total_b) < 0) ? 0 : ((total_b) > 255 ? 255 : total_b);
    
    STColor4ub color = STColor4ub(total_r,total_g,total_b) ;
    return color;
}

Ray *Scene::GetRay( float x, float y, float z )
{
    return new Ray(myCamera,STPoint3(x, y, z));
}

Ray *Scene::GenerateShadowRay(STPoint3 P, STPoint3 l)
{
    float mShadowBias = ShadowBias / Modulus(P - l);
    
    if (IsDirectional)
    {
        return new Ray(P, l, mShadowBias, std::numeric_limits<float>::infinity(), true);
    } 
    
    /* We want max_t to not go beyond the light source itself for a PointLight */
    return new Ray(P, l, mShadowBias, 1., false, false);
}

Ray *Scene::GenerateReflectionRay(STPoint3 P, STVector3 N, STPoint3 eye)
{
    
    STVector3 d = Normalize(P - eye);
    STVector3 r = d - 2 * STVector3::Dot(d, N) * N;
    float mShadowBias = ShadowBias / Modulus(P - STPoint3(r));
    return new Ray(P, STPoint3(r), mShadowBias, std::numeric_limits<float>::infinity(), true);
}

void Scene::RenderScene ( float i, float j) 
{
    
    // Map from Pixel coordinates to image plane coord.
    float l = mImagePlane->LL.x;
    float r = mImagePlane->LR.x;
    float b = mImagePlane->LL.y;
    float t = mImagePlane->UL.y;
    
    float u = l + (r-l) * (i + 0.5) / imgWidth;
    float v = b + (t-b) * (j + 0.5) / imgHeight;
    
        
    STColor4ub color =  TraceRay(u, v);
    mImagePlane->writePixel(i,j, color);
    
}

STColor4ub Scene::TraceRay(float u, float v)
{
    int index = 0;
    bool isShadow;
    std::vector<Shape *>::iterator eachShape, eachShadowShape, eachreflectedShape;
    float z = mImagePlane->LL.z;
    float t_value;
    STColor4ub color = STColor4ub(0,0,0);
    
    Ray *eachRay = GetRay(u, v, z);
    
    /* Check for intersection with all shapes */
    t_value = std::numeric_limits<float>::infinity();
    
    for (eachShape = mShapes.begin() ; eachShape != mShapes.end(); eachShape++) {
        
        /* This is the Point we're currently looking at and shading */
        Intersection *inter = (*eachShape)->FindIntersection(eachRay);
        
        if (inter->isValid && inter->t < t_value) {
            isShadow = false;
            std::vector<Light *>::iterator eachLight;
            
            /* Perform Shadow Test here only if there's light */
            for (eachLight = Lights.begin(); eachLight != Lights.end(); eachLight++  ) {
                
                Ray *ShadowRay = GenerateShadowRay(inter->P, (*eachLight)->lightPos );
                
                for (eachShadowShape = mShapes.begin(); eachShadowShape < mShapes.end(); eachShadowShape++) {
                    Intersection *inter2 = (*eachShadowShape)->FindIntersection(ShadowRay);
                    if (inter2->isValid) {
                        isShadow = true;
                        break;
                    } 
                }
            }
            
            /* Reflection Test */
            STColor3f reflectedcolor = TraceReflections(0, inter->P, inter->normal, myCamera->eye);
            
            color = STColor4ub(mMaterial[index]->mirror * reflectedcolor +
                               STColor3f(calculateShading(inter->P,inter->normal,index, isShadow,*eachShape, myCamera->eye)));
            t_value = inter->t;
        }
        // Index into the shape
        index++;
    }
    
    return color;
}

STColor3f Scene::TraceReflections(float localBounceDepth, STPoint3 P, STVector3 N, STPoint3 eye)
{
    /* Perform Mirror Reflection here */
    STColor3f reflectedColor = STColor3f(0., 0., 0.);
    std::vector<Shape *>::iterator eachreflectedShape, eachShadowShape;
    
    
    int reflectionIndex = 0;
    if (localBounceDepth < BounceDepth) {
        
        Ray *eachReflectRay = GenerateReflectionRay(P, N, eye);
        
        /* Check for intersection with other objects */ 
        float t_val_reflect = std::numeric_limits<float>::infinity();
        
        for (eachreflectedShape = mShapes.begin(); eachreflectedShape != mShapes.end(); eachreflectedShape++) {
            
            /* Find intersection with every other object. This is the point whose color we want */
            Intersection *inter3 = (*eachreflectedShape)->FindIntersection(eachReflectRay);
            
            if (inter3->isValid && inter3->t < t_val_reflect ) {
                
                t_val_reflect = inter3->t;
                /* Get the color of the point of intersection of the reflected ray + Trace its reflections */
                
                bool isShadow = false;
                std::vector<Light *>::iterator eachLight;
                
                /* Perform Shadow Test here only if there's light */
                for (eachLight = Lights.begin(); eachLight != Lights.end(); eachLight++  ) {
                    
                    Ray *ShadowRay = GenerateShadowRay(inter3->P, (*eachLight)->lightPos );
                    
                    for (eachShadowShape = mShapes.begin(); eachShadowShape < mShapes.end(); eachShadowShape++) {
                        Intersection *inter2 = (*eachShadowShape)->FindIntersection(ShadowRay);
                        if (inter2->isValid) {
                            isShadow = true;
                            break;
                        } 
                    }
                }
                
                reflectedColor = STColor3f(calculateShading(inter3->P, inter3->normal, 
                                                                  reflectionIndex, 
                                                                  isShadow,
                                                                  *eachreflectedShape,
                                                                  P))
                + TraceReflections(localBounceDepth+1, inter3->P, inter3->normal, P);
            }
            
            reflectionIndex++;
        }
    }
    
    return reflectedColor;
}

void Scene::DrawScene()
{
    mImagePlane->DrawImage();
}

void Scene::ParsedBounceDepth(int depth)
{
	BounceDepth = depth;
}

void Scene::ParsedShadowBias(float bias)
{
	ShadowBias = bias;
}

void Scene::ParsedPushMatrix()
{
	TransformationMatrixStack.push_back(currentMatrix);
}

void Scene::ParsedPopMatrix()
{
	currentMatrix = (STTransform4)TransformationMatrixStack.back();
    TransformationMatrixStack.pop_back();
}

void Scene::ParsedRotate(float rx, float ry, float rz)
{
    currentMatrix = currentMatrix * STTransform4::Rotation(rx*PI/180., ry*PI/180., rz*PI/180.) ;
}

void Scene::ParsedScale(float sx, float sy, float sz)
{
    currentMatrix = currentMatrix * STTransform4::Scaling(sx, sy, sz) ;
}

void Scene::ParsedTranslate(float tx, float ty, float tz)
{
    currentMatrix = currentMatrix * STTransform4::Translation(tx, ty, tz);
}

void Scene::ParsedSphere(const STPoint3& center, float radius)
{
	Sphere *mSphere = new Sphere(radius, center, currentMatrix);
    mShapes.push_back(mSphere);
    if (mMaterial.size() != mShapes.size()) {
        mMaterial.push_back(mMaterial.back());
    }
}

void Scene::ParsedTriangle(const STPoint3& v1, const STPoint3& v2, const STPoint3& v3)
{
	Triangle *mTriangle = new Triangle(v1, v2, v3, currentMatrix);
    mShapes.push_back(mTriangle);
    if (mMaterial.size() != mShapes.size()) {
        mMaterial.push_back(mMaterial.back());
    }
}

void Scene::ParsedAmbientLight(const STColor3f& col)
{
	mAmbientLight = new AmbientLight(col, currentMatrix);
}

void Scene::ParsedPointLight(const STPoint3& loc, const STColor3f& col)
{
    STPoint3 transformedloc = currentMatrix * loc;
	mPointLight = new PointLight(transformedloc, col, currentMatrix);
    IsDirectional = false;
    Lights.push_back(mPointLight);
}

void Scene::ParsedDirectionalLight(const STVector3& dir, const STColor3f& col)
{
    STVector3 transformeddir = currentMatrix * dir;
	mDirectionalLight = new DirectionalLight(STPoint3(transformeddir), col, currentMatrix);
    IsDirectional = true;
    Lights.push_back(mDirectionalLight);
}

void Scene::ParsedMaterial(const STColor3f& amb, const STColor3f& diff, const STColor3f& spec, const STColor3f& mirr, float shine)
{
	Material *nextMaterial = new Material(amb,diff,spec,mirr,shine);
    mMaterial.push_back(nextMaterial);
}