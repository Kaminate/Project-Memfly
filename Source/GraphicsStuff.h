#ifndef GRAPHICSSTUFFH
#define GRAPHICSSTUFFH

#include "Core.h"
#include "IrrlichtIncludes.h"
#include <set>
#include <map>
#include <string>

#include "Point4.h"
#include "Matrix4.h"
#include "Vector4.h"


class GraphicsSystem;
class GraphicsComponent;
class CameraComponent;

extern GraphicsSystem * g_GraphicsSystem;

class Transform;

class GraphicsSystem : public System
{
public:
  GraphicsSystem(unsigned width = 800, unsigned height = 600); // pixels of backbuffer
  ~GraphicsSystem();
  virtual void Update(float dt);
  void LoadTexture(const std::string & filePath, const std::string & name);
  void SetCamera(CameraComponent * camera);
private:
  friend class GraphicsComponent;
  CameraComponent * m_currCamera;
  dimension2d<u32>  m_resolution; // px of backbuffer
  IrrlichtDevice  * m_device;
  IVideoDriver    * m_driver;
  ISceneManager   * m_smgr; 
  IGUIEnvironment * m_guienv;

  std::set<GraphicsComponent*> m_components;
  std::map<std::string, video::ITexture*> m_textureBank; // texture name (not filepath)
  Point4 Pipeline(const Transform * transform);
  Matrix4 NDCToViewport() const;
};

class GraphicsComponent : public Component
{
public:
  GraphicsComponent(const std::string & textureName);
  ~GraphicsComponent();
  video::ITexture * m_texture;
};

class CameraComponent : public Component
{
public:
  CameraComponent(float width = 800, float height = 600); // in arbitrary units
  Matrix4 GetViewMatrix() const;
  void SetWidth(float width);
  void SetHeight(float height);
private:
  float m_width;
  float m_height;
};

#endif
