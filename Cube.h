#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

float cubeSize = 0.05;

struct point {
	float x, y, z;
	point() {
		x = 0.0; y = 0.0; z = 0.0;
	}
	point(float newX, float newY, float newZ) {
		x = newX; y = newY; z = newZ;
	}
};

struct square {
	vector<point> points; // ojo con points y coordinates, pueden tener valores distintos
	vector<float> coordinates;
	unsigned int color = 0;
	square() {}
	square(point a, point b, point c, point d) {
		points.clear();
		points.push_back(a);
		points.push_back(b);
		points.push_back(c);
		points.push_back(d);
		fillVector();
	}

	void sumX(float num)	{
		for (int i = 0; i < points.size(); i++){
			points[i].x += num;
		}
	}

	void sumY(float num) {
		for (int i = 0; i < points.size(); i++) {
			points[i].y += num;
		}
	}
	void sumZ(float num) {
		for (int i = 0; i < points.size(); i++) {
			points[i].z += num;
		}
	}

	void fillVector() {
		coordinates.clear();
		//cout << "Square " << points.size() << endl;
		for (int i = 0; i < points.size(); i++)
		{
			coordinates.push_back(points[i].x);
			coordinates.push_back(points[i].y);
			coordinates.push_back(points[i].z);
		}
	}
	void setVertex()
	{
		for (int i = 0; i < coordinates.size(); i++)
		{
			vertex.push_back(coordinates[i]);
		}
	}
	void draw()
	{
		bufferArray(coordinates);
		glUseProgram(color);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);

		glLineWidth(2);
		glUseProgram(black);
		glDrawArrays(GL_LINE_LOOP, 0, 4);

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}

	void rotateX(float angle)
	{
		coordinates = rotateRx(coordinates, angle);
	}
	void rotateY(float angle)
	{
		coordinates = rotateRy(coordinates, angle);
	}
	void rotateZ(float angle)
	{
		coordinates = rotateRz(coordinates, angle);
	}

	void rotate(float angleX, float angleY, float angleZ)
	{
		coordinates = rotateR(coordinates, angleX, angleY,angleZ);
	}

};

struct cube {
	vector<square*> squares;
	square* front = new square();
	square* back = new square();
	square* left = new square();
	square* right = new square();
	square* up = new square();
	square* down = new square();

	point A, B, C, D, A1, B1, C1, D1;
	string idCube;

	cube() {}
	cube(square* _front, string _idCube) {
		idCube = _idCube;

		A = (_front->points[0]); //a - 0
		B = (_front->points[1]); //b - 1
		C = (_front->points[2]); //c - 2
		D = (_front->points[3]); //d - 3
		
		A1 = (_front->points[0]);
		(A1.z) -= cubeSize;
		B1 = (_front->points[1]);
		(B1.z) -= cubeSize;
		C1 = (_front->points[2]);
		(C1.z) -= cubeSize;
		D1 = (_front->points[3]);
		(D1.z) -= cubeSize;

		*back = square(A, B, C, D);
		*front = square(A1, B1, C1, D1);
		*left = square(A, A1, D1, D);
		*right = square(B, B1, C1, C);
		*up = square(A1, B1, B, A);
		*down = square(D1, C1, C, D);
		fillVector();
	}
	void sumX(float num) {
		for (int i = 0; i < squares.size(); i++) {
			squares[i]->sumX(num);
		}
	}
	void sumY(float num) {
		for (int i = 0; i < squares.size(); i++) {
			squares[i]->sumY(num);
		}
	}
	void sumZ(float num) {
		for (int i = 0; i < squares.size(); i++) {
			squares[i]->sumZ(num);
		}
	}


	void fillVector() {
		squares.clear();
		squares.push_back(front);
		squares.push_back(back);
		squares.push_back(left);
		squares.push_back(right);
		squares.push_back(up);
		squares.push_back(down);
	}

	void setVertex()
	{
		for (int i = 0; i < squares.size(); i++)
		{
			squares[i]->setVertex();
		}
	}
	void setColors()
	{
		switch (idCube[0])
		{
			case 'F':
				front->color = red;
				back->color = gray;
				break;

			case 'C':
				front->color = gray;
				back->color = gray;
				break;

			case 'B':
				front->color = gray;
				back->color = orange;
				break;

		}
		switch (idCube[1])
		{
			case 'I':
				left->color = green;
				right->color = gray;
				break;

			case 'C':
				left->color = gray;
				right->color = gray;
				break;

			case 'D':
				left->color = gray;
				right->color = blue;
				break;
		}
		switch (idCube[2])
		{
			case 'T':
				up->color = white;
				down->color = gray;
				break;

			case 'C':
				up->color = gray;
				down->color = gray;
				break;

			case 'D':
				up->color = gray;
				down->color = yellow;
				break;
		}
	}
	void draw()	{
		//cout << idCube << endl;
		for (int i = 0; i < squares.size(); i++){
			squares[i]->draw();
		}
	}

