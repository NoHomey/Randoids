import output = require('./driver/output/output');
import input = require('./driver/input/input');

var out: output.Output = new output.Output(2, 0, 3);
var arr: number[] = new Array<number>(192);
var val: number = 0;

setInterval(() => {
    if(val < 4096) {
        val++;
    } else {
        val = 0;
    }
    for(var i: number = 0; i < 192; ++i) {
        arr[i] = val;
    }
    out.write(new Uint16Array(arr));
}, 1000);
var buttons: number = input();
console.log("Input:", buttons);
