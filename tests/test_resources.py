import pytest
import yarl


@pytest.mark.parametrize(
    'subpath,content_type',
    [
        ('index.html', 'text/html; charset=UTF-8'),
        ('index.js', 'application/javascript'),
    ],
)
async def test_found(service_client, subpath, content_type):
    response = await service_client.get(f'/r/{subpath}')
    assert response.status == 200
    assert response.headers['content-type'] == content_type


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
