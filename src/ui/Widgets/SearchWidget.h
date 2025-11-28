#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QPropertyAnimation>
#include <QWidget>
#include <QHBoxLayout>

#include "ui/Custom/YumeButton.h"
#include "ui/Custom/YumeLineEdit.h"

class SearchWidget : public QWidget
{
public:
    void set_search_width(int search_width)
    {
        _search->setFixedWidth(search_width);
        _search_width = search_width;
    }

    [[nodiscard]] YumeLineEdit * search() const
    {
        return _search;
    }

    [[nodiscard]] YumeButton * add_friend() const
    {
        return _add_friend;
    }

private:
    Q_OBJECT

public:
    SearchWidget(QWidget* parent = nullptr);
    ~SearchWidget();

    void set_text(const QString& message);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    void expandSearch();    // 展开搜索框
    void collapseSearch();  // 收起搜索框

private:
    QPropertyAnimation* _search_animation;
    QPropertyAnimation* _label_animation;
    YumeLabel* _label;
    QHBoxLayout* _main_layout;
    YumeLineEdit* _search;
    YumeButton* _add_friend;

    int _search_width=80;
    
    bool _isExpanded = false; // 记录当前状态
};

#endif // SEARCHWIDGET_H