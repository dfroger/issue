Note: example source code can be found
[here](https://github.com/dfroger/issue/tree/master/jest-promise-error).

Consider the following function, which creates a `Promise`, and invokes the
`done` callback when the promise is resolved:

    // file: foo.js

    function foo(done) {
        const p = new Promise((resolve, reject) => {
            setTimeout(() => {
                //const xxx = 2;
                resolve(xxx);
            }, 100);
        });
        p.then(data => {
            console.log(data);
            done()
        })
    }

    exports.foo = foo;

It contains an error: the `xxx` variable is not defined, so a error must
raised.

If I run import this function and execute it in a script:

    // file: index.js

    const foo = require('./foo').foo;

    foo();

and run the script with `node v8.6.0`:

    node index.js

I get the expected error (`ReferenceError: xxx is not defined`):

    /home/dfroger/repo/dfroger/issue/jest-promise-error/foo.js:5
                resolve(xxx);
                        ^

    ReferenceError: xxx is not defined
        at Timeout.setTimeout [as _onTimeout] (/home/dfroger/repo/dfroger/issue/jest-promise-error/foo.js:5:21)
        at ontimeout (timers.js:469:11)
        at tryOnTimeout (timers.js:304:5)
        at Timer.listOnTimeout (timers.js:264:5)

If now I write a unit test for `foo`:

    // file: foo.test.js

    const foo = require('./foo').foo

    describe('async', () => {
        it('run foo', done => {
            foo(done);
        });
    });

And run it with `jest v21.2.1`:

    ./node_modules/.bin/jest

I no more get the error message about `xxx being not defined`:

      async
        ✕ run foo (5004ms)

      ● async › run foo

        Timeout - Async callback was not invoked within timeout specified by jasmine.DEFAULT_TIMEOUT_INTERVAL.

          at node_modules/jest-jasmine2/build/queue_runner.js:64:21
          at ontimeout (timers.js:469:11)
          at tryOnTimeout (timers.js:304:5)
          at Timer.listOnTimeout (timers.js:264:5)

    Test Suites: 1 failed, 1 total
    Tests:       1 failed, 1 total
    Snapshots:   0 total
    Time:        5.574s, estimated 6s
    Ran all test suites.

Did I miss used `jest`? Is it a `jest` bug? How can I make sure that `jest`
always correctly report error messages?
