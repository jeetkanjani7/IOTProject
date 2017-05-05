/*
 * build_database.cpp
 *
 *  Created on: 11-Feb-2017
 *      Author: jeetkanjani7
 */

/*
 * detectface.cpp
 *
 *  Created on: 11-Feb-2017
 *      Author: jeetkanjani7
*/

#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/objdetect/objdetect.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include<opencv2/contrib/contrib.hpp>
#include<stdio.h>
#include<unistd.h>
#include<iostream>
#include<fstream>

using namespace std;
using namespace cv;


Mat getvidframe(void);

int main()
{
    Mat frame;

    Mat base=imread("/home/jeetkanjani7/Study/opencv_res/database/s2/1.pgm",0);

    
    //-----------------------------------------------------------------------------------------------------
                //CASCADE CLASSIFIER OBJECTS
            float scale_factor = 1.1;
            int min_neighbours = 2;
            vector<Rect> oboi;
            Rect roi_a;
            int aoi_a = 0;
            Mat feature;
            string filename;

            //------------------------------------------------------------------------------------------------------


            String class_address = "/home/jeetkanjani7/opencv-2.4.13/samples/android/face-detection/res/raw/lbpcascade_frontalface.xml";
            int const lower_thresh = 100;
            int thresh_ratio = 3, kernel_thresh = 2;


            frame=getvidframe();
            imshow("hey",frame);
            if(frame.empty())
            {
                exit(0);
            }

              CascadeClassifier vio_jones = CascadeClassifier(class_address);
                            if (!vio_jones.load(class_address))
                            {
                                    cout << "cannot load classifier";

                                    exit(0);
                            }
                           
            vio_jones.load(class_address);
            for(int j=0;j<10;)
            {
                frame=getvidframe();
                vio_jones.detectMultiScale(frame, oboi, min_neighbours, scale_factor, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));
                cout <<  oboi.size();
                for (int i = 0; i < oboi.size(); i++)
                {

                    roi_a.x = oboi[i].x;
                    roi_a.y = oboi[i].y;
                            roi_a.width = oboi[i].width;
                    roi_a.height = oboi[i].height;
                    line(frame, Point(roi_a.x, roi_a.y), Point(roi_a.x + roi_a.width, roi_a.y), Scalar(94.0, 206.0, 165.0, 0.0), 2, 8, 0);
                    line(frame, Point(roi_a.x, roi_a.y + roi_a.height), Point(roi_a.x + roi_a.width, roi_a.y + roi_a.height), Scalar(94.0, 206.0, 165.0, 0.0), 2, 8, 0);
                    line(frame, Point(roi_a.x, roi_a.y), Point(roi_a.x, roi_a.y + roi_a.height), Scalar(94.0, 206.0, 165.0, 0.0), 2, 8, 0);
                    line(frame, Point(roi_a.x + roi_a.width, roi_a.y), Point(roi_a.x + roi_a.width, roi_a.y + roi_a.height), Scalar(94.0, 206.0, 165.0, 0.0), 2, 8, 0);
                    feature = frame(roi_a);
                    resize(feature,feature,base.size());
                    stringstream filestream;
                    j++;
                    cout<<"image taken";
                    filestream << j << ".png";
                    filename = "/home/jeetkanjani7/Study/opencv_res/database/s4/" + filestream.str();
                    imwrite(filename, feature);
                }

            }


}

Mat getvidframe()
{

    VideoCapture cap(1);
     Mat frame;
     cap >> frame;
     return frame;

}
