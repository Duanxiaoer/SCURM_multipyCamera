//
// Created by duanxiaoer on 18-1-20.
//

#ifndef RM_CAMERA_H
#define RM_CAMERA_H


class camera {
public:
    void setnum(int num){
        this->num = num;
    }
    //void setwidth(int width);
    //void setheight(int height);

private:
    int num;//摄像头个数
    int width;
    int height;

};


#endif //RM_CAMERA_H