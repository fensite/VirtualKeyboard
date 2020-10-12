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
#include "atspistatetracker.h"
#include <QDebug>

AtspiStateTracker* AtspiStateTracker::m_self = NULL;
AtspiStateTracker::AtspiStateTracker(QObject *parent) : QObject(parent)
{
    m_self = this;
    m_listener4Event = atspi_event_listener_new(onAtspiFocus, NULL, NULL);
    m_listener4TextCaretMoved = atspi_event_listener_new(onAtspiTextCaretMoved, NULL, NULL);
    atspi_init();
    registerAtspiListeners();
}

void AtspiStateTracker::start()
{
    atspi_event_main ();
}

void AtspiStateTracker::updateListeners()
{

}

void AtspiStateTracker::registerAtspiListeners()
{
    atspi_event_listener_register (m_listener4Event, "object:state-changed:focused", NULL);
//    atspi_event_listener_register (m_listener4Event, "object:state-changed:sensitive", NULL);
    atspi_event_listener_register (m_listener4Event, "object:state-changed:active", NULL);
    atspi_event_listener_register (m_listener4Event, "mouse:abs:focus", NULL);
//    atspi_event_listener_register (m_listener4Event, "object:state-changed:visible", NULL);
//    atspi_event_listener_register (m_listener4Event, "object:state-changed", NULL);
//    atspi_event_listener_register (m_listener4Event, "object:text-changed", NULL);
//    atspi_event_listener_register (m_listener4Event, "window:activate", NULL);
    atspi_event_listener_register (m_listener4TextCaretMoved, "object:text-caret-moved", NULL);
    atspi_event_listener_register (m_listener4TextCaretMoved, "object:text-entry-activated", NULL);
//    atspi_event_listener_register (m_listener4Event, "object:state-changed:selected", NULL);
//    atspi_event_listener_register (m_listener4Event, "object:text-changed:insert", NULL);
//    atspi_event_listener_register (m_listener4Event, "object:text-changed:delete", NULL);
//    atspi_event_listener_register (m_listener4Event, "object:text-caret-moved", NULL);
//    atspi_event_listener_register (m_listener4Event, "window:desktop-destroy:active", NULL);
//    object:state-changed:focused
//    object:state-changed:active  object:state-changed:sensitive  object:state-changed:enabled   object:state-changed:showing  object:text-caret-moved
}

void AtspiStateTracker::onAtspiEvent(AtspiEvent *event, void *data)
{
}

void AtspiStateTracker::onAtspiFocus(AtspiEvent *event, void *data)
{
//    qDebug() << "-----------------event type " << event->type;
    AtspiAccessible *application = NULL;
     gchar *app_name = NULL;

     if (event->source == NULL)
       return;

     /* We only care about focus/selection gain */
     if (!event->detail1)
     {
         emit m_self->onFocusLoss();
         return;
     }

     application = atspi_accessible_get_application (event->source, NULL);
     if (application == NULL)
       return;

     app_name = atspi_accessible_get_name (application, NULL);
     AtspiEditableText *editable = atspi_accessible_get_editable_text(event->source);
     if (editable == NULL)
     {
//         qDebug() << "----------------------------editable:false";
     } else {
         emit m_self->onFocus();
//         qDebug() << "----------------------------editable:true";
     }
//     qDebug() << "----------------------------app_name:" << app_name;
//     qDebug() << "----------------------------process_id:" << atspi_accessible_get_process_id (event->source, NULL);

//    qDebug() << "-----------------event  source " << event->source;
}

void AtspiStateTracker::onAtspiTextCaretMoved(AtspiEvent *event, void *data)
{
    AtspiAccessible *application = NULL;
     gchar *app_name = NULL;

     if (event->source == NULL)
       return;

     /* We only care about focus/selection gain */
     if (!event->detail1)
       return;

     application = atspi_accessible_get_application (event->source, NULL);
     if (application == NULL)
       return;

     app_name = atspi_accessible_get_name (application, NULL);
//     qDebug() << "----------------------------app_name:" << app_name;
//     qDebug() << "-----------------event type " << event->type;
}

void AtspiStateTracker::onAtspiTextChanged(AtspiEvent *event, void *data)
{
//    qDebug() << "-----------------onAtspiTextChanged";
    emit m_self->onTextChanged();
}
