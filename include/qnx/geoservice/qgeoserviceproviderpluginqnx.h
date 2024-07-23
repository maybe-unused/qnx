#pragma once

#include <qobject.h>
#include <qgeoserviceproviderfactory.h>

QT_BEGIN_NAMESPACE

class QGeoServiceProviderFactoryQNX : public QObject,
                                      public QGeoServiceProviderFactory
{
  Q_OBJECT
  Q_INTERFACES(QGeoServiceProviderFactory)
  Q_PLUGIN_METADATA(IID "org.qt-project.qt.geoservice.serviceproviderfactory/6.0"
                    FILE "qnx_plugin.json")

 public:
  auto createMappingManagerEngine(
    QVariantMap const& parameters,
    QGeoServiceProvider::Error* error,
    QString* errorString
  ) const -> QGeoMappingManagerEngine* override;
};

QT_END_NAMESPACE