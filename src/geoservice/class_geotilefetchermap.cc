#include <geoservice/class_geotilefetchermap.hh>

namespace qnx::geoservice
{

  CGeoTileFetcherMap::CGeoTileFetcherMap(CConfig* mapTypesFetcher, QVariantMap const& parameters,
                                         ::QGeoMappingManagerEngine* parent)
  {
  }
  auto CGeoTileFetcherMap::getTileImage(QGeoTileSpec const& spec) -> ::QGeoTiledMapReply*
  {
    return nullptr;
  }
  auto CGeoTileFetcherMap::url(QGeoTileSpec const& spec) const -> ::QString { return QString(); }
  auto CGeoTileFetcherMap::storage_network_tile(::QGeoTiledMapReply* reply) -> void {}
} // namespace qnx::geoservice