	void rotateX(float angle)
	{
		for (int i = 0; i < squares.size(); i++) {
			squares[i]->rotateX(angle);
		}
	}
	void rotateY(float angle)
	{
		for (int i = 0; i < squares.size(); i++) {
			squares[i]->rotateY(angle);
		}
	}
	void rotateZ(float angle)
	{
		for (int i = 0; i < squares.size(); i++) {
			squares[i]->rotateZ(angle);
		}
	}

	void rotate(float angleX, float angleY, float angleZ)
	{
		for (int i = 0; i < squares.size(); i++) {
			squares[i]->rotate(angleX, angleY, angleZ);
		}
	}
};

struct litter {
	vector<cube*> cubes;
	cube* E1 = new cube();
	cube* V1 = new cube();
	cube* E2 = new cube();
	cube* V2 = new cube();
	cube* E3 = new cube();
	cube* V3 = new cube();
	cube* E4 = new cube();
	cube* V4 = new cube();
	cube* CC = new cube();

	square* front = new square();
	litter() {	}

	litter(cube* _CC, string idLitter)
	{
		string idCube = "" + idLitter;
		CC = new cube(_CC->back, idCube + "CC");
		*front = *(CC->back);

		front->sumX(-cubeSize);
		*V4 = cube(front, idCube + "IC");

		front->sumY(cubeSize);
		*E1 = cube(front, idCube + "IT");

		front->sumX(cubeSize);
		*V1 = cube(front, idCube + "CT");

		front->sumX(cubeSize);
		*E2 = cube(front, idCube + "DT");

		front->sumY(-cubeSize);
		*V2 = cube(front, idCube + "DC");

		front->sumY(-cubeSize);
		*E3 = cube(front, idCube + "DD");

		front->sumX(-cubeSize);
		*V3 = cube(front, idCube + "CD");

		front->sumX(-cubeSize);
		*E4 = cube(front, idCube + "ID");

		//reacomodamos el cubo central
		front->sumY(cubeSize);
		front->sumX(cubeSize);
		CC = new cube(_CC->back, idCube + "CC");
		fillVectorCubes();
	}

	void fillVectorCubes() {
		cubes.clear();
		cubes.push_back(E1);
		cubes.push_back(V1);
		cubes.push_back(E2);
		cubes.push_back(V4);
		cubes.push_back(CC);
		cubes.push_back(V2);
		cubes.push_back(E4);
		cubes.push_back(V3);
		cubes.push_back(E3);
	}
	void setVertex()
	{
		for (int i = 0; i < cubes.size(); i++)
		{
			cubes[i]->setVertex();
		}
	}
	void draw()	{		
		for (int i = 0; i < cubes.size(); i++){
			cubes[i]->draw();
		}
	}

	void rotateX(float angle){
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i]->rotateX(angle);
		}
	}
	void rotateY(float angle){
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i]->rotateY(angle);
		}
	}
	void rotateZ(float angle){
		for (int i = 0; i < cubes.size(); i++) {
			cubes[i]->rotateZ(angle);
		}
	}
};

struct rubik {
	vector<cube*> vFront;
	vector<cube*> vBack;
	vector<cube*> vLeft;
	vector<cube*> vRight;
	vector<cube*> vUp;
	vector<cube*> vDown;

	litter* front = new litter();
	litter* center = new litter();
	litter* back = new litter();
	vector<litter*> litters;
	cube* CC = new cube();
	int velocidad = 2; // mayor numero más lento, menor numero más rapido
	int velocity = velocidad;
	bool mess;
	string moves;


	rubik() {}

	rubik(cube* _CC) {
		string idCube = "FCC";
		mess = 1;
		moves = "";
		CC = new cube(_CC->back, idCube);
		front = new litter(CC, "F");
		fillVectorFront();

		idCube = "CCC";
		CC = new cube(_CC->back, idCube);
		CC->sumZ(cubeSize);
		center = new litter(CC, "C");

		idCube = "BCC";
		CC = new cube(_CC->back, idCube);
		CC->sumZ(cubeSize);
		CC->sumZ(cubeSize);
		back = new litter(CC, "B");
		fillVectorBack();

		fillVectorLitters();
		fillVectorOthers();
	}

