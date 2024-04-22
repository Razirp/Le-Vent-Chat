#ifndef USERINFO_H
#define USERINFO_H
#include <QString>

struct UserInfo
{
    QString userName;
    QString nickname;
    QString password;
};

struct ONPassword
{
    QString oldPassword;
    QString newPassword;
};

struct Message
{
    QString senderUserName;
    QString targetUserName;
    QString time;
    QString content;
};

#endif // USERINFO_H
