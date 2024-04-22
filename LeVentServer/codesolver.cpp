#include "codesolver.h"
#include <QtDebug>

UserInfo CodeSolver::A_decode_register(QString msg)
{
    UserInfo user;
    int x1 = msg.indexOf("/a");
    int x2 = msg.indexOf("/b");
    int x3 = msg.indexOf("/c");
    user.userName = msg.mid(x1+2,x2-x1-2);
    user.nickname = msg.mid(x2+2,x3-x2-2);
    user.password = msg.mid(x3+2,msg.length()-x3-2);
    //qDebug() << "1  " << user.userName << " " << user.nickname << " " << user.password;
    return user;
}

UserInfo CodeSolver::B_decode_login(QString msg)
{
    UserInfo user;
    int x1 = msg.indexOf("/a");
    int x2 = msg.indexOf("/b");
    user.userName = msg.mid(x1+2,x2-x1-2);
    user.password = msg.mid(x2+2,msg.length()-x2-2);
    user.nickname = "";
    //qDebug() << "2  " << user.userName << " "<< user.nickname << " " << user.password;
    return user;
}

QString CodeSolver::C_decode_addFriend(QString msg)
{
    //qDebug() << "3  " << msg.mid(4,msg.length()-4);
    return msg.mid(4,msg.length()-4);
}

ONPassword CodeSolver::D_decode_modifyPwd(QString msg)
{
    ONPassword pwd;
    int x1 = msg.indexOf("/a");
    int x2 = msg.indexOf("/b");
    pwd.oldPassword = msg.mid(x1+2,x2-x1-2);
    pwd.newPassword = msg.mid(x2+2,msg.length()-x2-2);
    //qDebug() << "4  " << pwd.oldPassword << " "<< pwd.newPassword;
    return pwd;
}

Message CodeSolver::E_decode_getClientMsg(QString msg, QString senderUserName)
{
    Message message;
    int x1 = msg.indexOf("/a");
    int x2 = msg.indexOf("/b");
    int x3 = msg.indexOf("/c");
    message.senderUserName = senderUserName;
    message.targetUserName = msg.mid(x1+2,x2-x1-2);
    message.time = msg.mid(x2+2,x3-x2-2);
    message.content = msg.mid(x3+2,msg.length()-x3-2);
    //qDebug() << "5  " << message.senderUserName << " "<< message.targetUserName << " " << message.time << " " << message.content;
    return message;
}

int CodeSolver::F_decode_sendMsgToTarget(QString msg)
{
    //qDebug() << "6  " << msg.endsWith("0");
    return !msg.endsWith("0");
}




QString CodeSolver::encode_statusMsg(QChar msgType, int status)
{
    QString m = msgType;
    //qDebug() << "7  " << (m+"#"+char(status+'0'));
    return (m+"#"+char(status+'0'));
}

QString CodeSolver::A_encode_register(int status)
{
    //qDebug() << "8  " << encode_statusMsg('A',status);
    return encode_statusMsg('A',status);
}

QString CodeSolver::B_encode_login(int status)
{
    //qDebug() << "9  " << encode_statusMsg('B',status);
    return encode_statusMsg('B',status);
}

QString CodeSolver::B_encode_login(int status, UserInfo userInfo, QList<UserInfo> friendsInfo)
{
    qDebug() << "encode_-1";
    QString m = "B#"+ QString::number(status) +"/a"+userInfo.userName+"/b"+userInfo.nickname;
    qDebug() << "encode_0";
    if(status == 0){
        int n = friendsInfo.size();
        qDebug() << "encode_1";
        //qDebug() << n;
        for(int i=0;i<n;i++)
        {
            m = m+"$/a"+friendsInfo[i].userName+"/b"+friendsInfo[i].nickname;
        }
        qDebug() << "encode_2";
        m = m + "$";
    }
    //qDebug() << "10  " << m;
    return m;
}

QString CodeSolver::C_encode_addFriend(int status)
{
    return encode_statusMsg('C',status);
}

QString CodeSolver::C_encode_addFriend(int status, UserInfo friendInfo)
{
    QString Status(status+'0');
    QString m = "C#"+Status;
    if(status == 0){
        m = m+"/a"+friendInfo.userName+"/b"+friendInfo.nickname;
    }
    //qDebug() << "12  " << m;
    return m;
}

QString CodeSolver::D_encode_modifyPwd(int status)
{
    return encode_statusMsg('D',status);
}

QString CodeSolver::E_encode_getClientMsg(int status)
{
    return encode_statusMsg('E',status);
}

QString CodeSolver::F_encode_sendMsgToTarget(Message message)
{
    //qDebug() << "15  " << "F#/a"+message.senderUserName+"/b"+message.targetUserName+"/c"+message.time+"/d"+message.content;
    return "F#/a"+message.senderUserName+"/b"+message.time+"/c"+message.content;
}

QString CodeSolver::G_encode_userOffline(int status)
{
    return encode_statusMsg('G',status);
}

QString CodeSolver::H_encode_newFriendIn(UserInfo friendInfo)
{
    return "H#/a" + friendInfo.userName + "/b" + friendInfo.nickname;
}