	void fillVectorFront() {
		vFront.clear();
		for (int i = 0; i < front->cubes.size(); i++){
			vFront.push_back(front->cubes[i]);
		}		
	}
	void fillVectorBack() {
		vBack.clear();
		for (int i = 0; i < back->cubes.size(); i++) {
			vBack.push_back(back->cubes[i]);
		}
	}
	void fillVectorOthers() {
		vLeft.clear();
		for (int j = 0; j < 9; j += 3){
			for (int i = 0; i < litters.size(); i++){
				vLeft.push_back(litters[i]->cubes[j]);
			}
		}
		vRight.clear();
		for (int j = 2 ; j < 9; j += 3)	{
			for (int i = 0; i < litters.size(); i++){
				vRight.push_back(litters[i]->cubes[j]);
			}
		}
		vUp.clear(); 
		for (int i = litters.size()-1; i >= 0; i--)	{
			for (int j = 0; j < 3; j++)	{
				vUp.push_back(litters[i]->cubes[j]);
			}
		}
		vDown.clear();
		for (int i = 0; i < litters.size(); i++){
			for (int j = 6; j < 9; j++)	{
				vDown.push_back(litters[i]->cubes[j]);
			}
		}
	}
	void fillVectorLitters() {
		litters.clear();
		litters.push_back(front);
		litters.push_back(center);
		litters.push_back(back);
	}
	void solver(string solution)
	{		
		mess = 0;
		cout <<endl<< "INPUT: "<< moves << endl;
		cout << "OUTPUT:  " << solution << endl;
		solution = translate(solution);
		//cout << "OUTPUT:  " << solution << endl;

		for (int i = 0; i < solution.length(); i++)
		{
			rotate(solution[i]);
		}
		mess = 1;
		moves = "";
	}

	string translate(string solver) {
		string result = "";
		string tmp = "";
		for (int i = 0; i < solver.length(); i++)
		{
			if (solver[i] == ' ')
			{
				if (tmp.length() < 1) continue;
				if (tmp.length() == 1)
				{
					result += tmp;
				}
				else {
					//if (tmp[1] == "2")
					result += tmp[0];
					result += tmp[0];
					if (tmp[1] == '\'') result += tmp[0];
				}
				tmp = "";
				continue;
			}
			tmp += solver[i];
		}
		return result;
	}

	void disorder(int steps) {
		string movements = "FBLRUD";
		int r;
		for (int i = 0; i < steps; i++)
		{
			r = rand() % 6;
			rotate(movements[r]);
		}
	}

	void rotate(char move) {
		if (mess) {
			moves += move;
			moves += " ";
		}

		switch (move)
		{
		case 'F':
			rotateFF();
			break;
		case 'B':
			rotateBB();
			break;
		case 'U':
			rotateUU();
			break;
		case 'D':
			rotateDD();
			break;
		case 'L':
			rotateLL();
			break;
		case 'R':
			rotateRR();
			break;
		}
	}

