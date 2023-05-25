set(SOURCE_FILES
  main_team_test.cpp
  packet.cpp
  action.cpp
  attribute.cpp
  command.cpp
  event.cpp
  herodto.cpp
  skill.cpp
  skillinfo.cpp
  heroinfo.cpp
  teamcombo.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
target_link_libraries(${CMAKE_PROJECT_NAME} cadmium)