#include "resources.hpp"

#include <userver/components/component_context.hpp>
// #include <userver/formats/json/inline.hpp>
// #include <userver/http/common_headers.hpp>
// #include <userver/server/handlers/exceptions.hpp>
// #include <userver/server/handlers/http_handler_base.hpp>

namespace upastebin {

namespace {

void ValidateFilename(std::string_view filename) {
  // TODO
}

}  // namespace

ResourcesHandler::ResourcesHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      fs_(context.GetTaskProcessor("fs-task-processor")) {}

std::string ResourcesHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  auto subpath = request.GetPathArg("subpath");
  ValidateFilename(subpath);

  return {};
}

}  // namespace upastebin
