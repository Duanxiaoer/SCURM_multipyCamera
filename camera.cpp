//
// Created by duanxiaoer on 18-1-20.
//

#include "camera.h"

void Camera::setnum(int num) {
    Camera::num = num;
};

int Camera::getnum() {
    return Camera::num;
}

Camera::Camera(int n) {
    num = n;
}
