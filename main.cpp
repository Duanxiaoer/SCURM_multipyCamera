#include "System.h"

/*              命名规则
 * 类名：首字母大写，单词首字母大写         System
 * 函数名：首字母小写，单词首字母大写        getSysName()
 * 变量：首字母小写，单词首字母大写          sysName
 * */




int main() {
    try {
        System system1;
        system1.setCameraNum(1);
        system1.setdoubleCamer(true);
        system1.setwidth(600);
        system1.setheight(400);
        system1.startCamera();
        return 0;
    }catch (std::exception e){
        std::cerr<<"The livesystem crashed before begin to work!!!!!";
    }
}