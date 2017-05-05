#include "time.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/opencv.hpp"
#include "stdio.h"
#include "fstream"
#include "iostream"
#include "stdlib.h"
#include "opencv2/core/utility.hpp"
#include "unistd.h"
#include "opencv2/imgcodecs.hpp"

void pollgpio();
void detection();
using namespace std;
using namespace cv;

timespec ts_beg, ts_end;
int main()
{
    
    int i;
    pollgpio();
    return 0;
}

void pollgpio()
{
        int i=1,flag=-1;
        do
        {
                ifstream gp("/sys/class/gpio/gpio4/value",ifstream::in);
                usleep(50000);
                gp>>i;
                if(flag==-1 && i==0)
                {
                        detection();
                        flag=-flag;
                        break;
                }
                else
                {
                        flag=-flag;
                        continue;
                }
        }while(1);

}


void detection()
{
        Mat getvidframe();
        Mat base=imread("/home/pi/Desktop/opencv/opencv-3.1.0/samples/cpp/10.pgm");
        Mat original, grayscale, blured;
        Mat dst;
        String class_address = "haarcascade_frontalface_alt.xml";
        int const lower_thresh = 100;
        int thresh_ratio = 3, kernel_thresh = 2;
        string barack_filename;
        string image_name;
        original=getvidframe();

        //------------------------------------------------------------------------------------------------------
        //CASCADE CLASSIFIER OBJECTS
                float scale_factor = 1.1;
                int min_neighbours = 2;         vector<Rect> oboi;
                Rect roi_a;
                 int aoi_a = 0;
                Mat feature;
                string filename;

                //------------------------------------------------------------------------------------------------------


//                cvtColor(original, grayscale, CV_BGR2GRAY);

                CascadeClassifier classifier = CascadeClassifier(class_address);
                if (!classifier.load(class_address))
                {
                        cout << "cannot load classifier";

                        exit(0);
                }
                
                clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_beg);
               
		classifier.detectMultiScale(original, oboi, min_neighbours, scale_factor, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

     //           cout << "the no of objects I found: " << oboi.size();
                int i;
                for (i = 0; i < oboi.size(); i++)
                {
			        if(i==1)
		          	{
			         	break;
		      	    }
                        roi_a.x = oboi[i].x;
                        roi_a.y = oboi[i].y;
                        roi_a.width = oboi[i].width;
                        roi_a.height = oboi[i].height;
                        feature = original(roi_a);
                        stringstream filestream;
                        resize(feature,feature,base.size());
                        filestream <<"recognition.png";
                        filename = "/home/pi/Desktop/" + filestream.str();
                        imwrite(filename, feature);


                        system("/home/pi/Desktop/opencv/opencv-3.1.0/samples/cpp/rasp_script.sh");
                }




                if(i>0)
                {
			     string line;
                 while(1)
                 {
                     ifstream myfile ("./prediction.txt");

                     if(myfile.is_open())
                     {
                         usleep(1000000);
                         while (getline (myfile,line) )
                        {
                           cout<<"\n";
                           cout<<"Predicted class: ";
                           
                            char ch = line[0]; // Get the first char of str
                            int i = ch;
                           if(i==1)
                           {
                            cout<<" Jeet Kanjani";
                           }
                           else
                            
                            {cout << line << '\n';}

                        }
                         clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts_end);
                 std::cout << (ts_end.tv_sec - ts_beg.tv_sec) + (ts_end.tv_nsec - ts_beg.tv_nsec) / 1e9 << " sec";
        
                        myfile.close();
                        system("./remove_predict.sh");

			            
                        break;
                    }
                

                 
                }
            }

	//	cout<<"outside loop";


            
    pollgpio();


}

Mat getvidframe()
{
        VideoCapture cap(0);
         Mat frame;
         cap >> frame;
         return frame;

}
                                                                                                                                                  



