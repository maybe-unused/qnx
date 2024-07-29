#pragma once

#include <vector>
#include <qlist.h>
#include <qnx/detail/export.h>
#include <floppy/configuration.h>

class QGeoMapType;
namespace qnx::geoservice
{
  struct ConfigData final
  {
    enum class MapStyle
    {
      NoMap = 0,
      StreetMap,
      SatelliteMapDay,
      SatelliteMapNight,
      TerrainMap,
      HybridMap,
      TransitMap,
      GrayStreetMap,
      PedestrianMap,
      CarNavigationMap,
      CycleMap,
      CustomMap = 100
    };

    struct ViewEntry
    {
      u16 id{};
      std::string name;
      std::string description;
      MapStyle style = MapStyle::GrayStreetMap;
      std::string offline_url;
      std::string online_url;
      bool supports_bearing = true;
      bool supports_tilting = true;
      bool supports_rolling = true;
      std::pair<u16, u16> zoom_range = { 0, 20 };
    };

    std::vector<ViewEntry> views = {
      ViewEntry {
        .id = 0,
        .name = "street",
        .description = "Default street view (Google Maps)",
        .style = MapStyle::StreetMap,
        .offline_url = "",
        .online_url = "https://mt.google.com/vt/lyrs=r&hl=ru&z={z}&x={x}&y={y}"
      },
      ViewEntry {
        .id = 1,
        .name = "satellite",
        .description = "Default satellite view (Google Maps)",
        .style = MapStyle::SatelliteMapDay,
        .offline_url = "",
        .online_url = "https://mt.google.com/vt/lyrs=s&hl=ru&z={z}&x={x}&y={y}"
      },
      ViewEntry {
        .id = 2,
        .name = "hybrid",
        .description = "Default hybrid view (Google Maps)",
        .style = MapStyle::HybridMap,
        .offline_url = "",
        .online_url = "https://mt.google.com/vt/lyrs=y&hl=ru&z={z}&x={x}&y={y}"
      }
    };
  };
} // namespace qnx::geoservice

namespace floppy::serialization
{
  template <> auto serialize<format::yaml>(qnx::geoservice::ConfigData const& value) -> std::string;
  template <> auto deserialize<format::yaml>(std::string const& value) -> qnx::geoservice::ConfigData;
} // namespace floppy::serialization

namespace qnx::geoservice
{
  class CConfig
  {
   public:
    explicit CConfig(std::filesystem::path folder);
    [[nodiscard]] auto map_type(usize index) const -> ::QGeoMapType;
    [[nodiscard]] inline auto size() const noexcept -> usize {
      return this->config_.values().views.size();
    }

    [[nodiscard]] auto as_qlist() const noexcept -> ::QList<::QGeoMapType>;

    [[nodiscard]] inline auto at(usize index) const -> ConfigData::ViewEntry const& {
      if(index >= this->config_.values().views.size())
        throw std::out_of_range("CConfig: index out of bounds");
      return this->config_.values().views[index];
    }

    [[nodiscard]] inline auto at(usize index) -> ConfigData::ViewEntry& {
      if(index >= this->config_.values().views.size())
        throw std::out_of_range("CConfig: index out of bounds");
      return this->config_.values_mut().views[index];
    }

    [[nodiscard]] inline auto operator[](usize index) const -> ConfigData::ViewEntry const& {
      return this->at(index);
    }

    [[nodiscard]] inline auto operator[](usize index) -> ConfigData::ViewEntry& {
      return this->at(index);
    }

    explicit inline operator bool() const noexcept { return not this->config_.values().views.empty(); }

   private:
    std::filesystem::path folder_;
    fl::configuration_file<fl::serialization::format::yaml, ConfigData> config_;
  };
} // namespace qnx::geoservice
