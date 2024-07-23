#pragma once

#include <qgeoserviceprovider.h>
#include <private/qgeotiledmappingmanagerengine_p.h>
#include <private/qgeofiletilecache_p.h>
#include <qnx/detail/export.h>

namespace qnx::geoservice
{
  class CGeoTiledMappingManagerEngineMap : public ::QGeoTiledMappingManagerEngine
  {
   public:
    CGeoTiledMappingManagerEngineMap(
      ::QVariantMap const& parameters,
      ::QGeoServiceProvider::Error* error,
      ::QString* error_string
    );
    virtual ~CGeoTiledMappingManagerEngineMap() override = default;

    [[nodiscard]] auto createMap() -> ::QGeoMap* override;

   protected:
    [[nodiscard]] auto generate_tile_cache(::QVariantMap const& parameters) -> ::QGeoFileTileCache*;
  };
} // namespace qnx::geoservice