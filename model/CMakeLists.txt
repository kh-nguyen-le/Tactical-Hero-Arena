# Add header files for the target
set(HEADER_FILES
    hero.hpp
    mux.hpp
    team.hpp
    testhero.hpp
)

# Create the library target
add_library(Models INTERFACE)

# Set the target's include directories
target_include_directories(Models INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

# Add the header files to the target
target_sources(Models INTERFACE ${HEADER_FILES})

# Link the necessary libraries, including Cadmiumv2
target_link_libraries(Models INTERFACE cadmium)