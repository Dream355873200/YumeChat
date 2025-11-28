//
// Created by 残梦 on 2025/11/28.
//

#include "SelectWindow.h"

SelectWindow::SelectWindow()
{

    this->setFixedSize(600,700);

    _central_widget=new QWidget(this);
    this->setCentralWidget(_central_widget);

    _main_layout=new QVBoxLayout;
    _main_layout->setContentsMargins(0,5,0,0);
    _main_layout->setAlignment(Qt::AlignTop);
    _central_widget->setLayout(_main_layout);

    _title_bar=new YumeTitleBar(this);
    _main_layout->addWidget(_title_bar);

    _search_layout=new QHBoxLayout;
    _search_layout->setContentsMargins(10,5,10,5);
    _main_layout->addLayout(_search_layout);

    _search=new YumeLineEdit(this);
    _search->setMode(LineEditMode::Search);
    _search->setFixedSize(450,30);
    _search_layout->addWidget(_search);

    _button=new YumeButton;
    _button->setText("搜索");
    _button->setFixedSize(100,30);
    _search_layout->addWidget(_button);

    _list=new SmoothListWidget(this);


    _title_bar->setIconEffect(1.0,0.2,Qt::black);

    connect(_title_bar->x(),&YumeLabel::clicked,[this]()
    {
        this->hide();
    });
}
