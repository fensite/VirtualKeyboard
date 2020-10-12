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
#include <QGSettings>
#include <QSettings>
#include "autoshow.h"
#include "virtualkeyboard.h"
#include "atspistatetracker.h"
#include <QDebug>

const QByteArray SCHEME_TABLET_MODE = "org.ukui.SettingsDaemon.plugins.tablet-mode";
const QString KEY_TABLE_MODE = "tablet-mode";

AutoShow::AutoShow(VirtualKeyboard *keyboard, QObject *parent) : QObject(parent),
    m_isTabletMode(false),
    m_tabletModeGSettings(nullptr)
{
    m_virtualKeyboard = keyboard;
    m_atspiStateTracker = new AtspiStateTracker(this);
    connect(AtspiStateTracker::m_self, SIGNAL(onFocus(void)), this, SLOT(showKeyboard(void)));
    connect(AtspiStateTracker::m_self, SIGNAL(onFocusLoss(void)), this, SLOT(hideKeyboard(void)));
    connect(m_virtualKeyboard, SIGNAL(aboutToClose(void)),  this, SLOT(hideKeyboard(void)));

    if (QGSettings::isSchemaInstalled(SCHEME_TABLET_MODE)) {
        m_tabletModeGSettings = new QGSettings(SCHEME_TABLET_MODE, QByteArray(), this);
        if(m_tabletModeGSettings != nullptr)
        {
            m_isTabletMode = m_tabletModeGSettings->get(KEY_TABLE_MODE).toBool();
        }
    }

    if(m_tabletModeGSettings) {
        connect(m_tabletModeGSettings, &QGSettings::changed, this, [=](const QString &key){
            if (key == "tabletMode") {
                m_isTabletMode = m_tabletModeGSettings->get(KEY_TABLE_MODE).toBool();
            }
        });
    }

    m_atspiStateTracker->start();
}

void AutoShow::showKeyboard()
{
    if(!m_isTabletMode)
        return;

    m_virtualKeyboard->show();
}

void AutoShow::hideKeyboard()
{
    if(m_virtualKeyboard && m_virtualKeyboard->isVisible())
        m_virtualKeyboard->hide();
}
