#pragma once

#include <userver/server/handlers/exceptions.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/http/common_headers.hpp>

namespace upastebin {

namespace {

const std::string kLocation = "Location";
}

class RedirectHandler final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-redirect";

  using HttpHandlerBase::HttpHandlerBase;

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    auto& response = request.GetHttpResponse();
    response.SetStatus(userver::server::http::HttpStatus::kTemporaryRedirect);
    response.SetHeader(userver::http::headers::kLocation, "/index.html");
    return {};
  }
};

}  // namespace upastebin
