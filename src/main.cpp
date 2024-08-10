#include <userver/clients/http/component.hpp>
#include <userver/components/minimal_server_component_list.hpp>
#include <userver/server/handlers/ping.hpp>
#include <userver/server/handlers/tests_control.hpp>
#include <userver/testsuite/testsuite_support.hpp>
#include <userver/storages/postgres/component.hpp>
#include <userver/utils/daemon_run.hpp>
#include <userver/clients/dns/component.hpp>
#include <userver/components/fs_cache.hpp>

#include "redirect.hpp"
#include "store.hpp"
#include "retrieve_by_uuid.hpp"
#include "latest.hpp"
#include "resources.hpp"
#include "text.hpp"

int main(int argc, char* argv[]) {
  auto component_list = userver::components::MinimalServerComponentList()
                            .Append<userver::server::handlers::Ping>()
                            .Append<userver::components::TestsuiteSupport>()
                            .Append<userver::components::HttpClient>()
                            .Append<userver::server::handlers::TestsControl>();

  component_list.Append<userver::components::Postgres>("postgres");
  component_list.Append<userver::clients::dns::Component>();
  component_list.Append<userver::components::FsCache>("resources-cache");

  component_list.Append<upastebin::RedirectHandler>();
  component_list.Append<upastebin::StoreHandler>();
  component_list.Append<upastebin::RetrieveHandler>();
  component_list.Append<upastebin::LatestHandler>();
  component_list.Append<upastebin::TextHandler>();
  component_list.Append<upastebin::ResourcesHandler>();

  return userver::utils::DaemonMain(argc, argv, component_list);
}
