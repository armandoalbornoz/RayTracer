// Based on templates from learnopengl.com

#define GLEW_STATIC
#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <Eigen/Dense>
#include "RayTracer.h"
#include "./OrtographicCamera.h"
#include <iostream>
#include "./LightSource.h"
#include <string>
#include <fstream>
#include "./Triangle.h"


using namespace std;
using Eigen::Vector3d;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 800;

std::vector<unsigned char> imageVecOrto;
std::vector<unsigned char> imageVecProj;

unsigned char* imageProj;
unsigned char* imageOrto;

unsigned char* dataProj;
unsigned char* dataOrto;
bool current = false;

int width; 
int height;


const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"layout (location = 2) in vec2 aTexCoord;\n"
"out vec3 ourColor;\n"
"out vec2 TexCoord;\n"
"void main()\n"
"{\n"
"gl_Position = vec4(aPos, 1.0);\n"
"ourColor = aColor;\n"
"TexCoord = vec2(aTexCoord.x, aTexCoord.y);\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"in vec2 TexCoord;\n"
"uniform sampler2D texture1;\n"
"void main()\n"
"{\n"
"   FragColor = texture(texture1, TexCoord);\n"
"}\n\0";



void keyCallback(GLFWwindow* window, int key, int scancode, int  action, int mods)
{
    
    if (key == GLFW_KEY_P && action == GLFW_PRESS && imageVecProj.size() > 0 && imageVecOrto.size() > 0)
    {
        current = !current;

        if (current && dataProj)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataProj);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else if (!current && dataOrto)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataOrto);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
    }
}


bool writeImage(string filename, int width, int height, std::vector<unsigned char> imageToWrite) {
    ofstream image;
    image.open(filename, ios::out | ios::binary);
    if (!image) {
        cerr << "Cannot open file" << endl;
        return false;
    }

    image << "P3" << "\n";
    image << width << " " << height << "\n";
    image << "255" << "\n";

    //size_t size = height * width;

    for (int i = 0; i < 3 * width * height ; i+= 3)
    {
        image << (int)imageToWrite[i]  << " " << (int)imageToWrite[(i + 1)] << " " << (int)imageToWrite[(i + 2)] << endl;
    }

    image.close();
  

}


int main()
{

  /*
    Vector3d v1(0, 0, 1);
    Vector3d v2(0, -1, 0);

    Vector3d v3 = v1.cross(v2);

    if (v1.cross(v2) == Vector3d(0, 0, 0))
    {
        std::cout << "orthogonal" << std::endl;

    }
   
    std::cout << v1.cross(v2) << std::endl;
    */

    width = 128; // keep it in powers of 2!
    height = 128; // keep it in powers of 2!


    // Scene


    
    Scene scene(std::make_shared<Sphere>(Vector3d(-40, 0, 0), 20, Vector3d(0.3,0.2, 0.4), Vector3d(1,1,1), Vector3d(0.3, 0.2, 0.4), Vector3d(0,0,0)));
    scene.add(std::make_shared<Sphere>(Vector3d(35, 0, 20), 20, Vector3d(0.3, 0.8,0.6), Vector3d(0,0,0), Vector3d(0.3, 0.8, 0.6), Vector3d(0, 0, 0)));
    scene.add(std::make_shared<Triangle>(Vector3d(-20, -20, 0), Vector3d(0 , -20, -20), Vector3d(0,20,-10), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0), Vector3d(0, 0.4, 0.4), Vector3d(0,0,0)));
    scene.add(std::make_shared<Triangle>(Vector3d(20, -20, 0), Vector3d(0, -20, -20), Vector3d(0, 20, -10), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0)));
    scene.add(std::make_shared<Triangle>(Vector3d(-20, -20, 0), Vector3d(20, -20, 0), Vector3d(0, 20, -10), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0)));
    scene.add(std::make_shared<Triangle>(Vector3d(-20, -20, 0), Vector3d(20, -20, 0), Vector3d(0, -20, -20), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0), Vector3d(0, 0.4, 0.4), Vector3d(0, 0, 0)));


    scene.add(std::make_shared<Plane>(Vector3d(0, -20, 0), Vector3d(0, 1, 0), Vector3d(0.35, 0.1, 0.17), Vector3d(1, 1, 1), Vector3d(0.4, 0.7, 0.9), Vector3d(0.4, 0.4, 0.4)));

    // Cameras
    OrthographicCamera ortographicCamera(Vector3d(20, 50, -125), Vector3d(-20, -50, 125), Vector3d(200, 0, 0), width, height);
    PerspectiveCamera perspectiveCamera(Vector3d(20, 50, -125), Vector3d(-20, -50, 125), Vector3d(200, 0, 0), width, height, 100);
    LightSource light(Vector3d(1,1,1), Vector3d(-150, 300, 50), Vector3d(1.2,1.2,1.2));

    // RayTracer

    Raytracer r(width, height);
   
    // std::vector<unsigned char> imageVec = r.render(scene, ortographicCamera, perspectiveCamera, light, true);

      imageVecProj = r.render(scene, ortographicCamera, perspectiveCamera, light, true);
      imageVecOrto = r.render(scene, ortographicCamera, perspectiveCamera, light, false);

    
    //std::vector<unsigned char> imageVec;;
     //writeImage("C:/Users/PC/Desktop/images/0.ppm", width, height, imageVec);

    // Code to generate video
    /*
    for (int frame = 0; frame < 360; frame++)
    {
        double t = frame / 100.0;
        Vector3d e = Vector3d(100 * std::cos(t), 0, 100 * std::sin(t));
        Vector3d viewVector = -e + Vector3d(0,0,1);
        perspectiveCamera.setViewpoint(e);
        perspectiveCamera.setViewDirection(viewVector);

        // render and save image
        imageVecProj = r.render(scene, ortographicCamera, perspectiveCamera, light, true);
        writeImage("C:/Users/PC/Desktop/images/" + std::to_string(frame) + ".ppm", width, height, imageVecProj);
        
        // change camera position by finding the new center of the camera and the view vector
 


      //  perspectiveCamera.s

    }

    */

   
    
    

    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Display RGB Array", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, keyCallback);

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // // GLEW: load all OpenGL function pointers
    glewInit();

    // build and compile the shaders
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
        // positions          // colors           // texture coords
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
    };
    unsigned int indices[] = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);


    // load and create a texture 
    // -------------------------
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    // Create the image (RGB Array) to be displayed

     imageProj = &imageVecProj[0];
     imageOrto = &imageVecOrto[0];


    //unsigned char* image = &imageVec[0];
    //unsigned char image[width * height * 3];

    /*
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int idx = (i * width + j) * 3;
            image[idx] = (unsigned char)(255 * i * j / height / width); //((i+j) % 2) * 255;
            image[idx + 1] = 0;
            image[idx + 2] = 0;
        }
    }
    */

    
    //unsigned char* data = &image[0];
     dataProj = &imageProj[0];
     dataOrto = &imageOrto[0];




    if (dataProj)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, dataProj);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }



    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind Texture
        glBindTexture(GL_TEXTURE_2D, texture);

        // render container
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

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
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}