	void rotateFF() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateF(angle / velocidad);
			draw();
		}
		reorganizeCubesF();
	}

	void rotateF(float angle)
	{
		for (int i = 0; i < vFront.size(); i++) {
			vFront[i]->rotateZ(-angle);
		}
	}
	//ok
	void reorganizeCubesF(){
		cube* cTemp;
		//Esquinas
		cTemp = vFront[0];
		vFront[0] = vFront[6];
		vFront[6] = vFront[8];
		vFront[8] = vFront[2];
		vFront[2] = cTemp;
		//centros
		cTemp = vFront[1];
		vFront[1] = vFront[3];
		vFront[3] = vFront[7];
		vFront[7] = vFront[5];
		vFront[5] = cTemp;

		//delete cTemp;
		vLeft[0] = vFront[0];//
		vLeft[3] = vFront[3];
		vLeft[6] = vFront[6];

		vRight[0] = vFront[2];//
		vRight[3] = vFront[5];
		vRight[6] = vFront[8];

		vUp[6] = vFront[0];//
		vUp[7] = vFront[1];
		vUp[8] = vFront[2];

		vDown[0] = vFront[6];//
		vDown[1] = vFront[7];
		vDown[2] = vFront[8];
	}
	
	void rotateBB() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateB(angle / velocidad);
			draw();
		}
		reorganizeCubesB();
	}
	void rotateB(float angle)
	{
		for (int i = 0; i < vBack.size(); i++) {
			vBack[i]->rotateZ(angle);
		}
	}
	//ok
	void reorganizeCubesB(){
		cube* cTemp;
		///Reordenar Back
		//Esquinas
		cTemp = vBack[0];
		vBack[0] = vBack[2];
		vBack[2] = vBack[8];
		vBack[8] = vBack[6];
		vBack[6] = cTemp;

		//centros
		cTemp = vBack[1];
		vBack[1] = vBack[5];
		vBack[5] = vBack[7];
		vBack[7] = vBack[3];
		vBack[3] = cTemp;

		///  otras capas
		vLeft[2] = vBack[0];//ok
		vLeft[5] = vBack[3];
		vLeft[8] = vBack[6];

		vRight[2] = vBack[2];//ok
		vRight[5] = vBack[5];
		vRight[8] = vBack[8];

		vUp[0] = vBack[0];//ok
		vUp[1] = vBack[1];
		vUp[2] = vBack[2];

		vDown[6] = vBack[6];//ok
		vDown[7] = vBack[7];
		vDown[8] = vBack[8];
	}
	
	void rotateLL() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateL(angle / velocidad);
			draw();
		}
		reorganizeCubesL();
	}
	void rotateL(float angle)
	{
		for (int i = 0; i < vLeft.size(); i++) {
			vLeft[i]->rotateX(-angle);
		}
	}

	//ok
	void reorganizeCubesL(){
		cube* cTemp;
		//Esquinas
		cTemp = vLeft[0];
		vLeft[0] = vLeft[2];
		vLeft[2] = vLeft[8];
		vLeft[8] = vLeft[6];
		vLeft[6] = cTemp;

		//centros
		cTemp = vLeft[1];
		vLeft[1] = vLeft[5];
		vLeft[5] = vLeft[7];
		vLeft[7] = vLeft[3];
		vLeft[3] = cTemp;


		///  otras capas
		vFront[0] = vLeft[0];//ok
		vFront[3] = vLeft[3];
		vFront[6] = vLeft[6];

		vBack[0] = vLeft[2];//ok
		vBack[3] = vLeft[5];
		vBack[6] = vLeft[8];

		vUp[0] = vLeft[2];//ok
		vUp[3] = vLeft[1];
		vUp[6] = vLeft[0];

		vDown[6] = vLeft[8];//ok
		vDown[3] = vLeft[7];
		vDown[0] = vLeft[6];
	}

	void rotateRR() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateR(angle / velocidad);
			draw();
		}
		reorganizeCubesR();
	}

	void rotateR(float angle)
	{
		for (int i = 0; i < vRight.size(); i++) {
			vRight[i]->rotateX(angle);
		}
	}
	//ok
	void reorganizeCubesR(){
		cube* cTemp;
		//Esquinas
		cTemp = vRight[0];
		vRight[0] = vRight[6];
		vRight[6] = vRight[8];
		vRight[8] = vRight[2];
		vRight[2] = cTemp;
		//centros
		cTemp = vRight[1];
		vRight[1] = vRight[3];
		vRight[3] = vRight[7];
		vRight[7] = vRight[5];
		vRight[5] = cTemp;

		///  otras capas
		vFront[2] = vRight[0];//ok
		vFront[5] = vRight[3];
		vFront[8] = vRight[6];

		vBack[2] = vRight[2];//ok
		vBack[5] = vRight[5];
		vBack[8] = vRight[8];

		vUp[2] = vRight[2];//ok
		vUp[5] = vRight[1];
		vUp[8] = vRight[0];

		vDown[8] = vRight[8];//ok
		vDown[5] = vRight[7];
		vDown[2] = vRight[6];
	}
	
	void rotateUU() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateU(angle / velocidad);
			draw();
		}
		reorganizeCubesU();
	}
	void rotateU(float angle)
	{
		for (int i = 0; i < vUp.size(); i++) {
			vUp[i]->rotateY(angle);
		}
	}
	//ok
	void reorganizeCubesU() {
		cube* cTemp;
		//Esquinas
		cTemp = vUp[0];
		vUp[0] = vUp[6];
		vUp[6] = vUp[8];
		vUp[8] = vUp[2];
		vUp[2] = cTemp;

		//centros
		cTemp = vUp[1];
		vUp[1] = vUp[3];
		vUp[3] = vUp[7];
		vUp[7] = vUp[5];
		vUp[5] = cTemp;

		///  otras capas
		vFront[0] = vUp[6];//ok
		vFront[1] = vUp[7];
		vFront[2] = vUp[8];

		vBack[0] = vUp[0];//ok
		vBack[1] = vUp[1];
		vBack[2] = vUp[2];

		vLeft[0] = vUp[6];//ok
		vLeft[1] = vUp[3];
		vLeft[2] = vUp[0];

		vRight[0] = vUp[8];//ok
		vRight[1] = vUp[5];
		vRight[2] = vUp[2];
	}
	
	void rotateDD() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateD(angle / velocidad);
			draw();
		}
		reorganizeCubesD();
	}
	void rotateD(float angle)
	{
		for (int i = 0; i < vDown.size(); i++) {
			vDown[i]->rotateY(-angle);
		}
	}
	//ok
	void reorganizeCubesD() {
		cube* cTemp;
		//Esquinas
		cTemp = vDown[0];
		vDown[0] = vDown[6];
		vDown[6] = vDown[8];
		vDown[8] = vDown[2];
		vDown[2] = cTemp;

		//centros
		cTemp = vDown[1];
		vDown[1] = vDown[3];
		vDown[3] = vDown[7];
		vDown[7] = vDown[5];
		vDown[5] = cTemp;

		///  otras capas
		vFront[6] = vDown[0];//ok
		vFront[7] = vDown[1];
		vFront[8] = vDown[2];

		vBack[8] = vDown[8];//ok
		vBack[7] = vDown[7];
		vBack[6] = vDown[6];

		vLeft[6] = vDown[0];//ok
		vLeft[7] = vDown[3];
		vLeft[8] = vDown[6];

		vRight[6] = vDown[2];//ok
		vRight[7] = vDown[5];
		vRight[8] = vDown[8];
	}

	void setVertex()
	{
		vertex.clear();

		for (int i = 0; i < litters.size(); i++)
		{
			litters[i]->setVertex();
		}
	}

	void draw()
	{
		/*
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);

		glfwSetKeyCallback(window, key_callback);
				
		glClearColor(0.5f, 0.5f, 0.2f, 1.0f);
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		*/
		for (int i = 0; i < litters.size(); i++){
			
			for (int j = 0; j < litters[i]->cubes.size(); j++)	{
				litters[i]->cubes[j]->setColors();
			}
			litters[i]->draw();
		}/*
		glfwSwapBuffers(window);
		glfwPollEvents();*/
	}

	void rotateX(float angle)
	{
		for (int i = 0; i < litters.size(); i++) {
			litters[i]->rotateX(angle);
		}
	}
	void rotateY(float angle)
	{
		for (int i = 0; i < litters.size(); i++) {
			litters[i]->rotateY(angle);
		}
	}
	void rotateZ(float angle)
	{
		for (int i = 0; i < litters.size(); i++) {
			litters[i]->rotateZ(angle);
		}
	}
	void setColors() {
		for (int i = 0; i < litters.size(); i++) {
			for (int j = 0; j < litters[i]->cubes.size(); j++)
			{
				litters[i]->cubes[j]->setColors();
			}
		}
	}
	void setVelocity(int cant){
		velocity += cant;
		if (velocity == 0){
			velocity = 1;
		}
	}
};

