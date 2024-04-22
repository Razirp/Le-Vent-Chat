#include "basewidget.h"
#include <QDebug>

BaseWidget::BaseWidget(QWidget *parent) :
  QWidget(parent)
{
  //设置无边框透明
  setWindowFlags(Qt::FramelessWindowHint);//无边框
  setAttribute(Qt::WA_TranslucentBackground);//背景透明

  m_areaMovable = geometry();
  m_bPressed = false;
}

void BaseWidget::mousePressEvent(QMouseEvent *e)
{
  //鼠标左键
  if(e->button() == Qt::LeftButton)
  {
    m_bPressed = true;
    m_ptPress = e->globalPos()-this->pos();
    e->accept();
  }
}

void BaseWidget::mouseMoveEvent(QMouseEvent *e)
{

  if(m_bPressed && (e->buttons()) && (Qt::LeftButton))
  {
    this->move(e->globalPos()-m_ptPress);
     e->accept();
  }
}

void BaseWidget::mouseReleaseEvent(QMouseEvent *)
{
  m_bPressed = false;
}

//设置鼠标按下的区域
void BaseWidget::setAreaMovable(const QRect rt)
{
  if(m_areaMovable != rt)
  {
    m_areaMovable = rt;
  }
}
