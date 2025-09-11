//
// Created by 残梦 on 2025/6/3.
//

#ifndef GLOBAL_H
#define GLOBAL_H
#include <QWidget>
#include <functional>
#include<memory>
#include <iostream>
#include<mutex>


extern std::function<void(QWidget*)> repolish;

enum ReqId
{
    ID_GET_VARIFY_CODE=1001,//获取验证码
    ID_REG_USER=1002,//注册用户
    ID_RESET_PWD=1003,//重置密码
    ID_LOGIN_USER=1004,//用户登录
    ID_CHAT_LOGIN=1005,//登录聊天服务器
    ID_CHAT_LOGIN_RSP=1006,//登录聊天服务器回包
};
enum Modules
{
    REGISITERMOD=0,
    RESETMOD=1,
    LOGINMOD=2,
};

enum ErrorCodes
{
    SUCCESS=0,
    ERR_NETWORK=2,//网络错误
    ERR_JSON=1001,//json解析失败
    ERR_USER_EXSIT=1002,//邮箱已存在
    ERR_CODE_REG=1003,//注册验证码不存在
    ERR_GRPC_FAILED=1004,//grpc调用失败
    ERR_USER_UNEXSIT=1005,//用户不存在
    ERR_PASSWORD_FAILED=1006,//密码错误
};
struct ServerInfo
{
    uint16_t Port;
    std::string Host;
};
enum LineEditMode
{
    Account,
    Password,
    Email,
    VerifyCode,
};
extern qreal Global_ScaleDpi;
extern QString Global_id;
QPixmap setPixmapDpi(const QSize& size, const QPixmap& pixmap);
#endif //GLOBAL_H
