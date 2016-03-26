module color {
    export enum ColorName {
        Black,
        Red,
        Green,
        Yellow,
        Blue,
        Purple,
        Cyan,
        White,
    }
    
    export class Color {
        private red_: boolean;
        private green_: boolean;
        private blue_: boolean;
        private name_: ColorName;
        
        private static NumberToBoolean(num: number): boolean {
            if(num > 0) {
                return true;
            } else {
                return false;
            }
        }
        
        private static BooleanToNumber(bool: boolean): number {
            if(bool) {
                return 4095;
            } else {
                return 0;
            }
        }
        
        public set name(name: ColorName) {
            this.name_ = name;
        }
        
        public set red(red: number) {
            this.red_ = Color.NumberToBoolean(red);
        }
        
        public set green(green: number) {
            this.green_ = Color.NumberToBoolean(green);
        }
        
        public set blue(blue: number) {
            this.blue_ = Color.NumberToBoolean(blue);
        }
        
        public get name(): ColorName {
            return this.name_;
        }
        
        public get red(): number {
            return Color.BooleanToNumber(this.red_);
        }
        
        public get green(): number {
            return Color.BooleanToNumber(this.green_);
        }
        
        public get blue(): number {
            return Color.BooleanToNumber(this.blue_);
        }
        
        public constructor(name: ColorName) {
            this.red_ = Color.NumberToBoolean(name & 1);
            this.green_ = Color.NumberToBoolean(name & 2);
            this.blue_ = Color.NumberToBoolean(name & 4);
            this.name_ = name;
        }
        
        public ToUint16Array(): Uint16Array {
            return new Uint16Array([
                Color.BooleanToNumber(this.red_),
                Color.BooleanToNumber(this.green_),
                Color.BooleanToNumber(this.blue_),
            ]);
        }
    } 
}

export = color;