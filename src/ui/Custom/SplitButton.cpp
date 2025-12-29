//
// Created by 残梦 on 2025/12/23.
//

#include "SplitButton.h"

#include <QPushButton>

#include "YumeButton.h"


class YumeButton;

SplitButton::SplitButton(QWidget *parent)
{
    setCheckable(true); // 让按钮可以被选中
    setMouseTracking(true);//鼠标追踪



    _label=new YumeLabel(this);
    //避免事件过滤器冲突
    _label->setAttribute(Qt::WA_TransparentForMouseEvents);

    _main_layout = new QHBoxLayout(this);
    _main_layout->setAlignment(Qt::AlignCenter);
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    this->setFixedHeight(35);

    _main_layout->setContentsMargins(0, 0, 0, 0);

    QPalette pale;
    pale.setColor(QPalette::WindowText, QColor(255, 255, 255));
    _label->setPalette(pale);


   _label->set_font_size(12);

    _main_layout->addWidget(_label, 0, Qt::AlignCenter);
    _label->setAlignment(Qt::AlignCenter);

    _menu=new YumeMenu();//析构函数会deletelater

    this->setCursor(Qt::PointingHandCursor);
    this->installEventFilter(this);

    // 2. 添加菜单项 (这里可以用你之前的 YumeButton)
    QStringList options = {"拒绝", "忽略"};
    for (const QString &text : options) {
        YumeButton *item = new YumeButton(_menu);
        item->setText(text);
        item->setNormalColor(Qt::white);
        item->setHoverColor(QColor::fromRgb(192,192,192));
        item->setFixedHeight(30);

        // 点击菜单项后，关闭菜单
        connect(item, &QPushButton::clicked, _menu, &QWidget::close);

        // 处理具体的业务逻辑
        connect(item, &QPushButton::clicked, [text](){
            qDebug() << "点击了：" << text;
        });

        _menu->addWidget(item);
    }

}

SplitButton::~SplitButton()
{
    if (_menu) {
        _menu->deleteLater(); // 优雅地请求销毁，而不是直接 delete
        _menu = nullptr;
    }
}

void SplitButton::setText(const QString &text)
{
    _label->setText(text);
    _label->adjustSize();
}

void SplitButton::setHoverColor(const QColor &color)
{
    hoverColor = color;
    this->update();
}

void SplitButton::setNormalColor(const QColor &color)
{
    normalColor = color;
    this->update();
}

void SplitButton::mouseMoveEvent(QMouseEvent *event)
{
    // 1. 记录旧的状态
    bool wasInMenu = inMenu;

    // 2. 更新当前状态
    inMenu = (event->pos().x() > (width() - _menuWidth));

    // 3. 如果状态发生了切换（从左移到右，或从右移到左），强制重绘
    if (wasInMenu != inMenu) {
        update();
    }
    QAbstractButton::mouseMoveEvent(event);
}

void SplitButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // 定义两个区域
    QRect leftRect(0, 0, width() - _menuWidth, height());
    QRect rightRect(width() - _menuWidth, 0, _menuWidth, height());


    QColor leftColor = (isHovered && !inMenu) ? hoverColor : normalColor;
    QColor rightColor = (isHovered && inMenu) ? hoverColor : normalColor;


    if (isPressed && !inMenu) {
        leftColor = leftColor.darker(120); // 120 表示变暗 20%
    } else if (isPressed && inMenu) {
        rightColor = rightColor.darker(120);
    }

    // 默认背景色（普通状态）
    painter.fillRect(rect(), normalColor);

    painter.fillRect(leftRect, leftColor);
    painter.fillRect(rightRect, rightColor);

    // --- 绘制虚线 ---
    QPen dashPen;
    dashPen.setColor(QColor(255, 255, 255, 180)); // 稍微透明一点的白色
    dashPen.setStyle(Qt::DashLine);
    dashPen.setWidth(1);
    painter.setPen(dashPen);

    int lineX = width() - _menuWidth;
    painter.drawLine(lineX, 6, lineX, height() - 6);

    // --- 绘制右侧小箭头 ---
    drawArrow(&painter);
}
// 一个简单的绘制箭头辅助函数
void SplitButton::drawArrow(QPainter *painter)
{
    int centerX = width() - (_menuWidth / 2);
    int centerY = height() / 2;
    int size = 3; // 箭头大小

    QPainterPath path;
    path.moveTo(centerX - size, centerY - size / 2);
    path.lineTo(centerX, centerY + size / 2);
    path.lineTo(centerX + size, centerY - size / 2);

    painter->setPen(QPen(Qt::white, 1.5));
    painter->drawPath(path);
}
bool SplitButton::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == this) {
        if (event->type() == QEvent::Enter) {
            isHovered = true;

            update();
            return true; // 悬停事件可拦截
        }
        if (event->type() == QEvent::Leave) {
            isHovered = false;
            update();
            return true; // 悬停事件可拦截
        }
        if (event->type() == QEvent::MouseButtonPress)
            {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton)
                {
                isPressed=true;
                if(inMenu)
                {
                    showMenu();
                    isPressed=false;

                    return true;
                }
                update();
                return false; // 关键：允许事件继续传递
            }
        }
        if (event->type() == QEvent::MouseButtonRelease) {
            QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
            if (mouseEvent->button() == Qt::LeftButton) {
                isPressed=false;
                update();
                return false; // 关键：允许事件继续传递
            }
        }
    }
    return QWidget::eventFilter(watched, event);
}

void SplitButton::showMenu()
{
    // 1. 创建菜单实例
    // 注意：这里不要传 this 作为父对象指针给构造函数，或者使用 Qt::Popup 标志
    // 这样它就是一个顶层独立窗口，不会被父窗口裁剪

    // 设置菜单宽度与按钮一致，或者自定义宽度
    _menu->setFixedWidth(this->width());



    // 3. 计算弹出位置 (按钮的正下方)
    // mapToGlobal 将按钮左下角的坐标 (0, height()) 转换为屏幕绝对坐标
    QPoint pos = this->mapToGlobal(QPoint(0, this->height()));

    // 加上一点微调间距（比如向下偏移 2 像素）
    pos.setY(pos.y() + 2);

    // 4. 显示菜单
    _menu->move(pos);
    _menu->show();


}