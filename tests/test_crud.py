TEXT = 'Some string'


async def test_404(service_client):
    response = await service_client.get(
        '/api/v1/posts/06c89e28-15c6-4380-a1e8-a6bf389ba0c6',
    )
    assert response.status == 404
    assert response.text == ''


async def test_empty_db(service_client):
    response = await service_client.get('/api/v1/latest')
    assert response.status == 200
    assert response.json() == {'items': []}


async def test_create_and_retrieve(service_client):
    response = await service_client.post(
        '/api/v1/posts/', params={'author': 'foo'}, data=TEXT,
    )
    assert response.status == 200

    json_response = response.json()
    assert list(json_response) == ['uuid']
    uuid = json_response['uuid']

    response = await service_client.get(f'/api/v1/posts/{uuid}')
    assert response.status == 200
    assert response.text == TEXT

    response = await service_client.get('/api/v1/latest')
    assert response.status == 200
    json = response.json()
    assert json == {
        'items': [
            {
                'author': 'foo',
                'ip': '::ffff:127.0.0.1',
                'id': uuid,
                'text': TEXT,
            }
        ],
    }
