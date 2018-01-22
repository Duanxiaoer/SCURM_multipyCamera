#include <iostream>
#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.hpp>
#include "camera.h"


using namespace std;
using namespace cv;
//
//class Carmera{
//public:
//    static void setNum(int);
//    static int  getNUm();
//
//private:
//    static int num;
//};
//
//void Carmera::setNum(int a) {
//    num = a;
//}
//
//int Carmera::getNUm() {
//    return num;
//}



int main() {
    //外部调用
    Camera carmera(0);
    carmera.setnum(3);


    int num = carmera.getnum();   //设置相机个数

    bool carmera_2 = false;//默认只打开一个相机
    bool carmera_3 = false;

    if (num == 1){
        VideoCapture capture(0);
        Mat frame;
        while (capture.read(frame)){
            imshow("show",frame);
            char key = static_cast<char>(waitKey(10));
            if (key == 27){
                break;
            }
        }
    }

    if (num == 2){
        VideoCapture capture_C(0);
        VideoCapture capture_V(1);
        if(!capture_C.isOpened())
            cout<<"fail to open!"<<endl;

        Mat frame_c,frame_c2,imageROI;
        bool AisUP = false;

        char key;
        while(capture_C.read(frame_c) && capture_V.read(frame_c2)){

            putText(frame_c2,"A",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));

            if(AisUP){
                resize(frame_c2,frame_c2,Size(1200,800),0,0);
                resize(frame_c,frame_c,Size(300,200),0,0);
                imageROI = frame_c2(cv::Rect(frame_c2.cols-frame_c.cols,frame_c2.rows-frame_c.rows,frame_c.cols,frame_c.rows));//选定要贴图的区域
                frame_c.copyTo(imageROI);
                imshow("show",frame_c2);
            } else{
                resize(frame_c,frame_c,Size(1200,800),0,0);
                resize(frame_c2,frame_c2,Size(300,200),0,0);

                imageROI = frame_c(cv::Rect(frame_c.cols-frame_c2.cols,frame_c.rows-frame_c2.rows,frame_c2.cols,frame_c2.rows));//选定要贴图的区域
                frame_c2.copyTo(imageROI);//将frame_c2贴在imageROI上
                imshow("show",frame_c);
            }


            key = static_cast<char>(waitKey(10));

            switch (key){
                case '1'://按‘1’A窗口在下
                    AisUP = false;
                    break;
                case '2'://按'2'A窗口在上
                    AisUP = true;
                    break;
                default:
                    break;
            }
            if (key == 27){
                break;
            }
        }
    }

    if (num == 3){
        VideoCapture capture_1(0);
        Mat frame_1,frame_2,frame_3,imageROI_2, imageROI_1;


        if (!capture_1.isOpened())
                cout<<"1 fail to open"<<endl;


        int which_UP = 1;//哪个摄像头是主图像    1:A  2:B 3:C

        char key;
        while(true){

            if (which_UP == 1){
                capture_1.read(frame_1);
                resize(frame_1,frame_1,Size(1200,800),0,0);
                putText(frame_1,"A",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
//                //贴B
//                resize(frame_2,frame_2,Size(300,200),0,0);
//                imageROI_1 = frame_1(cv::Rect(0,frame_1.rows-frame_2.rows,frame_2.cols,frame_2.rows));//选定要贴图的区域
//                frame_2.copyTo(imageROI_1);
//                //贴C
//                resize(frame_3,frame_3,Size(300,200),0,0);
//                imageROI_2 = frame_1(cv::Rect(frame_1.cols-frame_3.cols,frame_1.rows-frame_3.rows,frame_3.cols,frame_3.rows));//选定要贴图的区域
//                frame_3.copyTo(imageROI_2);
                imshow("show",frame_1);


            }else if (which_UP == 2){


                VideoCapture capture_2(1);
                VideoCapture capture_3(2);
                if (!capture_3.isOpened())
                    cout<<"3 fail to open"<<endl;
                if (!capture_2.isOpened())
                    cout<<"2 fail to open"<<endl;

                capture_2.read(frame_2);
                capture_3.read(frame_3);
                resize(frame_2,frame_2,Size(1200,800),0,0);
                putText(frame_2,"B",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                putText(frame_1,"A",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                putText(frame_3,"C",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
//                //贴A
//                resize(frame_1,frame_1,Size(300,200),0,0);
//                imageROI_1 = frame_2(cv::Rect(0,frame_2.rows-frame_1.rows,frame_1.cols,frame_1.rows));//选定要贴图的区域
//                frame_1.copyTo(imageROI_1);
                //贴C
                resize(frame_3,frame_3,Size(600,400),0,0);
                imageROI_2 = frame_2(cv::Rect(frame_2.cols-frame_3.cols,frame_2.rows-frame_3.rows,frame_3.cols,frame_3.rows));//选定要贴图的区域
                frame_3.copyTo(imageROI_2);
                imshow("show",frame_2);

            }else {

//                capture_1.read(frame_1);
//                capture_3.read(frame_3)
//                resize(frame_3,frame_3,Size(1200,800),0,0);
//                putText(frame_3,"C",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
//                putText(frame_1,"A",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
//                putText(frame_2,"B",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
//                //贴A
//                resize(frame_1,frame_1,Size(300,200),0,0);
//                imageROI_1 = frame_3(cv::Rect(0,frame_3.rows-frame_1.rows,frame_1.cols,frame_1.rows));//选定要贴图的区域
//                frame_1.copyTo(imageROI_1);
//                //贴B
//                resize(frame_2,frame_2,Size(300,200),0,0);
//                imageROI_2 = frame_3(cv::Rect(frame_3.cols-frame_2.cols,frame_3.rows-frame_2.rows,frame_2.cols,frame_2.rows));//选定要贴图的区域
//                frame_2.copyTo(imageROI_2);
//                imshow("show",frame_3);
            }

            key = static_cast<char>(waitKey(10));

            switch (key){
                case '1'://按‘1’A窗口在上   B  C
                    which_UP = 1;

                    break;
                case '2'://按'2'B窗口在上    A  C
                    which_UP = 2;

                    break;
                case '3'://按'3'C窗口在上    A   B
//                    which_UP = 3;
                    break;
                default:
                    break;
            }
            if (key == 27){
                break;
            }
        }
    }




}



























