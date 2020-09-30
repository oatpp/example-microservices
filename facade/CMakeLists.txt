cmake_minimum_required(VERSION 3.1)

set(project_name facade) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/facade/AppComponent.hpp
        src/facade/SwaggerComponent.hpp
        src/facade/controller/BookController.hpp
        src/facade/controller/UserController.hpp
        src/facade/dto/BookDto.hpp
        src/facade/dto/BookInfoDto.hpp
        src/facade/dto/UserDto.hpp
        src/facade/Runner.cpp
        src/facade/Runner.hpp
        src/facade/service/BookService.hpp
        src/facade/service/UserService.hpp
        src/facade/Constants.hpp)

## include directories

target_include_directories(${project_name}-lib PUBLIC src)


## link libs

find_package(oatpp          1.2.0 REQUIRED)
find_package(oatpp-swagger  1.2.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
)

## define path to swagger-ui res folder

add_definitions(-DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res")


## add executables

add_executable(${project_name}-exe src/facade/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/facade/tests.cpp
)
target_link_libraries(${project_name}-test ${project_name}-lib)

enable_testing()
add_test(project-tests ${project_name}-test)
