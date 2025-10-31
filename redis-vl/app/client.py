import asyncio
import struct

from redis.asyncio.cluster import ClusterNode, RedisCluster
from redisvl.index import AsyncSearchIndex
from redisvl.schema import IndexSchema


SCHEMA = IndexSchema.from_dict(
    {
        "index": {
            "name": "user-index",
            "prefix": "user:",
        },
        "fields": [
            {"name": "user", "type": "tag"},
            {"name": "credit_score", "type": "tag"},
            {
                "name": "embedding",
                "type": "vector",
                "attrs": {
                    "algorithm": "flat",
                    "dims": 3,
                    "distance_metric": "cosine",
                    "datatype": "float32",
                },
            },
        ],
    }
)


async def client():
    index = AsyncSearchIndex(
        SCHEMA,
        redis_client=RedisCluster(
            startup_nodes=[ClusterNode(host="redis-1", port=6379)],
            username=None,
            password=None,
            client_name="client-issue",
        ),
    )
    await index.client.initialize()
    await index.create()
    keys = await index.load(
        [
            {
                "user": "bob",
                "credit_score": "good",
                "embedding": struct.pack("3f", 0.1, 0.2, 0.3),
            }
        ],
        keys=["user:bob"],
        ttl=3600
    )
    print(f"Inserted: {keys}", flush=True)


asyncio.run(client())
