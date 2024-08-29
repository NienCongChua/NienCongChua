#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

#include <GL/glew.h>
#include <GL/freeglut.h>

#include <Vector_Matrix.h>


using namespace std;

typedef struct
{
	float XYZW[4];
	float RGBA[4];
} Vertex;

//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

// hehe
Vertex Vertices[] =
{
	// v0-v1-v2 (front)
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	// v2-v3-v0
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	0.5f,	1.0f },{ 1.0f,	0.0f,	0.0f,	1.0f } },

	// v0-v3-v4 (right)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	-0.5f,  -0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	// v4-v5-v0
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,	-0.5f,	1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },
	{ { 0.5f,	 0.5f,   0.5f,1.0f },{ 0.0f,	1.0f,	0.0f,	1.0f } },

	// v0-v5-v6 (top)
	{ { 0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v6-v1-v0
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { 0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v1-v6-v7 (left)
	{ { -0.5f,	 0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	-0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	// v7-v2-v1
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },
	{ { -0.5f,	0.5f,	 0.5f,	1.0f },{ 0.0f,	0.0f,	1.0f,	1.0f } },

	// v7-v4-v3 (bottom)
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	// v3-v2-v7
	{ { 0.5f,	-0.5f,	 0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	0.5f,	1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },
	{ { -0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.1f,	0.2f,	0.3f,	1.0f } },

	// v4-v7-v6 (back)
	{ { 0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	-0.5f,	-0.5f,	1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { -0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	// v6-v5-v4
	{ { -0.5f,	 0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } },
	{ { 0.5f,	-0.5f,	 -0.5f,1.0f },{ 0.4f,	0.5f,	0.6f,	1.0f } }
};

const size_t BufferSize = sizeof(Vertices);
const size_t VertexSize = sizeof(Vertices[0]);
const size_t RgbOffset = sizeof(Vertices[0].XYZW);

// định nghĩa stack cho ma trận
class MatrixStack {
	int    index;
	int    size;
	mat4* matrices;


public:
	MatrixStack(int numMatrices = 32) :index(0), size(numMatrices)
	{
		matrices = new mat4[numMatrices];
	}

	~MatrixStack()
	{
		delete[]matrices;
	}

	// phép toán đẩy vào
	mat4& push(const mat4& m) {
		assert(index + 1 < size);
		matrices[index++] = m;
		return matrices[index];
	}

	// phép toán lấy ra
	mat4& pop(void) {
		assert(index - 1 >= 0);
		index--;
		return matrices[index];
	}
};

float R[3] = { 10.0f, 10.0f, 12.0f };
float T[3] = { 0.0f, 0.0f, 0.0f };
float Y[3] = { 0.0f, 1.0f, 0.0f };
float U[] = { 0.0f, 0.0f, 0.0f };
float nien[3] = { 0.0f, 0.0f, 0.0f };

int
CurrentWidth = 800,
CurrentHeight = 600;

GLuint
VaoId,
VboId,
VertexShaderId,
FragmentShaderId,
ProgramId;

MatrixStack  mvstack;

mat4  model_mat_cpp,
projection_mat_cpp;

GLuint
model_mat_location,
projection_mat_location;

// thiết lập chỉ mục cho menu, 
// sử dụng các chỉ số này cho các joint angles
enum {
	Ban,
	NganBan,//1
	ArmScr1,
	ArmScr2,		//2
	Cua1,			//3
	NumJointAngles,	//11
	Quit			//12
};

// giá trị ban đầu của các Joint angles
GLfloat
theta[NumJointAngles] = {
	0.0,    // Torso
	0.0,    // Head1
	85.0,    // Head2
	45.0,
	45.0
},

thetaArmScreen[NumJointAngles] = {
	30.0,    // Torso
	45.0,    // Head1
	80.0,    // Head2
	45.0,
	30.0
};

// khởi tạo đối tượng quay
GLint angle = NganBan;

// ------------------------------------------
	// thân
void matban()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0.0, 8.0, 2.0)) *
		scale(vec3(10, 0.1, 5)); //6, 8, 4

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// ------------------------------------------

// ------------------------------------------
// 
	// mat san
void matsan() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance =
		scale(vec3(20.0f, 0.01f, 20.0f)) * rotate_z(90) * rotate_y(90) * rotate_x(180);

	mat4 model_left_upper_arm = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_arm.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}
// chan ban
void chanban()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance =
		translate(vec3(0, 4.0, 0)) *
		scale(vec3(0.5f, 8.0f, 0.5f));

	mat4 model_left_upper_arm = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_left_upper_arm.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}



void nganban()
{
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 6, 2)) *
		scale(vec3(8.5, 0.1, 5)); //6, 8, 4

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

// Xay dung cai ghe
void changhedai() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(1.5, 4, 8)) *
		scale(vec3(0.25f, 8.0f, 0.25f));

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void tuaghe() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 1.25, 7.75)) *
		scale(vec3(3.0f, 2.5f, 0.25f));

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void changhengan() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(2, 2, 8)) *
		scale(vec3(0.25f, 3.75f, 0.25f));

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void chongoi() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0, 0)) *
		scale(vec3(3.5f, 0.25f, 3.5f));

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void casemaytinh() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0, 0)) *
		scale(vec3(1.0f, 0.5f, 1.0f)) *
		rotate_z(90);

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}


