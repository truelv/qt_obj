/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/
#include "global.h"
#include "myinputpanel.h"
#include <QDebug>

//! [0]

MyInputPanel::MyInputPanel()
    : QWidget(0, Qt::Tool | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint),
      lastFocusedWidget(0)
{
    form.setupUi(this);

    this->setStyleSheet("#MyInputPanelForm{background-color:rgb(153, 153, 153);border-radius:20px;}");
    form.panelButton_0->setStyleSheet("font: 50pt;");
    form.panelButton_1->setStyleSheet("font: 50pt;");
    form.panelButton_2->setStyleSheet("font: 50pt;");
    form.panelButton_3->setStyleSheet("font: 50pt;");
    form.panelButton_4->setStyleSheet("font: 50pt;");
    form.panelButton_5->setStyleSheet("font: 50pt;");
    form.panelButton_6->setStyleSheet("font: 50pt;");
    form.panelButton_7->setStyleSheet("font: 50pt;");
    form.panelButton_8->setStyleSheet("font: 50pt;");
    form.panelButton_9->setStyleSheet("font: 50pt;");
    form.panelButton_a->setStyleSheet("font: 50pt;");
    form.panelButton_abcpgdn->setStyleSheet("font: 50pt;");
    form.panelButton_abcpgup->setStyleSheet("font: 50pt;");
    form.panelButton_abctomark->setStyleSheet("font: 50pt;");
    form.panelButton_addition->setStyleSheet("font: 50pt;");
    form.panelButton_and->setStyleSheet("font: 50pt;");
    form.panelButton_apostrophe->setStyleSheet("font: 50pt;");
    form.panelButton_asterisk->setStyleSheet("font: 50pt;");
    form.panelButton_at->setStyleSheet("font: 50pt;");
    form.panelButton_b->setStyleSheet("font: 50pt;");
    form.panelButton_backquote->setStyleSheet("font: 50pt;");
    form.panelButton_backslash->setStyleSheet("font: 50pt;");
    form.panelButton_backspace->setStyleSheet("image: url(" PROJECT_DIR_IMG"/backspace.png)");
    form.panelButton_c->setStyleSheet("font: 50pt;");
    form.panelButton_Caps1->setStyleSheet("font: 50pt;");
    form.panelButton_Caps2->setStyleSheet("font: 50pt;");
    form.panelButton_caret->setStyleSheet("font: 50pt;");
    form.panelButton_colon->setStyleSheet("font: 50pt;");
    form.panelButton_comma->setStyleSheet("font: 50pt;");
    form.panelButton_d->setStyleSheet("font: 50pt;");
    form.panelButton_dollar->setStyleSheet("font: 50pt;");
    form.panelButton_double_apostrophe->setStyleSheet("font: 50pt;");
    form.panelButton_e->setStyleSheet("font: 50pt;");
    form.panelButton_equality->setStyleSheet("font: 50pt;");
    form.panelButton_exclamation->setStyleSheet("font: 50pt;");
    form.panelButton_f->setStyleSheet("font: 50pt;");
    form.panelButton_g->setStyleSheet("font: 50pt;");
    form.panelButton_h->setStyleSheet("font: 50pt;");
    form.panelButton_hash->setStyleSheet("font: 50pt;");
    form.panelButton_hash_key->setStyleSheet("font: 50pt;");
    form.panelButton_i->setStyleSheet("font: 50pt;");
    form.panelButton_j->setStyleSheet("font: 50pt;");
    form.panelButton_k->setStyleSheet("font: 50pt;");
    form.panelButton_l->setStyleSheet("font: 50pt;");
    form.panelButton_L_l_bracket->setStyleSheet("font: 50pt;");
    form.panelButton_L_m_bracket->setStyleSheet("font: 50pt;");
    form.panelButton_L_s_bracket->setStyleSheet("font: 50pt;");
    form.panelButton_m->setStyleSheet("font: 50pt;");
    form.panelButton_markpgdn->setStyleSheet("font: 50pt;");
    form.panelButton_markpgup->setStyleSheet("font: 50pt;");
    form.panelButton_modulus->setStyleSheet("font: 50pt;");
    form.panelButton_n->setStyleSheet("font: 50pt;");
    form.panelButton_numtomark->setStyleSheet("font: 50pt;");
    form.panelButton_o->setStyleSheet("font: 50pt;");
    form.panelButton_or->setStyleSheet("font: 50pt;");
    form.panelButton_p->setStyleSheet("font: 50pt;");
    form.panelButton_point->setStyleSheet("font: 50pt;");
    form.panelButton_point_2->setStyleSheet("font: 50pt;");
    form.panelButton_q->setStyleSheet("font: 50pt;");
    form.panelButton_question->setStyleSheet("font: 50pt;");
    form.panelButton_r->setStyleSheet("font: 50pt;");
    form.panelButton_R_l_bracket->setStyleSheet("font: 50pt;");
    form.panelButton_R_m_bracket->setStyleSheet("font: 50pt;");
    form.panelButton_R_s_bracket->setStyleSheet("font: 50pt;");
    form.panelButton_s->setStyleSheet("font: 50pt;");
    form.panelButton_semicolon->setStyleSheet("font: 50pt;");
    form.panelButton_slash->setStyleSheet("font: 50pt;");
    form.panelButton_space->setStyleSheet("font: 50pt;");
    form.panelButton_star->setStyleSheet("font: 50pt;");
    form.panelButton_subtraction->setStyleSheet("font: 50pt;");
    form.panelButton_switchbox->setStyleSheet("font: 50pt;");
    form.panelButton_t->setStyleSheet("font: 50pt;");
    form.panelButton_tilde->setStyleSheet("font: 50pt;");
    form.panelButton_u->setStyleSheet("font: 50pt;");
    form.panelButton_v->setStyleSheet("font: 50pt;");
    form.panelButton_w->setStyleSheet("font: 50pt;");
    form.panelButton_x->setStyleSheet("font: 50pt;");
    form.panelButton_xyztomark->setStyleSheet("font: 50pt;");
    form.panelButton_y->setStyleSheet("font: 50pt;");
    form.panelButton_z->setStyleSheet("font: 50pt;");
    form.panelButton__->setStyleSheet("font: 50pt;");
    form.closeButton->setStyleSheet("font: 50pt;");
    // 默认数字键盘
    form.stackedWidget->setCurrentIndex(0);
    form.panelButton_switchbox->setText(tr("abc"));
    form.panelButton_switchbox->setProperty("jointype", 1); // 1表示字母键盘

    form.panelButton_Caps1->setProperty("textType", 1); // 字母键盘，默认点击切换为大写
    form.panelButton_Caps2->setProperty("textType", 1);

    connect(form.panelButton_markpgdn, SIGNAL(clicked()), this, SLOT(slotPanelPageDown()));
    connect(form.panelButton_abcpgdn, SIGNAL(clicked()), this, SLOT(slotPanelPageDown()));
    connect(form.panelButton_abcpgup, SIGNAL(clicked()), this, SLOT(slotPanelPageUp()));
    connect(form.panelButton_markpgup, SIGNAL(clicked()), this, SLOT(slotPanelPageUp()));

    connect(qApp, SIGNAL(focusChanged(QWidget*,QWidget*)),
            this, SLOT(saveFocusWidget(QWidget*,QWidget*)));

    signalMapper.setMapping(form.panelButton_1, form.panelButton_1);
    signalMapper.setMapping(form.panelButton_2, form.panelButton_2);
    signalMapper.setMapping(form.panelButton_3, form.panelButton_3);
    signalMapper.setMapping(form.panelButton_4, form.panelButton_4);
    signalMapper.setMapping(form.panelButton_5, form.panelButton_5);
    signalMapper.setMapping(form.panelButton_6, form.panelButton_6);
    signalMapper.setMapping(form.panelButton_7, form.panelButton_7);
    signalMapper.setMapping(form.panelButton_8, form.panelButton_8);
    signalMapper.setMapping(form.panelButton_9, form.panelButton_9);
    signalMapper.setMapping(form.panelButton_star, form.panelButton_star);
    signalMapper.setMapping(form.panelButton_0, form.panelButton_0);
    signalMapper.setMapping(form.panelButton_hash, form.panelButton_hash);
    signalMapper.setMapping(form.panelButton_point, form.panelButton_point);
    signalMapper.setMapping(form.panelButton_backspace, form.panelButton_backspace);
    signalMapper.setMapping(form.panelButton_space, form.panelButton_space);

    signalMapper.setMapping(form.panelButton_a, form.panelButton_a);
    signalMapper.setMapping(form.panelButton_b, form.panelButton_b);
    signalMapper.setMapping(form.panelButton_c, form.panelButton_c);
    signalMapper.setMapping(form.panelButton_d, form.panelButton_d);
    signalMapper.setMapping(form.panelButton_e, form.panelButton_e);
    signalMapper.setMapping(form.panelButton_f, form.panelButton_f);
    signalMapper.setMapping(form.panelButton_g, form.panelButton_g);
    signalMapper.setMapping(form.panelButton_h, form.panelButton_h);
    signalMapper.setMapping(form.panelButton_i, form.panelButton_i);
    signalMapper.setMapping(form.panelButton_j, form.panelButton_j);
    signalMapper.setMapping(form.panelButton_k, form.panelButton_k);
    signalMapper.setMapping(form.panelButton_l, form.panelButton_l);
    signalMapper.setMapping(form.panelButton_m, form.panelButton_m);
    signalMapper.setMapping(form.panelButton_n, form.panelButton_n);
    signalMapper.setMapping(form.panelButton_o, form.panelButton_o);
    signalMapper.setMapping(form.panelButton_p, form.panelButton_p);
    signalMapper.setMapping(form.panelButton_q, form.panelButton_q);
    signalMapper.setMapping(form.panelButton_r, form.panelButton_r);
    signalMapper.setMapping(form.panelButton_s, form.panelButton_s);
    signalMapper.setMapping(form.panelButton_t, form.panelButton_t);
    signalMapper.setMapping(form.panelButton_u, form.panelButton_u);
    signalMapper.setMapping(form.panelButton_v, form.panelButton_v);
    signalMapper.setMapping(form.panelButton_w, form.panelButton_w);
    signalMapper.setMapping(form.panelButton_x, form.panelButton_x);
    signalMapper.setMapping(form.panelButton_y, form.panelButton_y);
    signalMapper.setMapping(form.panelButton_z, form.panelButton_z);

    signalMapper.setMapping(form.panelButton_addition, form.panelButton_addition);
    signalMapper.setMapping(form.panelButton_and, form.panelButton_and);
    signalMapper.setMapping(form.panelButton_apostrophe, form.panelButton_apostrophe);
    signalMapper.setMapping(form.panelButton_asterisk, form.panelButton_asterisk);
    signalMapper.setMapping(form.panelButton_at, form.panelButton_at);
    signalMapper.setMapping(form.panelButton_backquote, form.panelButton_backquote);
    signalMapper.setMapping(form.panelButton_backslash, form.panelButton_backslash);
    signalMapper.setMapping(form.panelButton_caret, form.panelButton_caret);
    signalMapper.setMapping(form.panelButton_colon, form.panelButton_colon);
    signalMapper.setMapping(form.panelButton_comma, form.panelButton_comma);
    signalMapper.setMapping(form.panelButton_dollar, form.panelButton_dollar);
    signalMapper.setMapping(form.panelButton_double_apostrophe, form.panelButton_double_apostrophe);
    signalMapper.setMapping(form.panelButton_equality, form.panelButton_equality);
    signalMapper.setMapping(form.panelButton_exclamation, form.panelButton_exclamation);
    signalMapper.setMapping(form.panelButton_hash_key, form.panelButton_hash_key);
    signalMapper.setMapping(form.panelButton_L_l_bracket, form.panelButton_L_l_bracket);
    signalMapper.setMapping(form.panelButton_L_m_bracket, form.panelButton_L_m_bracket);
    signalMapper.setMapping(form.panelButton_L_s_bracket, form.panelButton_L_s_bracket);
    signalMapper.setMapping(form.panelButton_R_l_bracket, form.panelButton_R_l_bracket);
    signalMapper.setMapping(form.panelButton_R_m_bracket, form.panelButton_R_m_bracket);
    signalMapper.setMapping(form.panelButton_R_s_bracket, form.panelButton_R_s_bracket);
    signalMapper.setMapping(form.panelButton_modulus, form.panelButton_modulus);
    signalMapper.setMapping(form.panelButton_or, form.panelButton_or);
    signalMapper.setMapping(form.panelButton_point_2, form.panelButton_point_2);
    signalMapper.setMapping(form.panelButton_question, form.panelButton_question);
    signalMapper.setMapping(form.panelButton_semicolon, form.panelButton_semicolon);
    signalMapper.setMapping(form.panelButton_slash, form.panelButton_slash);
    signalMapper.setMapping(form.panelButton_subtraction, form.panelButton_subtraction);
    signalMapper.setMapping(form.panelButton_tilde, form.panelButton_tilde);
    signalMapper.setMapping(form.panelButton__, form.panelButton__);

    connect(form.panelButton_1, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_2, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_3, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_4, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_5, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_6, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_7, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_8, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_9, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_star, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_0, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_hash, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_point, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));

    connect(form.panelButton_backspace, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_space, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));


    connect(form.panelButton_a, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_b, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_c, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_d, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_e, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_f, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_g, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_h, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_i, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_j, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_k, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_l, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_m, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_n, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_o, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_p, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_q, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_r, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_s, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_t, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_u, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_v, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_w, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_x, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_y, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_z, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));

    connect(form.panelButton_addition, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_and, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_apostrophe, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_asterisk, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_at, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_backquote, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_backslash, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_caret, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_colon, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_comma, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_dollar, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_double_apostrophe, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_equality, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_exclamation, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_hash_key, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_L_l_bracket, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_L_m_bracket, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_L_s_bracket, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_R_l_bracket, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_R_m_bracket, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_R_s_bracket, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_modulus, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_or, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_point_2, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_question, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_semicolon, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_slash, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_subtraction, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton_tilde, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));
    connect(form.panelButton__, SIGNAL(clicked()),
            &signalMapper, SLOT(map()));


    connect(&signalMapper, SIGNAL(mapped(QWidget*)),
            this, SLOT(buttonClicked(QWidget*)));
}

