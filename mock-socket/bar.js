
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
