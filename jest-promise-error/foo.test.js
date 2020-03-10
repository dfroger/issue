// workaround from https://github.com/facebook/jest/issues/2980
/*
const top = global || window;
let [nativeTest, _setTimeout, _setInterval, test]=[top.test, top.setTimeout, top.setInterval, function (name, currentTest) {
    if (!currentTest.length) return nativeTest(name, currentTest);
    return nativeTest(name, (done) => {
        let queue = new Set();
        let proxy = (execute) => {
            return (callback, mills, args) => {
                let tid = Symbol();
                queue.add(tid);
                return execute(() => {
                    try {
                        callback();
                        queue.delete(tid);
                    } catch (e) {
                        queue.clear();
                        done.fail(e);
                    }
                }, mills, args);
            }
        };
        top.setTimeout = proxy(_setTimeout);
        top.setInterval = proxy(_setInterval);
        try {
            currentTest(done);
        } finally {
            let timerId = _setInterval(() => {
                if (!queue.size) {
                    clearInterval(timerId);
                    global.setTimeout = _setTimeout;
                    global.setTimeout = _setInterval;
                }
            });
        }
    });
}];
top.it = top.test = test;
*/

const foo = require('./foo').foo

describe('async', () => {
    it('run foo', done => {
        foo(done);
    });
});