//! [0]

bool MyInputPanel::event(QEvent *e)
{
    switch (e->type())
    {
    //! [1]
    case QEvent::WindowActivate:
        if (lastFocusedWidget)
            lastFocusedWidget->activateWindow();
        break;
        //! [1]
    default:
        break;
    }

    return QWidget::event(e);
}

//! [2]

void MyInputPanel::saveFocusWidget(QWidget * /*oldFocus*/, QWidget *newFocus)
{
    if (newFocus != 0 && !this->isAncestorOf(newFocus))
    {
        lastFocusedWidget = newFocus;
    }
}

//! [2]

//! [3]

void MyInputPanel::buttonClicked(QWidget *w)
{
    int code = qvariant_cast<int>(w->property("keyCode"));
    //qDebug() << "按键字符" << code;
    emit characterGenerated(code);
}

//! [3]

void MyInputPanel::on_panelButton_switchbox_clicked()
{
    // 切换数字字母键盘
    int jointype = sender()->property("jointype").toInt();
    switch (jointype)
    {
    case 0:
        // 进入数字键盘
        form.stackedWidget->setCurrentIndex(0);
        form.panelButton_switchbox->setText(tr("abc"));
        form.panelButton_switchbox->setProperty("jointype", 1);
        break;
    case 1:
        // 进入字母键盘
        form.stackedWidget->setCurrentIndex(1);
        form.panelButton_switchbox->setText(tr("123"));
        form.panelButton_switchbox->setProperty("jointype", 0);
        break;
    default:
        break;
    }
}

