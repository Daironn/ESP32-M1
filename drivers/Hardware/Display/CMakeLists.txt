set(SOURCES ./src/Display.cpp)

idf_component_register(SRCS ${SOURCES}
                       INCLUDE_DIRS "." "inc" "../Button/inc"
                       REQUIRES driver)
