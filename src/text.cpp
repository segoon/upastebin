#include "text.hpp"

#include <userver/components/component_context.hpp>
// #include <userver/formats/json/inline.hpp>
// #include <userver/http/common_headers.hpp>
// #include <userver/server/handlers/exceptions.hpp>
// #include <userver/server/handlers/http_handler_base.hpp>

namespace upastebin {

TextHandler::TextHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      fs_(context.GetTaskProcessor("fs-task-processor")) {}

std::string TextHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {

  return {};
}

}  // namespace upastebin
