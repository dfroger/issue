const foo = require('./foo').foo;

try {
    foo(() => {});
}
catch(err) {
    console.log('plantage');
}
