vector<float>  MultMatrizVector(float MatrizA[][N], vector<float> vectorB)
{
	float temp;
	vector<float> resultado;
	for (int i = 0; i < N; i++)
	{

		for (int k = 0; k < vectorB.size() / N; k++)
		{
			temp = 0;
			for (int j = 0; j < N; j++)
			{
				temp += MatrizA[i][j] * vectorB[(N * k) + j];
				//cout << MatrizA[i][j] << "  *  " << vectorB[(N * k) + j]<<" = " ;
			}
			resultado.push_back(temp);
			//cout << temp << "  " ;
		}
		//cout << endl;
	}
	return resultado;
};

vector<float> HomogeneousCoord(vector<float> vectorA)
{
	vector<float> resultado;
	for (int i = 1; i <= vectorA.size(); i++) {

		resultado.push_back(vectorA[i - 1]);
		if (i % 3 == 0)
		{
			resultado.push_back(1);
		}
	}
	return resultado;
};

vector<float> resizeCoord(vector<float> vectorA)
{
	vector<float> resultado;
	//cout <<"vector size  "<< vectorA.size() / N << endl;
	int temp = vectorA.size() / N;
	for (int i = 0; i < vectorA.size() / N; i++) {

		resultado.push_back(vectorA[i]);
		resultado.push_back(vectorA[i + temp]);
		resultado.push_back(vectorA[i + temp * 2]);
		
	}

	return resultado;
};

vector<float> rotateRx(vector<float> coordenadas, float angulo) {

	float rad = pi * angulo / 180;
	float Rx[N][N] = { {1,0,0,0},
								{0,cos(rad),-sin(rad),0},
								{0,sin(rad),cos(rad),0},
								{0,0,0,1} };

	vector<float> vertices;
	vertices = HomogeneousCoord(coordenadas);
	vertices = MultMatrizVector(Rx, vertices);
	coordenadas.clear();
	coordenadas = resizeCoord(vertices);
	return coordenadas;
}

vector<float> rotateRy(vector<float> coordenadas, float angulo) {

	float rad = pi * angulo / 180;
	float Ry[N][N] = { {cos(rad),0,sin(rad),0},
								{0,1,0,0},
								{-sin(rad),0,cos(rad),0},
								{0,0,0,1} };

	vector<float> vertices;
	vertices = HomogeneousCoord(coordenadas);
	vertices = MultMatrizVector(Ry, vertices);
	coordenadas.clear();
	coordenadas = resizeCoord(vertices);
	return coordenadas;
}

vector<float> rotateRz(vector<float> coordenadas, float angulo) {

	float rad = pi * angulo / 180;
	float Rz[N][N] = { {cos(rad),-sin(rad),0,0},
							{sin(rad),cos(rad),0,0},
							{0,0,1,0},
							{0,0,0,1} };

	vector<float> vertices;
	vertices = HomogeneousCoord(coordenadas);
	vertices = MultMatrizVector(Rz, vertices);
	coordenadas.clear();
	coordenadas = resizeCoord(vertices);
	return coordenadas;
}

vector<float> rotateR(vector<float> coordenadas, float anguloX, float anguloY, float anguloZ) {

	coordenadas = rotateRx(coordenadas, anguloX);
	coordenadas = rotateRx(coordenadas, anguloY);
	coordenadas = rotateRx(coordenadas, anguloZ);
	return coordenadas;
}
