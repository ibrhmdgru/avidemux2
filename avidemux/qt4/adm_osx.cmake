#
 #include(BundleUtilities)

#
SET(bundle avidemux3_${QT_EXTENSION})
#
MACRO(ADM_PREBUILD)
        LIST(APPEND PlatformLibs   "-lm -lstdc++")
        LIST(APPEND PlatformLibs  "-framework CoreServices -framework CoreAudio -framework AudioUnit -framework Carbon")
        LIST(APPEND PlatformLibs  "-Wl,-dylib_file,/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib:/System/Library/Frameworks/OpenGL.framework/Versions/A/Libraries/libGL.dylib")
ENDMACRO(ADM_PREBUILD)
#
MACRO(ADM_MAIN_APP)
    SET(S_VERSION "${AVIDEMUX_MAJOR_MINOR}") # Short version
    SET(B_VERSION "${AVIDEMUX_VERSION}") # Long version
    CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/Info.plist.in ${CMAKE_BINARY_DIR}/Info.plist @ONLY)
    ADD_EXECUTABLE(avidemux3_${QT_EXTENSION}  MACOSX_BUNDLE ${ADM_EXE_SRCS})
    SET_PROPERTY(TARGET avidemux3_${QT_EXTENSION} PROPERTY OUTPUT_NAME Avidemux${AVIDEMUX_MAJOR_MINOR})
    SET( MACOSX_BUNDLE_INFO_STRING "Avidemux - version ${AVIDEMUX_MAJOR_MINOR}" )
    SET( MACOSX_BUNDLE_BUNDLE_VERSION "${AVIDEMUX_MAJOR_MINOR}" )
    SET( MACOSX_BUNDLE_ICON_FILE avidemux.icns )
    SET_PROPERTY(TARGET avidemux3_${QT_EXTENSION} PROPERTY   MACOSX_BUNDLE_INFO_PLIST ${CMAKE_BINARY_DIR}/Info.plist)
    SET_SOURCE_FILES_PROPERTIES(avidemux.icns PROPERTIES MACOSX_PACKAGE_LOCATION Resources )
    qt5_use_modules( avidemux3_${QT_EXTENSION}   Widgets Network)
    IF (USE_SDL)
       TARGET_LINK_LIBRARIES(avidemux3_${QT_EXTENSION}   ADM_libsdl)
    ENDIF(USE_SDL)
ENDMACRO(ADM_MAIN_APP)
#
MACRO(ADM_POSTBUILD)
    SET(CMAKE_INSTALL_PREFIX ${CMAKE_BINARY_DIR}/..)
    INSTALL(TARGETS avidemux3_${QT_EXTENSION}  BUNDLE DESTINATION . COMPONENT RUNTIME)
ENDMACRO(ADM_POSTBUILD)

