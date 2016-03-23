declare module output {
    class Output {
        constructor(data: number, clock: number, latch: number);
        write(screen: Uint16Array): void;
        private data_: number;
        private clock_: number;
        private latch_: number;
    }
}

export = output;