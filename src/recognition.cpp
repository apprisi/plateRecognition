#include "recognition.h"
#include <iostream>
#include <opencv2/imgproc.hpp>
using namespace std;
using namespace cv;

vector<int> getMaxClass(dnn::Blob &probBlob){
	vector<int>plateNumberIndex(7);
	Mat probMat = probBlob.matRefConst().reshape(1, 7); 
	Point classNumber;
	for (int i = 0; i < 7; i++){
		minMaxLoc(probMat.rowRange(i, i + 1).clone(), NULL, NULL, NULL, &classNumber);
		plateNumberIndex[i] = classNumber.x;
	}
	return plateNumberIndex;
}

vector<int> myCaffePredict(vector<Mat>& plateNumber, dnn::Net& net){

	dnn::Blob inputBlob = dnn::Blob(plateNumber);
	net.setBlob(".data", inputBlob);
	net.forward();
	dnn::Blob prob = net.getBlob("prob");
	vector<int> classId;
	classId = getMaxClass(prob);
	return classId;
}

void plateRecognition(vector<Mat>& plateNumber, dnn::Net& net){

	vector<int> label;
	label = myCaffePredict(plateNumber, net);
	string plate;
	for (int i = 0; i < 7; i++){
		string fhz;
		switch (label[i])
		{
		case 0: fhz = "0"; break; case 1: fhz = "1"; break; case 2: fhz = "2"; break; case 3: fhz = "3"; break;
		case 4: fhz = "4"; break; case 5: fhz = "5"; break; case 6: fhz = "6"; break; case 7: fhz = "7"; break;
		case 8: fhz = "8"; break; case 9: fhz = "9"; break; case 10: fhz = "A"; break; case 11: fhz = "B"; break;
		case 12: fhz = "C"; break; case 13: fhz = "D"; break; case 14: fhz = "E"; break; case 15: fhz = "F"; break;
		case 16: fhz = "G"; break; case 17: fhz = "H"; break; case 18: fhz = "J"; break; case 19: fhz = "K"; break;
		case 20: fhz = "L"; break; case 21: fhz = "M"; break; case 22: fhz = "N"; break; case 23: fhz = "P"; break;
		case 24: fhz = "Q"; break; case 25: fhz = "R"; break; case 26: fhz = "S"; break; case 27: fhz = "T"; break;
		case 28: fhz = "U"; break; case 29: fhz = "V"; break; case 30: fhz = "W"; break; case 31: fhz = "X"; break;
		case 32: fhz = "Y"; break; case 33: fhz = "Z"; break; case 34: fhz = "��"; break; case 35: fhz = "��"; break;
		case 36: fhz = "��"; break; case 37: fhz = "��"; break; case 38: fhz = "��"; break; case 39: fhz = "��"; break;
		case 40: fhz = "��"; break; case 41: fhz = "��"; break; case 42: fhz = "��"; break; case 43: fhz = "��"; break;
		case 44: fhz = "��"; break; case 45: fhz = "��"; break; case 46: fhz = "��"; break; case 47: fhz = "³"; break;
		case 48: fhz = "��"; break; case 49: fhz = "��"; break; case 50: fhz = "��"; break; case 51: fhz = "��"; break;
		case 52: fhz = "��"; break; case 53: fhz = "��"; break; case 54: fhz = "��"; break; case 55: fhz = "��"; break;
		case 56: fhz = "��"; break; case 57: fhz = "��"; break; case 58: fhz = "��"; break; case 59: fhz = "ԥ"; break;
		case 60: fhz = "��"; break; case 61: fhz = "��"; break; case 62: fhz = "��"; break; case 63: fhz = "��"; break;
		case 64: fhz = "��"; break;
		}
		plate += fhz;
	}
	cout << plate << endl;
}
