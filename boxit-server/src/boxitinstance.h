/*
 *  BoxIt - Manjaro Linux Repository Management Software
 *  Roland Singer <roland@manjaro.org>
 *
 *  Copyright (C) 2007 Free Software Foundation, Inc.
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BOXITINSTANCE_H
#define BOXITINSTANCE_H

#include <QString>
#include <QList>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QByteArray>
#include <QCryptographicHash>
#include <QMutex>
#include <QMutexLocker>
#include <unistd.h>

#include "network/boxitsocket.h"
#include "const.h"
#include "user/user.h"
#include "user/userdbs.h"
#include "db/database.h"


class BoxitInstance : public BoxitSocket
{
    Q_OBJECT
public:
    BoxitInstance(const int sessionID);
    ~BoxitInstance();

private:
    const QString tmpPath;
    int loginCount, syncSessionID;
    User user;
    QFile file;
    QByteArray fileCheckSum;
    QStringList uploadedFiles;
    bool listenOnStatus;
    QMutex statusMutex;

    void cleanupTmpDir();
    void sendStringList(const quint16 msgID, const QStringList & list);

private slots:
    void read_Data(quint16 msgID, QByteArray data);
    void sendStatus();
    void statusBranchSessionFinished(int sessionID);
    void statusBranchSessionFailed(int sessionID);

};


#endif // BOXITINSTANCE_H
