SET(ADM_coreSqlLight3_SRCS 
        Database.cpp
        Query.cpp
        StderrLog.cpp
        SysLog.cpp
)

add_compiler_export_flags()
ADM_ADD_SHARED_LIBRARY(ADM_coreSqlLight3 ${ADM_coreSqlLight3_SRCS})

IF (APPLE)
	TARGET_LINK_LIBRARIES(ADM_coreSqlLight3 -Wl,-read_only_relocs,suppress)
ENDIF (APPLE)

IF (UNIX)
	TARGET_LINK_LIBRARIES(ADM_coreSqlLight3 dl)
ENDIF (UNIX)

INCLUDE_DIRECTORIES(../include ${SQLITE3_INCLUDEDIR})
TARGET_LINK_LIBRARIES(ADM_coreSqlLight3 ADM_core6 ${SQLITE3_LDFLAGS})
ADM_INSTALL_LIB(ADM_coreSqlLight3)
