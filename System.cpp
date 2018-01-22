//
// Created by duanxiaoer on 18-1-22.
//


#include <highgui.h>
#include "System.h"

using namespace std;
using namespace cv;


System::System(){
        cameraNum = 1;
        doubleCamera = false;
        screenRatio = 100;
        width = 600;
        height = 400;
}

void System::setCameraNum(int n){
        cameraNum = n;
}

int System::getCameraNum(){
        return cameraNum;
}

void System::setdoubleCamer(bool douCamera){
        doubleCamera = douCamera;
}

bool System::getdoubleCamer(){
        return doubleCamera;
}

void System::setscreenRatio(int scrRatio){
        screenRatio = scrRatio;
}

int System::getscreenRatio(){
        return screenRatio;
}

void System::setwidth(int wd){
        width = wd;
}

int System::getwidth(){
        return width;
}

void System::setheight(int ht){
        height = ht;
}

int System::getheight(){
        return height;
}

void System::startCamera() {
    int cameraNum = getCameraNum();
    int width = getwidth();
    int height = getheight();
    bool doubleCamera = getdoubleCamer();
    int screenRatio = getscreenRatio();
    switch (cameraNum){
        case 1:
            cameraShoot(width,height);//调用单摄像头摄影
            break;
        case 2:
            cameraShoot2(width,height,doubleCamera,screenRatio);//调用双摄像头摄影
            break;
        case 3:
            cameraShoot3(width,height,doubleCamera,screenRatio);//调用三摄像头摄影
            break;
        default:
            break;
    }
}



void System::cameraShoot(int width,int height){
    RMVideoCapture capture("/dev/video0");
    cv::Mat frame;
    if (1){//
        char key;
        while(1){
            capture.changeVideoFormat(width,height);
            capture>>frame;
            putText(frame,"按ESC退出",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
            cv::imshow("show",frame);
            key = cv::waitKey(1);
            if (key == 27){
                break;
            }
        }
    }else{
        std::cerr<<"摄像头未成功开启"<<std::endl;
    }

}

void System::cameraShoot2(int width,int height,bool doubleCamera, int screenRatio){
    RMVideoCapture capture("/dev/video0");
    RMVideoCapture capture1("/dev/video2");
    if (1){/*           */
        cv::Mat frame1,frame2,temp,imageROI1,imageROI2;
        char key;
        int changeWin = 1;
        while(1){/*         */
            cv::resizeWindow("show",width,height);
            capture.changeVideoFormat(width,height);
            capture1.changeVideoFormat(width,height);
            capture>>frame1;
            capture1>>frame2;

            switch (changeWin){
                case 1:
                    putText(frame1,"按ESC退出,1/2/3切换窗口",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                    imshow("show",frame1);
                    break;
                case 2:
                    putText(frame2,"按ESC退出,1/2/3切换窗口",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                    imshow("show",frame2);
                    break;
                case 3:
                    resize(frame1,frame1,Size(width/2,height),0,0);
                    resize(frame2,frame2,Size(width/2,height),0,0);
                    temp = frame1;
                    resize(temp,temp,Size(width,height),0,0);
                    putText(frame1,"按ESC退出,1/2/3切换窗口",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                    imageROI1 = temp(cv::Rect(0,0,frame1.cols,frame1.rows));
                    imageROI2 = temp(cv::Rect(width-frame2.cols,height-frame2.rows,frame2.cols,frame2.rows));
                    frame1.copyTo(imageROI1);
                    frame2.copyTo(imageROI2);
                    imshow("show",temp);
                    break;
                default:
                    break;
            }


            key = waitKey(1);
            switch (key){
                case '1':
                    changeWin = 1;
                    break;
                case '2':
                    changeWin = 2;
                    break;
                case '3':
                    changeWin = 3;
                    break;
                default:
                    break;
            }
            if (key == 27){
                break;
            }
        }
    }else{
        std::cerr<<"摄像头未成功开启"<<std::endl;
    }
}

void System::cameraShoot3(int width, int height, bool doubleCamera, int screenRatio) {
    RMVideoCapture capture0("/dev/video0");
    RMVideoCapture capture1("/dev/video1");
    RMVideoCapture capture2("/dev/video2");

    if (1){
        cv::Mat frame1,frame2,frame3,imageROI1,imageROI2;
        char key;
        int changeWin = 4;
        while(1){
            cv::resizeWindow("show",width,height);
            capture0.changeVideoFormat(width,height);
            capture1.changeVideoFormat(width,height);
            capture2.changeVideoFormat(width,height);
            capture0>>frame1;
            capture1>>frame2;
            capture2>>frame3;
            switch (changeWin){
                case 1:
                    if (1)//摄像头1未打开，则开启摄像头1
                        //capture0.restartCapture();
                    putText(frame1,"按ESC退出,1/2/3/4切换窗口",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                    imshow("show",frame1);
                    break;
                case 2:
                    putText(frame2,"按ESC退出,1/2/3/4切换窗口",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                    imshow("show",frame2);
                    break;
                case 3:
                    putText(frame3,"按ESC退出,1/2/3/4切换窗口",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                    imshow("show",frame3);
                    break;
                case 4:
                    if(1)//摄像头1打开，则关闭摄像头1
                        //capture0.closeStream();
                    resize(frame2,frame2,Size(width/2,height),0,0);
                    resize(frame3,frame3,Size(width/2,height),0,0);
                    resize(frame1,frame1,Size(width,height),0,0);
                    putText(frame1,"按ESC退出,1/2/3切换窗口",Point(100,100),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                    imageROI1 = frame1(cv::Rect(0,0,frame1.cols,frame1.rows));
                    imageROI2 = frame1(cv::Rect(width-frame2.cols,height-frame2.rows,frame2.cols,frame2.rows));
                    frame1.copyTo(imageROI1);
                    frame2.copyTo(imageROI2);
                    imshow("show",frame1);
                    break;
                    break;
                default:
                    break;
            }


            key = waitKey(1);
            switch (key){
                case '1':
                    changeWin = 1;
                    break;
                case '2':
                    changeWin = 2;
                    break;
                case '3':
                    changeWin = 3;
                    break;
                case '4':
                    changeWin = 4;
                    break;
                default:
                    break;
            }
            if (key == 27){
                break;
            }
        }
    }else{
        std::cerr<<"摄像头未成功开启"<<std::endl;
    }
}