void MyInputPanel::on_panelButton_xyztomark_clicked()
{
    form.stackedWidget->setCurrentIndex(3);
    form.panelButton_switchbox->setText(tr("abc"));
    form.panelButton_switchbox->setProperty("jointype", 1);
}

void MyInputPanel::on_panelButton_abctomark_clicked()
{
    form.stackedWidget->setCurrentIndex(3);
    form.panelButton_switchbox->setText(tr("abc"));
    form.panelButton_switchbox->setProperty("jointype", 1);
}

void MyInputPanel::on_panelButton_numtomark_clicked()
{
    form.stackedWidget->setCurrentIndex(3);
    form.panelButton_switchbox->setText(tr("123"));
    form.panelButton_switchbox->setProperty("jointype", 0);
}

void MyInputPanel::slotPanelPageDown()
{
    int index = form.stackedWidget->currentIndex();
    form.stackedWidget->setCurrentIndex(index+1);
}

void MyInputPanel::slotPanelPageUp()
{
    int index = form.stackedWidget->currentIndex();
    form.stackedWidget->setCurrentIndex(index-1);
}

void MyInputPanel::on_panelButton_Caps2_clicked()
{
    int type = sender()->property("textType").toInt();
    if (1==type)
        form.panelButton_Caps2->setProperty("textType", 0);
    else
        form.panelButton_Caps2->setProperty("textType", 1);

    // 显示修改为大写/小写
    const QObjectList& list = form.stackedWidget->widget(2)->children();
    //qDebug() << "有子控件个数 " << list.count();
    foreach (QObject* obj, list)
    {
        //qDebug() << "修改大小写\n" << obj->objectName();
        if (!obj->inherits("QPushButton") || obj->objectName().length()>13)
            continue ;
        QPushButton* bt = (QPushButton*)obj;
        if (1==type)
        {
            bt->setText(bt->text().toUpper());
            int code = bt->property("keyCode").toInt();
            bt->setProperty("keyCode", code-32);
        }
        else
        {
            bt->setText(bt->text().toLower());
            int code = bt->property("keyCode").toInt();
            bt->setProperty("keyCode", code+32);
        }
    }
}

