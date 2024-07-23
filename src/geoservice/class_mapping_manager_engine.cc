#include <geoservice/class_mapping_manager_engine.hh>

#include <qdir.h>
#include <private/qgeocameracapabilities_p.h>
#include <private/qgeomaptype_p.h>
#include <private/qgeotiledmap_p.h>
#include <floppy/logging.h>
#include <qnx/formatters.h>
#include <geoservice/parameters.hh>

namespace llog = floppy::log;

namespace cfg
{
  auto constexpr cache_size = 512 * 1024 * 1024;
} // namespace cfg

namespace qnx::geoservice
{
  CGeoTiledMappingManagerEngineMap::CGeoTiledMappingManagerEngineMap(
    QVariantMap const& parameters,
    ::QGeoServiceProvider::Error* error,
    ::QString* error_string
  ) {
    auto camera_capabilities = ::QGeoCameraCapabilities();
    camera_capabilities.setMinimumZoomLevel(0.0);
    camera_capabilities.setMaximumZoomLevel(18.0);
    camera_capabilities.setSupportsBearing(true);
    camera_capabilities.setSupportsTilting(true);
    camera_capabilities.setOverzoomEnabled(false);
    this->setCameraCapabilities(camera_capabilities);
    this->setTileSize({256, 256});
    //  auto mapTypesFetcher = MapTypesFetcher();
    //    auto targetConfigDirectoryKey = QString::fromStdString(ModuleParameters::parameter(ModuleParameters::ParameterType::TargetConfigDirectory));
    //    if(parameters.contains(targetConfigDirectoryKey)) {
    //        mapTypesFetcher.parse(parameters.value(targetConfigDirectoryKey).toString());
    //        qInfo() << "gs_plugin config_dir:\t" << parameters.value(targetConfigDirectoryKey).toString();
    //    }
    //    if(mapTypesFetcher.count() == 0) {
    //        throw std::runtime_error("Map config directory not found or no map types found in config directory");
    //    }
    //    QList<QGeoMapType> types;
    //    for(int i = 0 ; i < mapTypesFetcher.count(); ++i){
    //        types << mapTypesFetcher.mapType(i);
    //    }
    //    setSupportedMapTypes(types);
    //
    //
    //    setTileFetcher(new GeoTileFetcherMap(mapTypesFetcher, parameters, this));
    this->setTileCache(this->generate_tile_cache(parameters));
    this->m_prefetchStyle = ::QGeoTiledMap::NoPrefetching;
    *error = ::QGeoServiceProvider::NoError;
    error_string->clear();
  }

  auto CGeoTiledMappingManagerEngineMap::createMap() -> ::QGeoMap* {
    auto* map = new ::QGeoTiledMap(this, nullptr); // NOLINT(*-owning-memory)
    map->setPrefetchStyle(this->m_prefetchStyle);
    return map;
  }

  auto CGeoTiledMappingManagerEngineMap::generate_tile_cache(::QVariantMap const& parameters)
    -> ::QGeoFileTileCache* {
    auto cache_dir = parameters::parse(
      parameters,
      parameters::target_cache_directory,
      []() { llog::warn("CGeoTiledMappingManagerEngineMap: target_cache_directory parameter not found, falling back to default"); }
    ).value_or(::QAbstractGeoTileCache::baseLocationCacheDirectory());
    if(cache_dir.back() ==  QDir::separator())
      cache_dir.chop(1);
    cache_dir += ::QString::fromStdString(fmt::format("{}{}", static_cast<::QString>(::QDir::separator()), "qnx_geoservice"));
    llog::trace("CGeoTiledMappingManagerEngineMap: tile cache directory: {}", cache_dir);
    auto* tile_cache = new ::QGeoFileTileCache(cache_dir, this); // NOLINT(*-owning-memory)
    tile_cache->setMaxDiskUsage(cfg::cache_size);
    return tile_cache;
  }
} // namespace qnx::geoservice