struct SuperLitter {
	vector<rubik*> rubiks;
	rubik* rE1 = new rubik();
	rubik* rV1 = new rubik();
	rubik* rE2 = new rubik();
	rubik* rV2 = new rubik();
	rubik* rE3 = new rubik();
	rubik* rV3 = new rubik();
	rubik* rE4 = new rubik();
	rubik* rV4 = new rubik();
	rubik* rCC = new rubik();

	cube* cCC = new cube();

	square* front = new square();
	SuperLitter() {	}

	SuperLitter(rubik* _CR)
	{
		rCC = new rubik(_CR->CC);
		*front = *(_CR->CC->front);

		front->sumX(-cubeSize*3);
		*cCC = cube(front, "CCC");
		*rV4 = rubik(cCC);

		front->sumY(cubeSize*3);
		*cCC = cube(front, "CCC");
		*rE1 = rubik(cCC);

		front->sumX(cubeSize*3);
		*cCC = cube(front, "CCC");
		*rV1 = rubik(cCC);

		front->sumX(cubeSize*3);
		*cCC = cube(front, "CCC");
		*rE2 = rubik(cCC);

		front->sumY(-cubeSize*3);
		*cCC = cube(front, "CCC");
		*rV2 = rubik(cCC);

		front->sumY(-cubeSize*3);
		*cCC = cube(front, "CCC");
		*rE3 = rubik(cCC);

		front->sumX(-cubeSize*3);
		*cCC = cube(front, "CCC");
		*rV3 = rubik(cCC);

		front->sumX(-cubeSize*3);
		*cCC = cube(front, "CCC");
		*rE4 = rubik(cCC);

		//reacomodamos el cubo central
		front->sumY(cubeSize*3);
		front->sumX(cubeSize*3);
		*cCC = cube(front, "CCC");
		rCC = new rubik(cCC);
		fillVectorRubiks();
	}

	void fillVectorRubiks() {
		rubiks.clear();
		rubiks.push_back(rE1);
		rubiks.push_back(rV1);
		rubiks.push_back(rE2);
		rubiks.push_back(rV4);
		rubiks.push_back(rCC);
		rubiks.push_back(rV2);
		rubiks.push_back(rE4);
		rubiks.push_back(rV3);
		rubiks.push_back(rE3);
	}
	void setVertex()
	{
		for (int i = 0; i < rubiks.size(); i++)
		{
			rubiks[i]->setVertex();
		}
	}
	void draw() {
		int limit = rubiks.size();
		//limit = 4;
		for (int i = 0; i < limit; i++) {
			rubiks[i]->draw();
		}
	}
	void rotateX(float angle) {
		for (int i = 0; i < rubiks.size(); i++) {
			rubiks[i]->rotateX(angle);
		}
	}
	void rotateY(float angle) {
		for (int i = 0; i < rubiks.size(); i++) {
			rubiks[i]->rotateY(angle);
		}
	}
	void rotateZ(float angle) {
		for (int i = 0; i < rubiks.size(); i++) {
			rubiks[i]->rotateZ(angle);
		}
	}
};
struct SuperRubik {
	vector<rubik*> vFront;
	vector<rubik*> vBack;
	vector<rubik*> vLeft;
	vector<rubik*> vRight;
	vector<rubik*> vUp;
	vector<rubik*> vDown;

