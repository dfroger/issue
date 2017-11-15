const Server = require('mock-socket').Server;
const WebSocket = require('mock-socket').WebSocket;


const url = 'ws://localhost:8080';
const server = new Server(url);
const client = new WebSocket(url);

client.onmessage = (event) => {
    console.log('client receives', event.data);
    const response = JSON.parse(event.data);
};

server.on('message', str => {
    const response = JSON.stringify({'result': 'ok'});
    console.log('server receives and send')
    server.send(response);
});

console.log('client requests');
client.send(JSON.stringify(['foo', 1, 2]));
