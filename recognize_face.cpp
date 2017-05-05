
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/contrib/contrib.hpp>
#include<stdio.h>
#include<iostream>
#include<fstream>
#include<unistd.h>
#include <sstream>

using namespace std;
using namespace cv;


vector<Mat> images;
vector<int> labels;
void poll();
void recognize_face(Mat);
/*

static Mat normat(InputArray a)
{
	Mat src=a.getMat();
	Mat	 dst;

	switch(src.channels()){

	case 1: cv::normalize(a,dst,0,255,NORM_MINMAX,CV_8UC1);break;

	case 3: cv::normalize(a,dst,0,255,NORM_MINMAX,CV_8UC3);break;

	default:src.copyTo(dst);break;


	}
	return dst;
}*/
void readcsv(string path)
{
	char delimeter=';';
	string line,classpath,label;
	ifstream csv_file(path.c_str(),ifstream::in);
	if(!csv_file)
	{
		cout<<"csv file not found";
		exit(0);
	}
	else
	{
		while(getline(csv_file,line))
		{
			stringstream parse(line);
			getline(parse,classpath,delimeter);
			getline(parse,label);
			if(!label.empty() && !classpath.empty())
			{

				images.push_back(imread(classpath,0));
				labels.push_back(atoi(label.c_str()));
			}


		}



	}
}





int main()
{
	

	poll();

waitKey(0);

return 0;
}

void recognize_face(Mat orig)
{
	int predictlabel=0,height,testlabel=1;
	Mat testimage, eigenvalues, eigenvectors, mean,eface,cgrayscale,gray;
	string result_message;
	Ptr<FaceRecognizer> model = createEigenFaceRecognizer(10);
	model->train(images,labels);
	predictlabel=model->predict(orig);
	eigenvectors=model->getMat("eigenvectors");
	eigenvalues=model->getMat("eigenvalues");
	mean=model->getMat("mean");
	cout<<endl<<"Eigenvectors=" <<eigenvectors.rows<<"  "<<eigenvectors.cols<<endl;
	cout<<endl<<"Eigenvalues=" <<eigenvalues.rows<<"  "<<eigenvalues.cols<<endl;
	cout<<endl<<"mean=" <<mean.rows<<"  "<<mean.cols<<endl;
	height=images[0].rows;
	result_message = format("Predicted class = %d / Actual class = %d.",predictlabel, testlabel);
	ofstream filestream ;
	filestream.open("/home/jeetkanjani7/prediction.txt");
	
    
    //String filename = "/home/jeetkanjani7/" + filestream.str();
    
    filestream<<predictlabel;
    filestream.close();
    system("/home/jeetkanjani7/sftp.sh");
	cout<<result_message;
	poll();
}
void poll()
{
	String path_csv="/home/jeetkanjani7/Study/opencv_res/labels.txt";
	ifstream myfile ("/home/jeetkanjani7/recognition.png");

    if(myfile.is_open())
    {
		system("/home/jeetkanjani7/Study/opencv_res/test/remove.sh");
	}
	try
	{
		readcsv(path_csv);
	}
	catch (Exception e) {
		cout<<e.msg;
	}
	Mat orig;
	while(1)
	{
		usleep(1000000);
		orig=imread("/home/jeetkanjani7/recognition.png",0);

		if(orig.empty())
		{
			continue;
		}
		else
		{
			recognize_face(orig);
			break;
		}
	}
}