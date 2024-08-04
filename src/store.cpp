#include "store.hpp"

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
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
      pg_(context.FindComponent<userver::components::Postgres>("pg-1")
              .GetCluster()) {}

std::string StoreHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  auto uuid = userver::utils::generators::GenerateBoostUuid();
  auto text = request.RequestBody();
  auto created_at = userver::utils::datetime::Now();

  pg_->Execute(
      userver::storages::postgres::ClusterHostType::kMaster,
      "INSERT INTO upastebin.texts (uuid, text, created_at) VALUES $1, $2;",
      uuid, text, created_at);
  return {};
}

}  // namespace upastebin
