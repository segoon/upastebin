#include "latest.hpp"

#include <userver/components/component_context.hpp>
#include <userver/formats/json/value_builder.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/boost_uuid4.hpp>

namespace upastebin {

LatestHandler::LatestHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      pg_(context.FindComponent<userver::components::Postgres>("postgres")
              .GetCluster()) {}

std::string LatestHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest&,
    userver::server::request::RequestContext&) const {
  auto result = pg_->Execute(
      userver::storages::postgres::ClusterHostType::kSlave,
      "SELECT author, substring(text for $1::INTEGER) AS text_tr, ip_source "
      "FROM "
      "upastebin.texts ORDER BY created_at DESC LIMIT $2::INTEGER;",
      1000, 10);

  userver::formats::json::ValueBuilder response;
  for (const auto& item : result) {
    userver::formats::json::ValueBuilder response_item;

    response_item["author"] = item["author"].As<std::string>();
    response_item["ip"] = item["ip_source"].As<std::string>();
    response_item["text"] = item["text_tr"].As<std::string>();

    response.PushBack(response_item.ExtractValue());
  }
  return ToString(response.ExtractValue());
}

}  // namespace upastebin
