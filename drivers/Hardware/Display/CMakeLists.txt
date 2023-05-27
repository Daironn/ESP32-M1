set(SOURCES ./src/Display.cpp)

idf_component_register(SRCS ${SOURCES} ./src/Scroll.cpp
                       INCLUDE_DIRS "." "inc" "../Button/inc"
                       REQUIRES driver)
