#include <iostream>
#include <qguiapplication.h>
#include <qqmlapplicationengine.h>
#include <floppy/logging.h>
#include <qnx/geoservice/import.h>

using std::nullopt;
using namespace std::chrono_literals;

auto main(int argc, char** argv) -> int {
  spdlog::set_level(spdlog::level::trace);
  auto app = QGuiApplication(argc, argv);
  if(not qnx::import_geoservice_plugin())
    fl::panic("main: qnx::imports::import_geoservice_plugin() failed");
  auto engine = QQmlApplicationEngine("qrc:/dev/Main.qml");
  return QGuiApplication::exec();
}