#pragma once

#include <qglobal.h>
#include <qnx/detail/export.h>

namespace qnx // NOLINT(*-concat-nested-namespaces)
{
  inline namespace imports
  {
    [[maybe_unused]] [[nodiscard]] auto import_geoservice_plugin() -> bool;
  } // namespace imports
} // namespace qnx
