{
  "targets": [
    {
      "target_name": "output",
      "sources": [
        "output.cc",
        "Output.cc",
	"TLC5947.cc"
      ],
      "ldflags": ["-lwiringPi"],
      "cflags!": ["-fno-exceptions"],
      "cflags_cc!": ["-fno-exceptions"]
    }
  ]
}
