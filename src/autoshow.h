/*
 * Copyright (C) 2020 Tianjin KYLIN Information Technology Co., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: ZHAI Kang-ning <zhaikangning@kylinos.cn>
**/
#ifndef AUTOSHOW_H
#define AUTOSHOW_H

#include <QObject>
#include <QGSettings>

class VirtualKeyboard;
class AtspiStateTracker;

class AutoShow : public QObject
{
    Q_OBJECT
public:
    explicit AutoShow(VirtualKeyboard *keyboard, QObject *parent = nullptr);

signals:

private:
    VirtualKeyboard *m_virtualKeyboard;
    AtspiStateTracker *m_atspiStateTracker;

private Q_SLOTS:
    void showKeyboard();
    void hideKeyboard();

private:
    bool m_isTabletMode;
    QGSettings *m_tabletModeGSettings;
};

#endif // AUTOSHOW_H
