#include <iostream>
#include <vector>
#include <fstream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


using namespace std;

// the application will close after this amount of time
const float MILISECONDS_TO_CLOSE = 10 * 1000;

GLFWwindow* window;

int main(int argc, char** argv)
{
	if (!glfwInit())
		return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	window = glfwCreateWindow(800, 600, "test", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glClearColor(0.15f, 0.15f, 0.15f, 1.0f);

	vector<unsigned> deltas;
	deltas.reserve(10 * MILISECONDS_TO_CLOSE);

	static unsigned firstTime, prevTime, curTime;
	firstTime = prevTime = curTime = (unsigned)(1000 * glfwGetTime());
	while (!glfwWindowShouldClose(window))
	{
		// compute delta time
		curTime = (unsigned)(1000 * glfwGetTime());
		unsigned dt = curTime - prevTime;
		prevTime = curTime;
		deltas.push_back(dt);

		// close the application after some time
		if (curTime - firstTime > MILISECONDS_TO_CLOSE) break;

		// handle closing events
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break;

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();

	// save recorded deltas to a file
	fstream f("out.txt", ios::out | ios::trunc);
	for (unsigned dt : deltas) f << dt << endl;
	f << flush;
	f.close();

	return 0;
}