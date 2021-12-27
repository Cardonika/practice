#ifndef _USER_CONTROLLER_HH_
#define _USER_CONTROLLER_HH_

#include <memory>
#include <oatpp/core/Types.hpp>
#include <oatpp/core/macro/component.hpp>
#include <oatpp/parser/json/mapping/ObjectMapper.hpp>
#include <oatpp/web/server/api/ApiController.hpp>
#include <string>
#include <iostream>
#include "service/user_service.hh"
#include "dto/quzl_dto.hh"

class UserController: public oatpp::web::server::api::ApiController {
public:
    UserController(const std::shared_ptr<ObjectMapper>& objectMapper);

private:
    UserService user_service_;

public:

    static std::shared_ptr<UserController> createShared(
        OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper)
    ) {
        return std::make_shared<UserController>(objectMapper);
    }

#include OATPP_CODEGEN_BEGIN(ApiController) // codegen begin

    ENDPOINT("POST", "/login", login,
             BODY_DTO(Object<UserDto>, user)) {
        auto session_id = user_service_.checkUser(user);
        auto ret = createResponse(Status::CODE_200, "登录成功");
        ret->putHeader("Set-Cookie", "session_id=" + std::to_string(session_id));
        return ret;
    }

    ENDPOINT("POST", "/signin", signIn,
             BODY_DTO(Object<UserDto>, user)) {
        user_service_.createUser(user);
        
        oatpp::Vector<oatpp::Object<UserDto>> vec;
        return createResponse(Status::CODE_200, "注册成功");
    }

    ENDPOINT("GET", "/user/username", userName, HEADER(oatpp::String, cookie, "Cookie")) {
        int64_t session_id = std::atoi(cookie->substr(cookie->find("session_id") + 11).c_str());
        auto user = user_service_.getUserByCookie(session_id);
        return createDtoResponse(Status::CODE_200, user);
    }

    ENDPOINT("POST", "/user/test", test, BODY_DTO(Object<QuzlDto>, quzl)) {
        using namespace std;
        cout << quzl->quzl_name->c_str() << "\n";
        cout << quzl->quz_list[0]->quz_content->c_str() << "\n";
        cout << quzl->quz_list[0]->option_list[0]->option_content->c_str() << "\n";

        return createResponse(Status::CODE_200, "ok");
    }

#include OATPP_CODEGEN_END(ApiController) // codegen end

};

#endif