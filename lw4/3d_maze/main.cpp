#define _USE_MATH_DEFINES
#include "glfw3.h"
#include <chrono>
#include <cmath>
#include "Includes/glm/ext/matrix_clip_space.hpp"
#include "Includes/glm/ext/matrix_transform.hpp"
#include <stdexcept>

class GLFWInitializer final
{
public:
	GLFWInitializer()
	{
		if (!glfwInit())
		{
			throw std::runtime_error("Failed to initialize GLFW");
		}
	}

	GLFWInitializer(const GLFWInitializer&) = delete;
	GLFWInitializer& operator=(const GLFWInitializer&) = delete;

	~GLFWInitializer()
	{
		glfwTerminate();
	}
};

class BaseWindow
{
public:
	BaseWindow(int w, int h, const char* title)
		: m_window{ MakeWindow(w, h, title) }
	{
		if (!m_window)
		{
			throw std::runtime_error("Failed to create window");
		}
	}
	BaseWindow(const BaseWindow&) = delete;
	BaseWindow& operator=(const BaseWindow&) = delete;

	virtual ~BaseWindow()
	{
		glfwDestroyWindow(m_window);
	}

	void Run()
	{
		glfwMakeContextCurrent(m_window);
		//glfwSetCursorPosCallback(m_window, static_cast<GLFWcursorposfun*>(mouse_callback(m_window, lastX, lastY)));
		OnRunStart();
		// tell GLFW to capture our mouse
		//glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		while (!glfwWindowShouldClose(m_window))
		{
			int w, h;
			glfwGetFramebufferSize(m_window, &w, &h);
			Draw(m_window, w, h);
			glFinish();
			glfwSwapBuffers(m_window);
			glfwPollEvents();
		}
		OnRunEnd();
	}

private:
	virtual void Draw(GLFWwindow* window, int width, int height) = 0;

	virtual void OnRunStart() {}
	virtual void OnRunEnd() {}

	static GLFWwindow* MakeWindow(int w, int h, const char* title)
	{
		glfwWindowHint(GLFW_DEPTH_BITS, 24);
		return glfwCreateWindow(w, h, title, nullptr, nullptr);
	}
	GLFWwindow* m_window;
};

class Window : public BaseWindow
{
public:
	using BaseWindow::BaseWindow;

private:

	glm::dvec3 cameraPos = glm::vec3(0.0f, 0.0f, 3.0f);
	glm::dvec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
	glm::dvec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

	float yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a 
	//yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
	float pitch = 0.0f;

	double deltaTime = 0.0f;	// time between current frame and last frame
	double lastFrame = 0.0f;

	void OnRunStart() override
	{
		// Задаем цвет очистки буфера кадра
		glClearColor(1, 1, 1, 1);
	}

	void Draw(GLFWwindow* window, int width, int height) override
	{
		double currentFrame = static_cast<double>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
			
		processInput(window);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		SetupProjectionMatrix(width, height);
		SetupCameraMatrix(cameraPos, cameraFront, cameraUp);
		//glEnable(GL_DEPTH_TEST);

		// Рисуем красный квадрат в плоскости XOY
		glColor3f(0.99215686275, 0.91764705882, 0.85490196078);
		glRectf(-1, 0, 1, 1);

		// Рисуем синий квадрат в плоскости Z=0, предварительно задав для него
		// трансформацию повоота вокруг оси Y и а затем переноса на 0.2 вдоль оси Z
		// Порядок умножения матриц - обратный
		float m_size = 1;
		float m_endSize = 0.1;
		float arrowOffset = m_size * m_endSize;
		float arrowOffset2 = arrowOffset * 0.5f;

		glBegin(GL_LINES);
		// Ось X
		{
			glColor3ub(255, 0, 0);

			// Рисуем ось X
			glVertex3f(0, 0, 0);
			glVertex3f(m_size, 0, 0);
			// Рисуем наконечник оси X
			glVertex3f(m_size, 0, 0);
			glVertex3f(m_size - arrowOffset, -arrowOffset2, 0);
			glVertex3f(m_size, 0, 0);
			glVertex3f(m_size - arrowOffset, +arrowOffset2, 0);
		}
		// Ось Y
		{
			glColor3ub(0, 255, 0);

			// Рисуем ось Y
			glVertex3f(0, 0, 0);
			glVertex3f(0, m_size, 0);
			// Рисуем наконечник оси Y
			glVertex3f(0, m_size, 0);
			glVertex3f(-arrowOffset2, m_size - arrowOffset, 0);
			glVertex3f(0, m_size, 0);
			glVertex3f(+arrowOffset2, m_size - arrowOffset, 0);
		}
		// Ось Z
		{
			glColor3ub(0, 0, 255);
			// Рисуем ось Z
			glVertex3f(0, 0, 0);
			glVertex3f(0, 0, m_size);
			// Рисуем наконечник оси Z
			glVertex3f(0, 0, m_size);
			glVertex3f(-arrowOffset2, 0, m_size - arrowOffset);
			glVertex3f(0, 0, m_size);
			glVertex3f(+arrowOffset2, 0, m_size - arrowOffset);
		}
		glEnd();

	}

