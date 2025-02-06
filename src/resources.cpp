#include "resources.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/components/fs_cache.hpp>

namespace upastebin {

namespace {

std::string_view GetContentType(std::string_view extention) {
  if (extention == ".js")
    return "application/javascript";
  else if (extention == ".css")
    return "text/css";
  else if (extention == ".html")
    return "text/html; charset=UTF-8";
  else
    return "application/octet-stream";
}

}  // namespace

ResourcesHandler::ResourcesHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      fs_client_(
          context.FindComponent<userver::components::FsCache>("resources-cache")
              .GetClient()) {}

std::string ResourcesHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  auto subpath = request.GetPathArg("subpath");
  // Note: no need to validate subpath as invalid name would lead to cache miss
  // in FsCacheClient

  auto file_ptr = fs_client_.TryGetFile("/" + subpath);
  auto& response = request.GetHttpResponse();
  if (file_ptr) {
    response.SetContentType(GetContentType(file_ptr->extension));
    response.SetHeader(USERVER_NAMESPACE::http::headers::kExpires, "600");
    return file_ptr->data;
  } else {
    auto& response = request.GetHttpResponse();
    response.SetStatus(userver::server::http::HttpStatus::kNotFound);
    return {};
  }
}

}  // namespace upastebin
