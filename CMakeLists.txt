cmake_minimum_required(VERSION 3.10)

# Set the project name
project(TrieSearchBar)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML package
set(SFML_DIR "./SFML/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable with WIN32 option to disable console window
add_executable(TrieSearchBar
    src/main.cpp 
    src/model/timer.hpp
    src/model/trie.hpp
    src/model/trie.cpp
    src/view/base.hpp
    src/view/base.cpp
    src/view/Button.hpp
    src/view/Button.cpp
    src/view/TextField.hpp
    src/view/TextField.cpp    
    src/view/ResultTab.hpp
    src/view/ResultTab.cpp
    src/view/SettingTab.hpp
    src/view/SettingTab.cpp
    src/view/DropdownBox.hpp
    src/view/DropdownBox.cpp
    src/view/SearchBar.hpp
    src/view/SearchBar.cpp
    src/controller/app.hpp
    src/controller/app.cpp
)
# Include directories
target_include_directories(TrieSearchBar PRIVATE ${SFML_INCLUDE_DIRS})

# Link SFML libraries
target_link_libraries(TrieSearchBar PRIVATE sfml-graphics sfml-window sfml-system)

# Custom command to ocopy SFML DLLs after build
add_custom_command(TARGET TrieSearchBar POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:TrieSearchBar>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/SFML/bin" "$<TARGET_FILE_DIR:TrieSearchBar>"
)