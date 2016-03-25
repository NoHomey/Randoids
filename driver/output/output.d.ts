declare module output {
    class Output {
        constructor(chips: number, data: number, clock: number, latch: number);
        setup(): void;
        write(): void;
        setLED(led: number, pwm: number): void;
        setRGBLED(rgb:number, pwm: Uint16Array): void;
    }
}

export = output;