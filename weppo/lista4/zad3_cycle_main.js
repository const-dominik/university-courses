//code from documentation: https://nodejs.org/api/modules.html#modules_cycles

console.log('main starting');
const a = require('./zad3_cycle_a.js');
const b = require('./zad3_cycle_b.js');
console.log('in main, a.done = %j, b.done = %j', a.done, b.done);