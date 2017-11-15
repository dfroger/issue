const foo = require('./foo').foo

describe('async', () => {
    it('waits until a condition', done => {
        foo(done);
    });
});
