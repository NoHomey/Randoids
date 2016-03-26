import Position = require('./Position');
import color = require('./Color');
declare class Pixel {
    color: color.Color;
    position: Position;
    constructor(color: color.Color, position: Position);
}
export = Pixel;
