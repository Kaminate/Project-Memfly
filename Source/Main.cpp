#include <iostream>
#include <time.h>

#include "Core.h"
#include "GraphicsStuff.h"
#include "PhysicsStuff.h"
#include "Transform.h"
#include "ActionList.h"
#include "Planning.h"

#include "Vector4.h"
#include "LerpAction.h"
#include "KillEnemy.h"
#include "InstakillEnemyAction.h"

int main()
{
  Core * core = new Core();
  core->AddSystem(new GraphicsSystem());
  core->AddSystem(new PhysicsSystem());
  core->AddSystem(new ActionManager());
  core->AddSystem(new PlanningSystem());

  g_GraphicsSystem->LoadTexture("Resources/fish.png", "fish");

  GameObject * fish = new GameObject();
  fish->AddComponent(new GraphicsComponent("fish"));
  fish->AddComponent(new Transform(0, 0));
  fish->AddComponent(new PhysicsComponent());
  fish->AddComponent(new ActionList());
  PlanningComponent * fishPlan = new PlanningComponent();
  fishPlan->AddGoal(new KillEnemyGoal());
  fishPlan->AddAction(new InstakillEnemyAction());
  fish->AddComponent(fishPlan);

  GameObject * camera = new GameObject();
  camera->AddComponent(new Transform(0,0));
  camera->AddComponent(new CameraComponent());

  g_GraphicsSystem->SetCamera(camera->GetComponent<CameraComponent>());


  time_t lastUpdate = clock();
  while(1)
  {
    time_t currTime = clock();
    float elapsedTimeInSeconds = (currTime - lastUpdate) / (float) CLOCKS_PER_SEC;
    if (elapsedTimeInSeconds > 0.016f)
    {
      core->Update(elapsedTimeInSeconds);
      lastUpdate = currTime;
    }
  }
  
	return 0;
}
