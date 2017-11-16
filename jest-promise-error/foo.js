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
