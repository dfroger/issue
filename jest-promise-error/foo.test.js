const foo = require('./foo').foo

describe('async', () => {
    it('run foo', done => {
        foo(done);
    });
});
