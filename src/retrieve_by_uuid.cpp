#include "retrieve_by_uuid.hpp"

#include <userver/components/component_context.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/boost_uuid4.hpp>

namespace upastebin {

RetrieveHandler::RetrieveHandler(
    const userver::components::ComponentConfig& config,
    const userver::components::ComponentContext& context)
    : HttpHandlerBase(config, context),
      pg_(context.FindComponent<userver::components::Postgres>("postgres")
              .GetCluster()) {}

std::string RetrieveHandler::HandleRequestThrow(
    const userver::server::http::HttpRequest& request,
    userver::server::request::RequestContext&) const {
  auto uuid_str = request.GetPathArg("uuid");
  auto uuid = userver::utils::BoostUuidFromString(uuid_str);

  auto result = pg_->Execute(
      userver::storages::postgres::ClusterHostType::kSlave,
      "SELECT text FROM upastebin.texts WHERE uuid=$1;", uuid);
  if (result.Size() == 0) {
    request.GetHttpResponse().SetStatusNotFound();
    return {};
  }

  auto row = result.Front();
  auto text = row["text"].As<std::string>();
  return text;
}

}  // namespace upastebin
