#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <LibMath/header/Angle.h>
#include "ResourceManager.h"
#include "EntityManager.h"
#include "GameObject.h"
#include "EmptyGM.h"
#include "PlayerGO.h"
#include "CameraG0.h"
#include "Shader.h"
#include "Texture.h"
#include "Model.h"
#include "Camera.h"
#include "Light.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

constexpr auto WINDOW_WIDTH = 800; 
constexpr auto WINDOW_HEIGHT = 600;

void onWindowResize(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void render();

using namespace LibMath::Literal;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, onWindowResize);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	Camera cam;
	Light lig(LibMath::Vector3(0, 0, 0));
	ResourceManager rm;
	//rm.Add<Texture>("png-clipart-barack-obama-barack-obama.png");
	//rm.Add<Texture>("red.png");
	//rm.Add<Texture>("green.png");
	//rm.Add<Texture>("blue.png");
	//rm.Add<Texture>("white.png");
	//rm.Add<Texture>("grey.png");
	//rm.Add<Texture>("black.png");
	//rm.Add<Shader>("shaderBuffer.txt")->Link();
	//rm.Add<Model>("Sting-Sword-lowpoly.obj")->SetVAO();
	//rm.Add<Model>("cube.obj")->SetVAO();
	//rm.Add<Model>("sphere.obj")->SetVAO();
	//rm.Add<Model>("cylindre.obj")->SetVAO();

	//auto& shader = *rm.Get<Shader>("shaderBuffer.txt");
	//auto green = rm.Get<Texture>("green.png");
	//auto red = rm.Get<Texture>("red.png");
	//auto grey = rm.Get<Texture>("grey.png");
	//auto model1 = rm.Get<Model>("Sting-Sword-lowpoly.obj");
	//auto modelCube = rm.Get<Model>("cube.obj");

	//cam.SetUniformCam(shader);
	//lig.SetUniformLight(shader);

	//// Setup Entities
	//EntityManager em;

	//GameObject* floor = em.Add<GameObject>("floor", nullptr, modelCube, grey);
	//floor->GetLocalTransform().translate(0, -1.0f, 0);
	//floor->GetLocalTransform().scale(100, 1, 100);

	//GameObject* cube = em.Add<GameObject>("cube", nullptr, modelCube, green);
	//GameObject* swrd = em.Add<GameObject>("swrd", nullptr, model1, green);

	////auto names = std::vector<std::string>{ "sword1" , "sword2" };
	////auto models = std::vector<Model*>{ model1 };
	////auto textures = std::vector<Texture*>{ green };

	////cube->AddChildreen<GameObject>(names, models, textures);
	//cube->AddCapsuleChild(3, 0.5f,	rm.Get<Model>("sphere.obj"),
	//								rm.Get<Model>("cylindre.obj"),
	//								red);
	//swrd->AddCapsuleChild(1, 1,		rm.Get<Model>("sphere.obj"),
	//								rm.Get<Model>("cylindre.obj"),
	//								red);

	//auto& cbe =		*em.Get<GameObject>("cube");
	//auto& swoard1 =		*em.Get<GameObject>("swrd");
	//auto& swr =		*em.Get<GameObject>("swrd");
	////auto& cpsl =	*cbe.GetChild<GameObject>("capsule");

	//cbe.GetLocalTransform().scale(3);
	//cbe.GetLocalTransform().translate(3, 0, -2);

	//swr.GetLocalTransform().translate(-3, 0, -2);

	////Player
	//PlayerGO* player	= em.Add<PlayerGO>("player", nullptr);
	//player->GetLocalTransform().translate(0, 4, 0);

	//CameraG0* camGO		= player->GetChild<CameraG0>(PlayerGO::CameraName);

	//Transform& t1 = camGO->AddChild<GameObject>("crosshair1", modelCube, red)->GetLocalTransform();
	//t1.translate(0, 0, -0.5f);
	//t1.scale(0.1f);
	//t1.scale(1.0f, 0.06f, 0.06f);

	//Transform& t2 = camGO->AddChild<GameObject>("crosshair2", modelCube, red)->GetLocalTransform();
	//t2.translate(0, 0, -0.5f);
	//t2.scale(0.1f);
	//t2.scale(0.06f, 1.0f, 0.06f);

	////capGO->GetLocalTransform().scale(0.5f);
	////capGO->GetLocalTransform().translate(0, 0, 0);

	//// Run main loop
	//while (!glfwWindowShouldClose(window))
	//{
	//	camGO->Update();

	//	processInput(window);
	//	player->Inputs(window);
	//	player->Update();

	//	render();

	//	em.DrawAllEntities(shader, camGO->GetCamera());

	//	//cam.SetUniformCam(shader);
	//	//model1.Draw(green, shader, cam);

	//	glfwSwapBuffers(window);
	//	glfwPollEvents();
	//}

    rm.DeleteAll();

	glfwTerminate();
	return 0;
}

void onWindowResize(GLFWwindow* window, const int width, const int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void render()
{
	glClearColor(0.1f, 0.2f, 0.4f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}




