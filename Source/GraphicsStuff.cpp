#include "GraphicsStuff.h"
#include "GraphicsMath.h"

#include "Transform.h"

GraphicsSystem * g_GraphicsSystem = 0;

GraphicsSystem::GraphicsSystem(unsigned width, unsigned height)
  : m_resolution(width, height)
  , m_currCamera(0)
{
  if (g_GraphicsSystem) __debugbreak();
  g_GraphicsSystem = this;

  // TODO: not software
  m_device = createDevice( video::EDT_SOFTWARE, m_resolution, 16, false, false, false, 0);
  
  if (!m_device) __debugbreak();

  m_device->setWindowCaption(L"Memfly");
  
  m_driver = m_device->getVideoDriver();
  m_smgr   = m_device->getSceneManager();
  m_guienv = m_device->getGUIEnvironment();

  m_driver->getMaterial2D().TextureLayer[0].BilinearFilter=true;
	m_driver->getMaterial2D().AntiAliasing=video::EAAM_FULL_BASIC;

}

GraphicsSystem::~GraphicsSystem()
{
  m_device->drop();
}

void GraphicsSystem::LoadTexture(const std::string & filePath, const std::string & name)
{
  video::ITexture * tex = m_driver->getTexture(filePath.c_str());
  m_textureBank[name] = tex;
	m_driver->makeColorKeyTexture(tex, core::position2d<s32>(0,0));
}

void GraphicsSystem::SetCamera(CameraComponent * camera)
{
  m_currCamera = camera;
}

void GraphicsSystem::Update(float dt)
{
  if (!m_device->run())            return;
  if (!m_driver)                   return;
  if (!m_device->isWindowActive()) return;
  if (!m_currCamera)
  {
    // you should attach a camera before rendering
    __debugbreak();
  }

  m_driver->beginScene(true, true, video::SColor(255,120,102,136));

  for (auto it = m_components.begin(); it != m_components.end(); ++it)
  {
    GraphicsComponent * component = *it;

    video::ITexture * texture = component->m_texture;

    const Transform * transform = component->GetOwner()->GetComponent<Transform>();

    Point4 screenPos = Pipeline(transform);

    core::vector2d<s32> position(
      (int)screenPos.x - texture->getSize().Width / 2,
      (int)screenPos.y - texture->getSize().Height / 2);
    
    /*
    core::vector2d<s32> position(
      (int)screenPos.x,// - texture->getSize().Width / 2,
      (int)screenPos.y);// - texture->getSize().Height / 2);
    */

    m_driver->draw2DImage(
      texture,
      position,
      core::rect<s32> (0,0,texture->getSize().Width, texture->getSize().Height),
      0,
      video::SColor(255,255,255,255), 
      true);
  }

  // Finally draw a half-transparent rect under the mouse cursor.
	core::position2d<s32> m = m_device->getCursorControl()->getPosition();
	m_driver->draw2DRectangle(video::SColor(100,255,255,255),
		core::rect<s32>(m.X-20, m.Y-20, m.X+20, m.Y+20));

	m_driver->endScene();
}

// pass by value so we dont need to make another variable to modify
// pos in in arbitrary units
Point4 GraphicsSystem::Pipeline(const Transform * transform)
{
  Point4 pos; // default (0,0,0,1). In model space

  // Apply world matrix. no scale, no rotation. Just translation
  Matrix4 world = Matrix4Trans(transform->m_pos);
  pos = world * pos;

  pos = m_currCamera->GetViewMatrix() * pos;

  pos = NDCToViewport() * pos;

  return pos;
}

Matrix4 GraphicsSystem::NDCToViewport() const
{
  float sx = (float)m_resolution.Width;
  float sy = -(float)m_resolution.Height;

  float tx = m_resolution.Width  / 2.0f;
  float ty = m_resolution.Height / 2.0f;

  return Matrix4(sx,  0,  0, tx,
                  0, sy,  0, ty,
                  0,  0,  1,  0,
                  0,  0,  0,  1);
}

GraphicsComponent::GraphicsComponent(const std::string & textureName)
{
  g_GraphicsSystem->m_components.insert(this);
  m_texture = g_GraphicsSystem->m_textureBank[textureName];
}
GraphicsComponent::~GraphicsComponent()
{
  g_GraphicsSystem->m_components.erase(this);
}

CameraComponent::CameraComponent(float width , float height ) // in arbitrary units
{
  SetWidth(width);
  SetHeight(height);
}

Matrix4 CameraComponent::GetViewMatrix() const
{
  const Transform * transform = GetOwner()->GetComponent<Transform>();

  Matrix4 invTrans = Matrix4Trans(-transform->m_pos);
  Matrix4 invScale = Matrix4Scaling(1.0f / m_width, 1.0f / m_height, 1);
  
  return invScale * invTrans;
}


void CameraComponent::SetWidth(float width)
{
  if (width <= 0) __debugbreak();
  m_width = width;
}
void CameraComponent::SetHeight(float height)
{
  if (height <= 0)__debugbreak();
  m_height = height;
}