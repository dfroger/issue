const Server = require('mock-socket').Server;
const WebSocket = require('mock-socket').WebSocket;

describe('websocket', () => {
    it('send and receive messages', (done) => {
        const url = 'ws://localhost:8080';
        const server = new Server(url);
        const client = new WebSocket(url);

        client.onmessage = (event) => {
            const response = JSON.parse(event.data);
        };

        server.on('message', str => {
            const response = JSON.stringify({'result': 'ok'});
            server.send(response);
        });

        client.send(JSON.stringify(['foo', 1, 2]));
        done()
    });
});
