import React, { Component } from 'react';
import logo from './logo.svg';
import './App.css';

export class Foo extends Component {
    render() {
        return <p>Foo</p>;
    }
}

export class Bar extends Component {
    render() {
        return <p>Bar</p>;
    }
}

export class Content extends Component {
    constructor(props) {
        super(props);
        this.state = { bar: false };
        setTimeout(() => {
            this.setState({ bar: true });
        }, 300);
    }
    render() {
        if (this.state.bar) {
            console.log('===============> render Bar')
            return <Bar/>;
        } else {
            console.log('===============> render Foo')
            return <Foo/>;
        }
    };

};

class App extends Component {
  render() {
    return (
      <div className="App">
        <Content />
      </div>
    );
  }
}

export default App;
