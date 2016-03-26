import Pixel = require('./Pixel');
import Position = require('./Position');

class GameObject {
    public position: Position;
    public direction: Position;
    public figure: Pixel[];
    
    public constructor(position: Position, direction: Position, figure: Pixel[]) {
        this.position = position;
        this.direction = direction;
        this.figure = figure;
    }
    
    public progress(position: Position): Pixel[] {
        return this.figure.map(pixel => {
            return new Pixel(pixel.color, pixel.position.add(position));
        });
    }
    
    public isDead(): boolean {
        return Boolean(this.figure.length);
    }
}

export = GameObject;