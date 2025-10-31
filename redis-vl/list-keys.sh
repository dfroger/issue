echo "=== redis-1 ==="
docker compose exec redis-1 redis-cli KEYS '*'

echo
echo "=== redis-2 ==="
docker compose exec redis-2 redis-cli KEYS '*'

echo
echo "=== redis-3 ==="
docker compose exec redis-3 redis-cli KEYS '*'
