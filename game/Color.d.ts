declare module color {
    enum ColorName {
        Black = 0,
        Red = 1,
        Green = 2,
        Yellow = 3,
        Blue = 4,
        Purple = 5,
        Cyan = 6,
        White = 7,
    }
    
    class Color {
        private red_;
        private green_;
        private blue_;
        private name_;
        private static NumberToBoolean(num);
        private static BooleanToNumber(bool);
        public name: ColorName;
        public red: number;
        public green: number;
        public blue: number;
        public constructor(name: ColorName);
        public ToUint16Array(): Uint16Array;
    }
}

export = color;