	static void SetupProjectionMatrix(int width, int height)
	{
		glViewport(0, 0, width, height);

		// Вычисляем соотношение сторон клиентской области окна
		double aspect = double(width) / double(height);

		glMatrixMode(GL_PROJECTION);
		const auto projMat = glm::perspective(60.0 * M_PI / 180.0, aspect, 0.1, 10.0);
		glLoadMatrixd(&projMat[0][0]);
	}

	void SetupCameraMatrix(glm::dvec3 cameraPos, glm::dvec3 cameraFront, glm::dvec3 cameraUp)
	{
		glMatrixMode(GL_MODELVIEW);
		const auto view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
		glLoadMatrixd(&view[0][0]);
	}

	void processInput(GLFWwindow* window)
	{
		glm::dvec3 front;

		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
			glfwSetWindowShouldClose(window, true);

		double cameraSpeed = static_cast<double>(2.5 * deltaTime);
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			cameraPos += cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			cameraPos -= cameraSpeed * cameraFront;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
		if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
		{
			yaw -= 0.1;
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			cameraFront = glm::normalize(front);
			cameraFront = glm::normalize(front);
		}
		if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
		{
			yaw += 0.1;
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			cameraFront = glm::normalize(front);
			cameraFront = glm::normalize(front);
		}
	}

};

int main()
{
	GLFWInitializer initGLFW;
	Window window{ 1000, 800, "Maze 3d" };
	window.Run();
}