void armScreen1() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 0, 0)) *
		scale(vec3(0.3f, 1.0f, 0.3f)) *
		rotate_z(90);

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void armScreen2() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 1, 0)) *
		scale(vec3(0.3f, 3.0f, 0.3f)) *
		rotate_z(90);

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

void screen() {
	mvstack.push(model_mat_cpp);

	mat4 instance = identity_mat4();
	instance = translate(vec3(0, 1, 0)) *
		scale(vec3(5.0f, 3.5f, 0.3f)) *
		translate(vec3(0, 3, 0)) *
		rotate_x(90) *
		rotate_z(90);

	mat4 model_torso = model_mat_cpp * instance;

	glUniformMatrix4fv(model_mat_location, 1, GL_FALSE, model_torso.m);
	glDrawArrays(GL_TRIANGLES, 0, 36);

	model_mat_cpp = mvstack.pop();
}

// ------------------------------------------

// ------------------------------------------
string ReadShaderSourceFile(string fileName) {
	fstream reader(fileName.c_str());
	string line;
	string code = "";
	while (getline(reader, line)) {
		code += line + "\n";
	}
	reader.close();
	return code;
}

// ------------------------------------------
void CreatVaoVbo()
{
	glGenVertexArrays(1, &VaoId);
	glBindVertexArray(VaoId);

	glGenBuffers(1, &VboId);
	glBindBuffer(GL_ARRAY_BUFFER, VboId);
	glBufferData(GL_ARRAY_BUFFER, BufferSize, Vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, VertexSize, 0);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, VertexSize, (GLvoid*)RgbOffset);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
}
// ------------------------------------------
void CreatShaders()
{
	string vertexSrc = ReadShaderSourceFile("./vs.shader");
	string fragmentSrc = ReadShaderSourceFile("./fs.shader");

	const GLchar* VertexShader = vertexSrc.c_str();
	const GLchar* FragmentShader = fragmentSrc.c_str();

	VertexShaderId = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(VertexShaderId, 1, &VertexShader, NULL);
	glCompileShader(VertexShaderId);

	FragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(FragmentShaderId, 1, &FragmentShader, NULL);
	glCompileShader(FragmentShaderId);

	ProgramId = glCreateProgram();
	glAttachShader(ProgramId, VertexShaderId);
	glAttachShader(ProgramId, FragmentShaderId);
	glLinkProgram(ProgramId);
	glUseProgram(ProgramId);
}
// ------------------------------------------
void CloseFunc()
{
	glUseProgram(0);

	glDetachShader(ProgramId, VertexShaderId);
	glDetachShader(ProgramId, FragmentShaderId);

	glDeleteShader(FragmentShaderId);
	glDeleteShader(VertexShaderId);

	glDeleteProgram(ProgramId);

	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glDeleteBuffers(1, &VboId);

	glBindVertexArray(0);
	glDeleteVertexArrays(1, &VaoId);
}
// ------------------------------------------
void DisplayFunc(void)
{

	vec3	eye(R[0], R[1], R[2]),
		at(0, 0, 0),
		up(0, 1, 0);

	model_mat_cpp = lookat(eye, at, up) * rotate_x(theta[Ban] + U[0]) * rotate_y(theta[Ban] + U[1]) * rotate_z(theta[Ban] + U[2]);
	model_mat_location = glGetUniformLocation(ProgramId, "model_mat_shader");

	float
		znear = 1.0f,
		zfar = 100.0f,
		fov = 67.0f,
		aspect = (float)CurrentWidth / CurrentHeight;

	// Tạo ma trận projection 
	projection_mat_cpp = perspective(fov, aspect, znear, zfar);
	projection_mat_location = glGetUniformLocation(ProgramId, "projection_mat_shader");
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection_mat_cpp.m);


	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// thân

	matsan();

	// matban
	matban();

	// Ngan ban

	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp
		* translate(vec3(0.0f, 0.0f, theta[NganBan]));
	nganban();
	model_mat_cpp = mvstack.pop();


	// Chan ban 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(-4.5, 0, 0.0));
	chanban();
	model_mat_cpp = mvstack.pop();

	// chan ban 2
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(-4.5, 0, 4.0));
	chanban();
	model_mat_cpp = mvstack.pop();

	// Chan ban 3
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(4.5, 0, 0.0));
	chanban();
	model_mat_cpp = mvstack.pop();
	//// chan ban 4
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		translate(vec3(4.5, 0, 4.0));
	chanban();
	model_mat_cpp = mvstack.pop();


	// chan ghe dai 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 0, 0));
	changhedai();
	model_mat_cpp = mvstack.pop();

	// chan ghe dai 2
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-3, 0, 0));
	changhedai();
	model_mat_cpp = mvstack.pop();

	// tua ghe
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 5.5, 0));
	tuaghe();
	model_mat_cpp = mvstack.pop();

	// chan ghe ngan 1
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-0.5, 0, -3));
	changhengan();
	model_mat_cpp = mvstack.pop();

	// chan ghe ngan 2
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-3.5, 0, -3));
	changhengan();
	model_mat_cpp = mvstack.pop();

	// cho ngoi (tren ghe)
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(0, 4, 6.5));
	chongoi();
	model_mat_cpp = mvstack.pop();

	// Case may tinh
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-2, 8.25, 0.25));
	casemaytinh();
	model_mat_cpp = mvstack.pop();

	// Arm man hinh duoi
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-5, 8.25, 0.25)) *
		rotate_y(thetaArmScreen[ArmScr1]);
	armScreen1();
	model_mat_cpp = mvstack.pop();

	// Arm man hinh tren
	mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp * translate(vec3(-5, 10, 0.25)) *
		rotate_y(thetaArmScreen[ArmScr1]) *
		translate(vec3(0, -1.5, 0)) *
		rotate_x(thetaArmScreen[ArmScr2] + 180) *
		translate(vec3(0, -3, 0));
	armScreen2();
	model_mat_cpp = mvstack.pop();


	// Man hinh
	/*mvstack.push(model_mat_cpp);
	model_mat_cpp = model_mat_cpp *
		rotate_y(thetaArmScreen[ArmScr1]) *
		translate(vec3(0, -1.5, 0)) *
		rotate_x(thetaArmScreen[ArmScr2] + 180) *
		translate(vec3(0, -3, 0)) * 
		translate(vec3(0, -14, 0)) * 
		rotate_y(90) * 
		translate(vec3(0, 0, -1.75)) *
		rotate_z(nien[2]) *
		translate(vec3(0, 0, -3.5));
	screen();
	model_mat_cpp = mvstack.pop();*/


	glutSwapBuffers();
}
// ------------------------------------------
void ReshapeFunc(int Width, int Height)
{
	CurrentWidth = Width;
	CurrentHeight = Height;

	glViewport(0, 0, CurrentWidth, CurrentHeight);

	float  left = -10.0, right = 10.0;
	float  bottom = -5.0, top = 15.0;
	float  zNear = -10.0, zFar = 10.0;

	float aspect = float(CurrentWidth) / CurrentHeight;

	if (aspect > 1.0) {
		left *= aspect;
		right *= aspect;
	}
	else {
		bottom /= aspect;
		top /= aspect;
	}

	mat4 projection = ortho(left, right, bottom, top, zNear, zFar);
	glUniformMatrix4fv(projection_mat_location, 1, GL_FALSE, projection.m);

	model_mat_cpp = identity_mat4();
}
// ------------------------------------------
void IdleFunc(void)
{
	glutPostRedisplay();
}
// ------------------------------------------

