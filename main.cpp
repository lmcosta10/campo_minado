#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>

int main() {
	int board_len;
	std::cout << "Enter board length: ";
	std::cin >> board_len;
	
	GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
          return -1;
        
        window = glfwCreateWindow(640, 640, "Campo Minado", NULL, NULL);
        if (!window)
        {
                glfwTerminate();
                return -1;
        }
	
	int board[board_len*board_len];
	
	for (int i = 0; i < board_len*board_len; i++) {
		board[i] = rand() % 2;
	}
	
	float delta = 0.02f;
	float square_length = 0.1f;
	
	/* Make the window's context current */
        glfwMakeContextCurrent(window);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT);
                
                for (int i = 0; i < board_len; i++) {
                        for (int j = 0; j < board_len; j++) {
		                glBegin(GL_QUADS);
                                glVertex2f( 0.1f*j + delta, 0.1f*i + delta);
                                glVertex2f( 0.1f*j + square_length - delta, 0.1f*i + delta);
                                glVertex2f( 0.1f*j + square_length - delta, 0.1f*i + square_length - delta);
                                glVertex2f( 0.1f*j + delta, 0.1f*i + square_length - delta);
                                glEnd();
                        }
	        }

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
        }
	
	glfwTerminate();
        return 0;
}
