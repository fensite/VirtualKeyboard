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
#ifndef ATSPISTATETRACKER_H
#define ATSPISTATETRACKER_H

#include <QObject>
#include <atspi/atspi.h>

class AtspiStateTracker : public QObject
{
    Q_OBJECT
public:
    explicit AtspiStateTracker(QObject *parent = nullptr);

Q_SIGNALS:
    void onFocus();
    void onFocusLoss();
    void onTextChanged();
public:
    void start();

public:
    static AtspiStateTracker* m_self;

private:
    void updateListeners();
    void registerAtspiListeners();

    static void onAtspiEvent(AtspiEvent *event, void *data);
    static void onAtspiFocus(AtspiEvent *event, void *data);
    static void onAtspiTextChanged(AtspiEvent *event, void *data);
    static void onAtspiTextCaretMoved(AtspiEvent *event, void *data);

private:
    AtspiEventListener *m_listener4Event;
    AtspiEventListener *m_listener4TextCaretMoved;
    AtspiEventListener *m_listener4Notify;
};

#endif // ATSPISTATETRACKER_H
