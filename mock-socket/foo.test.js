const foo = require('./bar').foo

describe('async', () => {
    it('waits until a condition', done => {
        foo();
        done();
    });
});
