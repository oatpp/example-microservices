cmake_minimum_required(VERSION 3.1)

set(project_name user-service) ## rename your project here

project(${project_name})

set(CMAKE_CXX_STANDARD 11)

add_library(${project_name}-lib
        src/user-service/AppComponent.hpp
        src/user-service/SwaggerComponent.hpp
        src/user-service/controller/UserController.hpp
        src/user-service/db/Database.cpp
        src/user-service/db/Database.hpp
        src/user-service/db/model/User.hpp
        src/user-service/dto/UserDto.hpp
        src/user-service/Runner.cpp
        src/user-service/Runner.hpp
)

## include directories

target_include_directories(${project_name}-lib PUBLIC src)


## link libs

find_package(oatpp          1.0.0 REQUIRED)
find_package(oatpp-swagger  1.0.0 REQUIRED)

target_link_libraries(${project_name}-lib
        PUBLIC oatpp::oatpp
        PUBLIC oatpp::oatpp-swagger
)

## define path to swagger-ui res folder

add_definitions(-DOATPP_SWAGGER_RES_PATH="${OATPP_BASE_DIR}/bin/oatpp-swagger/res")


## add executables

add_executable(${project_name}-exe src/user-service/App.cpp)
target_link_libraries(${project_name}-exe ${project_name}-lib)

add_executable(${project_name}-test
        test/user-service/tests.cpp
)
target_link_libraries(${project_name}-test ${project_name}-lib)

enable_testing()
add_test(project-tests ${project_name}-test)
