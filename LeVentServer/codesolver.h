#ifndef CODESOLVER_H
#define CODESOLVER_H
#include "datastructure.h"

class CodeSolver
{
public:
    CodeSolver();

    static UserInfo A_decode_register(QString msg);     //return用户注册信息
    static UserInfo B_decode_login(QString msg);        //return用户名、密码（昵称为空字符串即可）
    static QString C_decode_addFriend(QString msg);     //return目标用户名
    static ONPassword D_decode_modifyPwd(QString msg);  //return新老密码组成的结构体
    static Message E_decode_getClientMsg(QString msg, QString senderUserName);  //返回消息数据结构，发送者在输入中给出
    static int F_decode_sendMsgToTarget(QString msg);   //返回客户端返回的状态编码，目前0代表信息投递成功，1代表失败

    static QString A_encode_register(int status);       //status = 0代表成功；= 1代表用户名已被注册，注册失败
    static QString B_encode_login(int status);
    static QString B_encode_login(int status, UserInfo userInfo, QList<UserInfo> friendsInfo);      //0成功，后接用户本人及其好友信息；1用户名不存在；2密码错误
    static QString C_encode_addFriend(int status);
    static QString C_encode_addFriend(int status, UserInfo friendInfo);     //status0成功，并返回好友个人信息；1表示该用户名不存在；2表示重复添加好友
    static QString D_encode_modifyPwd(int status);      //0成功；1原密码不正确，修改失败
    static QString E_encode_getClientMsg(int status);    //0成功；1对方不在线，消息等待投送；2失败
    static QString F_encode_sendMsgToTarget(Message message);   //编码信息
    static QString G_encode_userOffline(int status);
    static QString H_encode_newFriendIn(UserInfo friendInfo);   //发送好友信息
private:
    static QString encode_statusMsg(QChar msgType, int status);        //用来统一编写发送状态编码的方法
};

#endif // CODESOLVER_H
