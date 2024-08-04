#pragma once

#include <userver/components/component_config.hpp>
#include <userver/components/component_context.hpp>
#include <userver/http/common_headers.hpp>
#include <userver/server/handlers/exceptions.hpp>
#include <userver/server/handlers/http_handler_base.hpp>
#include <userver/storages/postgres/cluster.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/boost_uuid4.hpp>

namespace upastebin {

class StoreHandler final : public userver::server::handlers::HttpHandlerBase {
 public:
  static constexpr std::string_view kName = "handler-store";

  StoreHandler(const userver::components::ComponentConfig& config,
               const userver::components::ComponentContext& context)
      : HttpHandlerBase(config, context),
        pg_(context.FindComponent<userver::components::Postgres>("pg-1")
                .GetCluster()) {}

  std::string HandleRequestThrow(
      const userver::server::http::HttpRequest& request,
      userver::server::request::RequestContext&) const override {
    auto uuid = userver::utils::generators::GenerateBoostUuid();
    auto text = request.RequestBody();

    pg_->Execute(userver::storages::postgres::ClusterHostType::kMaster,
                 "INSERT INTO upastebin.texts (uuid, text) VALUES $1, $2;",
                 uuid, text);
    return {};
  }

 private:
  userver::storages::postgres::ClusterPtr pg_;
};

}  // namespace upastebin
