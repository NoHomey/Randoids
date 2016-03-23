import output = require('./driver/output/output');
import input = require('./driver/input/input');

output.print(new Uint16Array([1, 3, 5, 7, 9, 2, 4, 6, 8, 0]));
var buttons: number = input.input();
console.log("Input:", buttons);