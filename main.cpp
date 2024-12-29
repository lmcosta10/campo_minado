#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>

struct Button {
        double x0;
        double x1;
        double y0;
        double y1;
        int type; // TODO
};


// TODO
int check_board_click () {
        return 0;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
        double xpos;
        double ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
                std::cout << "Click on x = " << xpos << "\n";
}


int main() {
	int board_len;
	std::cout << "Enter board length: ";
	std::cin >> board_len;
	
	Button board_buttons[board_len*board_len];
	
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
	
	float delta = 0.01f;
	float square_len = 0.1f;
	float start_x = 1.0/2.0 * square_len * board_len;
	float start_y = 1.0/2.0 * square_len * board_len;
	
	/* Place buttons on board */
	for (int i = 0; i < board_len; i++) {
                for (int j = 0; j < board_len; j++) {
                        board_buttons[board_len*i + j].x0 = 0.1f*j + delta - start_x;
                        board_buttons[board_len*i + j].x1 = 0.1f*j + square_len - delta - start_x;
                        board_buttons[board_len*i + j].y0 = 0.1f*i + delta - start_y;
                        board_buttons[board_len*i + j].y1 = 0.1f*i + square_len - delta - start_y;
                        board_buttons[board_len*i + j].type = 1;
                }
        }
	
	/* Make the window's context current */
        glfwMakeContextCurrent(window);
        
        /* Mouse click callback */
        glfwSetMouseButtonCallback(window, mouse_button_callback);

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
                /* Render here */
                glClear(GL_COLOR_BUFFER_BIT);
                
                // TODO: optimize loop (with the previous "for" one)
                for (int i = 0; i < board_len; i++) {
                        for (int j = 0; j < board_len; j++) {
		                glBegin(GL_QUADS);
                                glVertex2f( board_buttons[board_len*i + j].x0, board_buttons[board_len*i + j].y0);
                                glVertex2f( board_buttons[board_len*i + j].x1, board_buttons[board_len*i + j].y0);
                                glVertex2f( board_buttons[board_len*i + j].x1, board_buttons[board_len*i + j].y1);
                                glVertex2f( board_buttons[board_len*i + j].x0, board_buttons[board_len*i + j].y1);
                                glEnd();
                        }
	        }
	        
	        /* Testing */
	        std::cout << "Test\n"; // TODO: understand

                /* Swap front and back buffers */
                glfwSwapBuffers(window);

                /* Poll for and process events */
                glfwPollEvents();
        }
	
	glfwTerminate();
        return 0;
}
