
#ifndef example_facade_SwaggerComponent_hpp
#define example_facade_SwaggerComponent_hpp

#include "./Constants.hpp"

#include "oatpp-swagger/Model.hpp"
#include "oatpp-swagger/Resources.hpp"
#include "oatpp/core/macro/component.hpp"

namespace example { namespace facade {

class SwaggerComponent {
public:

  /**
   *  General API docs info
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::DocumentInfo>, swaggerDocumentInfo)(Qualifiers::SERVICE_FACADE, [] {

    oatpp::swagger::DocumentInfo::Builder builder;

    builder
      .setTitle("Facade Service")
      .setDescription("Monolithization Example")
      .setVersion("1.0")
      .setContactName("Oat++ Framework")
      .setContactUrl("https://oatpp.io/")

      .setLicenseName("The Unlicense")
      .setLicenseUrl("http://unlicense.org")

      .addServer("http://localhost:8000", "server on localhost");

    return builder.build();

  }());


  /**
   *  Swagger-Ui Resources (<oatpp-examples>/lib/oatpp-swagger/res)
   */
  OATPP_CREATE_COMPONENT(std::shared_ptr<oatpp::swagger::Resources>, swaggerResources)(Qualifiers::SERVICE_FACADE, [] {
    // Make sure to specify correct full path to oatpp-swagger/res folder !!!
    return oatpp::swagger::Resources::loadResources(OATPP_SWAGGER_RES_PATH);
  }());

};

}}

#endif /* example_facade_SwaggerComponent_hpp */
