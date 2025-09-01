/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RegisterDialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer_3;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QLabel *show_label;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout;
    QLabel *email_label;
    QLineEdit *email_lineEdit;
    QSpacerItem *verticalSpacer_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *code_label;
    QLineEdit *code_lineEdit;
    QPushButton *email_pushButton;
    QSpacerItem *verticalSpacer_5;
    QHBoxLayout *horizontalLayout_6;
    QLabel *pass_label;
    QLineEdit *pass_lineEdit;
    QSpacerItem *verticalSpacer_6;
    QHBoxLayout *horizontalLayout_5;
    QLabel *pass1_label;
    QLineEdit *pass1_lineEdit;
    QSpacerItem *verticalSpacer_7;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *confirm_pushButton;
    QPushButton *cancel_pushButton;
    QSpacerItem *verticalSpacer_8;

    void setupUi(QDialog *RegisterDialog)
    {
        if (RegisterDialog->objectName().isEmpty())
            RegisterDialog->setObjectName("RegisterDialog");
        RegisterDialog->resize(350, 500);
        verticalLayout_2 = new QVBoxLayout(RegisterDialog);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(5, 5, 5, 5);
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_3);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName("verticalLayout_3");
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout_3->addItem(verticalSpacer);

        show_label = new QLabel(RegisterDialog);
        show_label->setObjectName("show_label");

        horizontalLayout_3->addWidget(show_label);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        horizontalLayout_3->addItem(verticalSpacer_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout_3);


        verticalLayout->addLayout(verticalLayout_3);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_9);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        email_label = new QLabel(RegisterDialog);
        email_label->setObjectName("email_label");

        horizontalLayout->addWidget(email_label);

        email_lineEdit = new QLineEdit(RegisterDialog);
        email_lineEdit->setObjectName("email_lineEdit");

        horizontalLayout->addWidget(email_lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        code_label = new QLabel(RegisterDialog);
        code_label->setObjectName("code_label");

        horizontalLayout_4->addWidget(code_label);

        code_lineEdit = new QLineEdit(RegisterDialog);
        code_lineEdit->setObjectName("code_lineEdit");

        horizontalLayout_4->addWidget(code_lineEdit);

        email_pushButton = new QPushButton(RegisterDialog);
        email_pushButton->setObjectName("email_pushButton");
        email_pushButton->setMinimumSize(QSize(0, 30));

        horizontalLayout_4->addWidget(email_pushButton);


        verticalLayout->addLayout(horizontalLayout_4);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        pass_label = new QLabel(RegisterDialog);
        pass_label->setObjectName("pass_label");
        pass_label->setMinimumSize(QSize(0, 25));
        pass_label->setMaximumSize(QSize(16777215, 25));

        horizontalLayout_6->addWidget(pass_label);

        pass_lineEdit = new QLineEdit(RegisterDialog);
        pass_lineEdit->setObjectName("pass_lineEdit");

        horizontalLayout_6->addWidget(pass_lineEdit);


        verticalLayout->addLayout(horizontalLayout_6);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        pass1_label = new QLabel(RegisterDialog);
        pass1_label->setObjectName("pass1_label");

        horizontalLayout_5->addWidget(pass1_label);

        pass1_lineEdit = new QLineEdit(RegisterDialog);
        pass1_lineEdit->setObjectName("pass1_lineEdit");

        horizontalLayout_5->addWidget(pass1_lineEdit);


        verticalLayout->addLayout(horizontalLayout_5);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_7);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        confirm_pushButton = new QPushButton(RegisterDialog);
        confirm_pushButton->setObjectName("confirm_pushButton");
        confirm_pushButton->setMinimumSize(QSize(0, 50));

        horizontalLayout_2->addWidget(confirm_pushButton);

        cancel_pushButton = new QPushButton(RegisterDialog);
        cancel_pushButton->setObjectName("cancel_pushButton");
        cancel_pushButton->setMinimumSize(QSize(0, 50));

        horizontalLayout_2->addWidget(cancel_pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_8);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(RegisterDialog);

        QMetaObject::connectSlotsByName(RegisterDialog);
    } // setupUi

    void retranslateUi(QDialog *RegisterDialog)
    {
        RegisterDialog->setWindowTitle(QCoreApplication::translate("RegisterDialog", "RegisterDialog", nullptr));
        show_label->setText(QCoreApplication::translate("RegisterDialog", "TextLabel", nullptr));
        email_label->setText(QCoreApplication::translate("RegisterDialog", "\351\202\256\347\256\261\357\274\232", nullptr));
        code_label->setText(QCoreApplication::translate("RegisterDialog", "\351\252\214\350\257\201\347\240\201\357\274\232", nullptr));
        email_pushButton->setText(QCoreApplication::translate("RegisterDialog", "\350\216\267\345\217\226", nullptr));
        pass_label->setText(QCoreApplication::translate("RegisterDialog", "\345\257\206\347\240\201\357\274\232", nullptr));
        pass1_label->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244\357\274\232", nullptr));
        confirm_pushButton->setText(QCoreApplication::translate("RegisterDialog", "\347\241\256\350\256\244", nullptr));
        cancel_pushButton->setText(QCoreApplication::translate("RegisterDialog", "\345\217\226\346\266\210", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RegisterDialog: public Ui_RegisterDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
