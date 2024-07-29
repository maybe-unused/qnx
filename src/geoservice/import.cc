#include <qnx/geoservice/import.h>

#include <qplugin.h>
#include <qgeoserviceprovider.h>
#include <floppy/logging.h>
#include <qnx/formatters.h>

namespace llog = floppy::log;

inline auto init_plugin() -> void {
  #if defined(QNX_STATIC_LIBRARY)
  Q_IMPORT_PLUGIN(qnx_plugin);
  #endif // defined(QNX_STATIC_LIBRARY)
}

namespace qnx // NOLINT(*-concat-nested-namespaces)
{
  inline namespace imports
  {
    [[maybe_unused]] [[nodiscard]] auto import_geoservice_plugin() -> bool {
      ::init_plugin();
      llog::trace("qnx::import_geoservice_plugin: importing qnx geoservice plugin");
      llog::trace("qnx::import_geoservice_plugin: available service providers(): {}",
        ::QGeoServiceProvider::availableServiceProviders().join(", ")
      );
      if(not ::QGeoServiceProvider::availableServiceProviders().contains("qnx", Qt::CaseInsensitive)) {
        llog::error("qnx::import_geoservice_plugin: qnx not found in any known library paths");
        return false;
      }
      if(auto const t = ::QGeoServiceProvider("qnx"); t.error()) {
        llog::error("qnx::import_geoservice_plugin: qnx returned an error ({})", t.errorString());
        return false;
      }
      llog::debug("qnx::import_geoservice_plugin: qnx plugin imported successfully (geoservice/qnx)");
      return true;
    }
  } // namespace imports
} // namespace qnx