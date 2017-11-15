const Server = require('mock-socket').Server;
const WebSocket = require('mock-socket').WebSocket;

function until(predicate, options = {}) {
    const delay = options.delay != null ? options.delay : 5;
    const retries = options.retries != null ? options.retries : 20;
    const ontry = options.ontry != null ? options.ontry : currentTry => {};
    return new Promise((resolve, reject) => {
        var currentTry = 0;
        setTimeout(makeTry, delay);
        function makeTry() {
            currentTry += 1;
            ontry(currentTry);
            if (predicate()) {
                resolve()
            }
            if (currentTry >= retries) {
                reject()
            }
            setTimeout(makeTry, delay);
        }
    });
}


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

describe('async', async () => {
    it('waits until a condition', done => {
        let foo = 1;
        const predicate = () => xxx == 2;

        const options = {
            ontry: currentTry => {
                console.log(currentTry);
            }
        }

        const p = until(predicate, options);
        p.then(() => {
            console.log('ok')
            done()
        })


        setTimeout(() => foo = 2, 100);
    });
});
