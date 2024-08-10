#pragma once

#include <userver/engine/task/task_processor_fwd.hpp>
#include <userver/http/common_headers.hpp>
#include <userver/server/handlers/exceptions.hpp>
#include <userver/server/handlers/http_handler_base.hpp>

namespace upastebin {

class ResourcesHandler final
    : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-resources";

  ResourcesHandler(const userver::components::ComponentConfig& config,
                   const userver::components::ComponentContext& context);

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override;

 private:
  userver::engine::TaskProcessor& fs_;
};

}  // namespace upastebin
