function until(func, options = {}) {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            resolve(func());
        }, 100);
    });
}

function foo() {
    console.log('entering foo');
    const func = () => xxx;
    const p = until(func);
    p.then(() => {
        console.log('ok')
    })
}

exports.foo = foo;
