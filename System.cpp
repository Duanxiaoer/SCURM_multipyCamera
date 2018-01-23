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
    if (n<=0 || n>3){
        std::cerr<<"摄像头个数应为1～3\n";
    }

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
    if (wd<=0){
        std::cerr<<"width can't be fushu\n";
    }
    width = wd;
}

int System::getwidth(){
        return width;
}

void System::setheight(int ht){
    if (ht<=0){
        std::cerr<<"height can't be fushu\n";
    }
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
    //RMVideoCapture capture("/dev/video0");
    VideoCapture capture(0);
    cv::Mat frame;
    if (1){//
        char key;
        while(1){
            //capture.changeVideoFormat(width,height);

            capture>>frame;
            resize(frame,frame,Size(width,height),0,0);
            putText(frame,"ESC",Point(100,100),FONT_HERSHEY_PLAIN,1,Scalar(255,0,0));
            cv::imshow("SCURM_HotPot",frame);
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
//    RMVideoCapture capture("/dev/video0");
//    RMVideoCapture capture1("/dev/video2");
    VideoCapture capture(0);
    VideoCapture capture1(1);
    if (1){/*           */
        cv::Mat frame1,frame2,temp,imageROI1,imageROI2;
        char key;
        int changeWin = 1;
        while(1){/*         */
            cv::resizeWindow("SCURM_HotPot",width,height);
//            capture.changeVideoFormat(width,height);
//            capture1.changeVideoFormat(width,height);
            capture>>frame1;
            capture1>>frame2;

            switch (changeWin){
                case 1:
                    putText(frame1,"ESC,1/2/3",Point(100,100),FONT_HERSHEY_PLAIN,1,Scalar(255,0,0));
                    resize(frame1,frame1,Size(width,height),0,0);
                    imshow("SCURM_HotPot",frame1);
                    break;
                case 2:
                    putText(frame2,"ESC,1/2/3",Point(100,100),FONT_HERSHEY_PLAIN,1,Scalar(255,0,0));
                    resize(frame2,frame2,Size(width,height),0,0);
                    imshow("SCURM_HotPot",frame2);
                    break;
                case 3:
                    resize(frame1,frame1,Size(width/2,height),0,0);
                    resize(frame2,frame2,Size(width/2,height),0,0);
                    temp = frame1;
                    resize(temp,temp,Size(width,height),0,0);
                    putText(frame1,"ESC,1/2/3",Point(100,100),FONT_HERSHEY_PLAIN,1,Scalar(255,0,0));
                    imageROI1 = temp(cv::Rect(0,0,frame1.cols,frame1.rows));
                    imageROI2 = temp(cv::Rect(width-frame2.cols,height-frame2.rows,frame2.cols,frame2.rows));
                    frame1.copyTo(imageROI1);
                    frame2.copyTo(imageROI2);
                    imshow("SCURM_HotPot",temp);
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
//    RMVideoCapture capture0("/dev/video0");
//    RMVideoCapture capture1("/dev/video1");
//    RMVideoCapture capture2("/dev/video2");

//    VideoCapture capture0(0);
//    VideoCapture capture1(1);
//    VideoCapture capture2(2);

    VideoCapture* capture0 = new VideoCapture(0);
    VideoCapture* capture1 = new VideoCapture(1);
    VideoCapture* capture2 = new VideoCapture(2);

    if (capture0 != NULL && capture1 != NULL && capture2 != NULL){
        cv::Mat frame0,frame1,frame2,imageROI1,imageROI2;
        char key;
        int changeWin = 1;
        while(1){
            cv::resizeWindow("SCURM_HotPot",width,height);
//            capture0.changeVideoFormat(width,height);
//            capture1.changeVideoFormat(width,height);
//            capture2.changeVideoFormat(width,height);
//            capture0>>frame0;
//            capture1>>frame1;
//            capture2>>frame2;


            if (capture0 != NULL){
                capture0->operator>>(frame0);
            }

            //摄像头3始终打开，1和2排斥切换
            switch (changeWin){
                case 1:
                    if(capture1 != NULL){        //摄像头2打开，则关闭摄像头2
                        delete capture1;
                        capture1 = NULL ;
                    }
                    if (capture0 == NULL)//摄像头1未打开，则开启摄像头1
                        capture0 = new VideoCapture(0);

//                    capture0->operator>>(frame0);     上面已经读过了
                    resize(frame0,frame0,Size(width,height),0,0);
                    putText(frame0,"ESC,1/2/3/4",Point(50,50),FONT_HERSHEY_PLAIN,1,Scalar(255,0,0));
                    imshow("SCURM_HotPot",frame0);
                    break;
                case 2:
                    if(capture0 != NULL){        //摄像头1打开，则关闭摄像头1
                        delete capture0;
                        capture0 = NULL ;
                    }
                    if (capture1 == NULL)//摄像头2未打开，则开启摄像头2
                    {
                        capture1 = new VideoCapture(1);
                    }
                    capture1->operator>>(frame1);
                    resize(frame1,frame1,Size(width,height),0,0);
                    putText(frame1,"ESC,1/2/3/4",Point(50,50),FONT_HERSHEY_PLAIN,1,Scalar(255,0,0));
                    imshow("SCURM_HotPot",frame1);
                    break;
                case 3:
                    if(capture0 != NULL){        //摄像头1打开，则关闭摄像头1
                        delete capture0;
                        capture0 = NULL ;
                    }
                    capture2->operator>>(frame2);
                    resize(frame2,frame2,Size(width,height),0,0);
                    putText(frame2,"ESC,1/2/3/4",Point(50,50),FONT_HERSHEY_PLAIN,1,Scalar(255,0,0));
                    imshow("SCURM_HotPot",frame2);
                    break;
                case 4:
                    if(capture1 == NULL){        //摄像头2打开，则关闭摄像头2
                        capture1 = new VideoCapture(1) ;
                    }
                    if(capture0 != NULL){        //摄像头1打开，则关闭摄像头1
                        delete capture0;
                        capture0 = NULL ;
                    }
                    capture1->operator>>(frame1);
                    capture2->operator>>(frame2);
                    resize(frame1,frame1,Size(width/2,height),0,0);
                    resize(frame2,frame2,Size(width/2,height),0,0);
                    resize(frame0,frame0,Size(width,height),0,0);
                    putText(frame1,"ESC,1/2/3/4",Point(50,50),FONT_HERSHEY_PLAIN,3,Scalar(255,0,0));
                    imageROI1 = frame0(cv::Rect(0,0,frame1.cols,frame1.rows));
                    imageROI2 = frame0(cv::Rect(width-frame1.cols,height-frame1.rows,frame1.cols,frame1.rows));
                    frame1.copyTo(imageROI1);
                    frame2.copyTo(imageROI2);
                    imshow("SCURM_HotPot",frame0);
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

