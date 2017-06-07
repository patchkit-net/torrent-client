:: build <type>
@echo off

if [%1]==[] goto usage

if not %1==Release if not %1==Debug (
  echo Error: unavailable ^<type^> %1
  goto usage
)

mkdir %~dp0bin\%PDK_PLATFORM_NAME%\%1
pushd %~dp0bin\%PDK_PLATFORM_NAME%\%1

echo %PDK_BOOST_INCLUDEDIR%

call cmake ^
  -DCMAKE_BUILD_TYPE=%1 ^
  -DBOOST_INCLUDEDIR=%PDK_BOOST_INCLUDEDIR% ^
  -DLIBBOOST_SYSTEM_DEBUG=%PDK_BOOST_LIBRARYDIR_DEBUG%\libboost_system-mt-sd.lib ^
  -DLIBBOOST_SYSTEM_RELEASE=%PDK_BOOST_LIBRARYDIR_RELEASE%\libboost_system-mt-s.lib ^
  -DLIBBOOST_RANDOM_DEBUG=%PDK_BOOST_LIBRARYDIR_DEBUG%\libboost_random-mt-sd.lib ^
  -DLIBBOOST_RANDOM_RELEASE=%PDK_BOOST_LIBRARYDIR_RELEASE%\libboost_random-mt-s.lib ^
  -DLIBBOOST_CHRONO_DEBUG=%PDK_BOOST_LIBRARYDIR_DEBUG%\libboost_chrono-mt-sd.lib ^
  -DLIBBOOST_CHRONO_RELEASE=%PDK_BOOST_LIBRARYDIR_RELEASE%\libboost_chrono-mt-s.lib ^
  -DLIBTORRENT_DEBUG=%PDK_LIBTORRENT_LIBRARYDIR_DEBUG%\torrent-rasterbar.lib ^
  -DLIBTORRENT_RELEASE=%PDK_LIBTORRENT_LIBRARYDIR_RELEASE%\torrent-rasterbar.lib ^
  -DLIBTORRENT_INCLUDEDIR=%PDK_LIBTORRENT_INCLUDEDIR_RELEASE% ^
  -DJSON_INCLUDEDIR=%PDK_JSON_INCLUDEDIR% ^
  -DCMAKE_INSTALL_PREFIX=%~dp0bin\%PDK_PLATFORM_NAME%\output ^
  -DUSE_JSON=on ^
  -G "NMake Makefiles" ^
  %~dp0

call nmake

popd

:usage
echo.
echo Usage:
echo     %0 ^<type^>
echo Available types:
echo     * Release
echo     * Debug