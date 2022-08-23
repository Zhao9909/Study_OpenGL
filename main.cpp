#include <iostream>
using namespace std;

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

void framebuffer_size_callback(GLFWwindow* window,int width,int height);
void processInput(GLFWwindow* window);

const char* vertexShaderSource =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"
"layout(location = 1) in vec3 aColor;\n"
"out vec4 vertexColor;\n"
"void main() {	\n"
"gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"vertexColor = vec4(aColor.x , aColor.y , aColor.z , 1.0);\n"
"}\n";
const char* fragmentShaderSource =
"#version 330 core\n"
"in vec4 vertexColor;\n"
//"uniform vec4 ourColor;\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = vertexColor;}\n";

const char* fragmentShaderSource2 =
"#version 330 core\n"
"in vec4 vertexColor;\n"
"uniform vec4 ourColor;\n"
"out vec4 FragColor;\n"
"void main(){\n"
"FragColor = ourColor;}\n";

float vertices[] = {
	//-0.5f, -0.5f, 0.0f,//0
	// 0.5f, -0.5f, 0.0f,//1
	// 0.0f,  0.5f, 0.0f,//2
	// //0.5f, -0.5f, 0.0f,
	// //0.0f,  0.5f, 0.0f,
	// -0.5f,  0.5f, 0.0f//3
	0.5f,  0.5f, 0.0f , 1.f ,   0,  0,  // top right
	 0.5f, -0.9f, 0.0f, 0   ,1.f ,  0 , // bottom right
	-0.5f, -0.5f, 0.0f, 0   ,   0, 1.f, // bottom left
	-0.5f,  0.5f, 0.0f, 1.f ,   0, 1.f ,  // top left 
	-0.9f,  0.9f, 0.0f, 1.f , 1.f, 0
};

float vertices2[] = {
	//-0.5f, -0.5f, 0.0f,//0
	// 0.5f, -0.5f, 0.0f,//1
	// 0.0f,  0.5f, 0.0f,//2
	// //0.5f, -0.5f, 0.0f,
	// //0.0f,  0.5f, 0.0f,
	// -0.5f,  0.5f, 0.0f//3
	0.8f,  0.8f, 0.0f , 1.f ,   0,  0,  // top right
	 0.9f, 0.9f, 0.0f, 0   ,1.f ,  0 , // bottom right
	0.8f, 0.9f, 0.0f, 0   ,   0, 1.f, // bottom left
	
};

unsigned int indices[] = {
	0 , 1 , 3 ,
	1 , 2 , 3 ,
	2 , 4 , 3
};

unsigned int indices2[] = {
	0,2,1
};

int main()
{

	//cout << "Hello OpenGL!" << endl;

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR , 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR , 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800,600,"My OpenGL Window",NULL,NULL);
	if (window == NULL)
	{
		cout << "����ʧ��" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);
	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		cout << "��ʼ��ʧ��" << endl;
		glfwTerminate();
		return -1;
	}

	glViewport(0,0,800,400);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	Shader* myShader01 =new  Shader("vertexSource.txt","fragmentSource.txt");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	//VAO���ڹ���VBO��EBO��
	unsigned int VAOs[2];
	glGenVertexArrays(2,VAOs);

	//�����洢�������ԣ���GPU����һ��ռ䣬VBO����ͷ
	unsigned int VBOs[2];
	glGenBuffers(2,VBOs);
	//��������EBO
	unsigned int EBOs[2];
	glGenBuffers(2, EBOs);

	//��һ��
	glBindVertexArray(VAOs[0]);//�����VOA�趨Ϊ��ǰVAO��һ��ʱ�����ֻ����һ��VAO
	glBindBuffer(GL_ARRAY_BUFFER,VBOs[0]);//�趨VBO������
	//�Ѷ���λ�ô��뵽VOB��
	glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	//Shader* myShader01 = new  Shader("vertexSource.txt", "fragmentSource.txt");

	
	//����������ɫ��
	//unsigned int vertexShader;
	//vertexShader = glCreateShader(GL_VERTEX_SHADER);
	////Ӳ����ķ�ʽ����֪��ɫ����ν������������
	//glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	////������ɫ��
	//glCompileShader(vertexShader);

	////����Ƿ����ɹ�
	//int  success;
	//char infoLog[512];
	//glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	//if (!success)
	//{
	//	glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
	//	std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	//}

	//unsigned int fragmentShader;
	//fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	//glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	//glCompileShader(fragmentShader);

	//unsigned int shaderProgram;
	//shaderProgram = glCreateProgram();
	//glAttachShader(shaderProgram, vertexShader);
	//glAttachShader(shaderProgram, fragmentShader);
	//glLinkProgram(shaderProgram);

	//�ڶ���VBO
	glBindVertexArray(VAOs[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);//�趨VBO������
	//�Ѷ���λ�ô��뵽VOB��
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);
	Shader* myShader02 = new  Shader("vertexSource.txt", "fragmentSource02.txt");
	
	



	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		//render commands here
		glClearColor(0.1f,0.2f,0.3f,1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,EBOs[0]);

		


		//glUseProgram(shaderProgram);
		
		myShader01->use();
		glBindVertexArray(VAOs[0]);
	/*	glDrawArrays(GL_TRIANGLES,0,9);*/
		glDrawElements(GL_TRIANGLES,9,GL_UNSIGNED_INT,0);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
		
		float timeValue = glfwGetTime();
		float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//cout << greenValue << endl;
		int vertexColorLocation = glGetUniformLocation(myShader02->ID, "ourColor");
		glUseProgram(myShader02->ID);
		glUniform4f(vertexColorLocation, 0, greenValue, 0, 1.0f);


		myShader02->use();
		glBindVertexArray(VAOs[1]);
		glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);

		// check and call events and swap the buffers
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	//system("pause");
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window,true);
	}
}