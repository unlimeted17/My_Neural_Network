#include "NetWork.h"
#include <iostream>
#include <utility>
#include <cmath>
#include <fstream>
#include <string> 

NetWork::NetWork() : Layers(2), CountInputVector(6), CountNeurons(3)
{
	actFunc.set();
	Init();
}

std::pair<double, int>  Max(double* massive, int size)
{
	double a_max = 0;
	std::pair<double, int> res;
	for (int i = 0; i < size; ++i)
	{
		if (a_max < massive[i]) {
			a_max = massive[i];
			res = { a_max, i };
		}
	}
	
	return res;
}

int ParserLine(std::string& str)
{
	std::string number;
	size_t begin = str.find_first_of("0123456789");
	size_t end = str.find_last_of("0123456789");
	number = str.substr(begin, end - begin + 1);
	int result = atoi(number.c_str());
	std::cout << result << std::endl;

	return result;
}

int NetWork::Init()
{

	std::string line;
	int a = 0, b = 0, c = 0, d =0;

	std::ifstream in("Data.txt"); // окрываем файл для чтения
	if (in.is_open())
	{

		  std::getline(in, line);

		      std::cout << line << std::endl;
		CountInputVector = ParserLine(line);
		

	//	std::cout << "a: " << a << " b: " << b << std::endl;
	//	in >> a >> b;

	//	std::cout << "a: " << a << " b: " << b << std::endl;*/

	}
	in.close();     // закрываем файл

	std::ifstream icon("Config.txt");
	if (icon.is_open())
	{
		std::getline(icon, line);
		std::cout << line << std::endl;
		Layers = ParserLine(line);
	//	ParserLine(line);
	}

	
	int CountNeuron = 0;
	layers = new Layer[Layers];
	for (int i = 0; i < Layers; ++i) {
		
		std::getline(icon, line);
		std::cout << line << std::endl;
		CountNeuron = ParserLine(line);
		if (i == 0) {
			layers[i].matrix.Init(CountNeuron, CountInputVector);
			layers[i].values = new double[CountNeuron];
		}
		else {
			layers[i].matrix.Init(CountNeuron, layers[i-1].matrix.row);
			layers[i].values = new double[CountNeuron];
		}
	}

	return 0;
}

void NetWork::FeedForward()
{

	//double inputVector[6] = {12, 25.3, 15.4, 22, 9, 11};
//	Matrix matrix, matrix1;

	double tmp = 0;

//	matrix.Init(3, 6);
//	Outvector = new double[3];
	// Здесь проверка на сопоставление матриц



	for (int l = 0; l < Layers; ++l) {
		for (int n = 0; n < layers[l].matrix.row; ++n) {
			tmp = 0;
			for (int w = 0; w < layers[l].matrix.col; ++w) {
				if (l == 0)
					tmp += layers[l].matrix.matrix[n][w] * inputVector[w]; // Это спросить у Лехи
				else
					tmp += layers[l].matrix.matrix[n][w] * layers[l-1].values[w];
			}
			tmp += layers[l].matrix.bios[n];
			layers[l].values[n] = tmp;


		}
		actFunc.use(layers[l].values, layers[l].matrix.row);
	}

	/*
	for (int i = 0; i < 3; ++i)
	{
		tmp = 0;
		for (int j = 0; j < 6; ++j)
		{
			tmp += layers[i].matrix.matrix[i][j] * inputVector[j]; // Это спросить у Лехи
		}
		tmp += layers[i].matrix.bios[i];
		
		layers[i].values[i] = tmp;
	}
	actFunc.use(layers[0].values, 3);
	for (int p = 0; p < 3; ++p) {
		std::cout << layers[0].values[p] << std::endl;
	}
	
	double result[3];
	matrix1.Init(3, 3);
	
		for (int i = 0; i < 24; ++i)
		{
			tmp = 0;
			for (int j = 0; j < 3; ++j)
			{
				tmp += layers[0].values[j] * layers[1].matrix.matrix[i][j];
			}
			tmp += layers[1].matrix.bios[i];
			layers[1].values[i] = tmp;
		}
		*/

	//	actFunc.use(layers[1].values, 24);
		for (int i = 0; i < layers[Layers-1].matrix.row; ++i)
		{
			std::cout << "Result: " << layers[Layers-1].values[i] ;
			std::cout << " Err: " << ErrorVector[i] << " ";
			std::cout << " ErrR: " << layers[Layers - 1].values[i] -ErrorVector[i] << " " << std::endl;
		}
		
		std::pair<double, int> max = Max(layers[Layers-1].values, layers[Layers-1].matrix.row);
		std::cout << "Max Values: " << max.first << " Number: " << max.second << std::endl;


		/*
		double* Error = new double[24];
		for (int l = 0; l < 24; ++l) {
			if (l == max.second)
				Error[l] =	(pow((layers[1].values[l] - 1), 2)/2) * actFunc.useDer(layers[1].values[l]);
		}
		delete[] Error; */

			/*
		for (int i = 0; i < 24; ++i) {
			layers[1].values[i]
		}*/


			
	 
	delete [] Outvector;

//	return 0;
}

