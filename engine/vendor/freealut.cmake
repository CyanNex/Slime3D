set(FREEALUT_HEADER "${OPENAL_INCLUDE_DIR}/alut.h")
set(FREEALUT_LIBRARY "alut")

if (EXISTS ${FREEALUT_HEADER})
    include_directories(${OPENAL_INCLUDE_DIR})
else ()
    message(FATAL_ERROR "Cannot find freealut! (${FREEALUT_HEADER})")
endif ()
