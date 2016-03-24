/*
  3dinspector.h

  This file is part of GammaRay, the Qt application inspection and
  manipulation tool.

  Copyright (C) 2016 Klarälvdalens Datakonsult AB, a KDAB Group company, info@kdab.com
  Author: Volker Krause <volker.krause@kdab.com>

  Licensees holding valid commercial KDAB GammaRay licenses may use this file in
  accordance with GammaRay Commercial License Agreement provided with the Software.

  Contact info@kdab.com if any conditions of this licensing are not clear to you.

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef GAMMARAY_3DINSPECTOR_3DINSPECTOR_H
#define GAMMARAY_3DINSPECTOR_3DINSPECTOR_H

#include "qt3dinspectorinterface.h"

#include <core/toolfactory.h>

#include <Qt3DCore/QNode>

namespace Qt3DCore {
class QAspectEngine;
}

namespace GammaRay {

class Qt3DEntityTreeModel;

class Qt3DInspector: public Qt3DInspectorInterface
{
    Q_OBJECT
    Q_INTERFACES(GammaRay::Qt3DInspectorInterface)
public:
    explicit Qt3DInspector(ProbeInterface *probe, QObject *parent = 0);
    ~Qt3DInspector();

public slots:
    void selectEngine(int index) override;

private slots:
    void objectSelected(QObject *obj);

private:
    void selectEngine(Qt3DCore::QAspectEngine *engine);

    void registerCoreMetaTypes();
    void registerRenderMetaTypes();

private:
    QAbstractItemModel *m_engineModel;
    Qt3DCore::QAspectEngine *m_engine;
    Qt3DEntityTreeModel *m_entityModel;
};

class Qt3DInspectorFactory: public QObject, public StandardToolFactory<Qt3DCore::QNode, Qt3DInspector>
{
    Q_OBJECT
    Q_INTERFACES(GammaRay::ToolFactory)
    Q_PLUGIN_METADATA(IID "com.kdab.GammaRay.ToolFactory" FILE "gammaray_3dinspector.json")

public:
    explicit Qt3DInspectorFactory(QObject *parent = 0) : QObject(parent)
    {
    }

    QString name() const Q_DECL_OVERRIDE;
};

}

#endif