void NetWork::BackPropogation()
{
		for (int j = Layers; j > 0; --j) {
			layers[j - 1].Error = new double[layers[j - 1].matrix.row];
		}

	//	for (int j = Layers; j > 0; --j) {
		std::cout << "Error output layers: ";
			for (int e = 0; e < layers[Layers - 1].matrix.row; ++e) {
				std::cout << " Pow: " << (pow((layers[Layers - 1].values[e] - ErrorVector[e]), 2)) / 2;
				layers[Layers - 1].Error[e] = (pow((layers[Layers-1].values[e] - ErrorVector[e]), 2) / 2) * actFunc.useDer(layers[Layers -1].values[e]);
				
				std::cout  << layers[Layers - 1].Error[e] << " ";
			}
			std::cout << "\n";

			for (int j = Layers-1; j > 0; --j) {
				//for (int e = 0; e < layers[j - 1].matrix.row; ++e) {
				Multi_T(layers[j].Error, j);	
				WeightsUpdater(2, j);
			}

			

			

		//}

		
	
}

void NetWork::Multi_T(double *error, int Number_L)
{
	//for (int l = Layers; l > 0; --l) {
		for (int i = 0; i < layers[Number_L].matrix.col; ++i) {
			double tmp = 0;
			for (int j = 0; j < layers[Number_L].matrix.row; ++j) {
				tmp = layers[Number_L].matrix.matrix[i][j] * error[j];
				layers[Number_L-1].Error[i] += tmp;
			}
			
		}
		std::cout << "Error hide layers: ";
		for (int e = 0; e < layers[Number_L - 1].matrix.row; ++e) {
			layers[Number_L - 1].Error[e] *= actFunc.useDer(layers[Number_L - 1].values[e]);
			std::cout  << layers[Number_L - 1].Error[e] << " ";
		}
		std::cout << "\n";
	//}
}

int NetWork::Work()
{
	std::string line;
	std::ifstream in("Data.txt"); // окрываем файл для чтения
	std::ifstream sin("Standart.txt");
	if (in.is_open() && sin.is_open())
	{
		int epoch = 20;
		for (int i = 0; i < epoch; ++i) {
			std::getline(in, line);

			std::cout << line << std::endl;
			if (i == 0)
			CountInputVector = ParserLine(line);

			inputVector = new double[CountInputVector];
			for (int i = 0; i < CountInputVector; ++i)
			{
				in >> inputVector[i];
			}

			for (int i = 0; i < CountInputVector; ++i)
			{
				std::cout << inputVector[i] << " ";
			}
			std::cout << "\n";

			//	std::string line;
			ErrorVector = new double[layers[Layers - 1].matrix.row];

			for (int i = 0; i < layers[Layers - 1].matrix.row; ++i)
			{
				sin >> ErrorVector[i];
			}
			for (int i = 0; i < layers[Layers - 1].matrix.row; ++i)
			{
				std::cout << ErrorVector[i] << " ";
			}
			std::cout << "\n";



			FeedForward();
			BackPropogation();

			for (int j = 0; j < Layers; ++j) {
				delete[] layers[j].Error;
				//		delete[] layers[1].values;
			}

			delete[] inputVector;
			delete[] ErrorVector;
			inputVector = nullptr;
			ErrorVector = nullptr;

		}
		

	}
	in.close();     // закрываем файл   
	sin.close();
	
	return 0;
}

void NetWork::WeightsUpdater(double lr, int Number_L)
{
	//for (int l = Layers; l > 0; --l) {
	if (Number_L > 0) {
		for (int i = 0; i < layers[Number_L].matrix.row; ++i) {
			for (int j = 0; j < layers[Number_L].matrix.col; ++j)
			{
				layers[Number_L].matrix.matrix[i][j] = layers[Number_L].matrix.matrix[i][j]- layers[Number_L - 1].values[j] * layers[Number_L].Error[i] * lr;
			}
			layers[Number_L].matrix.bios[i] = layers[Number_L].matrix.bios[i] - layers[Number_L].Error[i] * lr;
		}
	}
	else
	{
		for (int i = 0; i < layers[Number_L].matrix.row; ++i) {
			for (int j = 0; j < layers[Number_L].matrix.col; ++j)
			{
				layers[Number_L].matrix.matrix[i][j] = layers[Number_L].matrix.matrix[i][j] - inputVector[j] * layers[Number_L].Error[i] * lr;
			}
			layers[Number_L].matrix.bios[i] = layers[Number_L].matrix.bios[i] - layers[Number_L].Error[i] * lr;
		}
	}


		
	//}
}
    

NetWork::~NetWork()
{
	if (layers != nullptr) {
		for (int j = 0; j < Layers; ++j) {
			delete[] layers[j].values;
			//delete[] layers[j].Error;
			//		delete[] layers[1].values;
		}
		delete[] layers;
	}
}
