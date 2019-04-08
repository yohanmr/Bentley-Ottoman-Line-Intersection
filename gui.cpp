#include <iostream>
#include <fstream>
#include "FindIntersections.h"

#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 1000

using namespace std;

// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void findIntersectionPoints();

vector<lineSegment> segmentVector;
// vector<int> a;
int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Line Intersection Algorithm", NULL, NULL);
    if (window == NULL)
    {
		cout<<"Failed to create window"<<endl;
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    // New coordinate system
    glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1);
    glMatrixMode( GL_MODELVIEW );

	// glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Set callback for mouse click
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    // set callback for change in cursor position
    glfwSetCursorPosCallback(window, cursor_position_callback);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
		// glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // draw all the line segments
        for(size_t i = 0; i < segmentVector.size(); i++)
        {
            if (segmentVector[i].endX != -1) {
                glBegin(GL_LINES);
                glVertex3f(segmentVector[i].startX, segmentVector[i].startY, 0);
                glVertex3f(segmentVector[i].endX, segmentVector[i].endY, 0);
                glEnd();
            }
        }

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

		// handle escape key press
        processInput(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();

    findIntersectionPoints();

    return 0;
}
int lineStartFlag = 0;
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS){
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        // create line segment and add to vetor depending upon the clicks
        // handle start and end point differently
        ypos = (SCREEN_HEIGHT-ypos);
        if (lineStartFlag == 0) {
            struct lineSegment newLine;
            newLine.startX = xpos;
            newLine.startY = ypos;
            lineStartFlag = 1;
            segmentVector.push_back(newLine);
        } else {
            segmentVector.back().endX = xpos;
            segmentVector.back().endY = ypos;
            lineStartFlag = 0;
        }
    }
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos){
    if (lineStartFlag == 1) {
        ypos = SCREEN_HEIGHT - ypos;
        segmentVector.back().endX = xpos;
        segmentVector.back().endY = ypos;
    }

}

// // Re-adjust Viewport size when window is resized
// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
// 	// cout<<height<<" "<<width<<endl;
//     glViewport(0, 0, width, height);
// }

void findIntersectionPoints(){
    ofstream myfile;
    myfile.open ("lines.txt");

    for(int i = 0; i < segmentVector.size(); i++)
    {
        myfile << segmentVector[i].startX << " " << segmentVector[i].startY << " " << segmentVector[i].endX << " " << segmentVector[i].endY << endl;
    }
    myfile.close();
    // FindIntersections findIntersection = FindIntersections(segmentVector);
    // findIntersection.runAlgorithm();

}

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }


    // if(glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS) printf("hello");
    //     // findIntersectionPoints();

}