void MyInputPanel::on_panelButton_Caps1_clicked()
{
    int type = sender()->property("textType").toInt();
    if (1==type)
        form.panelButton_Caps1->setProperty("textType", 0);
    else
        form.panelButton_Caps1->setProperty("textType", 1);

    // 显示修改为大写/小写
    const QObjectList& list = form.stackedWidget->widget(1)->children();
    foreach (QObject* obj, list)
    {
        if (!obj->inherits("QPushButton") || obj->objectName().length()>13)
            continue ;
        QPushButton* bt = (QPushButton*)obj;
        if (1==type)
        {
            bt->setText(bt->text().toUpper());
            int code = bt->property("keyCode").toInt();
            bt->setProperty("keyCode", code-32);
        }
        else
        {
            bt->setText(bt->text().toLower());
            int code = bt->property("keyCode").toInt();
            bt->setProperty("keyCode", code+32);
        }
    }
}

void MyInputPanel::on_stackedWidget_currentChanged(int num)
{
    // 不管最终字母键盘是大写或小写，重新切到界面，都小写显示
    switch (num)
    {
        case 1:
        {
            if (1==form.panelButton_Caps1->property("textType").toInt())
                return;

            form.panelButton_Caps1->setProperty("textType", 1);
            break;
        }
        case 2:
        {
            if (1==form.panelButton_Caps2->property("textType").toInt())
                return;

            form.panelButton_Caps2->setProperty("textType", 1);
            break;
        }
        default:
            return;
            break;
    }

    const QObjectList& list = form.stackedWidget->widget(num)->children();
    foreach (QObject* obj, list)
    {
        // panelButton_i
        if (!obj->inherits("QPushButton") || obj->objectName().length()>13)
            continue ;
        QPushButton* bt = (QPushButton*)obj;
        bt->setText(bt->text().toLower());
        int code = bt->property("keyCode").toInt();
        bt->setProperty("keyCode", code+32);
    }
}
