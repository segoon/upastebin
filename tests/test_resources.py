import pytest


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
        '../../../../../../../../../../etc/passwd',
    ],
)
async def test_not_found(service_client, subpath):
    response = await service_client.get(f'/r/{subpath}')
    assert response.text == ''
    assert response.status == 404
