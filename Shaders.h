#ifndef SHADERS_H
#define SHADERS_H


// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 1000;
unsigned int VBO, VAO;
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

const char* fragmentShader1Source = "#version 330 core\n" //Blanco RGB(255, 255, 255)
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.95f, 0.95f, 0.95f, 1.0f);\n"
"}\n\0";

const char* fragmentShader2Source = "#version 330 core\n" //Rojo RGB(176, 9, 9)
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.69f, 0.03f, 0.03f, 1.0f);\n"
"}\n\0";
const char* fragmentShader3Source = "#version 330 core\n" //Verde RGB(68, 161, 26)
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.26f, 0.63f, 0.10f, 1.0f);\n"
"}\n\0";
const char* fragmentShader4Source = "#version 330 core\n" //Azul RGB(23, 108, 173)
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.09f, 0.42f, 0.75f, 1.0f);\n"
"}\n\0";
const char* fragmentShader5Source = "#version 330 core\n" //Amarillo RGB(230, 219, 21)
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.90f, 0.85f, 0.08f, 1.0f);\n"
"}\n\0";
const char* fragmentShader6Source = "#version 330 core\n" //AnaranjadoRGB(230, 122, 21)
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.90f, 0.48f, 0.08f, 1.0f);\n"
"}\n\0";

const char* fragmentShader7Source = "#version 330 core\n" //Negro RGB(0, 0, 0)
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);\n"
"}\n\0";

const char* fragmentShader8Source = "#version 330 core\n" //Gris RGB(0, 0, 0)
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.15f, 0.15f, 0.15f, 1.0f);\n"
"}\n\0";


unsigned int SP;
unsigned int red = 1,blue = 3,green = 2,orange = 5, yellow = 4, white = 0, black = 6, gray = 7;
vector<string> vFS;
vector<unsigned int> vSP;
#define N 4
const double pi = 3.14159265;
int numColors = 8;
void generateColors(int numColors) {

	vFS.clear();
	vFS.push_back(fragmentShader1Source);
	vFS.push_back(fragmentShader2Source);
	vFS.push_back(fragmentShader3Source);
	vFS.push_back(fragmentShader4Source);
	vFS.push_back(fragmentShader5Source);
	vFS.push_back(fragmentShader6Source);
	vFS.push_back(fragmentShader7Source);
	vFS.push_back(fragmentShader8Source);
};


void compileShader() {
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	for (int i = 0; i < numColors; i++)
	{
		unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
		unsigned int shaderProgram = glCreateProgram();

		const char* source = vFS[i].c_str();
		glShaderSource(fragmentShader, 1, &source, NULL);
		glCompileShader(fragmentShader);

		glAttachShader(shaderProgram, vertexShader);
		glAttachShader(shaderProgram, fragmentShader);
		glLinkProgram(shaderProgram);

		vSP.push_back(shaderProgram);
		glDeleteShader(fragmentShader);
	}

	glDeleteShader(vertexShader);
	SP = vSP[0];
	red = vSP[red]; blue = vSP[blue]; green = vSP[green]; orange = vSP[orange];
	yellow = vSP[yellow]; white = vSP[white]; black = vSP[black];  gray = vSP[gray];
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

}


void bufferArray() {
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex.size(), &vertex.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

}

void bufferArray(vector<float> _vertex) {
	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * _vertex.size(), &_vertex.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

}
#endif
