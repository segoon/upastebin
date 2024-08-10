#include "store.hpp"

#include <userver/components/component_context.hpp>
#include <userver/formats/json/inline.hpp>
#include <userver/http/common_headers.hpp>
#include <userver/server/handlers/exceptions.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/boost_uuid4.hpp>
#include <userver/utils/datetime.hpp>

namespace upastebin {

StoreHandler::StoreHandler(const userver::components::ComponentConfig& config,
                           const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      pg_(context.FindComponent<userver::components::Postgres>("postgres")
              .GetCluster()) {}

std::string StoreHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  auto uuid = userver::utils::generators::GenerateBoostUuid();
  auto author = request.GetArg("author");
  // TODO: auto ip_source = request.Get
  std::string ip_source;
  auto text = request.RequestBody();
  auto created_at = userver::utils::datetime::Now();

  pg_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
               "INSERT INTO upastebin.texts (uuid, author, ip_source, text, created_at) VALUES "
               "($1, $2, $3, $4, $5);",
               uuid, author, ip_source, text, created_at);

  auto json_response = userver::formats::json::MakeObject("uuid",
                                            userver::utils::ToString(uuid));
  return ToString(json_response);
}

}  // namespace upastebin
