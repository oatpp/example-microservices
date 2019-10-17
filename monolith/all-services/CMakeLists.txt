cmake_minimum_required(VERSION 3.1)

set(project_name all-services) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_executable(${project_name}-exe
        App.cpp
)

find_package(oatpp          0.19.9 REQUIRED)
find_package(oatpp-swagger  0.19.9 REQUIRED)

target_link_libraries(${project_name}-exe
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
)

## define path to swagger-ui res folder
add_definitions(-DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res")

target_include_directories(${project_name}-exe
        PUBLIC ../../book-service/src
        PUBLIC ../../user-service/src
        PUBLIC ../../facade/src
)

target_link_directories(${project_name}-exe
        PUBLIC ../../book-service/build
        PUBLIC ../../user-service/build
        PUBLIC ../../facade/build
)

target_link_libraries(${project_name}-exe
        PUBLIC book-service-lib
        PUBLIC user-service-lib
        PUBLIC facade-lib
)