	vector<SuperLitter*> sLitters;
	rubik* rCC = new rubik();
	int velocidad = 2; // mayor numero más lento, menor numero más rapido
	int velocity = velocidad;
	bool mess;
	string moves;

	SuperLitter* front = new SuperLitter();
	SuperLitter* center = new SuperLitter();
	SuperLitter* back = new SuperLitter();

	SuperRubik() {};

	SuperRubik(rubik* _CC) {
		mess = 1;
		moves = "";
		rCC = new rubik(_CC->CC);
		back = new SuperLitter(rCC);
		fillVectorBack();			

		rCC = new rubik(_CC->CC);
		rCC->CC->sumZ(-cubeSize*3);
		center = new SuperLitter(rCC);

		rCC = new rubik(_CC->CC);
		rCC->CC->sumZ(-cubeSize*3);
		rCC->CC->sumZ(-cubeSize*3);
		front = new SuperLitter(rCC);
		fillVectorFront();

		fillVectorLitters();
		fillVectorOthers();
	}

	void fillVectorFront() {
		vFront.clear();
		for (int i = 0; i < front->rubiks.size(); i++) {
			vFront.push_back(front->rubiks[i]);
		}
	}
	void fillVectorBack() {
		vBack.clear();
		for (int i = 0; i < back->rubiks.size(); i++) {
			vBack.push_back(back->rubiks[i]);
		}
	}
	void fillVectorOthers() {
		vLeft.clear();
		for (int j = 0; j < 9; j += 3) {
			for (int i = 0; i < sLitters.size(); i++) {
				vLeft.push_back(sLitters[i]->rubiks[j]);
			}
		}
		vRight.clear();
		for (int j = 2; j < 9; j += 3) {
			for (int i = 0; i < sLitters.size(); i++) {
				vRight.push_back(sLitters[i]->rubiks[j]);
			}
		}
		vUp.clear();
		for (int i = sLitters.size() - 1; i >= 0; i--) {
			for (int j = 0; j < 3; j++) {
				vUp.push_back(sLitters[i]->rubiks[j]);
			}
		}
		vDown.clear();
		for (int i = 0; i < sLitters.size(); i++) {
			for (int j = 6; j < 9; j++) {
				vDown.push_back(sLitters[i]->rubiks[j]);
			}
		}
	}
	void fillVectorLitters() {
		sLitters.clear();
		sLitters.push_back(front);
		sLitters.push_back(center);
		sLitters.push_back(back);
	}
	void solver(string solution)
	{
		for (int i = 0; i < sLitters.size(); i++) {

			for (int j = 0; j < sLitters[i]->rubiks.size(); j++) {
				string moves = sLitters[i]->rubiks[j]->moves;
				string solution;
				solution = rubikS::solve(moves);
				sLitters[i]->rubiks[j]->solver(solution);
			}
		}

		mess = 0;
		cout << endl << "INPUT: " << moves << endl;
		cout << "OUTPUT:  " << solution << endl;
		solution = translate(solution);
		//cout << "OUTPUT:  " << solution << endl;

		for (int i = 0; i < solution.length(); i++)
		{
			rotate(solution[i]);
		}
		mess = 1;
		moves = "";
	}

	string translate(string solver) {
		string result = "";
		string tmp = "";
		for (int i = 0; i < solver.length(); i++)
		{
			if (solver[i] == ' ')
			{
				if (tmp.length() < 1) continue;
				if (tmp.length() == 1)
				{
					result += tmp;
				}
				else {
					//if (tmp[1] == "2")
					result += tmp[0];
					result += tmp[0];
					if (tmp[1] == '\'') result += tmp[0];
				}
				tmp = "";
				continue;
			}
			tmp += solver[i];
		}
		return result;
	}

	void rotate(char move) {
		if (mess) {
			moves += move;
			moves += " ";
		}

		switch (move)
		{
		case 'F':
			rotateFF();
			break;
		case 'B':
			rotateBB();
			break;
		case 'U':
			rotateUU();
			break;
		case 'D':
			rotateDD();
			break;
		case 'L':
			rotateLL();
			break;
		case 'R':
			rotateRR();
			break;
		}
	}

