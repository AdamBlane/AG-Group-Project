#include "stdafx.h"

using namespace std;


void error_callback(int error, const char* description)
{
	fputs(description, stderr);
}

static void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(win, GL_TRUE);
}


int main(int argc, char **argv)
{
	
    //auto eng = engine::get();
    //eng->add_subsystem("entity_manager", entity_manager::get());
    //eng->add_subsystem("physics_system", physics_system::get());
    //eng->add_subsystem("renderer", renderer::get());
    //eng->add_subsystem("state_machine", engine_state_machine::get());
    //eng->add_subsystem("input_handler", input_handler::get());

    //engine_state_machine::get()->add_state("1", make_shared<engine_state_1>());
    //engine_state_machine::get()->add_state("2", make_shared<engine_state_2>());
    //engine_state_machine::get()->change_state("1");

    //auto e = entity_manager::get()->create_entity("Test");
    //e->add_component("physics", physics_system::get()->build_component(e));
    //e->add_component("render", renderer::get()->build_component(e, "Blue", "Sphere", "Gouraud"));

    //eng->run();

	// Create window
	GLFWwindow* window;
	// Set error callbackc function
	glfwSetErrorCallback(error_callback);
	// Initialise GLFW
	if (!glfwInit())
		exit(EXIT_FAILURE);
	// Initialise the window, check for error after
	window = glfwCreateWindow(640, 480, "Triangle Simulator 2017", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// Assign context
	glfwMakeContextCurrent(window);
	// Assign key callback function for close on ESC
	glfwSetKeyCallback(window, key_callback);
	// While window is not to be closed...
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;

		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;

		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);

		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);

		glLoadIdentity();
		glRotatef((float)glfwGetTime() * 50.f, 0.f, 0.f, 1.0f);

		glBegin(GL_TRIANGLES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(-0.6f, -0.4f, 0.f);
		glColor3f(0.f, 1.f, 0.f);
		glVertex3f(0.6f, -0.4f, 0.f);
		glColor3f(0.f, 0.f, 1.f);
		glVertex3f(0.f, 0.6f, 0.f);
		glEnd();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);



    return 0;
}