//
// Created by 残梦 on 2025/8/1.
//

#include "YumeLineEdit.h"


YumeLineEdit::YumeLineEdit(QWidget *parent)
    :QWidget(parent)
{

    _main_layout=new QHBoxLayout(this);
    //设置自定义LineEdit属性
    _main_layout->setContentsMargins(11, 0, 11, 0);
    this->setFixedHeight(45);
    this->setFixedWidth(260);

    _lineEdit = new QLineEdit(this);
    //设置图标
    _ico = new QLabel(this);
    _ico->setFixedSize(19, 19);
    _ico->setScaledContents(true);
    //添加进入布局
    _main_layout->addWidget(_ico);
    _main_layout->addWidget(_lineEdit);

    QFont font;
    font.setPixelSize(13);
    QStringList qsslist;
    qsslist.append("QLineEdit:Hover{background-color:transparent}");
    qsslist.append("QLineEdit{background-color:transparent}");
    _lineEdit->setFrame(QFrame::NoFrame);
    _lineEdit->setAlignment(Qt::AlignCenter);
    _lineEdit->setFont(font);
    _lineEdit->setStyleSheet(qsslist.join(""));
}

YumeLineEdit::~YumeLineEdit()
{
}



void YumeLineEdit::setText(const QString &text)
{
    _lineEdit->setPlaceholderText(text);
}

void YumeLineEdit::loadPixmap(const QString &path)
{
    _image.load(path);
    _ico->setPixmap(setPixmapDpi(_ico->size(), _image));
}

void YumeLineEdit::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); //抗锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor::fromString("#eff2f6"));
    painter.drawRoundedRect(this->rect(), 10, 10);
}

void YumeLineEdit::setMode(LineEditMode mode)
{

    if (validator) {
        delete validator;
        validator = nullptr;
    }
    switch (mode)
    {
        case LineEditMode::Account:
            _lineEdit->setPlaceholderText("输入账号");
            _lineEdit->setEchoMode(QLineEdit::Normal);
            loadPixmap(":/Resource/ico/MingcuteUser2Fill.png");
            break;
        case LineEditMode::Password:
            _lineEdit->setPlaceholderText("输入密码");
            _lineEdit->setEchoMode(QLineEdit::Password);
            loadPixmap(":/Resource/ico/MajesticonsLock.png");
            break;
        case LineEditMode::Email:
            _lineEdit->setPlaceholderText("输入邮箱");
            _lineEdit->setEchoMode(QLineEdit::Normal);
            regx.setPattern(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
            validator = new QRegularExpressionValidator(regx, this);
            _lineEdit->setValidator(validator);
            loadPixmap(":/Resource/ico/MingcuteUser2Fill.png");
            break;
        case LineEditMode::VerifyCode:
            _lineEdit->setPlaceholderText("输入验证码");
            regx.setPattern("[1-9][0-9]+$");
            validator = new QRegularExpressionValidator(regx, this);
            _lineEdit->setValidator(validator);
            _lineEdit->setMaxLength(6);
            _lineEdit->setEchoMode(QLineEdit::Normal);
            break;
        default:
            qDebug() << "LineEdit模式传入错误";
            break;
    }
}

QString YumeLineEdit::currentText()
{
    return _lineEdit->text();
}
