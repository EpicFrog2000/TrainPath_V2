#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "shader.cpp"
#include "Contact_With_DB/contact_with_db.hpp"
#include "destination_functions/Coordinates_Calculations.hpp"
#include <vector>
#include <set>
#include <iostream>
GLFWwindow *window;
using namespace glm;
int main(void)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		getchar();
		return -1;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(1000, 1000, "MapDrawing", NULL, NULL);
	if (window == NULL)
	{

		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		getchar();
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = true;
	if (glewInit() != GLEW_OK)
	{
		fprintf(stderr, "Failed to initialize GLEW\n");
		getchar();
		glfwTerminate();
		return -1;
	}

	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	glEnable(GL_DEPTH_TEST);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	std::vector<std::pair<std::string, std::pair<int, int>>> allStations = GetAllStations();
	std::vector<std::pair<int, int>> firstStation = GetOneStationCoords("Zakopane", allStations);
	std::vector<std::pair<int, int>> secondStation = GetOneStationCoords("Gdańsk", allStations);
	const int ODCHYLENIE = 3;
	std::set<std::pair<int, int>> sortedStations = SortStationsByDistance(GetStationsFromArea(allStations, getPointsBetweenTwoStations(firstStation, secondStation), ODCHYLENIE), firstStation, secondStation);
	std::vector<std::pair<int, int>> PathPoints = GetPathBetweenMultipleStations(sortedStations);

	GLuint allstations_buffer;
	glGenBuffers(1, &allstations_buffer);
	GLuint colors_buffer;
	glGenBuffers(1, &colors_buffer);
	GLuint PathPoints_buffer;
	glGenBuffers(1, &PathPoints_buffer);
	GLuint Pathcolors_buffer;
	glGenBuffers(1, &Pathcolors_buffer);

	std::vector<GLfloat> additionalData;
	std::vector<GLfloat> additionalColorData;
	float x = 0.0f / 100;
	float y = 0.0f / 100;
	GLsizei vertexes = 0;
	for (const auto &station : allStations)
	{
		glBindBuffer(GL_ARRAY_BUFFER, allstations_buffer);
		x = static_cast<float>(station.second.first) / 100;
		y = static_cast<float>(station.second.second) / 100;
		vertexes += 3;
		GLfloat newData[] = {
			x - 0.005f,	y - 0.005f,	0.0f,
			x + 0.005f,	y - 0.005f,	0.0f,
			x - 0.005f,	y + 0.005f,	0.0f,
		};
		additionalData.insert(additionalData.end(), newData, newData + sizeof(newData) / sizeof(newData[0]));

		glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
		GLfloat newColorData[] = {
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
			1.0f,0.0f,0.0f,
		};
		additionalColorData.insert(additionalColorData.end(), newColorData, newColorData + sizeof(newColorData) / sizeof(newColorData[0]));
	}
	glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
	glBufferData(GL_ARRAY_BUFFER, additionalColorData.size() * sizeof(GLfloat), additionalColorData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, allstations_buffer);
	glBufferData(GL_ARRAY_BUFFER, additionalData.size() * sizeof(GLfloat), additionalData.data(), GL_STATIC_DRAW);
	//----------------------------------------------------------------------------------------------------------------------------------
	for (const auto &path : PathPoints)
	{
		glBindBuffer(GL_ARRAY_BUFFER, PathPoints_buffer);
		x = static_cast<float>(path.first) / 100;
		y = static_cast<float>(path.second) / 100;
		vertexes += 3;
		GLfloat newData[] = {
			x - 0.005f,y - 0.005f,0.0f,
			x + 0.005f,y - 0.005f,0.0f,
			x - 0.005f,y + 0.005f,0.0f,

		};
		additionalData.insert(additionalData.end(), newData, newData + sizeof(newData) / sizeof(newData[0]));

		glBindBuffer(GL_ARRAY_BUFFER, Pathcolors_buffer);
		GLfloat newColorData[] = {
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
			0.0f,0.0f,1.0f,
		};
		additionalColorData.insert(additionalColorData.end(), newColorData, newColorData + sizeof(newColorData) / sizeof(newColorData[0]));
	}
	glBindBuffer(GL_ARRAY_BUFFER, Pathcolors_buffer);
	glBufferData(GL_ARRAY_BUFFER, additionalColorData.size() * sizeof(GLfloat), additionalColorData.data(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, PathPoints_buffer);
	glBufferData(GL_ARRAY_BUFFER, additionalData.size() * sizeof(GLfloat), additionalData.data(), GL_STATIC_DRAW);
	do
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, allstations_buffer);

		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void *)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, colors_buffer);
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void *)0);
		glDrawArrays(GL_TRIANGLES, 0, vertexes);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, PathPoints_buffer);

		glVertexAttribPointer(
			0,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void *)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, Pathcolors_buffer);
		glVertexAttribPointer(
			1,
			3,
			GL_FLOAT,
			GL_FALSE,
			0,
			(void *)0);
		glDrawArrays(GL_TRIANGLES, 0, vertexes);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		glfwSwapBuffers(window);
		glfwPollEvents();

	} while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);

	glDeleteBuffers(1, &allstations_buffer);
	glDeleteBuffers(1, &colors_buffer);
	glDeleteBuffers(1, &PathPoints_buffer);
	glDeleteBuffers(1, &Pathcolors_buffer);
	glDeleteVertexArrays(1, &VertexArrayID);
	glDeleteProgram(programID);

	glfwTerminate();

	return 0;
}
// g++ -o draw draw.cpp Contact_With_DB/contact_with_db.cpp destination_functions/Coordinates_Calculations.cpp Drawing_Map/Map_Draw.cpp -lglfw -lGL -lGLEW `mysql_config --cflags --libs` && ./draw