void KeyboardFunc(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(EXIT_SUCCESS); break;
	case 'b':
		U[0] += 10.0f; break;
	case 'B':
		U[0] -= 10.0f; break;
	case 'n':
		U[1] += 10.0f; break;
	case 'N':
		U[1] -= 10.0f; break;
	case 'm':
		U[2] += 10.0f; break;
	case 'M':
		U[2] -= 10.0f; break;
	case '-':
		theta[angle] -= 0.1;
		if (theta[angle] < 0.0) { theta[angle] += 0.1; } glutPostRedisplay(); break;
	case '=':
		theta[angle] += 0.1;
		if (theta[angle] > 2.5) { theta[angle] -= 0.1; } glutPostRedisplay(); break;
	case 'z':
		R[0] += 0.1f; break;
	case 'Z':
		R[0] -= 0.1f; break;
	case 'x':
		R[1] += 0.1f; break;
	case 'X':
		R[1] -= 0.1f; break;
	case 'c':
		R[2] += 0.1f; break;
	case 'C':
		R[2] -= 0.1f; break;
	case 'a':
		T[0] += 0.1f; break;
	case 'A':
		T[0] -= 0.1f; break;
	case 's':
		T[1] += 0.1f; break;
	case 'S':
		T[1] -= 0.1f; break;
	case 'd':
		T[2] += 0.1f; break;
	case 'D':
		T[2] -= 0.1f; break;
	case 'q':
		Y[0] += 0.1f; break;
	case 'Q':
		Y[0] -= 0.1f; break;
	case 'w':
		Y[1] += 0.1f; break;
	case 'W':
		Y[1] -= 0.1f; break;
	case 'e':
		Y[2] += 0.1f; break;
	case 'E':
		Y[2] -= 0.1f; break;
	case '_':
		thetaArmScreen[angle] += 8;
		if (thetaArmScreen[angle] > 85) { thetaArmScreen[angle] -= 8; }; break;
	case '+':
		thetaArmScreen[angle] -= 8;
		if (thetaArmScreen[angle] < 0) { thetaArmScreen[angle] += 8; }; break;
	case '0':
		nien[0] += 10; break;
	case '1':
		nien[0] -= 10; break;
	case '2':
		nien[1] += 10; break;
	case '3':
		nien[1] -= 10; break;
	case '4':
		nien[2] += 10; break;
	case '5':
		nien[2] -= 10; break;
	}
}
// ------------------------------------------
void MouseFunc(int button, int state, int x, int y)
{

	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		thetaArmScreen[angle] += 8;
		if (thetaArmScreen[angle] > 85) { thetaArmScreen[angle] -= 8; }
	}

	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		thetaArmScreen[angle] -= 8;
		if (thetaArmScreen[angle] < 0) { thetaArmScreen[angle] += 8; }
	}

	glutPostRedisplay();
}
// ------------------------------------------
void menu(int option)
{
	if (option == Quit) {
		exit(EXIT_SUCCESS);
	}

	angle = option;
}
// ------------------------------------------
int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitContextVersion(4, 0);
	glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
	glutInitContextProfile(GLUT_CORE_PROFILE);
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);
	glutInitWindowSize(CurrentWidth, CurrentHeight);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutCreateWindow("Torso");

	glewExperimental = GL_TRUE;
	glewInit();

	CreatVaoVbo();
	CreatShaders();

	glutDisplayFunc(DisplayFunc);
	glutReshapeFunc(ReshapeFunc);
	glutIdleFunc(IdleFunc);
	glutKeyboardFunc(KeyboardFunc);
	glutMouseFunc(MouseFunc);
	glutCloseFunc(CloseFunc);

	// tạo menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Ngan Ban", NganBan);
	glutAddMenuEntry("Arm Low Screen", ArmScr1);
	glutAddMenuEntry("Arm High Screen", ArmScr2);
	glutAddMenuEntry("quit", Quit);

	// kích hoạt menu bằng nhấn nút giữa chuột
	glutAttachMenu(GLUT_MIDDLE_BUTTON);

	glutMainLoop();
	return 0;
}


