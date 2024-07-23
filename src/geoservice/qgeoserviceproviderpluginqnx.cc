#include <qnx/geoservice/qgeoserviceproviderpluginqnx.h>

#include <floppy/logging.h>
#include <qnx/detail/export.h>
#include <geoservice/class_mapping_manager_engine.hh>

namespace llog = floppy::log;

#if defined(QNX_STATIC_LIBRARY)
extern "C" QNX_API auto qt_plugin_query_metadata_v2() -> QT_PREPEND_NAMESPACE(QPluginMetaData);
extern "C" QNX_API auto qt_plugin_instance() -> QT_PREPEND_NAMESPACE(QObject)*;
[[maybe_unused]] auto qt_static_plugin_qnx_plugin() -> QT_PREPEND_NAMESPACE(QStaticPlugin) {
  auto const plugin = QT_PREPEND_NAMESPACE(QStaticPlugin) {
    qt_plugin_instance,
    qt_plugin_query_metadata_v2
  };
  return plugin;
}
#endif // defined(QNX_STATIC_LIBRARY)

QT_BEGIN_NAMESPACE

auto QGeoServiceProviderFactoryQNX::createMappingManagerEngine(
  QVariantMap const& parameters,
  QGeoServiceProvider::Error* error,
  QString* errorString
) const -> QGeoMappingManagerEngine* {
  llog::trace("QGeoServiceProviderFactoryQNX: creating mapping manager engine");
  return new qnx::geoservice::CGeoTiledMappingManagerEngineMap(parameters, error, errorString); // NOLINT(*-owning-memory)
}

QT_END_NAMESPACE