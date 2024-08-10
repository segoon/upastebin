import pathlib

import pytest
from testsuite.databases.pgsql import discover


pytest_plugins = ['pytest_userver.plugins.postgresql']

USERVER_CONFIG_HOOKS = ['prepare_service_config_resources']


WWW_DATA = pathlib.Path(__file__).parent.parent / 'www-data'


@pytest.fixture(scope='session')
def service_source_dir():
    """Path to root directory service."""
    return pathlib.Path(__file__).parent.parent


@pytest.fixture(scope='session')
def pgsql_local(service_source_dir, pgsql_local_create):
    """Create schemas databases for tests"""
    databases = discover.find_schemas(
        'upastebin',  # service name that goes to the DB connection
        [service_source_dir.joinpath('postgresql/schemas')],
    )
    return pgsql_local_create(list(databases.values()))


@pytest.fixture(scope='session')
def prepare_service_config_resources():
    def patch_config(config, config_vars):
        components = config['components_manager']['components']
        components['resources-cache']['dir'] = str(WWW_DATA)

    return patch_config
