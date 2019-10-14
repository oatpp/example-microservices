cmake_minimum_required(VERSION 3.1)

set(project_name book-service) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/AppComponent.hpp
        src/SwaggerComponent.hpp
        src/controller/BookController.hpp
        src/db/Database.cpp
        src/db/Database.hpp
        src/db/model/Book.hpp
        src/dto/BookDto.hpp
        src/Runner.cpp
        src/Runner.hpp
)

## include directories

target_include_directories(${project_name}-lib PUBLIC src)


## link libs

find_package(oatpp          0.19.9 REQUIRED)
find_package(oatpp-swagger  0.19.9 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
)

## define path to swagger-ui res folder

add_definitions(-DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res")


## add executables

add_executable(${project_name}-exe src/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/tests.cpp
)
target_link_libraries(${project_name}-test ${project_name}-lib)

enable_testing()
add_test(project-tests ${project_name}-test)
