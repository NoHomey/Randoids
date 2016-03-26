module color {
    export enum Color {
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Purple,
        Cyan,
        White,
    }
    
    export function ColorToUint16Array(color: Color): Uint16Array {
        var array: number[] = [];
        for(var i = 0; i < 3; ++i) {
            array[i] = (color & (1 << i)) ? 4095 : 0;
        }
        return new Uint16Array(array);
    } 
}

export = color;