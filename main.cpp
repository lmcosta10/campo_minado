#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <functional>
#include <vector>

struct Button {
        double x0;
        double x1;
        double y0;
        double y1;
        int type; // TODO

        Button(double x0_, double x1_, double y0_, double y1_, int type_)
        : x0(x0_), x1(x1_), y0(y0_), y1(y1_), type(type_) {};
};

// TODO
std::vector<Button> board_buttons;
float button_len = 0.1f;
int window_size = 640;
float delta = 0.01f;

int check_button_click (double click_x, double click_y, double x0, double y0) {
        x0 = window_size/2.0 + x0/2.0*window_size;
        y0 = window_size/2.0 + y0/2.0*window_size;
        float button_len_ = button_len*window_size/2.0;
        float delta_ = delta*window_size/2.0;


        std::cout << x0 << "\n";
        std::cout << click_x << "\n";
        
        if ((click_y >= y0 + delta_ && click_y <= y0 + button_len_ - delta_) && (click_x >= x0 + delta_ && click_x <= x0 + button_len_ - delta_))
                return 1;
        return 0;
}


void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
        double xpos;
        double ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
                std::cout << "Click on x = " << xpos << "\n";
        if (!board_buttons.empty()) {
                int is_btn;
                unsigned int i = 0;
                int btn = -1;
                while(i < board_buttons.size()) {
                        is_btn = check_button_click(xpos, ypos, board_buttons[i].x0, board_buttons[i].y0);
                        btn = i;
                        if (is_btn==1)
                                break;
                        i++;
                }
                if (is_btn==1) std::cout << btn << "!!!!!!!!!!!!!!!!!!!!!\n";
        }
}


int main() {
	int board_len;
	std::cout << "Enter board length: ";
	std::cin >> board_len;
	
	GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
          return -1;
        
        window = glfwCreateWindow(window_size, window_size, "Campo Minado", NULL, NULL);
        if (!window)
        {
                glfwTerminate();
                return -1;
        }
	
	int board[board_len*board_len];
	
	for (int i = 0; i < board_len*board_len; i++) {
		board[i] = rand() % 2;
	}
	
	float start_x = 1.0/2.0 * button_len * board_len;
	float start_y = 1.0/2.0 * button_len * board_len;
	
	/* Place buttons on board */
        double btn_x0, btn_x1, btn_y0, btn_y1;
        int btn_type;
	for (int i = 0; i < board_len; i++) {
                for (int j = 0; j < board_len; j++) {
                        btn_x0 = 0.1f*j + delta - start_x;
                        btn_x1 = 0.1f*j + button_len - delta - start_x;
                        btn_y0 = 0.1f*i + delta - start_y;
                        btn_y1 = 0.1f*i + button_len - delta - start_y;
                        btn_type = 1;
                        board_buttons.push_back(Button(btn_x0, btn_x1, btn_y0, btn_y1, btn_type));
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
