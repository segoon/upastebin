import pytest
import yarl


@pytest.mark.parametrize('subpath', ['index.html', 'index.js'])
async def test_found(service_client, subpath):
    response = await service_client.get(f'/r/{subpath}')
    assert response.status == 200


@pytest.mark.parametrize(
    'subpath',
    [
        '',
        '.',
        '..',
        'missing.html',
        # TODO: '../../../../../../../../../../etc/passwd',
    ],
)
async def test_not_found(service_client, subpath):
    # use yarl.Url() to keep '..' in URL
    url = yarl.URL(
        service_client._client.url('/') + f'r/{subpath}', encoded=True,
    )
    response = await service_client.get(url)
    assert response.text == ''
    assert response.status == 404
