import Position = require('./Position');
import color = require('./Color');

class Pixel {
    public color: color.Color;
    public position: Position;
    
    public constructor(color: color.Color, position: Position) {
        this.color = color;
        this.position = position;
    }   
}

export = Pixel;