/*void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
glm::dvec3 cameraPos = glm::vec3(3.0f, 3.0f, 3.0f);
glm::dvec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::dvec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
double yaw = -90.0f;	// yaw is initialized to -90.0 degrees since a yaw of 0.0 results in a direction vector pointing to the right so we initially rotate a bit to the left.
double pitch = 0.0f;
double lastX = 800.0f / 2.0;
double lastY = 600.0 / 2.0;
double fov = 45.0f;

// timing
double deltaTime = 0.0f;	// time between current frame and last frame
double lastFrame = 0.0f;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	// configure global opengl state
	// -----------------------------
glEnable(GL_DEPTH_TEST);

// build and compile our shader zprogram
// ------------------------------------
//Shader ourShader("7.3.camera.vs", "7.3.camera.fs");

// set up vertex data (and buffer(s)) and configure vertex attributes
// ------------------------------------------------------------------
float vertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
};
// world space positions of our cubes
glm::vec3 cubePositions[] = {
	glm::vec3(0.0f,  0.0f,  0.0f),
	glm::vec3(2.0f,  5.0f, -15.0f),
	glm::vec3(-1.5f, -2.2f, -2.5f),
	glm::vec3(-3.8f, -2.0f, -12.3f),
	glm::vec3(2.4f, -0.4f, -3.5f),
	glm::vec3(-1.7f,  3.0f, -7.5f),
	glm::vec3(1.3f, -2.0f, -2.5f),
	glm::vec3(1.5f,  2.0f, -2.5f),
	glm::vec3(1.5f,  0.2f, -1.5f),
	glm::vec3(-1.3f,  1.0f, -1.5f)
};
unsigned int VBO, VAO;
glGenVertexArrays(1, &VAO);
glGenBuffers(1, &VBO);

glBindVertexArray(VAO);

glBindBuffer(GL_ARRAY_BUFFER, VBO);
glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

// position attribute
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
glEnableVertexAttribArray(0);
// texture coord attribute
glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
glEnableVertexAttribArray(1);


// load and create a texture
// -------------------------
unsigned int texture1, texture2;
// texture 1
// ---------
glGenTextures(1, &texture1);
glBindTexture(GL_TEXTURE_2D, texture1);
// set the texture wrapping parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// set texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load image, create texture and generate mipmaps
int width, height, nrChannels;
stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
unsigned char* data = stbi_load(FileSystem::getPath("resources/textures/container.jpg").c_str(), &width, &height, &nrChannels, 0);
if (data)
{
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
	std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(data);
// texture 2
// ---------
glGenTextures(1, &texture2);
glBindTexture(GL_TEXTURE_2D, texture2);
// set the texture wrapping parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
// set texture filtering parameters
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
// load image, create texture and generate mipmaps
data = stbi_load(FileSystem::getPath("resources/textures/awesomeface.png").c_str(), &width, &height, &nrChannels, 0);
if (data)
{
	// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
}
else
{
	std::cout << "Failed to load texture" << std::endl;
}
stbi_image_free(data);

// tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
// -------------------------------------------------------------------------------------------
ourShader.use();
ourShader.setInt("texture1", 0);
ourShader.setInt("texture2", 1);


// render loop
// -----------
while (!glfwWindowShouldClose(window))
{
	// per-frame time logic
	// --------------------
	float currentFrame = static_cast<float>(glfwGetTime());
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	// input
	// -----
	processInput(window);

	// render
	// ------
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// bind textures on corresponding texture units
	//glActiveTexture(GL_TEXTURE0);
	//glBindTexture(GL_TEXTURE_2D, texture1);
	//glActiveTexture(GL_TEXTURE1);
	//glBindTexture(GL_TEXTURE_2D, texture2);

	// activate shader
	//ourShader.use();

	// pass projection matrix to shader (note that in this case it could change every frame)
	const auto projection = glm::perspective(glm::radians(fov), (double)SCR_WIDTH / (double)SCR_HEIGHT, 0.1, 100.0);
	glLoadMatrixd(&projection[0][0]);

	// camera/view transformation
	const auto view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
	glLoadMatrixd(&view[0][0]);

	// render boxes
	// Рисуем красный квадрат в плоскости XOY
	glColor3f(0, 0, 0);
	glRectf(-1, 0, 1, 1);

	// Рисуем синий квадрат в плоскости Z=0, предварительно задав для него
	// трансформацию повоота вокруг оси Y и а затем переноса на 0.2 вдоль оси Z
	// Порядок умножения матриц - обратный
	float m_size = 1;
	float m_endSize = 0.1;
	float arrowOffset = m_size * m_endSize;
	float arrowOffset2 = arrowOffset * 0.5f;

	glBegin(GL_LINES);
	// Ось X
	{
		glColor3ub(255, 0, 0);

		// Рисуем ось X
		glVertex3f(0, 0, 0);
		glVertex3f(m_size, 0, 0);
		// Рисуем наконечник оси X
		glVertex3f(m_size, 0, 0);
		glVertex3f(m_size - arrowOffset, -arrowOffset2, 0);
		glVertex3f(m_size, 0, 0);
		glVertex3f(m_size - arrowOffset, +arrowOffset2, 0);
	}
	// Ось Y
	{
		glColor3ub(0, 255, 0);

		// Рисуем ось Y
		glVertex3f(0, 0, 0);
		glVertex3f(0, m_size, 0);
		// Рисуем наконечник оси Y
		glVertex3f(0, m_size, 0);
		glVertex3f(-arrowOffset2, m_size - arrowOffset, 0);
		glVertex3f(0, m_size, 0);
		glVertex3f(+arrowOffset2, m_size - arrowOffset, 0);
	}
	// Ось Z
	{
		glColor3ub(0, 0, 255);
		// Рисуем ось Z
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, m_size);
		// Рисуем наконечник оси Z
		glVertex3f(0, 0, m_size);
		glVertex3f(-arrowOffset2, 0, m_size - arrowOffset);
		glVertex3f(0, 0, m_size);
		glVertex3f(+arrowOffset2, 0, m_size - arrowOffset);
	}
	glEnd();

	glTranslatef(0, 0, 0.2f);
	glRotatef(60, 0, 1, 0);

	glColor3f(0, 0, 1);
	glRectf(-0.5, -1.0, +0.5, +0.5);

	// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
	// -------------------------------------------------------------------------------
	glfwSwapBuffers(window);
	glfwPollEvents();
}

// optional: de-allocate all resources once they've outlived their purpose:
// ------------------------------------------------------------------------
//glDeleteVertexArrays(1, &VAO);
//glDeleteBuffers(1, &VBO);

// glfw: terminate, clearing all previously allocated GLFW resources.
// ------------------------------------------------------------------
glfwTerminate();
return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	double cameraSpeed = static_cast<float>(2.5 * deltaTime);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cameraPos += cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cameraPos -= cameraSpeed * cameraFront;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
{
	float xpos = static_cast<float>(xposIn);
	float ypos = static_cast<float>(yposIn);

	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.1f; // change this value to your liking
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	yaw += xoffset;
	pitch += yoffset;

	// make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.0f)
		pitch = 89.0f;
	if (pitch < -89.0f)
		pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	front.y = sin(glm::radians(pitch));
	front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
	cameraFront = glm::normalize(front);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	fov -= (float)yoffset;
	if (fov < 1.0f)
		fov = 1.0f;
	if (fov > 45.0f)
		fov = 45.0f;
}*/