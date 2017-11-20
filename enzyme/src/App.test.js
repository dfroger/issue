import React from 'react';
import ReactDOM from 'react-dom';
import App, { Content, Foo, Bar } from './App';

import Adapter from 'enzyme-adapter-react-16';
import { configure } from 'enzyme';
configure({ adapter: new Adapter() });
import { mount } from 'enzyme';

it('renders without crashing', done => {
  //const div = document.createElement('div');
  //ReactDOM.render(<App />, div);

    let app = mount(
        <App />
    );

    const n = 5;
    let i = 0;

    function findFooBar() {
        try {
            const foo = app.find(Foo).length;
            const bar = app.find(Bar).length;
            console.log(`Foo: ${foo}, Bar: ${bar}`);
            i += 1;
            if (i == n) {
                clearInterval(id);
                done();
            }
        } catch(e) {
            console.log(e);
            done();
        }
    };

    const id = setInterval(findFooBar, 100);
});
