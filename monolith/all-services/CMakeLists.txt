cmake_minimum_required(VERSION 3.1)

set(project_name all-services) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_executable(${project_name}-exe
        App.cpp
)

set(USER_SERVICE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../user-service/build)
set(BOOK_SERVICE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../book-service/build)
set(FACADE_SERVICE_DIR ${CMAKE_CURRENT_LIST_DIR}/../../facade/build)

FIND_LIBRARY(USER_LIBRARY
        NAMES user-service-lib
        HINTS ${USER_SERVICE_DIR}
)

FIND_LIBRARY(BOOK_LIBRARY
        NAMES book-service-lib
        HINTS ${BOOK_SERVICE_DIR}
)

FIND_LIBRARY(FACADE_LIBRARY
        NAMES facade-lib
        HINTS ${FACADE_SERVICE_DIR}
)

target_include_directories(${project_name}-exe
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../user-service/src
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../book-service/src
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/../../facade/src
)

target_link_libraries(${project_name}-exe
        PUBLIC ${USER_LIBRARY}
        PUBLIC ${BOOK_LIBRARY}
        PUBLIC ${FACADE_LIBRARY}
)

find_package(oatpp          1.2.5 REQUIRED)
find_package(oatpp-swagger  1.2.5 REQUIRED)

## define path to swagger-ui res folder
add_definitions(-DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res")

target_link_libraries(${project_name}-exe
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
)
