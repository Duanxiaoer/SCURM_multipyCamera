//
// Created by duanxiaoer on 18-1-22.
//


#include <iostream>
#include "RMVideoCapture.hpp"
#include "opencv/cv.hpp"
#ifndef RM_LIVESYS_SYSTEM_H
#define RM_LIVESYS_SYSTEM_H

class System{
public:
    System();
    //设置系统参数
    void setCameraNum(int n);
    int getCameraNum();
    void setdoubleCamer(bool douCamera);
    bool getdoubleCamer();
    void setscreenRatio(int scrRatio);
    int getscreenRatio();
    void setwidth(int wd);
    int getwidth();
    void setheight(int ht);
    int getheight();
    //功能函数
    void startCamera();//开始摄像
    void cameraShoot(int width,int height);;//单摄像头摄像
    void cameraShoot2(int width,int height,bool doubleCamera, int screenRatio);//双摄像头摄像
    void cameraShoot3(int width,int height,bool doubleCamera, int screenRatio);//三摄像头摄像



private:
    int cameraNum;//摄像头个数 0 1 2 3
    bool doubleCamera;//是否分屏显示
    int screenRatio;//分屏显示时各个摄像头画面所占比例
    int width;//显示窗口的宽度
    int height;//显示窗口的高度
};



#endif //RM_LIVESYS_SYSTEM_H
