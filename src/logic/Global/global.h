//
// Created by 残梦 on 2025/6/3.
//

#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include<QRegularExpression>
#include"QStyle"
#include<memory>
#include <iostream>
#include<mutex>


extern std::function<void(QWidget*)> repolish;

enum ReqId
{
    ID_GET_VARIFY_CODE=1001,//获取验证码
    ID_REG_USER=1002,//注册用户
};
enum Modules
{
    REGISITERMOD=0,
};

enum ErrorCodes
{
    SUCCESS=0,
    ERR_JSON=1,//json解析失败
    ERR_NETWORK=2,//网络错误
};




#endif //GLOBAL_H
