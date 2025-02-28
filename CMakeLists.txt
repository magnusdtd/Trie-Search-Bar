cmake_minimum_required(VERSION 3.10)

# Set the project name
project(TrieSearchBar)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find SFML package
set(SFML_DIR "./SFML-2.6.2/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Add the executable with WIN32 option to disable console window
add_executable(TrieSearchBar
    WIN32
    src/main.cpp 
    src/model/CompressedTrie.hpp
    src/model/CompressedTrie.cpp
    src/model/LRUCache.hpp
    src/model/LRUCache.cpp
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
    src/view/Theme.hpp
    src/view/Theme.cpp
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
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:TrieSearchBar>/assets"
    COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:TrieSearchBar>/data"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/SFML-2.6.2/bin" "$<TARGET_FILE_DIR:TrieSearchBar>"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/assets" "$<TARGET_FILE_DIR:TrieSearchBar>/assets"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${CMAKE_SOURCE_DIR}/data" "$<TARGET_FILE_DIR:TrieSearchBar>/data"
)