	void rotateFF() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateF(angle / velocidad);
			draw();
		}
		reorganizeCubesF();
	}
	void rotateF(float angle)
	{
		for (int i = 0; i < vFront.size(); i++) {
			vFront[i]->rotateZ(-angle);
		}
	}
	void reorganizeCubesF() {
		rubik* cTemp;
		//Esquinas
		cTemp = vFront[0];
		vFront[0] = vFront[6];
		vFront[6] = vFront[8];
		vFront[8] = vFront[2];
		vFront[2] = cTemp;
		//centros
		cTemp = vFront[1];
		vFront[1] = vFront[3];
		vFront[3] = vFront[7];
		vFront[7] = vFront[5];
		vFront[5] = cTemp;

		//delete cTemp;
		vLeft[0] = vFront[0];//
		vLeft[3] = vFront[3];
		vLeft[6] = vFront[6];

		vRight[0] = vFront[2];//
		vRight[3] = vFront[5];
		vRight[6] = vFront[8];

		vUp[6] = vFront[0];//
		vUp[7] = vFront[1];
		vUp[8] = vFront[2];

		vDown[0] = vFront[6];//
		vDown[1] = vFront[7];
		vDown[2] = vFront[8];
	}

	void rotateBB() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateB(angle / velocidad);
			draw();
		}
		reorganizeCubesB();
	}
	void rotateB(float angle)
	{
		for (int i = 0; i < vBack.size(); i++) {
			vBack[i]->rotateZ(angle);
		}
	}
	void reorganizeCubesB() {
		rubik* cTemp;
		///Reordenar Back
		//Esquinas
		cTemp = vBack[0];
		vBack[0] = vBack[2];
		vBack[2] = vBack[8];
		vBack[8] = vBack[6];
		vBack[6] = cTemp;

		//centros
		cTemp = vBack[1];
		vBack[1] = vBack[5];
		vBack[5] = vBack[7];
		vBack[7] = vBack[3];
		vBack[3] = cTemp;

		///  otras capas
		vLeft[2] = vBack[0];//ok
		vLeft[5] = vBack[3];
		vLeft[8] = vBack[6];

		vRight[2] = vBack[2];//ok
		vRight[5] = vBack[5];
		vRight[8] = vBack[8];

		vUp[0] = vBack[0];//ok
		vUp[1] = vBack[1];
		vUp[2] = vBack[2];

		vDown[6] = vBack[6];//ok
		vDown[7] = vBack[7];
		vDown[8] = vBack[8];
	}

	void rotateLL() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateL(angle / velocidad);
			draw();
		}
		reorganizeCubesL();
	}
	void rotateL(float angle)
	{
		for (int i = 0; i < vLeft.size(); i++) {
			vLeft[i]->rotateX(-angle);
		}
	}
	void reorganizeCubesL() {
		rubik* cTemp;
		//Esquinas
		cTemp = vLeft[0];
		vLeft[0] = vLeft[2];
		vLeft[2] = vLeft[8];
		vLeft[8] = vLeft[6];
		vLeft[6] = cTemp;

		//centros
		cTemp = vLeft[1];
		vLeft[1] = vLeft[5];
		vLeft[5] = vLeft[7];
		vLeft[7] = vLeft[3];
		vLeft[3] = cTemp;


		///  otras capas
		vFront[0] = vLeft[0];//ok
		vFront[3] = vLeft[3];
		vFront[6] = vLeft[6];

		vBack[0] = vLeft[2];//ok
		vBack[3] = vLeft[5];
		vBack[6] = vLeft[8];

		vUp[0] = vLeft[2];//ok
		vUp[3] = vLeft[1];
		vUp[6] = vLeft[0];

		vDown[6] = vLeft[8];//ok
		vDown[3] = vLeft[7];
		vDown[0] = vLeft[6];
	}

	void rotateRR() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateR(angle / velocidad);
			draw();
		}
		reorganizeCubesR();
	}
	void rotateR(float angle)
	{
		for (int i = 0; i < vRight.size(); i++) {
			vRight[i]->rotateX(angle);
		}
	}
	void reorganizeCubesR() {
		rubik* cTemp;
		//Esquinas
		cTemp = vRight[0];
		vRight[0] = vRight[6];
		vRight[6] = vRight[8];
		vRight[8] = vRight[2];
		vRight[2] = cTemp;
		//centros
		cTemp = vRight[1];
		vRight[1] = vRight[3];
		vRight[3] = vRight[7];
		vRight[7] = vRight[5];
		vRight[5] = cTemp;

		///  otras capas
		vFront[2] = vRight[0];//ok
		vFront[5] = vRight[3];
		vFront[8] = vRight[6];

		vBack[2] = vRight[2];//ok
		vBack[5] = vRight[5];
		vBack[8] = vRight[8];

		vUp[2] = vRight[2];//ok
		vUp[5] = vRight[1];
		vUp[8] = vRight[0];

		vDown[8] = vRight[8];//ok
		vDown[5] = vRight[7];
		vDown[2] = vRight[6];
	}

	void rotateUU() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateU(angle / velocidad);
			draw();
		}
		reorganizeCubesU();
	}
	void rotateU(float angle)
	{
		for (int i = 0; i < vUp.size(); i++) {
			vUp[i]->rotateY(angle);
		}
	}
	void reorganizeCubesU() {
		rubik* cTemp;
		//Esquinas
		cTemp = vUp[0];
		vUp[0] = vUp[6];
		vUp[6] = vUp[8];
		vUp[8] = vUp[2];
		vUp[2] = cTemp;

		//centros
		cTemp = vUp[1];
		vUp[1] = vUp[3];
		vUp[3] = vUp[7];
		vUp[7] = vUp[5];
		vUp[5] = cTemp;

		///  otras capas
		vFront[0] = vUp[6];//ok
		vFront[1] = vUp[7];
		vFront[2] = vUp[8];

		vBack[0] = vUp[0];//ok
		vBack[1] = vUp[1];
		vBack[2] = vUp[2];

		vLeft[0] = vUp[6];//ok
		vLeft[1] = vUp[3];
		vLeft[2] = vUp[0];

		vRight[0] = vUp[8];//ok
		vRight[1] = vUp[5];
		vRight[2] = vUp[2];
	}

	void rotateDD() {
		float angle = 90;
		velocidad = velocity;
		for (int i = 0; i < velocidad; i++) {
			rotateD(angle / velocidad);
			draw();
		}
		reorganizeCubesD();
	}
	void rotateD(float angle)
	{
		for (int i = 0; i < vDown.size(); i++) {
			vDown[i]->rotateY(-angle);
		}
	}
	void reorganizeCubesD() {
		rubik* cTemp;
		//Esquinas
		cTemp = vDown[0];
		vDown[0] = vDown[6];
		vDown[6] = vDown[8];
		vDown[8] = vDown[2];
		vDown[2] = cTemp;

		//centros
		cTemp = vDown[1];
		vDown[1] = vDown[3];
		vDown[3] = vDown[7];
		vDown[7] = vDown[5];
		vDown[5] = cTemp;

		///  otras capas
		vFront[6] = vDown[0];//ok
		vFront[7] = vDown[1];
		vFront[8] = vDown[2];

		vBack[8] = vDown[8];//ok
		vBack[7] = vDown[7];
		vBack[6] = vDown[6];

		vLeft[6] = vDown[0];//ok
		vLeft[7] = vDown[3];
		vLeft[8] = vDown[6];

		vRight[6] = vDown[2];//ok
		vRight[7] = vDown[5];
		vRight[8] = vDown[8];
	}

	void setVertex()
	{
		vertex.clear();

		for (int i = 0; i < sLitters.size(); i++)
		{
			sLitters[i]->setVertex();
		}
	}

	void draw()
	{

		// Habilidad el test de profundidad
		glEnable(GL_DEPTH_TEST);
		// Aceptar el fragmento si está más cerca de la cámara que el fragmento anterior
		glDepthFunc(GL_LESS);

		glfwSetKeyCallback(window, key_callback);
		// render
		// ------
		//Color pantalla
		glClearColor(0.5f, 0.5f, 0.2f, 1.0f);
		// Limpiar la ventana
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		int limit = sLitters.size();
		
		for (int i = 0; i < limit; i++) {
			for (int j = 0; j < sLitters[i]->rubiks.size(); j++) {
				sLitters[i]->rubiks[j]->setColors();
			}
			sLitters[i]->draw();
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	void rotateX(float angle)
	{
		for (int i = 0; i < sLitters.size(); i++) {
			sLitters[i]->rotateX(angle);
		}
	}
	void rotateY(float angle)
	{
		for (int i = 0; i < sLitters.size(); i++) {
			sLitters[i]->rotateY(angle);
		}
	}
	void setColors() {
		for (int i = 0; i < sLitters.size(); i++) {
			for (int j = 0; j < sLitters[i]->rubiks.size(); j++)
			{
				sLitters[i]->rubiks[j]->setColors();
			}
		}
	}

	void setVelocity(int cant) {
		velocity += cant;
		if (velocity == 0) {
			velocity = 1;
		}
	}
	void disorder(int steps) {

		int limit = sLitters.size();
		//limit = 1;
		for (int i = 0; i < limit; i++) {

			for (int j = 0; j < sLitters[i]->rubiks.size(); j++) {
				sLitters[i]->rubiks[j]->disorder(steps);
			}
		}
		/*
		srand(time(NULL));
		string movements = "FBLRUD";
		int r;
		for (int i = 0; i < steps; i++)
		{
			r = rand() % 6;
			rotate(movements[r]);
		}*/
	}
};
