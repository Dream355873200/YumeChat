//
// Created by 残梦 on 2025/9/1.
//

#ifndef SMOOTHSCROLLBAR_H
#define SMOOTHSCROLLBAR_H
#include <QPropertyAnimation>
#include <QScrollBar>


class SmoothScrollBar : public QScrollBar {
    Q_OBJECT
public:
    SmoothScrollBar(QWidget *parent = nullptr) : QScrollBar(parent) {}

protected:
    void sliderChange(SliderChange change) override {
        if (change == QAbstractSlider::SliderValueChange) {
            // 如果滚动条的值变化（如拖动或点击），触发动画
            int currentPos = value();
            int targetPos = sliderPosition();  // 获取目标位置

            // 使用动画平滑滚动到目标位置
            QPropertyAnimation* animation = new QPropertyAnimation(this, "value");
            animation->setDuration(200);
            animation->setStartValue(currentPos);
            animation->setEndValue(targetPos);
            animation->setEasingCurve(QEasingCurve::OutQuad);
            animation->start(QPropertyAnimation::DeleteWhenStopped);
        } else {
            QScrollBar::sliderChange(change);
        }
    }
};



#endif //SMOOTHSCROLLBAR_H
