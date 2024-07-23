#pragma once

#include <floppy/floppy.h>
#include <floppy/traits.h>

#if defined(FLOPPY_OS_WINDOWS)
# if defined(QNX_LIBRARY)
#   define QNX_API __declspec(dllexport)
# elif defined(QNX_STATIC_LIBRARY)
#   define QNX_API
# else
#   define QNX_API __declspec(dllimport)
# endif
#else
# define QNX_API __attribute__((visibility("default")))
#endif

/// \brief Qt Native Extensions main namespace.
namespace qnx
{
  using namespace fl::types;
  using namespace fl::literals;

  /// \brief Namespace for project metadata.
  namespace meta
  {
    /// \brief Meta information about the library.
    [[maybe_unused]] constexpr inline auto qde_meta = fl::meta::project_meta(
      fl::meta::version(
        #if defined(QNX_PROJECT_VERSION_MAJOR)
        QNX_PROJECT_VERSION_MAJOR,
        #else // defined(QNX_PROJECT_VERSION_MAJOR)
        0,
        #endif // defined(QNX_PROJECT_VERSION_MAJOR)
        #if defined(QNX_PROJECT_VERSION_MINOR)
        QNX_PROJECT_VERSION_MINOR,
        #else // defined(QNX_PROJECT_VERSION_MINOR)
        1,
        #endif // defined(QNX_PROJECT_VERSION_MINOR)
        #if defined(QNX_PROJECT_VERSION_PATCH)
        QNX_PROJECT_VERSION_PATCH
        #else // defined(QNX_PROJECT_VERSION_PATCH)
        0
        #endif // defined(QNX_PROJECT_VERSION_PATCH)
      ),
      std::string_view(
        #if defined(QNX_TARGET_NAME)
        QNX_TARGET_NAME
        #else // defined(QNX_TARGET_NAME)
        "qnx"
        #endif // defined(QNX_TARGET_NAME)
      ),
      "io.github.maybe-unused.qnx",
      "maybe-unused"
    );

    constexpr inline auto qml_namespace = "io.qnx.core";
  } // namespace meta
} // namespace qnx