declare module color {
    enum Color {
        Black = 0,
        Red = 1,
        Green = 2,
        Yellow = 3,
        Blue = 4,
        Purple = 5,
        Cyan = 6,
        White = 7,
    }
    function ColorToUint16Array(color: Color): Uint16Array;
}
export = color;
