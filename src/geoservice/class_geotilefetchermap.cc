#include <geoservice/class_geotilefetchermap.hh>

#include <qdir.h>
#include <qurl.h>
#include <qfileinfo.h>
#include <qnetworkaccessmanager.h>
#include <qnetworkrequest.h>
#include <private/qgeotilespec_p.h>
#include <private/qgeotilefetcher_p_p.h>
#include <qfile.h>
#include <floppy/logging.h>
#include <geoservice/parameters.hh>

namespace llog = floppy::log;
namespace qnx::geoservice
{

  CGeoTileFetcherMap::CGeoTileFetcherMap(
    CConfig* mapTypesFetcher,
    ::QVariantMap const& parameters,
    ::QGeoMappingManagerEngine* parent
  )
  {
    // todo
  }
  auto CGeoTileFetcherMap::getTileImage(QGeoTileSpec const& spec) -> ::QGeoTiledMapReply*
  {
    return nullptr;
  }
  auto CGeoTileFetcherMap::url(QGeoTileSpec const& spec) const -> ::QString { return QString(); }
  auto CGeoTileFetcherMap::storage_network_tile(::QGeoTiledMapReply* reply) -> void {}
} // namespace qnx::geoservice