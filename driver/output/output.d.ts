declare module output {
    class Output {
        constructor(chips: number, data: number, clock: number, latch: number, wire: string);
        write(): void;
        setLED(led: number, pwm: number): void;
        setRGBLED(rgb:number, pwm: Uint16Array): void;
        private data_: number;
        private clock_: number;
        private latch_: number;
    }
}

export = output;