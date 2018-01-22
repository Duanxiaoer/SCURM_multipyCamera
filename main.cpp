#include "System.h"

/*              命名规则
 * 类名：首字母大写，单词首字母大写         System
 * 函数名：首字母小写，单词首字母大写        getSysName()
 * 变量：首字母小写，单词首字母大写          sysName
 * */




int main() {
    System system1;
    system1.setCameraNum(3);
    system1.setdoubleCamer(true);
    system1.setwidth(600);
    system1.setheight(400);
    system1.startCamera();
    return 0;
}