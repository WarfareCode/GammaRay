/*
  qt3dgeometryextension.cpp

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

#include "qt3dgeometryextension.h"

#include <core/propertycontroller.h>

#include <Qt3DRender/QAttribute>
#include <Qt3DRender/QBuffer>
#include <Qt3DRender/QGeometry>
#include <Qt3DRender/QGeometryRenderer>

#include <Qt3DCore/QEntity>

#include <QDebug>

using namespace GammaRay;

Qt3DGeometryExtension::Qt3DGeometryExtension(GammaRay::PropertyController* controller) :
    Qt3DGeometryExtensionInterface(controller->objectBaseName() + ".qt3dGeometry", controller),
    PropertyControllerExtension(controller->objectBaseName() + ".qt3dGeometry"),
    m_geometry(nullptr)
{
}

Qt3DGeometryExtension::~Qt3DGeometryExtension()
{
}

bool Qt3DGeometryExtension::setQObject(QObject* object)
{
    Qt3DRender::QGeometryRenderer *geometry = nullptr;

    // try to find a half-way related QGeometryRenderer instance
    if (geometry = qobject_cast<Qt3DRender::QGeometryRenderer*>(object)) {
    } else if (auto entity = qobject_cast<Qt3DCore::QEntity*>(object)) {
        foreach (auto component, entity->components()) {
            if (geometry = qobject_cast<Qt3DRender::QGeometryRenderer*>(component))
                break;
        }
    } else if (auto geo = qobject_cast<Qt3DRender::QGeometry*>(object)) {
        return setQObject(geo->parent());
    } else if (auto attr = qobject_cast<Qt3DRender::QAttribute*>(object)) {
        return setQObject(attr->parent());
    } else if (auto buffer = qobject_cast<Qt3DRender::QBuffer*>(object)) {
        return setQObject(buffer->parent());
    }

    if (geometry == m_geometry)
        return geometry;
    m_geometry = geometry;

    if (!geometry)
        return false;

    // TODO
    qDebug() << geometry;

    return true;
}