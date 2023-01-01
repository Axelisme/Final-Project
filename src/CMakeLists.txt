cmake_minimum_required(VERSION 3.0.0)
project(Final_CMake VERSION 0.1.0)

include(CTest)
enable_testing()

# 新增原始檔列表變數
aux_source_directory(. SRC_LIST)

# 指定庫檔案搜尋目錄，必須為絕對路徑
link_directories(/usr/local/lib)
set(LINK_LIB -lallegro_image -lallegro_ttf -lallegro_font -lallegro_dialog -lallegro_primitives -lallegro_acodec -lallegro_audio -lallegro -lallegro_main)
link_libraries(${LINK_LIB})

# 指定標頭檔案目錄
INCLUDE_DIRECTORIES(../include)
INCLUDE_DIRECTORIES(/usr/local/include)

# 生成可執行檔案
set(EXECUTABLE_OUTPUT_PATH ../bin/${CMAKE_BUILD_TYPE})
add_executable(game ${SRC_LIST})

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)