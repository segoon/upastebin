async def test_404(service_client):
    response = await service_client.get(
        '/api/v1/posts/06c89e28-15c6-4380-a1e8-a6bf389ba0c6',
    )
    assert response.status == 404
    assert response.text == ''
